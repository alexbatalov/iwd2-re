#include "CPathSearch.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CSearchBitmap.h"
#include "CUtil.h"

// 0x84D69C
const SHORT CPathSearch::GRID_ACTUALX = 320;

// 0x84D69E
const SHORT CPathSearch::GRID_ACTUALY = 320;

// 0x84D6A0
const BYTE CPathSearch::GRID_SQUARE_SIZEX = 16;

// 0x84D6A1
const BYTE CPathSearch::GRID_SQUARE_SIZEY = 12;

// 0x84D6A2
const BYTE CPathSearch::COST_MINIMUM = 5;

// 0x84D6A3
const BYTE CPathSearch::COST_IMPASSABLE = 255;

// 0x84D6A4
const BYTE CPathSearch::COST_SCALE_ESTIMATE = 1;

// 0x8DE064
SHORT CPathSearch::m_nInstances;

// 0x8DE068
CPathNode* CPathSearch::m_nodeList;

// 0x8DE06C
LONG CPathSearch::m_nNodeList;

CPathNode::CPathNode()
{
    m_pathNodePrev = NULL;
    m_listOpenLeft = NULL;
    m_listOpenRight = NULL;
    m_listOpenParent = NULL;
    m_gridPosition = 0;
    m_costStart = 0;
    m_costTotal = 0;
    m_fIsOpen = FALSE;
}

// NOTE: Inlined.
void CPathSearch::PositionToPoint(LONG position, POINT* point)
{
    point->x = position % GRID_ACTUALX;
    point->y = GRID_ACTUALY - position / GRID_ACTUALX - 1;
}

// NOTE: Inlined.
LONG CPathSearch::PointToPosition(POINT* point)
{
    return point->x + GRID_ACTUALX * (GRID_ACTUALY - point->y - 1);
}

// 0x51D520
CPathSearch::CPathSearch(CPathNode** pListGrid)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 112
    UTIL_ASSERT(pListGrid != NULL);

    m_openList = NULL;
    m_openListLevel = 0;
    m_nOpenList = 0;

    if (++m_nInstances == 1) {
        CSearchRequest::MAXNODES = GetPrivateProfileIntA("Program Options",
            "Path Search Nodes",
            32000,
            g_pBaldurChitin->GetIniFileName());

        if (CSearchRequest::MAXNODES < 4000 || CSearchRequest::MAXNODES > 400000) {
            CSearchRequest::MAXNODES = 32000;
        }
        CSearchRequest::MINNODES = CSearchRequest::MAXNODES / 4;
        CSearchRequest::MAXNODESBACK = CSearchRequest::MAXNODES / 2;
        CSearchRequest::MINNODESBACK = CSearchRequest::MAXNODES / 10;

        m_nNodeList = min(CSearchRequest::MAXNODESBACK, 102400);
        m_nodeList = new CPathNode[m_nNodeList];
        if (m_nodeList == NULL) {
            m_nNodeList = 0;
        }
    }

    m_pListGrid = pListGrid;
    m_pathBegin = NULL;
    m_nPathNodes = 0;
    m_pathCurrent = 0;
    m_pathSmooth = TRUE;
}

// 0x51D670
CPathSearch::~CPathSearch()
{
    if (m_pathBegin != NULL) {
        delete m_pathBegin;
        m_pathBegin = NULL;
        m_nPathNodes = 0;
        m_pathCurrent = -1;
    }

    if (--m_nInstances == 0) {
        delete m_nodeList;
        m_nodeList = NULL;
    }
}

