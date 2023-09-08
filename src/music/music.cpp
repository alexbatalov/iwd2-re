#include "music/music.h"

#include <limits.h>
#include <stdarg.h>

#include "music/audio.h"
#include "music/sectionsize.h"
#include "music/sound.h"

typedef struct JumpList {
    char name[8];
    char* fileName;
    char* list;
    char (*tag)[8];
    char (*section)[8];
    int numSections;
} JumpList;

static char* defaultNameMangler(char* name);
static void deleteSound(void* userData, int action);
static void musicShutdown();
static int musicSoundOpen(char* fname, int mode);
static int musicSoundClose(int fd);
static size_t musicSoundWrite(int fd, void* buf, size_t size);
static size_t musicSoundRead(int fd, void* buf, size_t size);
static int musicSoundSeek(int fd, long offset, int origin);
static long musicSoundTell(int fd);
static long musicSoundFilesize(int fd);

static int internalMusicPlay(int song, int section, int position);
static int setupNewSong();
static char* getSectionName(char* song, char* section);
static int openSectionFile(char* fileName);
static void freeJumpList(JumpList* jumpList, int numSongs);
static void stripCRLF(char* string);
static void stripWhitespace(char* string);
static void fixTabs(char* string);
static char* nextToken(char* string);
static int findSong(const char* name);
static int findSongSection(int song, const char* name);

// 0x8BE274
static int fadeSong = -3;

// 0x8BE278
static int nextSong = -1;

// 0x8BE27C
static int nextSection = -1;

// 0x8BE280
static int nextPosition = -1;

// 0x8BE284
static unsigned short currentMusicVolume = VOLUME_MAX;

// 0x8BE288
static MusicFileNameMangler* nameMangler = defaultNameMangler;

// 0x8BE28C
static char defaultMusicExtension[16] = "acm";

// 0xA0E1C4
static int currentSection;

// 0xA0E1C8
static int musicInited;

// 0xA0E1D0
static int dword_A0E1D0;

// 0xA0E1D4
static int enabled;

// 0xA0E1D8
static int currentSong;

// 0xA0E1DC
static int fadePosition;

// 0xA0E1E0
static int numSongs;

// 0xA0E1E4
static Sound* songSound;

// 0xA0E1E8
static JumpList* jumpList;

// 0xA0E1EC
static char* currentSectionName;

// 0xA0E1F0
static char defaultMusicPath[256];

// 0xA0E3F0
static int dword_A0E3F0;

// 0xA0E3F4
static int currentSectionFile;

// 0xA0E3F8
static char* currentSongName;

// 0xA0E3FC
static int fadeSection;

// 0xA0E400
static int gSecondSectionSize;

// 0xA0E404
static MusicDebugFunc* outputFunc;

// 0x7D1600
char* defaultNameMangler(char* name)
{
    return name;
}

// 0x07D42B0
int musicInit(MusicCompressQueryFunc* compressQuery)
{
    audioInit(compressQuery);
    musicInited = 1;
    enabled = 1;
    dword_A0E3F0 = 0;
    dword_A0E1D0 = 0x7FFF;
    currentSong = -1;
    return 0;
}

// 0x7D42F0
void deleteSound(void* userData, int action)
{
    switch (action) {
    case 1:
        *((Sound**)userData) = NULL;
        currentSongName = NULL;
        currentSectionName = NULL;
        dword_A0E1D0 = 0;
        currentSong = -1;
        break;
    case 0x4000:
        if (fadeSong >= 0) {
            // NOTE: Uninline.
            musicForceSection(fadeSong, fadeSection, fadePosition);
            soundVolume(songSound, currentMusicVolume);
        } else if (fadeSong == -1) {
            // NOTE: Uninline.
            musicForceStop();
        }
        break;
    case 0x8000:
        if (fadeSong >= 0) {
            // NOTE: Uninline.
            musicForceSection(fadeSong, fadeSection, fadePosition);
        } else if (nextSong >= 0 && nextSection >= 0 && nextPosition >= 0) {
            // NOTE: Uninline.
            musicForceSection(nextSong, nextSection, nextPosition);

            soundVolume(songSound, currentMusicVolume);

            // NOTE: Uninline.
            musicFadeIn(5000);

            nextSection = -1;
            nextPosition = -1;
        } else {
            currentSong = -1;
        }
        break;
    }

    fadeSong = -3;
}

