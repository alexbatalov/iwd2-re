#ifndef CWORLDMAP_H_
#define CWORLDMAP_H_

#include "mfc.h"

#include "CResWorldMap.h"
#include "FileFormat.h"

class CWorldMap {
public:
    CWorldMap();
    ~CWorldMap();

    void ClearData();
    void SetResRef(const CResRef& cResRef);
    CWorldMapData* GetMap(DWORD nMap);
    CSize GetMapSize(DWORD nMap);
    DWORD GetNumAreas(DWORD nMap);
    CWorldMapArea* GetArea(DWORD nMap, DWORD nArea);
    CWorldMapLinks* GetLink(DWORD nMap, DWORD nLink);

    CResRef m_cResRef;
    CWorldMapHeader m_cHeader;
    CWorldMapData* m_pData;
    CWorldMapArea** m_ppAreas;
    CWorldMapLinks** m_ppLinks;
};

class CWorldMapFile : public CResHelper<CResWorldMap, 1015> {
public:
    void* GetData();
    DWORD GetDataSize();
};

#endif /* CWORLDMAP_H_ */
