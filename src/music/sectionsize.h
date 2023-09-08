#ifndef MUSIC_SECTIONSIZE_H_
#define MUSIC_SECTIONSIZE_H_

void* sectionsizeCreate();
void sectionsizeDestroy(void* sectionsizes);
void sectionsizeClear(void* sectionsizes);
void sectionsizeAdd(void* sectionsizes, int song, int section, int start, int size, int offset);
int sectionsizeGetSong(void* sectionsizes, int position);
int sectionsizeGetSection(void* sectionsizes, int position);
int sectionsizeGetSectionOffset(void* sectionsizes, int position);

#endif /* MUSIC_SECTIONSIZE_H_ */