// 0x7D4510
void musicClose()
{
    if (musicInited) {
        musicInited = 0;

        // NOTE: Uninline.
        musicShutdown();

        if (jumpList != NULL) {
            // NOTE: Uninline.
            freeJumpList(jumpList, numSongs);
            jumpList = NULL;
        }

        audioClose();
    }
}

// NOTE: Inlined in `musicClose`.
void musicShutdown()
{
    if (songSound != NULL) {
        soundDelete(songSound);
        songSound = NULL;
    }

    if (currentSectionFile != NULL) {
        audioCloseFile(currentSectionFile);
        currentSectionFile = NULL;
    }

    musicInited = 0;
}

// 0x7D45E0
int musicLoadSongList(char** list, int num)
{
    char buf[256];

    if (!musicInited) {
        return 1;
    }

    if (jumpList != NULL) {
        freeJumpList(jumpList, numSongs);
    }

    jumpList = (JumpList*)calloc(num + 1, sizeof(JumpList));
    int* v1 = (int*)malloc(sizeof(int) * num);

    currentSong = -1;
    currentSection = 0;
    nextSong = 0;
    nextPosition = -1;
    nextSection = -1;

    for (int index = 0; index < num; index++) {
        jumpList[index].fileName = strdup(list[index]);

        FILE* stream = audioOpenPtr(nameMangler(jumpList[index].fileName), "r");
        if (stream != NULL) {
            v1[index] = 1;

            do {
                buf[0] = '\0';
                audioGetStrPtr(buf, sizeof(buf) - 1, stream);

                // NOTE: Uninline.
                stripCRLF(buf);
            } while (buf[0] == '#');

            // NOTE: Uninline.
            stripWhitespace(buf);

            strncpy(jumpList[index].name, buf, 7);

            do {
                buf[0] = '\0';
                audioGetStrPtr(buf, sizeof(buf) - 1, stream);

                // NOTE: Uninline.
                stripCRLF(buf);
            } while (buf[0] == '#');

            // NOTE: Uninline.
            stripWhitespace(buf);

            jumpList[index].numSections = atoi(buf);

            if (jumpList[index].numSections != 0) {
                jumpList[index].section = (char(*)[8])malloc(8 * jumpList[index].numSections);
                jumpList[index].tag = (char(*)[8])calloc(8, jumpList[index].numSections);
            } else {
                jumpList[index].section = NULL;
                jumpList[index].tag = NULL;
            }

            for (int section = 0; section < jumpList[index].numSections; section++) {
                do {
                    buf[0] = '\0';
                    audioGetStrPtr(buf, sizeof(buf) - 1, stream);

                    // NOTE: Uninline.
                    stripCRLF(buf);
                } while (buf[0] == '#');

                if (buf[0] == '\0') {
                    break;
                }

                // NOTE: Uninline.
                fixTabs(buf);

                // NOTE: Uninline.
                nextToken(buf);

                strncpy(jumpList[index].section[section], buf, 7);
            }

            audioClosePtr(stream);
        } else {
            v1[index] = 0;
        }
    }

    for (int index = 0; index < num; index++) {
        if (v1[index] == 0) {
            if (jumpList[index].list != NULL) {
                free(jumpList[index].list);
                jumpList[index].list = NULL;
            }

            if (jumpList[index].section != NULL) {
                free(jumpList[index].section);
                jumpList[index].section = NULL;
            }

            if (jumpList[index].tag != NULL) {
                free(jumpList[index].tag);
                jumpList[index].tag = NULL;
            }
        }
    }

    numSongs = num;
    if (numSongs != 0) {
        for (int index = 0; index < num; index++) {
            FILE* stream = audioOpenPtr(nameMangler(jumpList[index].fileName), "r");
            if (stream != NULL) {
                // Skip name.
                do {
                    buf[0] = '\0';
                    audioGetStrPtr(buf, sizeof(buf) - 1, stream);

                    // NOTE: Uninline.
                    stripCRLF(buf);
                } while (buf[0] == '#');

                // Skip number of sections.
                do {
                    buf[0] = '\0';
                    audioGetStrPtr(buf, sizeof(buf) - 1, stream);

                    // NOTE: Uninline.
                    stripCRLF(buf);
                } while (buf[0] == '#');

                if (jumpList[index].numSections != 0) {
                    jumpList[index].list = (char*)malloc(numSongs * jumpList[index].numSections);

                    for (int k = 0; k < numSongs * jumpList[index].numSections; k++) {
                        jumpList[index].list[k] = -1;
                    }

                    for (int section = 0; section < jumpList[index].numSections; section++) {
                        do {
                            buf[0] = '\0';
                            audioGetStrPtr(buf, sizeof(buf) - 1, stream);

                            // NOTE: Uninline.
                            stripCRLF(buf);
                        } while (buf[0] == '#');

                        if (buf[0] == '\0') {
                            break;
                        }

                        // NOTE: Uninline.
                        fixTabs(buf);

                        // NOTE: Uninline.
                        char* token = nextToken(buf);

                        if (section == jumpList[index].numSections - 1) {
                            jumpList[index].list[section * numSongs + index] = 0;
                        } else {
                            jumpList[index].list[section * numSongs + index] = section + 1;
                        }

                        while (token != NULL) {
                            // NOTE: Uninline.
                            char* tokenValue = nextToken(token);

                            // NOTE: Uninline.
                            char* next = nextToken(tokenValue);

                            if (token[0] == '@') {
                                if (strcmpi(token + 1, "tag") == 0) {
                                    strcpy(jumpList[index].tag[section], tokenValue);

                                    if (strcmpi(tokenValue, "end") == 0) {
                                        jumpList[index].list[section * numSongs + index] = -1;
                                    }
                                }
                            } else {
                                // NOTE: Uninline.
                                int songRef = findSong(token);
                                if (songRef != -1) {
                                    if (strcmpi(token, "none") != 0 && strcmpi(token, "end") != 0) {
                                        // NOTE: Uninline.
                                        jumpList[index].list[section * numSongs + index] = findSongSection(songRef, tokenValue);
                                    } else {
                                        jumpList[index].list[section * numSongs + index] = -1;
                                    }
                                }
                            }

                            token = next;
                        }
                    }
                }

                audioClosePtr(stream);
            }
        }
    } else {
        if (jumpList != NULL) {
            free(jumpList);
            jumpList = NULL;
        }
        numSongs = 0;
    }

    if (v1 != NULL) {
        free(v1);
    }

    return 0;
}

