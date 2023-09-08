#ifndef MUSIC_SOUND_H_
#define MUSIC_SOUND_H_

#include <dsound.h>

#define VOLUME_MIN 0
#define VOLUME_MAX 0x7FFF

typedef enum SoundError {
    SOUND_NO_ERROR = 0,
    SOUND_SOS_DRIVER_NOT_LOADED = 1,
    SOUND_SOS_INVALID_POINTER = 2,
    SOUND_SOS_DETECT_INITIALIZED = 3,
    SOUND_SOS_FAIL_ON_FILE_OPEN = 4,
    SOUND_SOS_MEMORY_FAIL = 5,
    SOUND_SOS_INVALID_DRIVER_ID = 6,
    SOUND_SOS_NO_DRIVER_FOUND = 7,
    SOUND_SOS_DETECTION_FAILURE = 8,
    SOUND_SOS_DRIVER_LOADED = 9,
    SOUND_SOS_INVALID_HANDLE = 10,
    SOUND_SOS_NO_HANDLES = 11,
    SOUND_SOS_PAUSED = 12,
    SOUND_SOS_NO_PAUSED = 13,
    SOUND_SOS_INVALID_DATA = 14,
    SOUND_SOS_DRV_FILE_FAIL = 15,
    SOUND_SOS_INVALID_PORT = 16,
    SOUND_SOS_INVALID_IRQ = 17,
    SOUND_SOS_INVALID_DMA = 18,
    SOUND_SOS_INVALID_DMA_IRQ = 19,
    SOUND_NO_DEVICE = 20,
    SOUND_NOT_INITIALIZED = 21,
    SOUND_NO_SOUND = 22,
    SOUND_FUNCTION_NOT_SUPPORTED = 23,
    SOUND_NO_BUFFERS_AVAILABLE = 24,
    SOUND_FILE_NOT_FOUND = 25,
    SOUND_ALREADY_PLAYING = 26,
    SOUND_NOT_PLAYING = 27,
    SOUND_ALREADY_PAUSED = 28,
    SOUND_NOT_PAUSED = 29,
    SOUND_INVALID_HANDLE = 30,
    SOUND_NO_MEMORY_AVAILABLE = 31,
    SOUND_UNKNOWN_ERROR = 32,
    SOUND_ERR_COUNT,
} SoundError;

typedef enum SoundType {
    SOUND_TYPE_MEMORY = 0x01,
    SOUND_TYPE_STREAMING = 0x02,
    SOUND_TYPE_FIRE_AND_FORGET = 0x04,
    SOUND_TYPE_INFINITE = 0x10,
    SOUND_TYPE_0x20 = 0x20,
} SoundType;

typedef enum SoundFlags {
    SOUND_CTRL_VOLUME = 0x02,
    SOUND_CTRL_PAN = 0x04,
    SOUND_16BIT = 0x08,
    SOUND_8BIT = 0x10,
    SOUND_LOOPING = 0x20,
    SOUND_CTRL_FREQUENCY = 0x40,
    SOUND_FLAG_0x80 = 0x80,
    SOUND_FLAG_0x100 = 0x100,
    SOUND_FLAG_0x200 = 0x200,
} SoundFlags;

typedef enum SoundStatusFlags {
    SOUND_STATUS_DONE = 0x01,
    SOUND_STATUS_IS_PLAYING = 0x02,
    SOUND_STATUS_IS_FADING = 0x04,
    SOUND_STATUS_IS_PAUSED = 0x08,
} SoundStatusFlags;

typedef void*(SoundMallocFunc)(size_t size);
typedef void*(SoundReallocFunc)(void* ptr, size_t size);
typedef void(SoundFreeFunc)(void* ptr);

typedef char*(SoundFileNameMangler)(char* name);

typedef int(SoundOpenDataFunc)(char* fname, int mode);
typedef int(SoundCloseDataFunc)(int fd);
typedef size_t(SoundReadDataFunc)(int fd, void* buf, size_t size);
typedef size_t(SoundWriteDataFunc)(int fd, void* buf, size_t size);
typedef int(SoundSeekDataFunc)(int fd, long offset, int origin);
typedef long(SoundTellDataFunc)(int fd);
typedef long(SoundFileSizeFunc)(int fd);

