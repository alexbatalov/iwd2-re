#ifndef MUSIC_MUSIC_H_
#define MUSIC_MUSIC_H_

typedef char*(MusicFileNameMangler)(char* name);

typedef int(MusicCompressQueryFunc)(char* fname);
typedef void(MusicDebugFunc)(char* string);

int musicInit(MusicCompressQueryFunc* compressQuery);
void musicClose();
int musicLoadSongList(char** list, int num);
int musicSetVolume(int volume);
int musicGetSong();
int musicSetPath(const char* path, const char* extension);
int musicForceSection(int song, int section, int position);
void musicFade(int song, int section, int position, int fadeTime);
int musicSetSong(int song, int section, int position);
int musicStop();
int musicForceStop();
int musicGetSection();
int musicGetSectionPlaying();
int musicGetSongPlaying();
int musicGetPosition();
void musicFadeIn(int t);
int musicGetSecondSectionSize();
void musicSetDebugFunc(MusicDebugFunc* func);

#endif /* MUSIC_MUSIC_H_ */
