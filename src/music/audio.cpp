#include "music/audio.h"

#include <string.h>

#include "music/adecode.h"
#include "music/sound.h"

typedef enum AudioStreamFlags {
    AUDIO_STREAM_IN_USE = 0x1,
    AUDIO_STREAM_COMPRESSED = 0x2,
} AudioStreamFlags;

typedef struct AudioStream {
    /* 0000 */ int flags;
    /* 0004 */ FILE* file;
    /* 0008 */ AudioDecoder* decoder;
    /* 000C */ int preReadPos;
    /* 0010 */ int preReadSize;
    /* 0014 */ unsigned char* preReadBuf;
    /* 0018 */ int filesize;
    /* 001C */ int sampleRate;
    /* 0020 */ int channels;
    /* 0024 */ int currentPos;
} AudioStream;

static int audio_fclose(FILE* stream);
static FILE* audio_fopen(const char* fname, const char* mode);
static int audio_fseek(FILE* stream, long offset, int origin);
static size_t audio_fread(void* buf, size_t size, size_t count, FILE* stream);
static char* audio_fgets(char* buf, int maxCount, FILE* stream);
static int defaultCompressionFunc(char* fname);
static int decodeRead(void* data, void* buf, int size);
static long getLong(FILE* stream);
static int fileLength(FILE* stream);

// 0xA16430
static AudioStream* audio;

// 0xA16434
static int numAudio;

// 0x8BE3BC
AudioOpenFunc* audioOpenPtr = audio_fopen;

// 0x8BE3C0
AudioCloseFunc* audioClosePtr = audio_fclose;

// 0x8BE3C4
AudioReadFunc* audioReadPtr = audio_fread;

// 0x8BE3C8
AudioSeekFunc* audioSeekPtr = audio_fseek;

// 0x8BE3CC
AudioGetStrFunc* audioGetStrPtr = audio_fgets;

// 0x8BE3D0
static AudioCompressQueryFunc* queryCompressedFunc = defaultCompressionFunc;

// 0xA0E420
static FILE* dword_A0E420;

// 0xA0E424
static unsigned char byte_A0E424[0x8000];

// 0xA16424
static int dword_A16424;

// 0xA16428
static int dword_A16428;

// 0xA1642C
static int dword_A1642C;

// 0x7D9570
int audio_fclose(FILE* stream)
{
    if (dword_A0E420 != stream) {
        return fclose(stream);
    }

    int rc = fclose(stream);
    dword_A0E420 = NULL;
    return rc;
}

// 0x7D95A0
FILE* audio_fopen(const char* fname, const char* mode)
{
    if (dword_A0E420 != NULL) {
        return fopen(fname, mode);
    }

    FILE* stream = fopen(fname, mode);
    if (stream == NULL) {
        return NULL;
    }

    dword_A0E420 = stream;
    memset(byte_A0E424, 0, sizeof(byte_A0E424));
    dword_A16424 = 0;
    dword_A16428 = 0;
    dword_A1642C &= ~0x1;

    return stream;
}

// 0x7D9610
size_t audio_fread(void* buf, size_t size, size_t count, FILE* stream)
{
    if (dword_A0E420 != stream) {
        return fread(buf, size, count, stream);
    }

    int bytesRead = 0;
    int offset = 0;
    int remainder = size * count;
    while (remainder > 0) {
        if (dword_A16428 >= dword_A16424) {
            if ((dword_A1642C & 0x1) != 0) {
                break;
            }

            dword_A16424 = fread(byte_A0E424, 1, 0x8000, dword_A0E420);
            dword_A16428 = 0;
            if (dword_A16424 < 0x8000) {
                dword_A1642C |= 0x1;
            }
        }

        int chunkSize = dword_A16424 - dword_A16428;
        if (chunkSize >= remainder) {
            memcpy((unsigned char*)buf + offset, &(byte_A0E424[dword_A16428]), remainder);
            dword_A16428 += remainder;
            bytesRead += remainder;
            break;
        }

        remainder -= chunkSize;

        memcpy((unsigned char*)buf + offset, &(byte_A0E424[dword_A16428]), chunkSize);
        offset += chunkSize;
        dword_A16428 += chunkSize;
        bytesRead += chunkSize;
    }

    // FIXME: This is slighty incorrect as `fread` is supposed to return number
    // of elements read, not bytes.
    return bytesRead;
}

// 0x7D9730
int audio_fseek(FILE* stream, long offset, int origin)
{
    if (dword_A0E420 != stream) {
        return fseek(stream, offset, origin);
    }

    int rc = fseek(stream, offset, origin);
    dword_A16428 = 0;
    dword_A16424 = 0;
    dword_A1642C &= ~0x1;
    return rc;
}