// 0x51D6C0
LONG CPathSearch::EstimateCost(LONG startPosition, LONG* goalPositions, SHORT nGoalPosition)
{
    LONG minimumCost;
    LONG diffX;
    LONG diffY;
    LONG nDiagonal;
    LONG nOrthogonal;
    SHORT cnt;
    POINT startPoint;
    POINT endPoint;

    minimumCost = 0x19999999;

    PositionToPoint(startPosition, &startPoint);

    for (cnt = 0; cnt < nGoalPosition; cnt++) {
        if (goalPositions[cnt] != -1) {
            PositionToPoint(goalPositions[cnt], &endPoint);

            diffX = abs(endPoint.x - startPoint.x);
            diffY = abs(endPoint.y - startPoint.y);

            if (diffX > diffY) {
                nDiagonal = diffY;
                nOrthogonal = diffX - diffY;
            } else {
                nDiagonal = diffX;
                nOrthogonal = diffY - diffX;
            }

            if (minimumCost > nOrthogonal + 4 * (nOrthogonal + 2 * nDiagonal) - nDiagonal) {
                minimumCost = nOrthogonal + 4 * (nOrthogonal + 2 * nDiagonal) - nDiagonal;
            }
        }
    }

    return 5 * minimumCost;
}

// 0x51D7A0
void CPathSearch::SwapOpenListEntries(CPathNode* ancestor, CPathNode* descendant)
{
    CPathNode* temp;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 258
    UTIL_ASSERT(ancestor != NULL && descendant != NULL);

    if (descendant->m_listOpenParent == ancestor) {
        if (descendant->m_listOpenLeft != NULL) {
            descendant->m_listOpenLeft->m_listOpenParent = ancestor;
            if (descendant->m_listOpenRight != NULL) {
                descendant->m_listOpenRight = ancestor;
            }
        }

        if (ancestor->m_listOpenLeft == descendant) {
            ancestor->m_listOpenLeft = descendant->m_listOpenLeft;
            descendant->m_listOpenLeft = ancestor;
            if (ancestor->m_listOpenRight != NULL) {
                ancestor->m_listOpenRight->m_listOpenParent = descendant;
            }
            temp = ancestor->m_listOpenRight;
            ancestor->m_listOpenRight = descendant->m_listOpenRight;
            descendant->m_listOpenRight = temp;
        } else {
            ancestor->m_listOpenRight = descendant->m_listOpenRight;
            descendant->m_listOpenRight = ancestor;
            if (ancestor->m_listOpenLeft != NULL) {
                ancestor->m_listOpenLeft->m_listOpenParent = descendant;
            }
            temp = ancestor->m_listOpenLeft;
            ancestor->m_listOpenLeft = descendant->m_listOpenLeft;
            descendant->m_listOpenLeft = temp;
        }

        if (ancestor->m_listOpenParent != NULL) {
            if (ancestor->m_listOpenParent->m_listOpenLeft == ancestor) {
                ancestor->m_listOpenParent->m_listOpenLeft = descendant;
            } else {
                ancestor->m_listOpenParent->m_listOpenRight = descendant;
            }
        }

        descendant->m_listOpenParent = ancestor->m_listOpenParent;
        ancestor->m_listOpenParent = descendant;
    } else {
        if (descendant->m_listOpenLeft != NULL) {
            descendant->m_listOpenLeft->m_listOpenParent = ancestor;
            if (descendant->m_listOpenRight != NULL) {
                descendant->m_listOpenRight->m_listOpenParent = ancestor;
            }
        }
        if (ancestor->m_listOpenLeft != NULL) {
            ancestor->m_listOpenLeft->m_listOpenParent = descendant;
        }

        temp = ancestor->m_listOpenLeft;
        ancestor->m_listOpenLeft = descendant->m_listOpenLeft;
        descendant->m_listOpenLeft = temp;

        if (ancestor->m_listOpenRight != NULL) {
            ancestor->m_listOpenRight->m_listOpenParent = descendant;
        }

        temp = ancestor->m_listOpenRight;
        ancestor->m_listOpenRight = descendant->m_listOpenRight;
        descendant->m_listOpenRight = temp;

        if (ancestor->m_listOpenParent != NULL) {
            if (ancestor->m_listOpenParent->m_listOpenLeft == ancestor) {
                ancestor->m_listOpenParent->m_listOpenLeft = descendant;
            } else {
                ancestor->m_listOpenParent->m_listOpenRight = descendant;
            }
        }

        if (descendant->m_listOpenParent->m_listOpenLeft == descendant) {
            descendant->m_listOpenParent->m_listOpenLeft = ancestor;
        } else {
            descendant->m_listOpenParent->m_listOpenRight = ancestor;
        }

        temp = descendant->m_listOpenParent;
        descendant->m_listOpenParent = ancestor->m_listOpenParent;
        ancestor->m_listOpenParent = temp;
    }
}