typedef void SoundCallback(void* userData, int a2);
typedef void SoundDeleteCallback(void* userData);

typedef struct tag_stream {
    SoundOpenDataFunc* open;
    SoundCloseDataFunc* close;
    SoundReadDataFunc* read;
    SoundWriteDataFunc* write;
    SoundSeekDataFunc* seek;
    SoundTellDataFunc* tell;
    SoundFileSizeFunc* filesize;
    int fd;
} SoundStream;

typedef struct tag_sound {
    /* 0000 */ SoundStream io;
    /* 0020 */ unsigned char* data;
    /* 0024 */ LPDIRECTSOUNDBUFFER soundBuffer;
    /* 0028 */ DSBUFFERDESC bufferDesc;
    /* 003C */ int soundFlags;
    /* 0040 */ int statusFlags;
    /* 0044 */ int type;
    /* 0048 */ int pausePos;
    /* 004C */ int volume;
    /* 0050 */ int loops;
    /* 0054 */ int field_54;
    /* 0058 */ int field_58;
    /* 005C */ int field_5C;
    /* 0060 */ int fileSize;
    /* 0064 */ int numBytesRead;
    /* 0068 */ int field_68;
    /* 006C */ int field_6C;
    /* 0070 */ int readLimit;
    /* 0074 */ int field_74;
    /* 0078 */ int lastPosition;
    /* 007C */ int numBuffers;
    /* 0080 */ int dataSize;
    /* 0084 */ int field_84;
    /* 0088 */ void* callbackUserData;
    /* 008C */ SoundCallback* callback;
    /* 0090 */ void* deleteUserData;
    /* 0094 */ SoundDeleteCallback* deleteCallback;
    /* 0098 */ struct tag_sound* next;
    /* 009C */ struct tag_sound* prev;
    /* 00A0 */ void* sectionsizes;
    /* 00A4 */ int field_A4;
    /* 00A8 */ int deleted;
} Sound;

extern CRITICAL_SECTION soundCritSect;

int soundInit(HWND wnd, LPDIRECTSOUND ds, int num, int size, int rate);
int soundClose();
Sound* soundAllocate(int type, int soundFlags);
int soundSetBuffers(Sound* sound, int numBuffers, int bufferSize);
int soundLoad(Sound* sound, char* name);
int soundRewind(Sound* sound);
int soundPlayFromPosition(Sound* sound, int pos);
int soundStop(Sound* sound);
int soundDelete(Sound* sound);
int soundContinue(Sound* sound);
int soundPlaying(Sound* sound);
int soundPaused(Sound* sound);
int soundVolume(Sound* sound, int volume);
int soundSetCallback(Sound* sound, SoundCallback* callback, void* userData);
int soundSetChannel(Sound* sound, int channels);
void fadeSounds();
int soundFadeContinue(Sound* sound, int t, int end);
int soundFadePause(Sound* sound, int t, int end);
void soundUpdate();
int soundSetFileIO(Sound* sound, SoundOpenDataFunc* open, SoundCloseDataFunc* close, SoundReadDataFunc* read, SoundWriteDataFunc* write, SoundSeekDataFunc* seek, SoundTellDataFunc* tell, SoundFileSizeFunc* filesize);
int soundGetDirectSoundBufferPosition(Sound* sound);
int soundSetPosition(Sound* sound, int pos);
int soundSetDefaultFileIO(SoundOpenDataFunc* open, SoundCloseDataFunc* close, SoundReadDataFunc* read, SoundWriteDataFunc* write, SoundSeekDataFunc* seek, SoundTellDataFunc* tell, SoundFileSizeFunc* filesize);

void soundClearFades();
int soundGetVolume(Sound* sound);
int soundPlay(Sound* sound);

#endif /* MUSIC_SOUND_H_ */