// 0x7D9790
char* audio_fgets(char* buf, int maxCount, FILE* stream)
{
    if (dword_A0E420 != stream) {
        return fgets(buf, maxCount, stream);
    }

    char* pch = buf;
    for (int index = 1; index < maxCount; index++) {
        if (dword_A16428 >= dword_A16424) {
            if ((dword_A1642C & 1) != 0) {
                break;
            }

            dword_A16424 = fread(byte_A0E424, 1, sizeof(byte_A0E424), dword_A0E420);
            dword_A16428 = 0;

            if (dword_A16424 < sizeof(byte_A0E424)) {
                dword_A1642C |= 0x1;
            }
        }

        if (dword_A16424 - dword_A16428 > 0) {
            *pch++ = byte_A0E424[dword_A16428++];

            if (pch[-1] == '\n') {
                break;
            }
        }
    }

    *pch = '\0';
    return buf;
}

int defaultCompressionFunc(char* fname)
{
    char* extension = strrchr(fname, '.');
    if (extension != NULL) {
        strcpy(extension + 1, "raw");
    }
    return 0;
}

// 0x7D9870
int audioOpen(char* fname, int mode)
{
    int compression = queryCompressedFunc(fname) != 0 ? 2 : 0;

    char modeStr[4] = { 0 };
    char* pm = modeStr;

    if ((mode & 0x1) != 0) {
        *pm++ = 'w';
    } else if ((mode & 0x2) != 0) {
        *pm++ = 'w';
        *pm++ = '+';
    } else {
        *pm++ = 'r';
    }

    if ((mode & 0x4000) != 0) {
        *pm++ = 't';
    } else if ((mode & 0x8000) != 0) {
        *pm++ = 'b';
    }

    FILE* stream = audioOpenPtr(fname, modeStr);
    if (stream == NULL) {
        return -1;
    }

    int index;
    for (index = 0; index < numAudio; index++) {
        if ((audio[index].flags & AUDIO_STREAM_IN_USE) == 0) {
            break;
        }
    }

    if (index == numAudio) {
        if (audio != NULL) {
            audio = (AudioStream*)realloc(audio, sizeof(AudioStream) * (numAudio + 1));
        } else {
            audio = (AudioStream*)malloc(sizeof(AudioStream));
        }
        numAudio++;
    }

    AudioStream* audioStream = &(audio[index]);
    audioStream->file = stream;
    audioStream->flags = AUDIO_STREAM_IN_USE;

    if (compression == 2) {
        int type = getLong(audioStream->file);
        if (type == 'SFAD') {
            int preReadSize = getLong(audioStream->file);
            audioStream->preReadBuf = (unsigned char*)malloc(preReadSize);
            audioStream->preReadSize = preReadSize;
            audioStream->preReadPos = 0;
            audioReadPtr(audioStream->preReadBuf, 1, preReadSize, audioStream->file);
        } else {
            audioStream->preReadBuf = NULL;
            audioStream->preReadSize = 0;
            audioStream->preReadPos = 0;
            audioSeekPtr(audioStream->file, 0, SEEK_SET);
        }

        audioStream->flags |= AUDIO_STREAM_COMPRESSED;
        audioStream->decoder = Create_AudioDecoder(decodeRead,
            audioStream->file,
            &(audioStream->channels),
            &(audioStream->sampleRate),
            &(audioStream->filesize));
    } else {
        audioStream->filesize = fileLength(audioStream->file);
    }

    audioStream->currentPos = 0;

    return index + 1;
}

// 0x7D9B60
int decodeRead(void* data, void* buf, int size)
{
    return audioReadPtr(buf, 1, size, (FILE*)data);
}

// 0x7D9B80
int audioCloseFile(int fd)
{
    EnterCriticalSection(&soundCritSect);

    AudioStream* audioStream = &(audio[fd - 1]);
    audioClosePtr(audioStream->file);

    if ((audioStream->flags & AUDIO_STREAM_COMPRESSED) != 0) {
        AudioDecoder_Close(audioStream->decoder);

        if (audioStream->preReadBuf != NULL) {
            free(audioStream->preReadBuf);
            audioStream->preReadBuf = NULL;
        }
    }

    memset(audioStream, 0, sizeof(AudioStream));

    LeaveCriticalSection(&soundCritSect);
    return 0;
}