// 0x51D8E0
void CPathSearch::InsertOpenList(CPathNode* insertNode)
{
    CPathNode* currentNode;
    CPathNode* prevNode;
    SHORT level;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 354
    UTIL_ASSERT(insertNode != NULL);

    insertNode->m_fIsOpen = TRUE;
    insertNode->m_listOpenLeft = NULL;
    insertNode->m_listOpenRight = NULL;

    if (++m_nOpenList == (1 << m_openListLevel)) {
        m_openListLevel++;
    }

    currentNode = m_openList;
    level = m_openListLevel - 2;
    while (level > 0) {
        if (((1 << level) & m_nOpenList) != 0) {
            currentNode = currentNode->m_listOpenRight;
        } else {
            currentNode = currentNode->m_listOpenLeft;
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
        // __LINE__: 373
        UTIL_ASSERT(currentNode != NULL);
        level--;
    }

    insertNode->m_listOpenParent = currentNode;

    if (currentNode != NULL) {
        if ((m_nOpenList & 1) != 0) {
            currentNode->m_listOpenRight = insertNode;
        } else {
            currentNode->m_listOpenLeft = insertNode;
        }

        prevNode = currentNode;
        while (prevNode != NULL) {
            if (insertNode->m_costTotal > prevNode->m_costTotal
                || (insertNode->m_costTotal == prevNode->m_costTotal
                    && insertNode->m_costStart < prevNode->m_costStart)) {
                break;
            }
            SwapOpenListEntries(prevNode, insertNode);
            prevNode = insertNode->m_listOpenParent;
        }

        if (prevNode == NULL) {
            m_openList = insertNode;
        }
    } else {
        m_openList = insertNode;
    }
}

// 0x51D9E0
CPathNode* CPathSearch::PopOpenList()
{
    CPathNode* currentNode;
    CPathNode* returnNode;
    CPathNode* childNode;
    SHORT level;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 426
    UTIL_ASSERT(m_openList != NULL);

    currentNode = m_openList;
    level = m_openListLevel - 2;
    while (level > 0) {
        if (((1 << level) & m_nOpenList) != 0) {
            currentNode = currentNode->m_listOpenRight;
        } else {
            currentNode = currentNode->m_listOpenLeft;
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
        // __LINE__: 437
        UTIL_ASSERT(currentNode != NULL);
        level--;
    }

    if (m_nOpenList-- == (1 << (m_openListLevel - 1))) {
        m_openListLevel--;
    }

    if (m_nOpenList != 0) {
        returnNode = m_openList;
        m_openList = currentNode;
        if (m_nOpenList >= 3) {
            SwapOpenListEntries(returnNode, currentNode);
            if (returnNode->m_listOpenParent->m_listOpenLeft == returnNode) {
                returnNode->m_listOpenParent->m_listOpenLeft = NULL;
            } else {
                returnNode->m_listOpenParent->m_listOpenRight = NULL;
            }

            childNode = currentNode->m_listOpenLeft;
            while (childNode != NULL) {
                if (childNode->m_costTotal < currentNode->m_costTotal) {
                    if (currentNode->m_listOpenRight != NULL
                        && currentNode->m_listOpenRight->m_costTotal < childNode->m_costTotal) {
                        childNode = currentNode->m_listOpenRight;
                    }
                } else {
                    if (currentNode->m_listOpenRight == NULL
                        || currentNode->m_listOpenRight->m_costTotal >= currentNode->m_costTotal) {
                        break;
                    }
                }
                if (childNode == NULL) {
                    break;
                }
                SwapOpenListEntries(currentNode, childNode);
                if (m_openList->m_listOpenParent != NULL) {
                    m_openList = m_openList->m_listOpenParent;
                }
                childNode = currentNode->m_listOpenLeft;
            }
        } else {
            if (m_nOpenList == 2) {
                childNode = returnNode->m_listOpenLeft;
                if (childNode->m_costTotal < currentNode->m_costTotal) {
                    childNode = currentNode;
                    m_openList = returnNode->m_listOpenLeft;
                }
                m_openList->m_listOpenLeft = childNode;
                childNode->m_listOpenParent = m_openList;
            }

            m_openList->m_listOpenParent = NULL;
        }
    } else {
        m_openList = NULL;
        returnNode = currentNode;
    }

    return returnNode;
}

// 0x51DB40
void CPathSearch::SmoothPath(LONG* pivotPoints, LONG* pathSmooth, BYTE actualCost, CSearchBitmap* pSearchBitmap, BOOL bBump)
{
    SHORT cnt;
    POINT pointA;
    POINT pointC;
    POINT pointNew;
    LONG stepX;
    LONG stepY;
    LONG temp;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 519
    UTIL_ASSERT(pivotPoints != NULL && pathSmooth != NULL && pSearchBitmap != NULL);

    if (pivotPoints[0] != -1
        && (pivotPoints[1] - pivotPoints[2] > 3 || pivotPoints[0] - pivotPoints[1] > 3)) {
        PositionToPoint(m_pathBegin[pivotPoints[0]], &pointA);
        PositionToPoint(m_pathBegin[pivotPoints[2]], &pointC);

        pointNew = pointA;

        if (pointC.x == pointA.x || pointC.y == pointA.y) {
            pivotPoints[1] = pivotPoints[0];
            return;
        }

        stepX = pointC.x > pointA.x ? 1 : -1;
        stepY = pointC.y > pointA.y ? 1 : -1;

        if (stepX * (pointC.x - pointA.x) == stepY * (pointC.y - pointA.y)) {
            pivotPoints[1] = pivotPoints[0];
            return;
        }

        if (pointC.x - pointA.x == pivotPoints[0] - pivotPoints[2]
            && pointA.x - pointC.x == pivotPoints[0] - pivotPoints[2]) {
            temp = stepX * (pointC.x - pointA.x) * (2 * pointA.y + 1) / 2;
            for (cnt = static_cast<WORD>(pivotPoints[0]) - 1; cnt > pivotPoints[2]; cnt--) {
                pointNew.x += stepX;
                pointNew.y = stepX * ((pointC.y - pointA.y + temp) / (pointC.x - pointA.x));
                pathSmooth[cnt] = PointToPosition(&pointNew);
                if (pSearchBitmap->SnapshotGetCost(CPoint(pointNew), bBump) != actualCost) {
                    break;
                }
                pathSmooth[cnt] = -1;
            }
        } else if (pointC.y - pointA.y == pivotPoints[0] - pivotPoints[2]
            && pointA.y - pointC.y == pivotPoints[0] - pivotPoints[2]) {
            temp = stepY * (pointC.x - pointA.x) * (2 * pointA.y + 1) / 2;
            for (cnt = static_cast<WORD>(pivotPoints[0]) - 1; cnt > pivotPoints[2]; cnt--) {
                pointNew.y += stepY;
                pointNew.x = stepY * ((pointC.x - pointA.x + temp) / (pointC.y - pointA.y));
                pathSmooth[cnt] = PointToPosition(&pointNew);
                if (pSearchBitmap->SnapshotGetCost(CPoint(pointNew), bBump) != actualCost) {
                    break;
                }
                pathSmooth[cnt] = -1;
            }
        }
    }
}

// 0x51DE40
SHORT CPathSearch::BuildPathList(CPathNode* startNode, CSearchBitmap* pSearchBitmap, BOOL bBump)
{
    CPathNode* currentNode;
    LONG* pathSmooth = NULL;
    BYTE actualCost;
    LONG directionStep;
    LONG pivotPoints[3];
    SHORT cnt;
    POINT tempPoint;
    BYTE tempCost;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 616
    UTIL_ASSERT(startNode != NULL && pSearchBitmap != NULL);

    currentNode = startNode;
    while (currentNode != NULL) {
        currentNode = currentNode->m_pathNodePrev;
        m_nPathNodes++;
    }

    m_pathBegin = new LONG[m_nPathNodes];
    if (m_pathBegin == NULL) {
        m_nPathNodes = 0;
        return -1;
    }

    if (m_nPathNodes > 1) {
        if (m_pathSmooth) {
            pathSmooth = new LONG[m_nPathNodes - 1];
            if (pathSmooth == NULL) {
                delete m_pathBegin;
                m_pathBegin = NULL;
                m_nPathNodes = 0;
                return -1;
            }
        }

        m_pathBegin[m_nPathNodes - 1] = startNode->m_gridPosition;
        currentNode = startNode->m_pathNodePrev;

        if (m_pathSmooth) {
            PositionToPoint(m_pathBegin[m_nPathNodes - 1], &tempPoint);
            tempCost = pSearchBitmap->SnapshotGetCost(CPoint(tempPoint), bBump);
            pivotPoints[0] = -1;
            pivotPoints[1] = -1;
            pivotPoints[2] = m_nPathNodes - 1;
            directionStep = currentNode->m_gridPosition - m_pathBegin[m_nPathNodes - 1];
        }

        for (cnt = 2; cnt < m_nPathNodes; cnt++) {
            m_pathBegin[m_nPathNodes - cnt] = -currentNode->m_gridPosition;
            currentNode = currentNode->m_pathNodePrev;

            if (m_pathSmooth) {
                if (m_pathBegin[m_nPathNodes - cnt] - m_pathBegin[m_nPathNodes - cnt + 1] != directionStep) {
                    directionStep = m_pathBegin[m_nPathNodes - cnt] - m_pathBegin[m_nPathNodes - cnt + 1];
                    pivotPoints[0] = pivotPoints[1];
                    pivotPoints[1] = pivotPoints[2];
                    pivotPoints[2] = m_nPathNodes - cnt + 2;
                    SmoothPath(pivotPoints, pathSmooth, tempCost, pSearchBitmap, bBump);
                    pivotPoints[2] = m_nPathNodes - cnt;
                }

                PositionToPoint(m_pathBegin[m_nPathNodes - cnt], &tempPoint);
                actualCost = pSearchBitmap->SnapshotGetCost(CPoint(tempPoint), bBump);
                if (actualCost != tempCost) {
                    pivotPoints[0] = pivotPoints[1];
                    pivotPoints[1] = pivotPoints[2];
                    pivotPoints[2] = m_nPathNodes - cnt + 1;
                    SmoothPath(pivotPoints, pathSmooth, tempCost, pSearchBitmap, bBump);
                    tempCost = actualCost;
                    pivotPoints[1] = -1;
                    pivotPoints[2] = m_nPathNodes - cnt;
                }
            }
        }

        if (m_pathSmooth) {
            pivotPoints[0] = pivotPoints[1];
            pivotPoints[1] = pivotPoints[2];
            pivotPoints[2] = 0;
            SmoothPath(pivotPoints, pathSmooth, actualCost, pSearchBitmap, bBump);
            delete pathSmooth;
        }
    } else {
        m_pathBegin[0] = startNode->m_gridPosition;
    }

    return 1;
}

// 0x51E150
int CPathSearch::FindPath(POINT* startPoint, POINT* goalPoints, int nGoalPoints, LONG minNodeLimit, LONG maxNodeLimit, CSearchBitmap* pSearchBitmap, BYTE* serviceState, BOOL bBump, CRect* gridVirtual)
{
    CPathNode* currentNode;
    CPathNode* childNode;
    CPathNode* bestIncomplete;
    LONG startPosition;
    LONG* goalPositions;
    LONG childPosition;
    POINT currentPoint;
    POINT childPoint;
    LONG newCostStart;
    BYTE actualCost;
    SHORT startCol;
    SHORT endCol;
    SHORT startRow;
    SHORT endRow;
    SHORT row;
    SHORT col;
    SHORT cnt;
    SHORT rc;
    LONG cNodes;
    CRect fullSize;

    fullSize.left = 0;
    fullSize.top = 0;
    fullSize.right = GRID_ACTUALX - 1;
    fullSize.bottom = GRID_ACTUALY - 1;

    minNodeLimit = min(maxNodeLimit, 40000);

    if (gridVirtual == NULL) {
        gridVirtual = &fullSize;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 748
    UTIL_ASSERT(startPoint != NULL && goalPoints != NULL && nGoalPoints > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 749
    UTIL_ASSERT(startPoint->x >= 0 && startPoint->x < GRID_ACTUALX && startPoint->y >= 0 && startPoint->y < GRID_ACTUALY);

    if (minNodeLimit > GRID_ACTUALX * GRID_ACTUALY) {
        minNodeLimit = GRID_ACTUALX * GRID_ACTUALY;
    } else {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
        // __LINE__: 752
        UTIL_ASSERT(minNodeLimit > 1);
    }

    if (maxNodeLimit > GRID_ACTUALX * GRID_ACTUALY) {
        maxNodeLimit = GRID_ACTUALX * GRID_ACTUALY;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 755
    UTIL_ASSERT(maxNodeLimit >= minNodeLimit);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 756
    UTIL_ASSERT(pSearchBitmap != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 757
    UTIL_ASSERT(gridVirtual->left >= 0 && gridVirtual->left < gridVirtual->right && gridVirtual->right - gridVirtual->left < GRID_ACTUALX);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 758
    UTIL_ASSERT(gridVirtual->top >= 0 && gridVirtual->bottom > gridVirtual->top && gridVirtual->bottom - gridVirtual->top < GRID_ACTUALY);

    startPosition = PointToPosition(startPoint);

    goalPositions = new LONG[nGoalPoints];
    for (cnt = 0; cnt < nGoalPoints; cnt++) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
        // __LINE__: 756
        UTIL_ASSERT(goalPoints[cnt].x >= -1 && goalPoints[cnt].x < GRID_ACTUALX && goalPoints[cnt].y >= -1 && goalPoints[cnt].y < GRID_ACTUALY);

        if (goalPoints[cnt].y != -1 && goalPoints[cnt].y != -1) {
            goalPositions[cnt] = PointToPosition(&(goalPoints[cnt]));
        } else {
            goalPositions[cnt] = -1;
        }
    }

    if (m_pathBegin != NULL) {
        delete m_pathBegin;
        m_pathBegin = NULL;
        m_nPathNodes = 0;
        m_pathCurrent = -1;
    }

    if (m_nodeList == NULL || maxNodeLimit > m_nNodeList) {
        if (m_nodeList != NULL) {
            delete m_nodeList;
            m_nodeList = NULL;
        }

        m_nNodeList = maxNodeLimit;
        m_nodeList = new CPathNode[maxNodeLimit];
        if (m_nodeList == NULL) {
            delete[] goalPositions;
            return -1;
        }
    }

    m_openList = NULL;
    m_openListLevel = 0;
    m_nOpenList = 0;
    memset(m_pListGrid, 0, sizeof(*m_pListGrid) * GRID_ACTUALX * GRID_ACTUALY);

    currentNode = &(m_nodeList[0]);
    currentNode->m_gridPosition = startPosition;
    currentNode->m_costStart = 0;
    currentNode->m_costTotal = EstimateCost(startPosition, goalPositions, nGoalPoints);
    currentNode->m_pathNodePrev = NULL;
    m_pListGrid[startPosition] = currentNode;
    InsertOpenList(currentNode);

    cNodes = 0;
    while (*serviceState != CSearchRequest::STATE_STALE
        && m_openList != NULL
        && (cNodes < minNodeLimit
            || (g_pBaldurChitin->GetObjectGame()->m_searchRequestListEmpty
                && cNodes < maxNodeLimit))) {
        bestIncomplete = PopOpenList();
        if (bestIncomplete->m_costTotal == bestIncomplete->m_costStart) {
            delete[] goalPositions;
            return BuildPathList(bestIncomplete, pSearchBitmap, bBump);
        }

        // NOTE: Uninline.
        PositionToPoint(bestIncomplete->m_gridPosition, &currentPoint);

        endRow = 2;
        endCol = 2;
        startRow = -1;
        startCol = -1;

        if (currentPoint.y == gridVirtual->bottom) {
            endCol = 1;
        } else if (currentPoint.y == gridVirtual->top) {
            startCol = 0;
        }

        if (currentPoint.x == gridVirtual->left) {
            startRow = 0;
        } else if (currentPoint.x == gridVirtual->right) {
            endRow = 1;
        }

        for (col = startCol; col < endCol; col++) {
            for (row = startRow; row < endRow; row++) {
                if (col != 0 || row != 0) {
                    childPoint.x = currentPoint.x + row;
                    childPoint.y = currentPoint.y + col;
                    actualCost = pSearchBitmap->SnapshotGetCost(CPoint(childPoint), bBump);
                    if (actualCost != COST_IMPASSABLE) {
                        if (col != 0 && row != 0) {
                            newCostStart = bestIncomplete->m_costStart + 7 * actualCost;
                        } else {
                            newCostStart = bestIncomplete->m_costStart + 5 * actualCost;
                        }
                        childPosition = PointToPosition(&childPoint);
                        childNode = m_pListGrid[childPosition];
                        if (childNode == NULL || newCostStart < childNode->m_costStart) {
                            cNodes++;
                            if (cNodes < minNodeLimit
                                || (g_pBaldurChitin->GetObjectGame()->m_searchRequestListEmpty
                                    && cNodes < maxNodeLimit)) {
                                if (childNode == NULL) {
                                    childNode = &(m_nodeList[cNodes]);
                                    childNode->m_gridPosition = childPosition;
                                    childNode->m_fIsOpen = FALSE;
                                    m_pListGrid[childPosition] = childNode;
                                }
                                childNode->m_costStart = newCostStart;
                                childNode->m_costTotal = newCostStart + EstimateCost(childPosition, goalPositions, nGoalPoints);
                                childNode->m_pathNodePrev = bestIncomplete;
                                if (!childNode->m_fIsOpen) {
                                    InsertOpenList(childNode);
                                }
                            }
                        }
                    }
                }
            }
        }

        if (currentNode->m_costTotal - currentNode->m_costStart > bestIncomplete->m_costTotal - bestIncomplete->m_costStart) {
            currentNode = bestIncomplete;
        }

        bestIncomplete->m_fIsOpen = FALSE;
    }

    delete[] goalPositions;

    rc = BuildPathList(currentNode, pSearchBitmap, bBump);
    if (rc == 1) {
        return 0;
    }
    return rc;
}

// 0x51E7C0
LONG* CPathSearch::GetPath(SHORT* nSteps)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CPathSearch.cpp
    // __LINE__: 963
    UTIL_ASSERT(nSteps != NULL);

    *nSteps = 0;

    for (SHORT cnt = 0; cnt < m_nPathNodes; cnt++) {
        if (m_pathBegin[cnt] != -1) {
            m_pathBegin[(*nSteps)++] = m_pathBegin[cnt];
        }
    }

    LONG* path = m_pathBegin;
    m_pathBegin = NULL;
    m_nPathNodes = 0;
    m_pathCurrent = -1;

    return path;
}