// 0x7D5240
int musicSoundOpen(char* fname, int mode)
{
    return 0x18181818;
}

// 0x7D5250
int musicSoundClose(int fd)
{
    return 0;
}

// 0x7D5250
size_t musicSoundWrite(int fd, void* buf, size_t size)
{
    return 0;
}

// 0x7D5260
size_t musicSoundRead(int fd, void* buf, size_t size)
{
    gSecondSectionSize = 0;

    if (currentSection == -2) {
        memset(buf, 0, size);
        return size + 1;
    }

    if (currentSectionFile == 0) {
        if (jumpList[currentSong].list == NULL) {
            return 0;
        }

        // NOTE: Uninline.
        char* fileName = getSectionName(jumpList[currentSong].name, jumpList[currentSong].section[currentSection]);

        // NOTE: Uninline.
        currentSectionFile = openSectionFile(fileName);

        if (currentSectionFile == 0) {
            memset(buf, 0, size);
            return size;
        }

        currentSongName = jumpList[currentSong].name;
        currentSectionName = jumpList[currentSong].section[currentSection];
    }

    size_t bytesRead = audioRead(currentSectionFile, buf, size);
    if (bytesRead == size) {
        return bytesRead;
    }

    audioCloseFile(currentSectionFile);
    currentSectionFile = 0;

    if (jumpList[currentSong].list == NULL) {
        return bytesRead;
    }

    int v1 = 0;
    if (currentSection == -1) {
        currentSection = nextSection >= 0 ? nextSection : 0;
        currentSong = nextSong;
        v1 = 1;
    } else if (nextSong == numSongs || jumpList[currentSong].list[currentSection * numSongs + nextSong] == -1) {
        if (jumpList[currentSong].tag[currentSection][0] != '\0') {
            char* fileName = getSectionName(jumpList[currentSong].name, jumpList[currentSong].tag[currentSection]);
            if (stricmp(jumpList[currentSong].tag[currentSection], "none") == 0) {
                currentSong = nextSong;
                currentSection = 0;
            } else if (stricmp(jumpList[currentSong].tag[currentSection], "end") == 0) {
                currentSong = numSongs;
                currentSection = -2;
                memset((unsigned char*)buf + bytesRead, 0, size - bytesRead);
                return bytesRead;
            } else {
                currentSectionName = fileName;

                currentSong = nextSong;
                currentSection = -1;

                // NOTE: Uninline.
                currentSectionFile = openSectionFile(fileName);

                gSecondSectionSize = audioRead(currentSectionFile, (unsigned char*)buf + bytesRead, size - bytesRead);
                return bytesRead + gSecondSectionSize;
            }
        } else {
            currentSection = jumpList[currentSong].list[currentSection * numSongs + currentSong];
        }
    } else {
        currentSong = nextSong;
    }

    // NOTE: Uninline.
    char* fileName = getSectionName(jumpList[currentSong].name, jumpList[currentSong].section[currentSection]);

    // NOTE: Uninline.
    currentSectionFile = openSectionFile(fileName);

    currentSongName = jumpList[currentSong].name;
    currentSectionName = jumpList[currentSong].section[currentSection];

    if (v1 && nextPosition >= 0) {
        if (currentSectionFile != 0) {
            audioSeek(currentSectionFile, nextPosition - nextPosition % songSound->dataSize, 0);
        }

        memset(buf, 0, size - bytesRead);
        currentSection = -2;
        return size;
    }

    gSecondSectionSize = audioRead(currentSectionFile, (unsigned char*)buf + bytesRead, size - bytesRead);
    return bytesRead + gSecondSectionSize;
}

