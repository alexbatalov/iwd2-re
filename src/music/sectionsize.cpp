#include "music/sectionsize.h"

#include <stdlib.h>

typedef struct SectionSize {
    int song;
    int section;
    int start;
    int size;
    int startoffset;
    struct SectionSize* next;
} SectionSize;

class yfSectionSizeManager {
public:
    yfSectionSizeManager();
    virtual ~yfSectionSizeManager();
    void Add(int song, int section, int start, int size, int offset);
    void Clear();
    int GetSong(int position);
    int GetSection(int position);
    int GetSectionOffset(int position);

    SectionSize* sectionsizes;
};

// NOTE: Inlined in `sectionsizeCreate`.
yfSectionSizeManager::yfSectionSizeManager()
{
    sectionsizes = NULL;
}

// 0x7D90D0
yfSectionSizeManager::~yfSectionSizeManager()
{
    // NOTE: Uninline.
    Clear();
}

// 0x7D9120
void yfSectionSizeManager::Add(int song, int section, int start, int size, int offset)
{
    if (sectionsizes == NULL) {
        sectionsizes = new SectionSize;
        sectionsizes->next = NULL;
        sectionsizes->song = song;
        sectionsizes->section = section;
        sectionsizes->start = start;
        sectionsizes->size = size;
        sectionsizes->startoffset = offset;
        return;
    }

    SectionSize* curr = sectionsizes;
    SectionSize* prev = NULL;

    while (curr != NULL) {
        int currEnd = curr->start + curr->size - 1;
        int newEnd = start + size - 1;
        if (curr->start > start || currEnd < newEnd) {
            if (curr->size > 0
                && curr->start >= start
                && curr->start <= newEnd) {
                int v1 = start + size - curr->start;
                int v2 = curr->size - v1;
                curr->start = start + size;
                curr->size = v2;
                curr->startoffset += v1;
            }

            if (curr->size > 0
                && curr->start + curr->size - 1 >= start
                && curr->start + curr->size - 1 <= start + size - 1) {
                curr->size = start - curr->start;
            }

            if (curr->size > 0) {
                prev = curr;
                curr = curr->next;
            } else {
                SectionSize* next = curr->next;
                if (prev != NULL) {
                    prev->next = next;
                } else {
                    sectionsizes = next;
                }

                delete curr;
                curr = next;
            }
        } else if (curr->start == start && curr->size == size) {
            SectionSize* next = curr->next;
            if (prev != NULL) {
                prev->next = next;
            } else {
                sectionsizes = next;
            }

            delete curr;
            curr = next;
        } else {
            if (start <= curr->start || newEnd >= currEnd) {
                if (curr->size > 0 && newEnd < currEnd) {
                    int v1 = start + size - curr->start;
                    int v2 = curr->size - v1;
                    curr->start = start + size;
                    curr->size = v2;
                    curr->startoffset += v1;
                }

                if (curr->size > 0 && start > curr->start) {
                    curr->size = start - curr->start;
                }
            } else {
                SectionSize* newSectionSize = new SectionSize;
                newSectionSize->song = curr->song;
                newSectionSize->section = curr->section;
                newSectionSize->start = curr->start;
                newSectionSize->next = curr;
                newSectionSize->size = start - curr->start;
                newSectionSize->startoffset = curr->startoffset;

                if (prev != NULL) {
                    prev->next = newSectionSize;
                } else {
                    sectionsizes = newSectionSize;
                }

                int v1 = curr->start;
                int v2 = curr->size;
                curr->start += size;
                curr->size = curr->start - start - size + v2;
                curr->startoffset = start + size - v1;
            }

            prev = curr;
            curr = curr->next;
        }
    }

    SectionSize* newSectionSize = new SectionSize;
    newSectionSize->song = song;
    newSectionSize->section = section;
    newSectionSize->start = start;
    newSectionSize->size = size;
    newSectionSize->startoffset = offset;

    if (sectionsizes != NULL) {
        SectionSize* curr = sectionsizes;
        SectionSize* prev = NULL;
        while (curr != NULL) {
            if (start + size - 1 < curr->start) {
                break;
            }

            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL) {
            prev->next = newSectionSize;
            newSectionSize->next = NULL;
        } else {
            newSectionSize->next = curr;
            if (prev != NULL) {
                prev->next = newSectionSize;
            } else {
                sectionsizes = newSectionSize;
            }
        }
    } else {
        // TODO: Unclear. Looks like some kind of unreachable optimization.
        delete newSectionSize;
    }
}

// NOTE: Inlined in `sectionsizeClear`.
void yfSectionSizeManager::Clear()
{
    SectionSize* curr = sectionsizes;
    while (curr != NULL) {
        SectionSize* next = curr->next;
        delete curr;
        curr = next;
    }
    sectionsizes = NULL;
}

// NOTE: Inlined in `sectionsizeGetSong`.
int yfSectionSizeManager::GetSong(int position)
{
    SectionSize* curr = sectionsizes;
    while (curr != NULL) {
        if (position >= curr->start && position < curr->start + curr->size) {
            if (curr->section >= 0) {
                return curr->song;
            } else {
                return -1;
            }
        }
        curr = curr->next;
    }

    return -1;
}

// NOTE: Inlined in `sectionsizeGetSection`.
int yfSectionSizeManager::GetSection(int position)
{
    SectionSize* curr = sectionsizes;
    while (curr != NULL) {
        if (position >= curr->start && position < curr->start + curr->size) {
            return curr->section;
        }
        curr = curr->next;
    }

    return -1;
}

// NOTE: Inlined in `sectionsizeGetSectionOffset`.
int yfSectionSizeManager::GetSectionOffset(int position)
{
    SectionSize* curr = sectionsizes;
    while (curr != NULL) {
        if (position >= curr->start && position < curr->start + curr->size) {
            return position + curr->startoffset - curr->start;
        }
        curr = curr->next;
    }

    return -1;
}

// 0x7D9420
void* sectionsizeCreate()
{
    return new yfSectionSizeManager();
}

// 0x7D9440
void sectionsizeDestroy(void* sectionsizes)
{
    if (sectionsizes != NULL) {
        delete static_cast<yfSectionSizeManager*>(sectionsizes);
    }
}

// 0x7D9450
void sectionsizeClear(void* sectionsizes)
{
    if (sectionsizes != NULL) {
        // NOTE: Uninline.
        static_cast<yfSectionSizeManager*>(sectionsizes)->Clear();
    }
}

// 0x7D9480
void sectionsizeAdd(void* sectionsizes, int song, int section, int start, int size, int offset)
{
    if (sectionsizes != NULL) {
        static_cast<yfSectionSizeManager*>(sectionsizes)->Add(song, section, start, size, offset);
    }
}

// 0x7D94B0
int sectionsizeGetSong(void* sectionsizes, int position)
{
    if (sectionsizes != NULL) {
        // NOTE: Uninline.
        return static_cast<yfSectionSizeManager*>(sectionsizes)->GetSong(position);
    } else {
        return -1;
    }
}

// 0x7D94F0
int sectionsizeGetSection(void* sectionsizes, int position)
{
    if (sectionsizes != NULL) {
        // NOTE: Uninline.
        return static_cast<yfSectionSizeManager*>(sectionsizes)->GetSection(position);
    } else {
        return -1;
    }
}

// 0x7D9530
int sectionsizeGetSectionOffset(void* sectionsizes, int position)
{
    if (sectionsizes != NULL) {
        // NOTE: Uninline.
        return static_cast<yfSectionSizeManager*>(sectionsizes)->GetSectionOffset(position);
    } else {
        return -1;
    }
}