// 0x7D9C10
size_t audioRead(int fd, void* buf, size_t size)
{
    EnterCriticalSection(&soundCritSect);

    AudioStream* audioStream = &(audio[fd - 1]);

    size_t bytesRead;
    if ((audioStream->flags & AUDIO_STREAM_COMPRESSED) == 0) {
        bytesRead = audioReadPtr(buf, 1, size, audioStream->file);
    } else {
        bytesRead = AudioDecoder_Read(audio->decoder, buf, size);
        if (audioStream->preReadPos != audioStream->preReadSize) {
            size_t bytesToCopy = audioStream->preReadSize - audioStream->preReadPos;
            if (bytesToCopy > size) {
                bytesToCopy = size;
            }

            memcpy(buf, audioStream->preReadBuf, bytesToCopy);
            audioStream->preReadPos += bytesToCopy;
        }
    }

    audioStream->currentPos += bytesRead;

    LeaveCriticalSection(&soundCritSect);
    return bytesRead;
}

// 0x7ABB90
size_t audioWrite(int fd, void* buf, size_t size)
{
    return 0;
}

// 0x7D9CF0
int audioSeek(int fd, long offset, int origin)
{
    EnterCriticalSection(&soundCritSect);

    AudioStream* audioStream = &(audio[fd - 1]);

    long pos;
    switch (origin) {
    case SEEK_SET:
        pos = offset;
        break;
    case SEEK_CUR:
        pos = offset + audioStream->currentPos;
        break;
    case SEEK_END:
        pos = offset + audioStream->filesize;
        break;
    }

    int rc;
    if ((audioStream->flags & AUDIO_STREAM_COMPRESSED) != 0) {
        if (pos > audioStream->currentPos) {
            void* buffer = malloc(1024);
            pos -= audioStream->currentPos;
            while (pos > 1024) {
                pos -= 1024;
                audioRead(fd, buffer, 1024);
            }

            if (pos != 0) {
                audioRead(fd, buffer, pos);
            }

            free(buffer);
        } else {
            AudioDecoder_Close(audioStream->decoder);
            audioSeekPtr(audioStream->file, 0, SEEK_SET);

            int type = getLong(audioStream->file);
            if (type == 'SFAD') {
                int preReadSize = getLong(audioStream->file);
                if (audioStream->preReadBuf == NULL) {
                    audioStream->preReadBuf = (unsigned char*)malloc(preReadSize);
                }
                audioStream->preReadSize = preReadSize;
                audioStream->preReadPos = 0;
                audioReadPtr(audioStream->preReadBuf, 1, preReadSize, audioStream->file);
            } else {
                if (audioStream->preReadBuf != NULL) {
                    free(audioStream->preReadBuf);
                }
                audioStream->preReadBuf = NULL;
                audioStream->preReadSize = 0;
                audioStream->preReadPos = 0;
                audioSeekPtr(audioStream->file, 0, SEEK_SET);
            }

            audioStream->decoder = Create_AudioDecoder(decodeRead,
                audioStream->file,
                &(audioStream->channels),
                &(audioStream->sampleRate),
                &(audioStream->filesize));
            audioStream->filesize *= 2;
            audioStream->currentPos = 0;

            if (pos != 0) {
                void* buffer = malloc(4096);
                while (pos > 4096) {
                    pos -= 4096;
                    audioRead(fd, buffer, 4096);
                }

                if (pos != 0) {
                    audioRead(fd, buffer, pos);
                }

                free(buffer);
            }
        }

        rc = audioStream->currentPos;
    } else {
        rc = audioSeekPtr(audioStream->file, offset, origin);
    }

    LeaveCriticalSection(&soundCritSect);
    return rc;
}

// 0x7DA000
long audioFileSize(int fd)
{
    return audio[fd - 1].filesize;
}

// 0x7DA020
long audioTell(int fd)
{
    return audio[fd - 1].currentPos;
}

// 0x7DA040
void audioInit(AudioCompressQueryFunc* compressQuery)
{
    audio = NULL;
    numAudio = 0;

    if (compressQuery != NULL) {
        queryCompressedFunc = compressQuery;
    }

    soundSetDefaultFileIO(audioOpen,
        audioCloseFile,
        audioRead,
        audioWrite,
        audioSeek,
        audioTell,
        audioFileSize);

    dword_A0E420 = NULL;
}

// 0x7DA0A0
void audioClose()
{
    if (audio != NULL) {
        free(audio);
    }

    audio = NULL;
    numAudio = 0;
}

// NOTE: Inlined in `audioOpen`.
long getLong(FILE* stream)
{
    unsigned char c[4];
    audioReadPtr(c, 1, 4, stream);
    return c[3] | (c[2] << 8) | (c[1] << 16) | (c[0] << 24);
}

// NOTE: Inlined in `audioOpen`.
int fileLength(FILE* stream)
{
    long pos = audioSeekPtr(stream, 0, SEEK_CUR);
    long size = audioSeekPtr(stream, 0, SEEK_END);
    audioSeekPtr(stream, pos, SEEK_SET);
    return size;
}