// 0x7D5830
int musicSoundSeek(int fd, long offset, int origin)
{
    if (currentSectionFile != NULL) {
        audioSeek(currentSectionFile, offset, 0);
    }

    return 0;
}

// 0x7D5250
long musicSoundTell(int fd)
{
    return 0;
}

// 0x7D5850
long musicSoundFilesize(int fd)
{
    return INT_MAX;
}

// 0x7D5860
void musicFade(int song, int section, int position, int fadeTime)
{
    if (songSound != NULL) {
        fadeSong = song;
        fadeSection = section;
        fadePosition = position;
        soundFadePause(songSound, fadeTime, 0);
    }
}

// 0x7D58B0
int musicSetSong(int song, int section, int position)
{
    if (!musicInited) {
        return 1;
    }

    nextSong = song;
    nextSection = section;
    nextPosition = position;

    if (song < 0) {
        nextSong = 0;
        nextSection = -1;
        nextPosition = -1;
        song = 0;
    }

    if (song > numSongs) {
        nextSong = numSongs;
        nextSection = -1;
        nextPosition = -1;
        song = numSongs;
    }

    if (songSound == NULL) {
        // NOTE: Uninline.
        internalMusicPlay(song, 0, 0);
    }

    return 0;
}

// 0x7D5A30
int musicStop()
{
    // NOTE: Uninline.
    return musicSetSong(numSongs, 0, 0);
}

// 0x7D5BB0
int musicForceStop()
{
    if (!musicInited) {
        return 1;
    }

    if (songSound == NULL) {
        return 3;
    }

    if (currentSectionFile != NULL) {
        audioCloseFile(currentSectionFile);
        currentSectionFile = 0;
    }

    fadeSong = -3;
    soundDelete(songSound);
    currentSong = -1;
    currentSection = 0;
    nextSong = 0;
    nextPosition = -1;
    nextSection = -1;
    songSound = NULL;
    musicInited = 1;
    dword_A0E1D0 = 0x7FFF;

    return 0;
}

// 0x7D5C40
int musicSetVolume(int volume)
{
    currentMusicVolume = volume;

    if (songSound != NULL) {
        soundVolume(songSound, volume);
    }

    return 0;
}

// 0x7D5C70
int musicGetSong()
{
    return currentSong;
}

