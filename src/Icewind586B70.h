#ifndef ICEWIND586B70_H_
#define ICEWIND586B70_H_

#include <vector>

class CGameSprite;

class Icewind586B70 {
public:
    class Entry {
    public:
        Entry();
        Entry(int a1, int a2);
        void Clear();

        int field_0;
        int field_4;
        bool field_8;
    };

    static Icewind586B70* Instance();
    static void Destroy();

    Icewind586B70();
    bool sub_586CA0(CGameSprite* sprite);
    bool sub_586CF0(CGameSprite* sprite1, CGameSprite* sprite2);
    void sub_586D60(CGameSprite* sprite1, CGameSprite* sprite2);
    void sub_586F20(CGameSprite* sprite1, CGameSprite* sprite2);
    void Remove(CGameSprite* sprite);
    void sub_586FC0(CGameSprite* sprite);
    void sub_587190();
    void Clear();
    int GetCount();

    static Icewind586B70* mInstance;
    std::vector<Entry> mEntries;
};

#endif /* ICEWIND586B70_H_ */
