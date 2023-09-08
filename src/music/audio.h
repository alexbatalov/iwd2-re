#ifndef MUSIC_AUDIO_H_
#define MUSIC_AUDIO_H_

#include <stdio.h>

typedef int(AudioCompressQueryFunc)(char* fname);

typedef FILE*(AudioOpenFunc)(const char* fname, const char* mode);
typedef int(AudioCloseFunc)(FILE* stream);
typedef size_t(AudioReadFunc)(void* buf, size_t elements, size_t count, FILE* stream);
typedef int(AudioSeekFunc)(FILE* stream, long offset, int origin);
typedef char*(AudioGetStrFunc)(char* buf, int maxCount, FILE* stream);

extern AudioOpenFunc* audioOpenPtr;
extern AudioCloseFunc* audioClosePtr;
extern AudioReadFunc* audioReadPtr;
extern AudioSeekFunc* audioSeekPtr;
extern AudioGetStrFunc* audioGetStrPtr;

int audioOpen(char* fname, int mode);
size_t audioRead(int fd, void* buf, size_t size);
size_t audioWrite(int fd, void* buf, size_t size);
int audioCloseFile(int fd);
int audioSeek(int fd, long offset, int origin);
long audioFileSize(int fd);
long audioTell(int fd);
void audioInit(AudioCompressQueryFunc* compressQuery);
void audioClose();

#endif /* MUSIC_AUDIO_H_ */