// 0x7D5C80
int musicSetPath(const char* path, const char* extension)
{
    strcpy(defaultMusicPath, path);

    size_t end = strlen(defaultMusicPath) - 1;
    if (defaultMusicPath[end] != '//' && defaultMusicPath[end] != '/') {
        strcpy(&(defaultMusicPath[end + 1]), "/");
    }

    strcpy(defaultMusicExtension, extension);

    return 0;
}

// 0x7D5D00
int forceSong(int song, int section, int position)
{
    gSecondSectionSize = 0;
    fadeSong = -3;

    if (!musicInited) {
        return 1;
    }

    if (song < 0 || song >= numSongs) {
        return 5;
    }

    if (songSound == NULL) {
        // NOTE: Uninline.
        return internalMusicPlay(song, section, position);
    }

    currentSong = song;
    currentSection = section;

    nextSong = song;
    nextPosition = -1;
    nextSection = 1;

    fadeSong = -3;

    if (currentSectionFile != NULL) {
        audioCloseFile(currentSectionFile);
        currentSectionFile = 0;
    }

    // NOTE: Uninline.
    char* fileName = getSectionName(jumpList[currentSong].name, jumpList[currentSong].section[currentSection]);

    // NOTE: Uninline.
    currentSectionFile = openSectionFile(fileName);

    if (currentSectionFile == NULL) {
        return 0;
    }

    currentSongName = jumpList[currentSong].name;
    currentSectionName = jumpList[currentSong].section[currentSection];

    // NOTE: Uninline.
    return internalMusicPlay(song, section, position);
}

// 0x7D60E0
int musicForceSection(int song, int section, int position)
{
    return forceSong(song, section, position);
}

// 0x7D6100
int musicGetSection()
{
    return currentSection;
}

// 0x7D6110
int musicGetSectionPlaying()
{
    if (songSound == NULL) {
        return -1;
    }

    int pos = soundGetDirectSoundBufferPosition(songSound);
    return sectionsizeGetSection(songSound->sectionsizes, pos);
}

// 0x7D6140
int musicGetSongPlaying()
{
    if (songSound == NULL) {
        return -1;
    }

    int pos = soundGetDirectSoundBufferPosition(songSound);
    return sectionsizeGetSong(songSound->sectionsizes, pos);
}

// 0x7D6170
int musicGetPosition()
{
    if (songSound == NULL) {
        return -1;
    }

    int pos = soundGetDirectSoundBufferPosition(songSound);
    return sectionsizeGetSectionOffset(songSound->sectionsizes, pos);
}

// 0x7D61A0
void musicFadeIn(int t)
{
    if (songSound == NULL) {
        return;
    }

    soundVolume(songSound, 0);
    soundFadeContinue(songSound, t, currentMusicVolume);
    fadeSong = -2;
}

// 0x7D61E0
int musicGetSecondSectionSize()
{
    return gSecondSectionSize;
}

// 0x7D61F0
void musicDebug(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[512];
    vsprintf(buffer, format, args);

    if (outputFunc != NULL) {
        outputFunc(buffer);
    }

    va_end(args);
}

// 0x7D6230
void musicSetDebugFunc(MusicDebugFunc* func)
{
    outputFunc = func;
}

// NOTE: Inlined.
int internalMusicPlay(int song, int section, int position)
{
    gSecondSectionSize = 0;

    // NOTE: Uninline.
    int rc = setupNewSong();
    if (rc != 0) {
        return rc;
    }

    nextSong = song;

    currentSong = song;
    currentSection = section;

    if (soundLoad(songSound, "empty") == SOUND_NO_ERROR) {
        soundVolume(songSound, currentMusicVolume);
        soundPlayFromPosition(songSound, position);
    } else {
        soundDelete(songSound);
    }

    return 0;
}

// NOTE: Inlined.
int setupNewSong()
{
    if (!musicInited) {
        return 1;
    }

    if (jumpList == NULL) {
        return 2;
    }

    if (!enabled) {
        return 5;
    }

    songSound = soundAllocate(SOUND_TYPE_STREAMING | SOUND_TYPE_FIRE_AND_FORGET | SOUND_TYPE_0x20, SOUND_16BIT | SOUND_CTRL_VOLUME);
    if (songSound == NULL) {
        return 5;
    }

    soundSetChannel(songSound, 3);
    soundSetBuffers(songSound, 8, 0x8000);
    soundSetFileIO(songSound,
        musicSoundOpen,
        musicSoundClose,
        musicSoundRead,
        musicSoundWrite,
        musicSoundSeek,
        musicSoundTell,
        musicSoundFilesize);
    soundSetCallback(songSound, deleteSound, &songSound);

    return 0;
}

