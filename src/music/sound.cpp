#include "music/sound.h"

#include <io.h>
#include <math.h>
#include <stdlib.h>

#include "music/music.h"
#include "music/sectionsize.h"

typedef struct FadeSound {
    Sound* sound;
    int deltaVolume;
    int targetVolume;
    int initialVolume;
    int currentVolume;
    int pause;
    struct FadeSound* prev;
    struct FadeSound* next;
} FadeSound;

static void* defaultMalloc(size_t size);
static void* defaultRealloc(void* ptr, size_t size);
static void defaultFree(void* ptr);
static long soundFileSize(int fd);
static long soundTellData(int fd);
static size_t soundWriteData(int fd, void* buf, size_t size);
static size_t soundReadData(int fd, void* buf, size_t size);
static int soundOpenData(char* fname, int mode);
static int soundSeekData(int fd, long offset, int origin);
static int soundCloseData(int fd);
static char* defaultMangler(char* name);
static void soundMgrClose();
static int preloadBuffers(Sound* sound);
static void refreshSoundBuffers(Sound* sound);
static int soundVolumeHMItoDirectSound(int volume);
static void removeFadeSound(FadeSound* fadeSound);
static void soundRemoveFadingSound(Sound* sound);
static int internalSoundFade(Sound* sound, int millis, int end, int pause);
static void CALLBACK doTimerEvent(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

static int soundSetMasterVolume(int volume);
static void removeTimedEvent(unsigned int* timerId);
static int soundPause(Sound* sound);
static int soundSetData(Sound* sound, unsigned char* data, int size);
static int addSoundData(Sound* sound, unsigned char* data, int size);

// 0x8BDE30
static UINT fadeEventHandle = -1;

// 08BDE38
static SoundMallocFunc* mallocPtr = defaultMalloc;

// 0x8BDE3C
static SoundReallocFunc* reallocPtr = defaultRealloc;

// 0x8BDE40
static SoundFreeFunc* freePtr = defaultFree;

// 0x8BDE48
static SoundStream defaultStream = {
    soundOpenData,
    soundCloseData,
    soundReadData,
    soundWriteData,
    soundSeekData,
    soundTellData,
    soundFileSize,
    -1,
};

// 0x8BDE68
static SoundFileNameMangler* nameMangler = defaultMangler;

// 0x8BDE6C
static const char* errorMsgs[SOUND_ERR_COUNT] = {
    "sound.c: No error",
    "sound.c: SOS driver not loaded",
    "sound.c: SOS invalid pointer",
    "sound.c: SOS detect initialized",
    "sound.c: SOS fail on file open",
    "sound.c: SOS memory fail",
    "sound.c: SOS invalid driver ID",
    "sound.c: SOS no driver found",
    "sound.c: SOS detection failure",
    "sound.c: SOS driver loaded",
    "sound.c: SOS invalid handle",
    "sound.c: SOS no handles",
    "sound.c: SOS paused",
    "sound.c: SOS not paused",
    "sound.c: SOS invalid data",
    "sound.c: SOS drv file fail",
    "sound.c: SOS invalid port",
    "sound.c: SOS invalid IRQ",
    "sound.c: SOS invalid DMA",
    "sound.c: SOS invalid DMA IRQ",
    "sound.c: no device",
    "sound.c: not initialized",
    "sound.c: no sound",
    "sound.c: function not supported",
    "sound.c: no buffers available",
    "sound.c: file not found",
    "sound.c: already playing",
    "sound.c: not playing",
    "sound.c: already paused",
    "sound.c: not paused",
    "sound.c: invalid handle",
    "sound.c: no memory available",
    "sound.c: unknown error",
};

// 0xA0E18C
static Sound* soundMgrList;

// 0xA0E190
static int dataSize;

// 0xA0E194
static int driverInit;

// 0xA0E198
static int dword_A0E198;

// 0xA0E19C
static int sampleRate;

// 0xA0E1A0
static int soundErrorno;

// 0xA0E1A4
static int deviceInit;

// 0xA0E1A8
static int numBuffers;

// 0xA0E1AC
static int numSounds;

// 0xA0E1B0
static int masterVol;

// 0xA0E1B4
FadeSound* fadeHead;

// 0xA0E1B8
FadeSound* fadeFreeList;

// 0xA0E1BC
static int unowned;

// 0xA19160
CRITICAL_SECTION soundCritSect;

// 0xA19178
static LPDIRECTSOUND directSound;

// 0xA1917C
static LPDIRECTSOUNDBUFFER primarySoundBuffer;

// 0x7D14F0
void* defaultMalloc(size_t size)
{
    return malloc(size);
}

// 0x7D1500
void* defaultRealloc(void* ptr, size_t size)
{
    return realloc(ptr, size);
}

// 0x7D1520
void defaultFree(void* ptr)
{
    free(ptr);
}

// 0x7D1530
long soundFileSize(int fd)
{
    long pos = tell(fd);
    long size = lseek(fd, 0, SEEK_END);
    lseek(fd, pos, SEEK_SET);
    return size;
}

// 0x7D1560
long soundTellData(int fd)
{
    return tell(fd);
}

// 0x7D1570
size_t soundWriteData(int fd, void* buf, size_t size)
{
    return write(fd, buf, size);
}

// 0x7D1590
size_t soundReadData(int fd, void* buf, size_t size)
{
    return read(fd, buf, size);
}

// 0x7D15B0
int soundOpenData(char* fname, int mode)
{
    return open(fname, mode);
}

// 0x7D15D0
int soundSeekData(int fd, long offset, int origin)
{
    return lseek(fd, offset, origin);
}

// 0x7D15F0
int soundCloseData(int fd)
{
    return close(fd);
}

// 0x7D1600
char* defaultMangler(char* name)
{
    return name;
}

// 0x7D1610
int soundInit(HWND wnd, LPDIRECTSOUND ds, int num, int size, int rate)
{
    dataSize = size;
    sampleRate = rate;
    driverInit = 1;
    deviceInit = 1;
    numBuffers = num;

    if (ds == NULL) {
        unowned = 0;
        if (DirectSoundCreate(NULL, &directSound, NULL) != DS_OK) {
            directSound = NULL;
            soundErrorno = SOUND_SOS_DETECTION_FAILURE;
            return soundErrorno;
        }

        if (IDirectSound_SetCooperativeLevel(directSound, wnd, DSSCL_EXCLUSIVE) != DS_OK) {
            IDirectSound_Release(directSound);

            soundErrorno = SOUND_UNKNOWN_ERROR;
            return soundErrorno;
        }

        DSBUFFERDESC dsbd;
        dsbd.dwSize = sizeof(dsbd);
        dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
        dsbd.dwReserved = NULL;
        dsbd.dwBufferBytes = NULL;
        dsbd.lpwfxFormat = NULL;
        if (IDirectSound_CreateSoundBuffer(directSound, &dsbd, &primarySoundBuffer, NULL) != DS_OK) {
            // FIXME: Leaks `directSound`.
            soundErrorno = SOUND_UNKNOWN_ERROR;
            return soundErrorno;
        }

        WAVEFORMATEX waveFormat = { 0 };

        DSCAPS caps = { 0 };
        caps.dwSize = sizeof(caps);
        if (IDirectSound_GetCaps(directSound, &caps) == DS_OK) {
            waveFormat.wFormatTag = WAVE_FORMAT_PCM;
            waveFormat.wBitsPerSample = (caps.dwFlags & DSCAPS_PRIMARY16BIT) != 0 ? 16 : 8;
            waveFormat.cbSize = 0;
            waveFormat.nChannels = (caps.dwFlags & DSCAPS_PRIMARYSTEREO) != 0 ? 2 : 1;
            waveFormat.nSamplesPerSec = rate;
            waveFormat.nBlockAlign = waveFormat.wBitsPerSample * waveFormat.nChannels / 8;
            waveFormat.nAvgBytesPerSec = rate * waveFormat.nBlockAlign;

            if (IDirectSoundBuffer_SetFormat(primarySoundBuffer, &waveFormat) != DS_OK) {
                // FIXME: Leaks `directSound`.
                // FIXME: Leaks `primarySoundBuffer`.
                soundErrorno = SOUND_UNKNOWN_ERROR;
                return soundErrorno;
            }
        }
    } else {
        unowned = 1;
        directSound = ds;
    }

    InitializeCriticalSection(&soundCritSect);

    // NOTE: Uninline.
    soundSetMasterVolume(VOLUME_MAX);

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// NOTE: Inlined.
void soundMgrClose()
{
    while (soundMgrList != NULL) {
        Sound* next = soundMgrList->next;
        // NOTE: Uninline.
        soundDelete(soundMgrList);
        soundMgrList = next;
    }
}

// 0x7D1970
int soundClose()
{
    EnterCriticalSection(&soundCritSect);

    // NOTE: Uninline.
    soundMgrClose();

    // NOTE: Uninline
    removeTimedEvent(&fadeEventHandle);

    while (fadeFreeList != NULL) {
        FadeSound* next = fadeFreeList->next;
        freePtr(fadeFreeList);
        fadeFreeList = next;
    }

    if (!unowned) {
        if (primarySoundBuffer != NULL) {
            IDirectSoundBuffer_Release(primarySoundBuffer);
            primarySoundBuffer = NULL;
        }

        if (directSound != NULL) {
            IDirectSound_Release(directSound);
            directSound = NULL;
        }
    }

    driverInit = 0;

    LeaveCriticalSection(&soundCritSect);
    DeleteCriticalSection(&soundCritSect);

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D1BF0
Sound* soundAllocate(int type, int soundFlags)
{
    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return NULL;
    }

    Sound* sound = (Sound*)mallocPtr(sizeof(Sound));
    memset(sound, 0, sizeof(Sound));
    memcpy(&(sound->io), &defaultStream, sizeof(SoundStream));

    WAVEFORMATEX* waveFormat = (WAVEFORMATEX*)mallocPtr(sizeof(WAVEFORMATEX));
    memset(waveFormat, 0, sizeof(WAVEFORMATEX));

    waveFormat->wFormatTag = WAVE_FORMAT_PCM;
    waveFormat->nChannels = 1;

    if ((soundFlags & SOUND_16BIT) != 0) {
        waveFormat->wBitsPerSample = 16;
    } else {
        waveFormat->wBitsPerSample = 8;
    }

    if ((soundFlags & SOUND_CTRL_VOLUME) == 0) {
        soundFlags |= SOUND_CTRL_VOLUME;
    }

    waveFormat->nSamplesPerSec = sampleRate;
    waveFormat->nBlockAlign = waveFormat->wBitsPerSample / 8;
    waveFormat->nAvgBytesPerSec = waveFormat->nSamplesPerSec * waveFormat->nBlockAlign;

    sound->numBytesRead = 0;
    sound->field_6C = 0;
    sound->soundBuffer = NULL;
    sound->soundFlags = soundFlags;
    sound->type = type;
    sound->statusFlags = 0;
    sound->bufferDesc.dwSize = sizeof(DSBUFFERDESC);
    sound->dataSize = dataSize;
    sound->numBuffers = numBuffers;
    sound->readLimit = sound->dataSize * sound->numBuffers;

    if ((soundFlags & SOUND_CTRL_VOLUME) != 0) {
        sound->sectionsizes = sectionsizeCreate();
    } else {
        sound->sectionsizes = NULL;
    }
    sectionsizeClear(sound->sectionsizes);

    sound->bufferDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2;

    if ((soundFlags & SOUND_CTRL_VOLUME) != 0) {
        sound->bufferDesc.dwFlags |= DSBCAPS_CTRLVOLUME;
    }

    if ((soundFlags & SOUND_CTRL_PAN) != 0) {
        sound->bufferDesc.dwFlags |= DSBCAPS_CTRLPAN;
    }

    if ((soundFlags & SOUND_CTRL_FREQUENCY) != 0) {
        sound->bufferDesc.dwFlags |= DSBCAPS_CTRLFREQUENCY;
    }

    sound->bufferDesc.lpwfxFormat = waveFormat;

    if ((type & SOUND_TYPE_INFINITE) != 0) {
        sound->loops = -1;
        sound->soundFlags |= SOUND_LOOPING;
    } else {
        sound->loops = 0;
    }

    sound->field_54 = 0;
    sound->field_58 = -1;
    sound->field_5C = 1;
    sound->volume = VOLUME_MAX;
    sound->deleted = 0;

    EnterCriticalSection(&soundCritSect);
    sound->prev = NULL;
    sound->next = soundMgrList;

    if (soundMgrList != NULL) {
        soundMgrList->prev = sound;
    }

    soundMgrList = sound;
    LeaveCriticalSection(&soundCritSect);

    return sound;
}

// 0x7D1DC0
int soundSetBuffers(Sound* sound, int numBuffers, int bufferSize)
{
    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    // FIXME: Meaningless.
    if (sound->dataSize * sound->numBuffers == sound->readLimit) {
        sound->readLimit = sound->dataSize * sound->numBuffers;
    }

    sound->numBuffers = numBuffers;
    sound->dataSize = bufferSize;

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D1E30
int soundLoad(Sound* sound, char* fname)
{
    EnterCriticalSection(&soundCritSect);

    if (!driverInit) {
        LeaveCriticalSection(&soundCritSect);

        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->deleted) {
        LeaveCriticalSection(&soundCritSect);

        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    sound->io.fd = sound->io.open(nameMangler(fname), 0x8000);
    if (sound->io.fd == -1) {
        LeaveCriticalSection(&soundCritSect);

        soundErrorno = SOUND_FILE_NOT_FOUND;
        return soundErrorno;
    }

    int rc = preloadBuffers(sound);

    LeaveCriticalSection(&soundCritSect);
    return rc;
}

// 0x7D1EE0
int preloadBuffers(Sound* sound)
{
    if (sound->deleted) {
        return SOUND_NO_SOUND;
    }

    int section = musicGetSection();
    int song = musicGetSong();
    int size = sound->io.filesize(sound->io.fd);
    sound->fileSize = size;

    if ((sound->type & SOUND_TYPE_STREAMING) != 0) {
        if ((sound->soundFlags & SOUND_LOOPING) == 0) {
            sound->soundFlags |= SOUND_FLAG_0x100 | SOUND_LOOPING;
        }

        if (size <= sound->dataSize * sound->numBuffers) {
            if (sound->dataSize * (size / sound->dataSize) != size) {
                size = sound->dataSize * (size / sound->dataSize + 1);
            }
        } else {
            size = sound->dataSize * sound->numBuffers;
        }
    } else {
        sound->type &= ~SOUND_TYPE_STREAMING;
        sound->type |= SOUND_TYPE_MEMORY;
    }

    unsigned char* data = (unsigned char*)mallocPtr(size);
    int bytesRead = sound->io.read(sound->io.fd, data, size);
    if (bytesRead != size) {
        if ((sound->soundFlags & SOUND_LOOPING) != 0
            && (sound->soundFlags & SOUND_FLAG_0x100) == 0) {
            unsigned char* chunk = data + bytesRead;
            int remaining = bytesRead;
            while (size - remaining > bytesRead) {
                memcpy(chunk, data, bytesRead);
                remaining += bytesRead;
                chunk += bytesRead;
            }

            if (remaining < size) {
                memcpy(chunk, data, size - remaining);
            }
        } else {
            memset(data + bytesRead, 0, size - bytesRead);
        }
    }

    sectionsizeAdd(sound->sectionsizes, song, section, 0, bytesRead - musicGetSecondSectionSize(), 0);

    if (musicGetSecondSectionSize() > 0) {
        sectionsizeAdd(sound->sectionsizes,
            musicGetSong(),
            musicGetSection(),
            bytesRead - musicGetSecondSectionSize(),
            musicGetSecondSectionSize(),
            0);
        sound->field_6C = musicGetSecondSectionSize();
    }

    int rc = soundSetData(sound, data, size);
    freePtr(data);

    if ((sound->type & SOUND_TYPE_MEMORY) != 0) {
        sound->io.close(sound->io.fd);
        sound->io.fd = -1;
    } else {
        if (sound->data == NULL) {
            sound->data = (unsigned char*)mallocPtr(sound->dataSize);
        }
    }

    return rc;
}

// 0x7D2270
int soundRewind(Sound* sound)
{
    EnterCriticalSection(&soundCritSect);

    if (!driverInit) {
        LeaveCriticalSection(&soundCritSect);

        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->soundBuffer == NULL || sound->deleted) {
        LeaveCriticalSection(&soundCritSect);

        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    HRESULT hr;
    if ((sound->type & SOUND_TYPE_STREAMING) != 0) {
        sound->soundFlags &= ~(SOUND_FLAG_0x200 | SOUND_FLAG_0x80);
        sound->field_74 = 0;
        sound->lastPosition = 0;
        sound->numBytesRead = 0;
        sectionsizeClear(sound->sectionsizes);
        sound->field_6C = 0;
        hr = IDirectSoundBuffer_SetCurrentPosition(sound->soundBuffer, 0);
        preloadBuffers(sound);
    } else {
        hr = IDirectSoundBuffer_SetCurrentPosition(sound->soundBuffer, 0);
    }

    if (hr != DS_OK) {
        LeaveCriticalSection(&soundCritSect);

        soundErrorno = SOUND_UNKNOWN_ERROR;
        return soundErrorno;
    }

    sound->statusFlags &= ~SOUND_STATUS_DONE;

    LeaveCriticalSection(&soundCritSect);

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D2370
int soundPlayFromPosition(Sound* sound, int pos)
{
    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->soundBuffer == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    if (pos < 0) {
        pos = 0;
    }

    if ((sound->statusFlags & SOUND_STATUS_DONE) == 0 || pos >= 0) {
        soundRewind(sound);

        if (pos >= 0) {
            soundSetPosition(sound, pos);
        }
    }

    // NOTE: Uninline.
    soundVolume(sound, sound->volume);

    HRESULT hr;
    if ((sound->soundFlags & SOUND_LOOPING) != 0) {
        hr = IDirectSoundBuffer_Play(sound->soundBuffer, 0, 0, DSBPLAY_LOOPING);
    } else {
        hr = IDirectSoundBuffer_Play(sound->soundBuffer, 0, 0, 0);
    }

    if (hr != DS_OK) {
        soundErrorno = SOUND_UNKNOWN_ERROR;
        return soundErrorno;
    }

    DWORD readPos;
    DWORD writePos;
    IDirectSoundBuffer_GetCurrentPosition(sound->soundBuffer, &readPos, &writePos);
    sound->field_74 = readPos / sound->dataSize;
    sound->statusFlags |= SOUND_STATUS_IS_PLAYING;

    numSounds++;

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D2590
int soundStop(Sound* sound)
{
    HRESULT hr;

    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->soundBuffer == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    if ((sound->statusFlags & SOUND_STATUS_IS_PLAYING) == 0) {
        soundErrorno = SOUND_NOT_PLAYING;
        return soundErrorno;
    }

    hr = IDirectSoundBuffer_Stop(sound->soundBuffer);
    if (hr != DS_OK) {
        soundErrorno = SOUND_UNKNOWN_ERROR;
        return soundErrorno;
    }

    sound->statusFlags &= ~SOUND_STATUS_IS_PLAYING;
    numSounds--;

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D3D90
void soundMgrDelete(Sound* sound)
{
    EnterCriticalSection(&soundCritSect);

    // NOTE: Uninline.
    soundRemoveFadingSound(sound);

    if (sound->soundBuffer != NULL) {
        // NOTE: Uninline.
        soundStop(sound);

        if (sound->callback != NULL) {
            sound->callback(sound->callbackUserData, 1);
            sound->callback = NULL;
        }

        IDirectSoundBuffer_Release(sound->soundBuffer);
        sound->soundBuffer = NULL;
    }

    if (sound->deleteCallback != NULL) {
        sound->deleteCallback(sound->deleteUserData);
    }

    if (sound->data != NULL) {
        freePtr(sound->data);
        sound->data = NULL;
    }

    if (sound->sectionsizes != NULL) {
        sectionsizeDestroy(sound->sectionsizes);
        sound->sectionsizes = NULL;
    }

    if (sound->bufferDesc.lpwfxFormat != NULL) {
        freePtr(sound->bufferDesc.lpwfxFormat);
    }

    if (sound->next != NULL) {
        sound->next->prev = sound->prev;
    }

    if (sound->prev != NULL) {
        sound->prev->next = sound->next;
    } else {
        soundMgrList = sound->next;
    }

    freePtr(sound);

    LeaveCriticalSection(&soundCritSect);
}

// 0x7D2620
int soundDelete(Sound* sound)
{
    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    sound->deleted = 1;

    if (sound->io.fd == -1) {
        sound->io.close(sound->io.fd);
        sound->io.fd = -1;
    }

    // NOTE: Uninline.
    soundMgrDelete(sound);

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D2860
int soundContinue(Sound* sound)
{
    HRESULT hr;
    DWORD status;

    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->soundBuffer == NULL) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    if ((sound->statusFlags & SOUND_STATUS_IS_PLAYING) == 0
        || (sound->statusFlags & SOUND_STATUS_IS_PAUSED) != 0) {
        soundErrorno = SOUND_NOT_PLAYING;
        return soundErrorno;
    }

    if (sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    if ((sound->statusFlags & SOUND_STATUS_DONE) != 0) {
        soundErrorno = SOUND_UNKNOWN_ERROR;
        return soundErrorno;
    }

    hr = IDirectSoundBuffer_GetStatus(sound->soundBuffer, &status);
    if (hr != DS_OK) {
        soundErrorno = SOUND_UNKNOWN_ERROR;
        return soundErrorno;
    }

    if ((sound->soundFlags & SOUND_FLAG_0x80) == 0
        && (status & (DSBSTATUS_PLAYING | DSBSTATUS_LOOPING)) != 0) {
        if ((sound->statusFlags & SOUND_STATUS_IS_PAUSED) == 0
            && (sound->type & SOUND_TYPE_STREAMING) != 0) {
            refreshSoundBuffers(sound);
        }
    } else {
        if ((sound->statusFlags & SOUND_STATUS_IS_PAUSED) == 0) {
            if (sound->callback != NULL) {
                sound->callback(sound->callbackUserData, 1);
                sound->callback = NULL;
            }

            if ((sound->type & SOUND_TYPE_FIRE_AND_FORGET) != 0) {
                sound->callback = NULL;

                // NOTE: Uninline.
                soundDelete(sound);
            } else {
                sound->statusFlags |= SOUND_STATUS_DONE;

                if ((sound->statusFlags & SOUND_STATUS_IS_PLAYING) != 0) {
                    numSounds--;
                }

                // NOTE: Uninline.
                soundStop(sound);

                sound->statusFlags &= ~SOUND_STATUS_IS_PLAYING;
            }
        }
    }

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D2B50
void refreshSoundBuffers(Sound* sound)
{
    // 0xA0E1C0
    static int dword_A0E1C0;

    DWORD readPos;
    DWORD writePos;
    HRESULT hr;

    EnterCriticalSection(&soundCritSect);

    if (sound != NULL
        && sound->soundBuffer != NULL
        && (sound->soundFlags & SOUND_FLAG_0x80) == 0
        && !sound->deleted
        && IDirectSoundBuffer_GetCurrentPosition(sound->soundBuffer, &readPos, &writePos) == DS_OK) {
        // NOTE: Unsigned compare.
        if (readPos < (DWORD)sound->lastPosition) {
            sound->numBytesRead += readPos + sound->numBuffers * sound->dataSize - sound->lastPosition;
        } else {
            sound->numBytesRead += readPos - sound->lastPosition;
        }

        if ((sound->soundFlags & SOUND_FLAG_0x100) != 0) {
            if ((sound->type & SOUND_TYPE_0x20) != 0) {
                if ((sound->soundFlags & SOUND_FLAG_0x200) != 0) {
                    sound->soundFlags |= SOUND_FLAG_0x80;
                }
            } else {
                if (sound->fileSize <= sound->numBytesRead) {
                    sound->soundFlags |= SOUND_FLAG_0x200 | SOUND_FLAG_0x80;
                }
            }
        }

        sound->lastPosition = readPos;

        while (sound->numBytesRead > sound->fileSize) {
            sound->numBytesRead -= sound->fileSize;
        }

        int v1 = readPos / sound->dataSize;
        if (sound->field_74 == v1) {
            LeaveCriticalSection(&soundCritSect);
            return;
        }

        int v2;
        if (sound->field_74 < v1) {
            v2 = v1 - sound->field_74;
        } else {
            v2 = v1 + sound->numBuffers - sound->field_74;
        }

        if (sound->dataSize * v2 >= sound->readLimit) {
            v2 = (sound->readLimit + sound->dataSize - 1) / sound->dataSize;
        }

        if (v2 < sound->field_5C) {
            LeaveCriticalSection(&soundCritSect);
            return;
        }

        VOID* audioPtr1;
        VOID* audioPtr2;
        DWORD audioBytes1;
        DWORD audioBytes2;
        hr = IDirectSoundBuffer_Lock(sound->soundBuffer,
            sound->dataSize * sound->field_74,
            sound->dataSize * v2,
            &audioPtr1,
            &audioBytes1,
            &audioPtr2,
            &audioBytes2,
            0);
        if (hr == DSERR_BUFFERLOST) {
            IDirectSoundBuffer_Restore(sound->soundBuffer);
            hr = IDirectSoundBuffer_Lock(sound->soundBuffer,
                sound->dataSize * sound->field_74,
                sound->dataSize * v2,
                &audioPtr1,
                &audioBytes1,
                &audioPtr2,
                &audioBytes2,
                0);
        }

        if (hr != DS_OK) {
            LeaveCriticalSection(&soundCritSect);
            return;
        }

        if (audioBytes1 + audioBytes2 != v2 * sound->dataSize) {
            v2 = (audioBytes1 + audioBytes2) / sound->dataSize;
            if (v2 < sound->field_5C) {
                IDirectSoundBuffer_Unlock(sound->soundBuffer,
                    audioPtr1,
                    audioBytes1,
                    audioPtr2,
                    audioBytes2);
                LeaveCriticalSection(&soundCritSect);
                return;
            }
        }

        unsigned char* audioPtr = (unsigned char*)audioPtr1;
        int audioBytes = audioBytes1;
        while (v2-- > 0) {
            int bytesRead;
            if ((sound->soundFlags & SOUND_FLAG_0x200) != 0) {
                bytesRead = sound->dataSize;
                memset(sound->data, 0, bytesRead);
            } else {
                int section = musicGetSection();
                int song = musicGetSong();

                if (sound->field_58 == -1) {
                    bytesRead = sound->io.read(sound->io.fd, sound->data, sound->dataSize);
                } else {
                    int pos = sound->io.tell(sound->io.fd);
                    if (sound->dataSize + pos > sound->field_58) {
                        bytesRead = sound->io.read(sound->io.fd, sound->data, sound->field_58 - pos);
                    }
                }

                int sectionStart = audioPtr + sound->dataSize * sound->field_74 - (unsigned char*)audioPtr1;
                int sectionSize = sound->dataSize - musicGetSecondSectionSize();
                sectionsizeAdd(sound->sectionsizes,
                    song,
                    section,
                    sectionStart,
                    sectionSize,
                    sound->field_6C);

                if (musicGetSecondSectionSize() > 0) {
                    int secondSectionSize = musicGetSecondSectionSize();
                    sectionsizeAdd(sound->sectionsizes,
                        musicGetSong(),
                        musicGetSection(),
                        sectionStart + sectionSize,
                        secondSectionSize,
                        0);
                    sound->field_6C = secondSectionSize;
                } else {
                    if (section == musicGetSection()) {
                        sound->field_6C += sectionSize;
                    } else {
                        sound->field_6C = 0;
                    }
                }

                if (bytesRead > sound->dataSize) {
                    dword_A0E1C0++;

                    bytesRead = sound->dataSize;

                    if (dword_A0E1C0 > sound->numBuffers + 1) {
                        IDirectSoundBuffer_Unlock(sound->soundBuffer,
                            audioPtr1,
                            audioBytes1,
                            audioPtr2,
                            audioBytes2);

                        if (sound->callback != NULL) {
                            sound->callback(sound->callbackUserData, 0x8000);
                        }

                        LeaveCriticalSection(&soundCritSect);
                        return;
                    }
                } else {
                    dword_A0E1C0 = 0;
                }

                if (bytesRead < sound->dataSize) {
                    if ((sound->soundFlags & SOUND_LOOPING) == 0
                        || (sound->soundFlags & SOUND_FLAG_0x100) != 0) {
                        memset(sound->data + bytesRead, 0, sound->dataSize - bytesRead);
                        bytesRead = sound->dataSize;
                    } else {
                        while (bytesRead < sound->dataSize) {
                            if (sound->loops == -1) {
                                sound->io.seek(sound->io.fd, sound->field_54, SEEK_SET);
                                if (sound->callback != NULL) {
                                    sound->callback(sound->callbackUserData, 0x400);
                                }
                            } else {
                                if (sound->loops > 0) {
                                    sound->loops--;

                                    sound->io.seek(sound->io.fd, sound->field_54, SEEK_SET);
                                    if (sound->callback != NULL) {
                                        sound->callback(sound->callbackUserData, 0x400);
                                    }
                                } else {
                                    int section = musicGetSection();
                                    int song = musicGetSong();

                                    sound->field_58 = -1;
                                    sound->field_54 = 0;
                                    sound->loops = 0;
                                    sound->soundFlags &= ~SOUND_LOOPING;
                                    bytesRead += sound->io.read(sound->io.fd, sound->data + bytesRead, sound->dataSize - bytesRead);

                                    int sectionStart = audioPtr + bytesRead + sound->dataSize * sound->field_74 - (unsigned char*)audioPtr1;
                                    int sectionSize = sound->dataSize - musicGetSecondSectionSize();
                                    sectionsizeAdd(sound->sectionsizes,
                                        song,
                                        section,
                                        sectionStart,
                                        sectionSize,
                                        sound->field_6C);

                                    if (musicGetSecondSectionSize() > 0) {
                                        int secondSectionSize = musicGetSecondSectionSize();
                                        sectionsizeAdd(sound->sectionsizes,
                                            musicGetSong(),
                                            musicGetSection(),
                                            sectionStart + sectionSize,
                                            secondSectionSize,
                                            sectionSize);
                                        sound->field_6C = secondSectionSize;
                                    } else {
                                        if (section == musicGetSection()) {
                                            sound->field_6C += sectionSize;
                                        } else {
                                            sound->field_6C = 0;
                                        }
                                    }

                                    break;
                                }
                            }

                            int bytesToRead;
                            if (sound->field_58 == -1) {
                                bytesToRead = sound->dataSize - bytesRead;
                            } else {
                                int pos = sound->io.tell(sound->io.fd);
                                if (sound->dataSize + bytesRead + pos <= sound->field_58) {
                                    bytesToRead = sound->dataSize - bytesRead;
                                } else {
                                    bytesToRead = sound->field_58 - bytesRead - pos;
                                }
                            }

                            int section = musicGetSection();
                            int song = musicGetSong();

                            int chunkSize = sound->io.read(sound->io.fd, sound->data + bytesRead, bytesToRead);

                            int sectionStart = audioPtr + bytesRead + sound->dataSize * sound->field_74 - (unsigned char*)audioPtr1;
                            int sectionSize = sound->dataSize - musicGetSecondSectionSize();
                            sectionsizeAdd(sound->sectionsizes,
                                song,
                                section,
                                sectionStart,
                                sectionSize,
                                0);

                            if (musicGetSecondSectionSize() > 0) {
                                int secondSectionSize = musicGetSecondSectionSize();
                                sectionsizeAdd(sound->sectionsizes,
                                    musicGetSong(),
                                    musicGetSection(),
                                    sectionStart + sectionSize,
                                    secondSectionSize,
                                    sound->field_6C);
                                sound->field_6C = secondSectionSize;
                            } else {
                                if (section == musicGetSection()) {
                                    sound->field_6C += sectionSize;
                                } else {
                                    sound->field_6C = 0;
                                }
                            }

                            bytesRead += chunkSize;

                            if (chunkSize < bytesToRead) {
                                break;
                            }
                        }
                    }
                }
            }

            if (bytesRead > audioBytes) {
                if (audioBytes != 0) {
                    memcpy(audioPtr, sound->data, audioBytes);
                }

                if (audioPtr2 != NULL) {
                    memcpy(audioPtr2, sound->data + audioBytes, bytesRead - audioBytes);
                    audioPtr = (unsigned char*)audioPtr2 + bytesRead - audioBytes;
                    audioBytes += audioBytes2 - bytesRead;
                }
            } else {
                memcpy(audioPtr, sound->data, bytesRead);
                audioPtr += bytesRead;
                audioBytes -= bytesRead;
            }
        }

        IDirectSoundBuffer_Unlock(sound->soundBuffer,
            audioPtr1,
            audioBytes1,
            audioPtr2,
            audioBytes2);
        sound->field_74 = v1;
    }

    LeaveCriticalSection(&soundCritSect);
}

// 0x7D3240
int soundPlaying(Sound* sound)
{
    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return 0;
    }

    if (sound == NULL || sound->soundBuffer == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return 0;
    }

    return (sound->statusFlags & SOUND_STATUS_IS_PLAYING) != 0;
}

// 0x7D3290
int soundPaused(Sound* sound)
{
    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return 0;
    }

    if (sound == NULL || sound->soundBuffer == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return 0;
    }

    return (sound->statusFlags & SOUND_STATUS_IS_PAUSED) != 0;
}

// 0x7D32E0
int soundVolumeHMItoDirectSound(int volume)
{
    double normalizedVolume;

    if (volume > VOLUME_MAX) {
        volume = VOLUME_MAX;
    }

    if (volume != 0) {
        normalizedVolume = -1000.0 * log2(32767.0 / volume);
        normalizedVolume = max(min(normalizedVolume, 0.0), -10000.0);
    } else {
        normalizedVolume = -10000.0;
    }

    return (int)normalizedVolume;
}

// 0x7D33C0
int soundVolume(Sound* sound, int volume)
{
    int normalizedVolume;
    HRESULT hr;

    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    sound->volume = volume;

    if (sound->soundBuffer != NULL) {
        // NOTE: Uninline.
        normalizedVolume = soundVolumeHMItoDirectSound(masterVol * volume / VOLUME_MAX);

        hr = IDirectSoundBuffer_SetVolume(sound->soundBuffer, normalizedVolume);
        if (hr != DS_OK) {
            soundErrorno = SOUND_UNKNOWN_ERROR;
            return soundErrorno;
        }
    }

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D3520
int soundSetCallback(Sound* sound, SoundCallback* callback, void* userData)
{
    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    sound->callback = callback;
    sound->callbackUserData = userData;

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D3580
int soundSetChannel(Sound* sound, int channels)
{
    LPWAVEFORMATEX format;

    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    if (channels == 3) {
        format = sound->bufferDesc.lpwfxFormat;

        format->nChannels = 2;
        format->nBlockAlign = format->nChannels * format->wBitsPerSample / 8;
        format->nAvgBytesPerSec = format->nBlockAlign * sampleRate;
    }

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D3600
int soundSetFileIO(Sound* sound, SoundOpenDataFunc* open, SoundCloseDataFunc* close, SoundReadDataFunc* read, SoundWriteDataFunc* write, SoundSeekDataFunc* seek, SoundTellDataFunc* tell, SoundFileSizeFunc* filesize)
{
    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    if (open != NULL) {
        sound->io.open = open;
    }

    if (close != NULL) {
        sound->io.close = close;
    }

    if (read != NULL) {
        sound->io.read = read;
    }

    if (write != NULL) {
        sound->io.write = write;
    }

    if (seek != NULL) {
        sound->io.seek = seek;
    }

    if (tell != NULL) {
        sound->io.tell = tell;
    }

    if (filesize != NULL) {
        sound->io.filesize = filesize;
    }

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D36A0
int soundGetDirectSoundBufferPosition(Sound* sound)
{
    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->soundBuffer == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    DWORD readPos;
    DWORD writePos;
    IDirectSoundBuffer_GetCurrentPosition(sound->soundBuffer, &readPos, &writePos);

    return readPos;
}

// 0x7D3700
int soundSetPosition(Sound* sound, int pos)
{
    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->soundBuffer == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    if ((sound->type & SOUND_TYPE_STREAMING) != 0) {
        int section = pos / sound->dataSize % sound->numBuffers;
        sound->fileSize = sound->io.filesize(sound->io.fd);
        sound->io.seek(sound->io.fd, sound->dataSize * (pos / sound->dataSize), SEEK_SET);
        sound->soundFlags &= ~(SOUND_FLAG_0x200 | SOUND_FLAG_0x80);
        sound->field_74 = section;
        sound->numBytesRead = pos;
        sectionsizeClear(sound->sectionsizes);
        preloadBuffers(sound);
        dword_A0E198 = IDirectSoundBuffer_SetCurrentPosition(sound->soundBuffer, 0);
        sound->field_6C = pos;
        sound->lastPosition = 0;
    } else {
        IDirectSoundBuffer_SetCurrentPosition(sound->soundBuffer, pos);
    }

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D3800
void removeFadeSound(FadeSound* fadeSound)
{
    if (fadeSound == NULL
        || fadeSound->sound == NULL
        || (fadeSound->sound->statusFlags & SOUND_STATUS_IS_FADING) == 0) {
        return;
    }

    if (fadeSound->prev != NULL) {
        fadeSound->prev->next = fadeSound->next;
    } else {
        fadeHead = fadeSound->next;
    }

    if (fadeSound->next != NULL) {
        fadeSound->next->prev = fadeSound->prev;
    }

    fadeSound->sound->statusFlags &= ~SOUND_STATUS_IS_FADING;
    fadeSound->sound = NULL;
    fadeSound->next = fadeFreeList;
    fadeFreeList = fadeSound;
}

// 0x7D3860
void soundRemoveFadingSound(Sound* sound)
{
    if ((sound->statusFlags & SOUND_STATUS_IS_FADING) != 0) {
        FadeSound* fadeSound = fadeHead;
        while (fadeSound != NULL) {
            if (fadeSound->sound == sound) {
                // NOTE: Uninline.
                removeFadeSound(fadeSound);
                break;
            }
        }
    }
}

// 0x7D38E0
void fadeSounds()
{
    FadeSound* fadeSound;

    fadeSound = fadeHead;
    while (fadeSound != NULL) {
        FadeSound* next = fadeSound->next;

        if ((fadeSound->currentVolume > fadeSound->targetVolume
                || fadeSound->currentVolume + fadeSound->deltaVolume < fadeSound->targetVolume)
            && (fadeSound->currentVolume < fadeSound->targetVolume
                || fadeSound->currentVolume + fadeSound->deltaVolume > fadeSound->targetVolume)) {
            fadeSound->currentVolume += fadeSound->deltaVolume;
            soundVolume(fadeSound->sound, fadeSound->currentVolume);
        } else {
            if (fadeSound->targetVolume == 0) {
                if (fadeSound->pause != 2) {
                    if (fadeSound->pause == 1) {
                        // NOTE: Uninline.
                        soundPause(fadeSound->sound);

                        // NOTE: Uninline.
                        soundVolume(fadeSound->sound, fadeSound->initialVolume);
                    } else {
                        if ((fadeSound->sound->type & SOUND_TYPE_FIRE_AND_FORGET) != 0) {
                            // NOTE: Uninline.
                            soundDelete(fadeSound->sound);
                        } else {
                            soundStop(fadeSound->sound);

                            fadeSound->initialVolume = fadeSound->targetVolume;
                            fadeSound->currentVolume = fadeSound->targetVolume;
                            fadeSound->deltaVolume = 0;

                            soundVolume(fadeSound->sound, fadeSound->targetVolume);
                        }
                    }
                }
            }

            SoundCallback* callback = fadeSound->sound->callback;
            if (callback != NULL) {
                callback(fadeSound->sound->callbackUserData, 0x4000);
            }

            removeFadeSound(fadeSound);
        }

        fadeSound = next;
    }

    if (fadeHead == NULL) {
        // NOTE: Uninline.
        removeTimedEvent(&fadeEventHandle);
    }
}

// 0x7D3F70
int soundFadeContinue(Sound* sound, int t, int end)
{
    return internalSoundFade(sound, t, end, 2);
}

// 0x7D3F90
int internalSoundFade(Sound* sound, int millis, int end, int pause)
{
    if (!deviceInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    FadeSound* fadeSound = NULL;
    if (sound->statusFlags & SOUND_STATUS_IS_FADING) {
        fadeSound = fadeHead;
        while (fadeSound != NULL) {
            if (fadeSound->sound == sound) {
                break;
            }

            fadeSound = fadeSound->next;
        }
    }

    if (fadeSound == NULL) {
        if (fadeFreeList != NULL) {
            fadeSound = fadeFreeList;
            fadeFreeList = fadeFreeList->next;
        } else {
            fadeSound = (FadeSound*)mallocPtr(sizeof(FadeSound));
        }

        if (fadeSound != NULL) {
            if (fadeHead != NULL) {
                fadeHead->prev = fadeSound;
            }

            fadeSound->sound = sound;
            fadeSound->prev = NULL;
            fadeSound->next = fadeHead;
            fadeHead = fadeSound;
        }
    }

    if (fadeSound == NULL) {
        soundErrorno = SOUND_NO_MEMORY_AVAILABLE;
        return soundErrorno;
    }

    fadeSound->targetVolume = end;
    fadeSound->initialVolume = soundGetVolume(sound);
    fadeSound->currentVolume = fadeSound->initialVolume;
    fadeSound->pause = pause;
    fadeSound->deltaVolume = 8 * (125 * (end - fadeSound->initialVolume)) / (40 * millis);

    sound->statusFlags |= SOUND_STATUS_IS_FADING;

    // NOTE: Uninline.
    if (!soundPlaying(sound)) {
        // NOTE: Uninline.
        soundPlay(sound);
    }

    // NOTE: Uninline.
    if (fadeEventHandle != -1) {
        soundErrorno = SOUND_NO_ERROR;
        return soundErrorno;
    }

    fadeEventHandle = timeSetEvent(40, 10, doTimerEvent, (DWORD)fadeSounds, 1);
    if (fadeEventHandle == 0) {
        soundErrorno = SOUND_UNKNOWN_ERROR;
        return soundErrorno;
    }

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// 0x7D41E0
void CALLBACK doTimerEvent(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    void (*fn)();

    if (dwUser != 0) {
        fn = (void (*)())dwUser;
        fn();
    }
}

// 0x7D41F0
int soundFadePause(Sound* sound, int t, int end)
{
    return internalSoundFade(sound, t, end, 1);
}

// 0x7D4210
void soundUpdate()
{
    Sound* sound = soundMgrList;
    while (sound != NULL) {
        Sound* next = sound->next;
        if (sound->deleted != 1) {
            soundContinue(sound);
        }
        sound = next;
    }
}

// 0x7D4240
int soundSetDefaultFileIO(SoundOpenDataFunc* open, SoundCloseDataFunc* close, SoundReadDataFunc* read, SoundWriteDataFunc* write, SoundSeekDataFunc* seek, SoundTellDataFunc* tell, SoundFileSizeFunc* filesize)
{
    if (open != NULL) {
        defaultStream.open = open;
    }

    if (close != NULL) {
        defaultStream.close = close;
    }

    if (read != NULL) {
        defaultStream.read = read;
    }

    if (write != NULL) {
        defaultStream.write = write;
    }

    if (seek != NULL) {
        defaultStream.seek = seek;
    }

    if (tell != NULL) {
        defaultStream.tell = tell;
    }

    if (filesize != NULL) {
        defaultStream.filesize = filesize;
    }

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// NOTE: Inlined in `soundInit`.
int soundSetMasterVolume(int volume)
{
    masterVol = volume;

    Sound* curr = soundMgrList;
    while (curr != NULL) {
        soundVolume(curr, curr->volume);
        curr = curr->next;
    }

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}

// NOTE: Inlined.
void soundClearFades()
{
    FadeSound* fadeSound = fadeHead;
    while (fadeSound != NULL) {
        FadeSound* next = fadeSound->next;
        removeFadeSound(fadeSound);
        fadeSound = next;
    }
}

// NOTE: Inlined.
int soundGetVolume(Sound* sound)
{
    long volume;
    int v1;
    int v2;
    int diff;

    if (!deviceInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->soundBuffer == NULL) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    IDirectSoundBuffer_GetVolume(sound->soundBuffer, &volume);

    if (volume == -10000) {
        v1 = 0;
    } else {
        v1 = (int)(32767.0 / pow(2.0, (-volume * 0.001)));
    }

    v2 = VOLUME_MAX * v1 / masterVol;
    diff = abs(v2 - sound->volume);
    if (diff > 20) {
        return v2;
    }

    return sound->volume;
}

// NOTE: Inlined.
int soundPlay(Sound* sound)
{
    return soundPlayFromPosition(sound, -1);
}

// NOTE: Inlined.
void removeTimedEvent(unsigned int* timerId)
{
    if (*timerId != -1) {
        timeKillEvent(*timerId);
        *timerId = -1;
    }
}

// NOTE: Inlined.
int soundPause(Sound* sound)
{
    HRESULT hr;
    DWORD readPos;
    DWORD writePos;

    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->soundBuffer == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    // NOTE: Uninline.
    if (!soundPlaying(sound)) {
        soundErrorno = SOUND_NOT_PLAYING;
        return soundErrorno;
    }

    // NOTE: Uninline.
    if (soundPaused(sound)) {
        soundErrorno = SOUND_ALREADY_PAUSED;
        return soundErrorno;
    }

    hr = IDirectSoundBuffer_GetCurrentPosition(sound->soundBuffer, &readPos, &writePos);
    if (hr != DS_OK) {
        soundErrorno = SOUND_UNKNOWN_ERROR;
        return soundErrorno;
    }

    sound->pausePos = readPos;
    sound->statusFlags |= SOUND_STATUS_IS_PAUSED;

    return soundStop(sound);
}

// NOTE: Inlined.
int soundSetData(Sound* sound, unsigned char* data, int size)
{
    if (!driverInit) {
        soundErrorno = SOUND_NOT_INITIALIZED;
        return soundErrorno;
    }

    if (sound == NULL || sound->deleted) {
        soundErrorno = SOUND_NO_SOUND;
        return soundErrorno;
    }

    if (sound->soundBuffer == NULL) {
        sound->bufferDesc.dwBufferBytes = size;

        if (IDirectSound_CreateSoundBuffer(directSound, &(sound->bufferDesc), &(sound->soundBuffer), NULL) != DS_OK) {
            soundErrorno = SOUND_UNKNOWN_ERROR;
            return soundErrorno;
        }
    }

    return addSoundData(sound, data, size);
}

// NOTE: Inlined.
int addSoundData(Sound* sound, unsigned char* data, int size)
{
    HRESULT hr;
    void* audioPtr1;
    DWORD audioBytes1;
    void* audioPtr2;
    DWORD audioBytes2;

    hr = IDirectSoundBuffer_Lock(sound->soundBuffer, 0, size, &audioPtr1, &audioBytes1, &audioPtr2, &audioBytes2, DSBLOCK_FROMWRITECURSOR);
    if (hr == DSERR_BUFFERLOST) {
        IDirectSoundBuffer_Restore(sound->soundBuffer);
        hr = IDirectSoundBuffer_Lock(sound->soundBuffer, 0, size, &audioPtr1, &audioBytes1, &audioPtr2, &audioBytes2, DSBLOCK_FROMWRITECURSOR);
    }

    if (hr != DS_OK) {
        soundErrorno = SOUND_UNKNOWN_ERROR;
        return soundErrorno;
    }

    memcpy(audioPtr1, data, audioBytes1);

    if (audioPtr2 != NULL) {
        memcpy(audioPtr2, data + audioBytes1, audioBytes2);
    }

    hr = IDirectSoundBuffer_Unlock(sound->soundBuffer, audioPtr1, audioBytes1, audioPtr2, audioBytes2);
    if (hr != DS_OK) {
        soundErrorno = SOUND_UNKNOWN_ERROR;
        return soundErrorno;
    }

    soundErrorno = SOUND_NO_ERROR;
    return soundErrorno;
}
