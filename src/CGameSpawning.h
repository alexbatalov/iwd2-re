#ifndef CGAMESPAWNING_H_
#define CGAMESPAWNING_H_

#include "CGameObject.h"
#include "FileFormat.h"

class CGameSpawning : public CGameObject {
public:
    CGameSpawning(CGameArea* pArea, CAreaFileRandomMonsterSpawningPoint* pSpawningObject);
    /* 0000 */ ~CGameSpawning() override;
    /* 002C */ BOOLEAN CompressTime(DWORD deltaTime) override;
    /* 0048 */ void RemoveFromArea() override;

    void Spawn(const CPoint& ptFacingTowards, INT nTotalCharacterLevels);
    void Marshal(CAreaFileRandomMonsterSpawningPoint** pSpawningObject);

    /* 006E */ CAreaFileRandomMonsterSpawningPoint m_spawningObject;
    /* 0136 */ unsigned char field_136;
    /* 0137 */ BYTE m_terrainTable[16];
    /* 0147 */ BYTE m_visibleTerrainTable[16];
};

#endif /* CGAMESPAWNING_H_ */