// NOTE: Inlined.
char* getSectionName(char* song, char* section)
{
    // 0xA0E2F0
    static char buf[256];

    if (section != NULL) {
        if (strnicmp(section, "SPC", 3) == 0) {
            sprintf(buf,
                "%s%s.%s",
                defaultMusicPath,
                section,
                defaultMusicExtension);
        } else if (strnicmp(section, "MX0000A", 7) == 0) {
            sprintf(buf,
                "%sMX0000/MX0000A.ACM",
                defaultMusicPath);
        } else {
            sprintf(buf,
                "%s%s/%s%s.%s",
                defaultMusicPath,
                song,
                song,
                section,
                defaultMusicExtension);
        }
    }

    return buf;
}

// NOTE: Inlined.
int openSectionFile(char* fileName)
{
    if (fileName == NULL) {
        musicDebug("NULL filename passed to openSectionFile()\n");
        return 0;
    }

    int fd = audioOpen(nameMangler(fileName), 0x8000);
    if (fd == -1) {
        return 0;
    }

    return fd;
}

// NOTE: Inlined.
void freeJumpList(JumpList* jumpList, int numSongs)
{
    if (jumpList == NULL) {
        return;
    }

    for (int index = 0; index < numSongs; index++) {
        if (jumpList[index].list != NULL) {
            free(jumpList[index].list);
            jumpList[index].list = NULL;
        }

        if (jumpList[index].section != NULL) {
            free(jumpList[index].section);
            jumpList[index].section = NULL;
        }

        if (jumpList[index].tag != NULL) {
            free(jumpList[index].tag);
            jumpList[index].tag = NULL;
        }

        if (jumpList[index].fileName != NULL) {
            free(jumpList[index].fileName);
            jumpList[index].fileName = NULL;
        }
    }

    free(jumpList);
}

// NOTE: Inlined.
void stripCRLF(char* string)
{
    char* pch;

    pch = strchr(string, '\n');
    if (pch != NULL) {
        *pch = '\0';
    }

    pch = strchr(string, '\r');
    if (pch != NULL) {
        *pch = '\0';
    }

    pch = string;
    while (isspace(*pch)) {
        pch++;
    }

    if (pch != string) {
        strcpy(string, pch);
    }
}

// NOTE: Inlined.
void stripWhitespace(char* string)
{
    char* temp = (char*)malloc(256);
    if (temp != NULL) {
        temp[0] = '\0';

        char* dest = temp;
        for (int index = 0; index < 256; index++) {
            if (string[index] != '\t' && string[index] != ' ') {
                *dest++ = string[index];
            }
        }

        memcpy(string, temp, 256);
        free(temp);
    }
}

// NOTE: Inlined.
void fixTabs(char* string)
{
    for (int index = 0; index < 256; index++) {
        if (string[index] == '\n' || string[index] == '\0') {
            break;
        }

        if (string[index] == '\t') {
            string[index] = ' ';
        }
    }
}

// NOTE: Inlined.
char* nextToken(char* string)
{
    if (string == NULL) {
        return NULL;
    }

    char* pch = strchr(string, ' ');
    if (pch == NULL) {
        return NULL;
    }

    *pch = '\0';

    do {
        pch++;
    } while (*pch == ' ');

    if (*pch == '\0') {
        return NULL;
    }

    return pch;
}

// NOTE: Inlined.
int findSong(const char* name)
{
    for (int index = 0; index < numSongs; index++) {
        if (strcmpi(jumpList[index].name, name) == 0) {
            return index;
        }
    }

    return -1;
}

// NOTE: Inlined.
int findSongSection(int song, const char* name)
{
    for (int index = 0; index < jumpList[song].numSections; index++) {
        if (strcmpi(jumpList[song].section[index], name) == 0) {
            return index;
        }
    }

    return -1;
}
