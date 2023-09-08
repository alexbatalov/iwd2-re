#ifndef MUSIC_ADECODE_H_
#define MUSIC_ADECODE_H_

#include <stddef.h>

typedef int(AudioDecoderReadFunc)(void* data, void* buf, int size);

typedef struct _AudioDecoder AudioDecoder;

size_t AudioDecoder_Read(AudioDecoder* ad, void* buf, size_t size);
void AudioDecoder_Close(AudioDecoder* ad);
AudioDecoder* Create_AudioDecoder(AudioDecoderReadFunc* reader, void* data, int* channels, int* sampleRate, int* sampleCount);

#endif /* MUSIC_ADECODE_H_ */
