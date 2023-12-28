#ifndef CPATHSEARCH_H_
#define CPATHSEARCH_H_

#include "mfc.h"

class CSearchBitmap;

class CPathNode {
public:
    CPathNode();

    /* 0000 */ CPathNode* m_pathNodePrev;
    /* 0004 */ CPathNode* m_listOpenLeft;
    /* 0008 */ CPathNode* m_listOpenRight;
    /* 000C */ CPathNode* m_listOpenParent;
    /* 0010 */ LONG m_gridPosition;
    /* 0014 */ LONG m_costStart;
    /* 0018 */ LONG m_costTotal;
    /* 001C */ BOOLEAN m_fIsOpen;
};

class CPathSearch {
public:
    static const BYTE GRID_SQUARE_SIZEX;
    static const BYTE GRID_SQUARE_SIZEY;
    static const SHORT GRID_ACTUALX;
    static const SHORT GRID_ACTUALY;
    static const BYTE COST_IMPASSABLE;
    static const BYTE COST_MINIMUM;
    static const BYTE COST_SCALE_ESTIMATE;

    static SHORT m_nInstances;
    static CPathNode* m_nodeList;
    static LONG m_nNodeList;

    static void PositionToPoint(LONG position, POINT* point);
    static LONG PointToPosition(POINT* point);

    CPathSearch(CPathNode** pListGrid);
    ~CPathSearch();
    LONG EstimateCost(LONG startPosition, LONG* goalPositions, SHORT nGoalPosition);
    void SwapOpenListEntries(CPathNode* ancestor, CPathNode* descendant);
    void InsertOpenList(CPathNode* insertNode);
    CPathNode* PopOpenList();
    void SmoothPath(LONG* pivotPoints, LONG* pathSmooth, BYTE actualCost, CSearchBitmap* pSearchBitmap, BOOL bBump);
    SHORT BuildPathList(CPathNode* startNode, CSearchBitmap* pSearchBitmap, BOOL bBump);
    int FindPath(POINT* startPoint, POINT* goalPoints, int nGoalPoints, LONG minNodeLimit, LONG maxNodeLimit, CSearchBitmap* pSearchBitmap, BYTE* serviceState, BOOL bBump, CRect* gridVirtual);
    LONG* GetPath(SHORT* nSteps);

    /* 0000 */ BOOL m_pathSmooth;
    /* 0004 */ CPathNode** m_pListGrid;
    /* 0008 */ CPathNode* m_openList;
    /* 000C */ SHORT m_openListLevel;
    /* 000E */ SHORT m_nOpenList;
    /* 0010 */ LONG* m_pathBegin;
    /* 0014 */ SHORT m_nPathNodes;
    /* 0016 */ SHORT m_pathCurrent;
};

#endif /* CPATHSEARCH_H_ */
