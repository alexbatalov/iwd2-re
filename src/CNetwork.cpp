#include "CNetwork.h"

#include "CChitin.h"
#include "CUtil.h"

// 0x85E610
const DWORD CNetworkWindow::DEFAULT_PACKET_TIMEOUT = 3200;

// 0x85E614
const DWORD CNetworkWindow::DEFAULT_SENDPACKET_TIMEOUT = 200;

// 0x85E618
const DWORD CNetworkWindow::DEFAULT_PLAYER_TIMEOUT = 25000;

// 0x8FB9C4
const DWORD CNetworkWindow::MAX_TIMEOUT_TICK_COUNT = CNetwork::MAX_TIMEOUT_TICK_COUNT;

// 0x8FB9CC
const CString CNetwork::MG("MG");

// 0x8FB9D0
const CString CNetwork::JM("JM");

// 0x8FB9C8
const CString CNetwork::JB("JB");

// 0x8FB9D4
BYTE CNetwork::STATIC_MESSAGE_BUFFER[STATIC_MESSAGE_SIZE];

// 0x9039D4
DWORD CNetwork::DYNAMIC_MESSAGE_SIZE;

// 0x85E634
const INT CNetwork::MAX_PLAYERS = CNETWORK_MAX_PLAYERS;

// 0x85E638
const INT CNetwork::MAX_SESSIONS = CNETWORK_MAX_SESSIONS;

// 0x85E63C
const INT CNetwork::MAX_SERVICE_PROVIDERS = CNETWORK_MAX_SERVICE_PROVIDERS;

// 0x85E640
const INT CNetwork::MAX_STRING_LENGTH = 200;

// 0x85E644
const DWORD CNetwork::MAX_TIMEOUT_TICK_COUNT = DWORD_MAX - 1024;

// 0x85E64C
const INT CNetwork::SERV_PROV_TCP_IP = 8;

// 0x85E650
const INT CNetwork::SERV_PROV_MODEM = 4;

// 0x85E654
const INT CNetwork::SERV_PROV_SERIAL = 2;

// 0x85E658
const INT CNetwork::SERV_PROV_IPX = 1;

// 0x85E65C
const INT CNetwork::SERV_PROV_NULL = 0;

// 0x85E660
const INT CNetwork::SEND_ALL_PLAYERS = 0x100;

// 0x85E664
const INT CNetwork::SEND_GUARANTEED = 0x200;

// 0x85E668
const INT CNetwork::SEND_RAW = 0x400;

// 0x85E66C
const INT CNetwork::SEND_JOINING_PLAYERS = 0x800;

// 0x85E670
const INT CNetwork::SPEC_MSG_HEADER_LENGTH = 3;

// 0x85E674
const INT CNetwork::SPEC_MSG_FLAG = 0;

// 0x85E678
const INT CNetwork::SPEC_MSG_TYPE = 1;

// 0x85E67C
const INT CNetwork::SPEC_MSG_SUBTYPE = 2;

// 0x85E680
const BYTE CNetwork::SPEC_MSG_FLAG_ENABLED = 0xFF;

// 0x85E684
const DWORD CNetwork::MINIMAL_PACKET_SIZE = 128;

// 0x85E688
const DWORD CNetwork::MAXIMAL_PACKET_SIZE = 1024;

// 0x85E68C
const DWORD CNetwork::dword_85E68C = 16;

// 0x85E690
const DWORD CNetwork::dword_85E690 = 12;

// 0x85E694
const DWORD CNetwork::dword_85E694 = 12;

// 0x85E698
const DWORD CNetwork::dword_85E698 = 10;

// 0x85E69C
const DWORD CNetwork::dword_85E69C = 2;

// 0x85E6A0
const DWORD CNetwork::dword_85E6A0 = 2;

// 0x85E6A4
const DWORD CNetwork::dword_85E6A4 = 2;

// 0x85E6A8
const INT CNetwork::ERROR_NONE = 0;

// 0x85E6AC
const INT CNetwork::ERROR_PLAYEREXISTS = 1;

// 0x85E6B0
const INT CNetwork::ERROR_CANNOTCREATEPLAYER = 2;

// 0x85E6B4
const INT CNetwork::ERROR_CANNOTCONNECT = 3;

// 0x85E6B8
const INT CNetwork::ERROR_INVALIDPASSWORD = 4;

// #binary-identical
// 0x7A1E50
CNetworkWindow::CNetworkWindow()
{
    m_bInitialized = FALSE;
    m_bVSSent = FALSE;
    m_bVSReceived = FALSE;
    m_nPlayerNumber = 0;
    m_nAckExpected = 0;
    m_nNextFrameToSend = 0;
    m_nFrameExpected = 0;
    m_nTooFar = 0;
    m_nOldestFrame = 0;
    m_pbTimeOutSet[0] = FALSE;
    m_pnTimeOut[0] = 0;
    m_pbArrived[0] = FALSE;
    m_nNumBuffered = 0;
    m_bNoNak = FALSE;
    m_nPacketTimeout = 0;
    m_nAckTimer = 0;
    m_bAckTimerSet = FALSE;
    m_bSomethingHappened = 0;
    m_nNextEvent = 0;
    m_nPlayerTimeout = 0;
    m_nNoMessageTimeout = 0;
}

// #binary-identical
// 0x7A1F00
CNetworkWindow::~CNetworkWindow()
{
    m_bInitialized = FALSE;
}

// 0x7A1F50
void CNetworkWindow::AddToIncomingQueue(PLAYER_ID idFrom, PLAYER_ID idTo, BYTE* pData, DWORD dwDataSize)
{
    if (dwDataSize >= CNetwork::dword_85E68C
        && memcmp(pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JM, CNetwork::dword_85E69C) == 0
        && dwDataSize > (pData[CNetwork::dword_85E69C + CNetwork::dword_85E698 + CNetwork::dword_85E6A0] << 8)
                + pData[CNetwork::dword_85E69C + CNetwork::dword_85E698 + CNetwork::dword_85E6A0 + 1]
                + CNetwork::dword_85E68C) {
        DWORD dwOffset = 0;
        DWORD dwRemainingSize = dwDataSize;
        while (1) {
            DWORD dwChunkSize = (pData[dwOffset + CNetwork::dword_85E69C + CNetwork::dword_85E698 + CNetwork::dword_85E6A0] << 8)
                + pData[CNetwork::dword_85E69C + CNetwork::dword_85E698 + CNetwork::dword_85E6A0 + 1]
                + CNetwork::dword_85E68C;
            if (dwChunkSize > dwRemainingSize) {
                break;
            }

            BYTE* pChunkData = new BYTE[dwChunkSize];

            if (pChunkData == NULL) {
                // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
                // __LINE__: 344
                UTIL_ASSERT(FALSE);
            }

            memcpy(pChunkData, pData + dwOffset, dwChunkSize);

            CNETWORKWINDOW_QUEUEENTRY* pEntry = new CNETWORKWINDOW_QUEUEENTRY();
            pEntry->idFrom = idFrom;
            pEntry->idTo = idTo;
            pEntry->pData = pChunkData;
            pEntry->dwSize = dwChunkSize;
            m_lQueueIncomingMessages.AddTail(pEntry);

            dwOffset += dwChunkSize;
            dwRemainingSize -= dwChunkSize;

            if (dwRemainingSize == 0) {
                delete pData;
                return;
            }
        }
    } else {
        CNETWORKWINDOW_QUEUEENTRY* pEntry = new CNETWORKWINDOW_QUEUEENTRY();
        pEntry->idFrom = idFrom;
        pEntry->idTo = idTo;
        pEntry->pData = pData;
        pEntry->dwSize = dwDataSize;
        m_lQueueIncomingMessages.AddTail(pEntry);
    }
}

// 0x7A2100
BOOLEAN CNetworkWindow::CheckIncomingQueue()
{
    if (m_lQueueIncomingMessages.IsEmpty()) {
        return FALSE;
    }

    EnterCriticalSection(&(g_pChitin->cNetwork.field_F52));

    POSITION pos = m_lQueueIncomingMessages.GetHeadPosition();
    BYTE* pData = m_lQueueIncomingMessages.GetAt(pos)->pData;

    if (memcmp(pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::MG, CNetwork::dword_85E69C) == 0) {
        LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
        return TRUE;
    }

    if (memcmp(pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JM, CNetwork::dword_85E69C) == 0) {
        int cnt = 0;
        for (int offset = CNetwork::dword_85E69C + CNetwork::dword_85E698; offset < CNetwork::dword_85E69C + CNetwork::dword_85E698 + CNetwork::dword_85E6A0; offset++) {
            cnt = pData[offset] + (cnt << 8);
        }

        while (pos != NULL && cnt > 0) {
            m_lQueueIncomingMessages.GetNext(pos);
            cnt--;
        }

        LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
        return cnt == 0;
    }

    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));

    CString v1;
    CString v2;
    CString v3;
    CString v4;
    CString v5;

    v1.Format("Messages have been misordered.  Please report this bug to Interplay.\n");
    v2.Format("It is very important that the numbers below are recorded correctly.\n");
    v3.Format("Communication Parameters: PN:%d FTS:%d TF:%d AE:%d NB:%d FE:%d\n",
        m_nPlayerNumber,
        m_nNextFrameToSend,
        m_nTooFar,
        m_nAckExpected,
        m_nNumBuffered,
        m_nFrameExpected);
    v4.Format("Message Prefix: %x %x %x %x %x %x %x %x\n",
        pData[0],
        pData[1],
        pData[2],
        pData[3],
        pData[4],
        pData[5],
        pData[6],
        pData[7]);
    v5.Format("%s %s %s %s",
        (LPCSTR)v1,
        (LPCSTR)v2,
        (LPCSTR)v3,
        (LPCSTR)v4);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
    // __LINE__: 541
    UTIL_ASSERT_MSG(FALSE, (LPCSTR)v5);
}

// 0x7A2370
BOOLEAN CNetworkWindow::CheckIncomingQueueSpecific(BYTE nSpecMsgType, BYTE nSpecMsgSubType)
{
    EnterCriticalSection(&(g_pChitin->cNetwork.field_F52));

    if (!m_lQueueIncomingMessages.IsEmpty()) {
        POSITION pos = m_lQueueIncomingMessages.GetHeadPosition();
        while (pos != NULL) {
            BYTE* pData = m_lQueueIncomingMessages.GetNext(pos)->pData;

            if (memcmp(pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::MG, CNetwork::dword_85E69C) == 0) {
                pData += CNetwork::dword_85E694;
                if (pData[CNetwork::SPEC_MSG_FLAG] == CNetwork::SPEC_MSG_FLAG_ENABLED
                    && pData[CNetwork::SPEC_MSG_TYPE] == nSpecMsgType
                    && pData[CNetwork::SPEC_MSG_SUBTYPE] == nSpecMsgSubType) {
                    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
                    return TRUE;
                }
            }

            if (memcmp(pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JM, CNetwork::dword_85E69C) == 0) {
                int cnt = 0;
                for (int offset = CNetwork::dword_85E69C + CNetwork::dword_85E698; offset < CNetwork::dword_85E69C + CNetwork::dword_85E698 + CNetwork::dword_85E6A0; offset++) {
                    cnt = pData[offset] + (cnt << 8);
                }

                pData += CNetwork::dword_85E68C;
                if (pData[CNetwork::SPEC_MSG_FLAG] == CNetwork::SPEC_MSG_FLAG_ENABLED
                    && pData[CNetwork::SPEC_MSG_TYPE] == nSpecMsgType
                    && pData[CNetwork::SPEC_MSG_SUBTYPE] == nSpecMsgSubType) {
                    while (pos != NULL && cnt > 0) {
                        m_lQueueIncomingMessages.GetNext(pos);
                        cnt--;
                    }

                    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
                    return cnt == 0;
                }
            }
        }
    }

    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
    return FALSE;
}

// 0x7A2510
BOOLEAN CNetworkWindow::CheckOutgoingQueueForAppendableMsgs(DWORD dwSize)
{
    if (m_lQueueOutgoingMessages.IsEmpty()) {
        return FALSE;
    }

    CNETWORKWINDOW_QUEUEENTRY* pEntry = m_lQueueOutgoingMessages.GetHead();

    // NOTE: Original code is slightly different.
    if (pEntry->dwSize > CNetwork::dword_85E68C
        && pEntry->dwSize < dwSize
        && memcmp(pEntry->pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JM, CNetwork::dword_85E69C) == 0
        && pEntry->pData[CNetwork::dword_85E698 + CNetwork::dword_85E69C] == 0
        && pEntry->pData[CNetwork::dword_85E698 + CNetwork::dword_85E69C + 1] == 1) {
        return TRUE;
    }

    return FALSE;
}

// 0x7A2590
void CNetworkWindow::FrameSend(BYTE nFrameKind, WORD nFrameNumber)
{
    BYTE* pData;
    DWORD dwSize;

    if (nFrameKind != 0) {
        pData = new BYTE[CNetwork::dword_85E698];
        dwSize = CNetwork::dword_85E698;
    } else {
        pData = m_pOutgoingBuffers[0].pData;
        dwSize = m_pOutgoingBuffers[0].dwSize;
    }

    if (pData == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
        // __LINE__ 913
        UTIL_ASSERT_MSG(FALSE, "FrameSend:: Null Message!\n");
    }

    pData[0] = nFrameKind;
    pData[1] = static_cast<BYTE>(nFrameNumber >> 8);
    pData[2] = static_cast<BYTE>(nFrameNumber);
    pData[3] = static_cast<BYTE>((m_nFrameExpected - 1) >> 8);
    pData[4] = static_cast<BYTE>(m_nFrameExpected - 1);

    if (dwSize >= 10) {
        DWORD dwCrc = 0;

        pData[6] = 0;
        pData[7] = 0;
        pData[8] = 0;
        pData[9] = 0;

        for (DWORD k = 0; k < dwSize; k++) {
            dwCrc = g_pChitin->cNetwork.m_dwCRC32[(dwCrc & 0xFF) ^ pData[k]] ^ (dwCrc >> 8);
        }

        pData[6] = static_cast<BYTE>(dwCrc >> 24);
        pData[7] = static_cast<BYTE>(dwCrc >> 16);
        pData[8] = static_cast<BYTE>(dwCrc >> 8);
        pData[9] = static_cast<BYTE>(dwCrc);
    }

    if (nFrameKind == 2) {
        m_bNoNak = TRUE;
    }

    PLAYER_ID idTo = g_pChitin->cNetwork.GetPlayerID(m_nPlayerNumber);

    EnterCriticalSection(&(g_pChitin->cNetwork.field_F6A));
    g_pChitin->cNetwork.m_lpDirectPlay->Send(g_pChitin->cNetwork.m_idLocalPlayer,
        idTo,
        0,
        pData,
        dwSize);
    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F6A));

    if (nFrameKind == 0) {
        m_pbTimeOutSet[0] = TRUE;
        m_pnTimeOut[0] = m_nPacketTimeout + GetTickCount();
        if (m_pnTimeOut[0] > MAX_TIMEOUT_TICK_COUNT) {
            m_pnTimeOut[0] = 0;
        }
    } else {
        delete pData;
    }

    m_bAckTimerSet = FALSE;

    // NOTE: Uninline.
    SetNoMessageTimeout();
}

// #binary-identical
// 0x7A2770
void CNetworkWindow::Initialize(INT nIndex)
{
    if (m_bInitialized) {
        RemoveFromAllQueues();
    }

    m_bVSSent = FALSE;
    m_bVSReceived = FALSE;
    m_nPlayerNumber = static_cast<BYTE>(nIndex);
    m_nNextFrameToSend = 0;
    m_nTooFar = 1;
    m_nAckExpected = 0;
    m_nNumBuffered = 0;
    m_nFrameExpected = 0;
    m_bNoNak = TRUE;
    m_nPacketTimeout = DEFAULT_PACKET_TIMEOUT;
    m_bAckTimerSet = FALSE;

    // NOTE: Uninline.
    SetPlayerTimeout();

    // NOTE: Uninline.
    SetNoMessageTimeout();

    m_pbTimeOutSet[0] = FALSE;
    m_pbArrived[0] = FALSE;
    m_pOutgoingBuffers[0].dwSize = 0;
    m_pOutgoingBuffers[0].pData = NULL;
    m_pIncomingBuffers[0].dwSize = 0;
    m_pIncomingBuffers[0].pData = NULL;
    m_pnTimeOut[0] = 0;

    m_bInitialized = TRUE;
}

// 0x7A2810
void CNetworkWindow::ShutDown()
{
    PLAYER_ID nServerID = g_pChitin->cNetwork.GetHostPlayerID();
    PLAYER_ID nPlayerID = g_pChitin->cNetwork.m_idLocalPlayer;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
    // __LINE__: 1133
    UTIL_ASSERT(nPlayerID != 0 && nServerID != 0);

    SHORT nServerLocation = g_pChitin->cNetwork.FindPlayerLocationByID(nServerID, TRUE);

    EnterCriticalSection(&(g_pChitin->cNetwork.field_F52));

    // NOTE: Lots of jumps and conditions, probably wrong.
    while (m_nAckExpected != m_nNextFrameToSend) {
        BYTE* pData = m_pOutgoingBuffers[0].pData;
        DWORD dwDataSize = m_pOutgoingBuffers[0].dwSize;
        if (dwDataSize >= CNetwork::dword_85E68C
            && memcmp(pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JM, CNetwork::dword_85E69C) == 0
            && dwDataSize > ((pData[CNetwork::dword_85E69C + CNetwork::dword_85E698 + CNetwork::dword_85E6A0] << 8)
                   + pData[CNetwork::dword_85E69C + CNetwork::dword_85E698 + CNetwork::dword_85E6A0 + 1]
                   + CNetwork::dword_85E68C)) {
            DWORD dwOffset = 0;
            DWORD dwRemainingSize = dwDataSize;
            while (1) {
                DWORD dwChunkSize = (pData[dwOffset + CNetwork::dword_85E69C + CNetwork::dword_85E698 + CNetwork::dword_85E6A0] << 8)
                    + pData[CNetwork::dword_85E69C + CNetwork::dword_85E698 + CNetwork::dword_85E6A0 + 1]
                    + CNetwork::dword_85E68C;
                if (dwChunkSize > dwRemainingSize) {
                    break;
                }

                BYTE* pChunkData = new BYTE[dwChunkSize];

                if (pChunkData == NULL) {
                    // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
                    // __LINE__: 1194
                    UTIL_ASSERT(FALSE);
                }

                memcpy(pChunkData, pData + dwOffset, dwChunkSize);

                if (g_pChitin->MessageCallback(pChunkData + CNetwork::dword_85E68C, dwChunkSize - CNetwork::dword_85E68C) == TRUE) {
                    CNETWORKWINDOW_QUEUEENTRY* pEntry = new CNETWORKWINDOW_QUEUEENTRY();
                    pEntry->idFrom = nPlayerID;
                    pEntry->idTo = nServerID;
                    pEntry->pData = pChunkData;
                    pEntry->dwSize = dwChunkSize;
                    m_lQueueIncomingMessages.AddTail(pEntry);
                } else {
                    delete pChunkData;
                }

                dwOffset += dwChunkSize;
                dwRemainingSize -= dwChunkSize;

                if (dwRemainingSize == 0) {
                    break;
                }
            }
            delete m_pOutgoingBuffers[0].pData;
        } else {
            BYTE* pNewData = NULL;
            DWORD dwNewDataSize;
            if (memcmp(pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::MG, CNetwork::dword_85E69C) == 0) {
                pNewData = pData + CNetwork::dword_85E694;
                dwNewDataSize = dwDataSize - CNetwork::dword_85E694;
            } else if (memcmp(pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JM, CNetwork::dword_85E69C) == 0) {
                pNewData = pData + CNetwork::dword_85E68C;
                dwNewDataSize = dwDataSize - CNetwork::dword_85E68C;
            } else {
                delete m_pOutgoingBuffers[0].pData;
                m_pOutgoingBuffers[0].pData = NULL;
            }

            if (pNewData != NULL) {
                if (g_pChitin->MessageCallback(pNewData, dwNewDataSize) == TRUE) {
                    CNETWORKWINDOW_QUEUEENTRY* newNode = new CNETWORKWINDOW_QUEUEENTRY();
                    newNode->idFrom = nPlayerID;
                    newNode->idTo = nServerID;
                    newNode->pData = pData;
                    newNode->dwSize = dwDataSize;
                    m_lQueueOutgoingMessages.AddTail(newNode);
                } else {
                    delete m_pOutgoingBuffers[0].pData;
                }
            }
        }

        m_pOutgoingBuffers[0].pData = NULL;
        m_pOutgoingBuffers[0].dwSize = 0;

        m_nAckExpected++;
    }

    POSITION pos = m_lQueueOutgoingMessages.GetHeadPosition();
    while (pos != NULL) {
        POSITION posOld = pos;
        CNETWORKWINDOW_QUEUEENTRY* node = m_lQueueOutgoingMessages.GetNext(pos);

        DWORD v1;
        if (memcmp(node->pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::MG, CNetwork::dword_85E69C) == 0) {
            v1 = CNetwork::dword_85E694;
        } else if (memcmp(node->pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JM, CNetwork::dword_85E69C) == 0) {
            v1 = CNetwork::dword_85E68C;
        } else {
            v1 = -1;
        }

        if (v1 != -1) {
            BYTE* pData = node->pData + v1;
            if (pData != NULL && g_pChitin->MessageCallback(pData, node->dwSize - v1) == 1) {
                CNETWORKWINDOW_QUEUEENTRY* newNode = new CNETWORKWINDOW_QUEUEENTRY();
                newNode->idFrom = nPlayerID;
                newNode->idTo = nServerID;
                newNode->pData = node->pData;
                newNode->dwSize = node->dwSize;
                m_lQueueOutgoingMessages.AddTail(newNode);
            }
        } else {
            delete node->pData;
            node->pData = NULL;
        }

        m_lQueueOutgoingMessages.RemoveAt(posOld);
        delete node;
    }

    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));

    RemoveFromAllQueues();

    m_nNextFrameToSend = 0;
    m_nTooFar = 1;
    m_nAckExpected = 0;
    m_nNumBuffered = 0;
    m_nFrameExpected = 0;
    m_bNoNak = TRUE;
    m_nPacketTimeout = DEFAULT_PACKET_TIMEOUT;
    m_bAckTimerSet = FALSE;

    // NOTE: Uninline.
    SetPlayerTimeout();

    // NOTE: Uninline.
    SetNoMessageTimeout();

    m_pbTimeOutSet[0] = 0;
    m_pbArrived[0] = FALSE;
    m_pOutgoingBuffers[0].dwSize = 0;
    m_pOutgoingBuffers[0].pData = NULL;
    m_pIncomingBuffers[0].dwSize = 0;
    m_pIncomingBuffers[0].pData = NULL;
    m_pnTimeOut[0] = 0;

    m_bInitialized = TRUE;
}

// 0x7A2D10
void CNetworkWindow::RemoveFromAllQueues()
{
    POSITION pos;
    POSITION oldPos;
    CNETWORKWINDOW_QUEUEENTRY* node;

    if (m_pOutgoingBuffers[0].pData != NULL) {
        delete m_pOutgoingBuffers[0].pData;
        m_pOutgoingBuffers[0].pData = NULL;
        m_pOutgoingBuffers[0].dwSize = 0;
    }

    if (m_pIncomingBuffers[0].pData != NULL) {
        delete m_pIncomingBuffers[0].pData;
        m_pIncomingBuffers[0].pData = NULL;
        m_pIncomingBuffers[0].dwSize = 0;
    }

    EnterCriticalSection(&(g_pChitin->cNetwork.field_F52));

    pos = m_lQueueIncomingMessages.GetHeadPosition();
    while (pos != NULL) {
        oldPos = pos;
        node = m_lQueueIncomingMessages.GetNext(pos);
        m_lQueueIncomingMessages.RemoveAt(oldPos);
        delete node;
    }

    pos = m_lQueueOutgoingMessages.GetHeadPosition();
    while (pos != NULL) {
        oldPos = pos;
        node = m_lQueueOutgoingMessages.GetNext(pos);
        m_lQueueOutgoingMessages.RemoveAt(oldPos);
        delete node;
    }

    m_bInitialized = FALSE;
    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
}

// 0x7A2DE0
BYTE* CNetworkWindow::RemoveFromIncomingQueue(PLAYER_ID& idDPFrom, PLAYER_ID& idDPTo, DWORD& dwDataSize, BOOLEAN& bCompressed)
{
    EnterCriticalSection(&(g_pChitin->cNetwork.field_F52));

    if (m_lQueueIncomingMessages.IsEmpty()) {
        LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
        return NULL;
    }

    CNETWORKWINDOW_QUEUEENTRY* node = m_lQueueIncomingMessages.GetHead();
    if (memcmp(node->pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::MG, CNetwork::dword_85E69C) == 0) {
        idDPFrom = node->idFrom;
        idDPTo = node->idTo;
        dwDataSize = node->dwSize - CNetwork::dword_85E694;
        bCompressed = node->pData[5];

        BYTE* pData = new BYTE[dwDataSize];
        if (pData != NULL) {
            memcpy(pData, node->pData + CNetwork::dword_85E694, dwDataSize);

            node = m_lQueueIncomingMessages.RemoveHead();
            delete node->pData;
            delete node;
        }

        LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
        return pData;
    }

    if (memcmp(node->pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JM, CNetwork::dword_85E69C) == 0) {
        idDPFrom = node->idFrom;
        idDPTo = node->idTo;

        int cnt = 0;
        for (int offset = CNetwork::dword_85E69C + CNetwork::dword_85E698; offset < CNetwork::dword_85E69C + CNetwork::dword_85E698 + CNetwork::dword_85E6A0; offset++) {
            cnt = node->pData[offset] + (cnt << 8);
        }

        POSITION pos = m_lQueueIncomingMessages.GetHeadPosition();
        int remaining = cnt;

        dwDataSize = 0;

        while (pos != NULL && remaining > 0) {
            dwDataSize += node->dwSize;

            if (remaining == cnt) {
                dwDataSize -= CNetwork::dword_85E68C;
            } else {
                if (memcmp(node->pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JB, CNetwork::dword_85E69C) != 0) {
                    CString v1;
                    CString v2;
                    CString v3;
                    CString v4;
                    CString v5;

                    v1.Format("Messages have been misordered.  Please report this bug to Interplay.\n");
                    v2.Format("It is very important that the numbers below are recorded correctly.\n");
                    v3.Format("Communication Parameters: PN:%d FTS:%d TF:%d AE:%d NB:%d FE:%d\n",
                        m_nPlayerNumber,
                        m_nNextFrameToSend,
                        m_nTooFar,
                        m_nAckExpected,
                        m_nNumBuffered,
                        m_nFrameExpected);
                    v4.Format("Message Prefix: %x %x %x %x %x %x %x %x\n",
                        node->pData[0],
                        node->pData[1],
                        node->pData[2],
                        node->pData[3],
                        node->pData[4],
                        node->pData[5],
                        node->pData[6],
                        node->pData[7]);
                    v5.Format("%s %s %s %s",
                        (LPCSTR)v1,
                        (LPCSTR)v2,
                        (LPCSTR)v3,
                        (LPCSTR)v4);

                    // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
                    // __LINE__: 1673
                    UTIL_ASSERT_MSG(FALSE, (LPCSTR)v5);
                }

                dwDataSize -= CNetwork::dword_85E690;
            }

            remaining--;
            m_lQueueIncomingMessages.GetNext(pos);
        }

        if (remaining == 0) {
            BYTE* pMessage = new BYTE[dwDataSize];
            if (pMessage != NULL) {
                DWORD dwOffset = 0;
                DWORD dwHeaderLength;

                remaining = cnt;

                while (remaining > 0) {
                    node = m_lQueueIncomingMessages.RemoveHead();

                    if (remaining == cnt) {
                        bCompressed = node->pData[5];
                        dwHeaderLength = CNetwork::dword_85E68C;
                    } else {
                        dwHeaderLength = CNetwork::dword_85E690;
                    }

                    memcpy(pMessage + dwOffset,
                        node->pData + dwHeaderLength,
                        node->dwSize - dwHeaderLength);
                    dwOffset += node->dwSize - dwHeaderLength;

                    delete node->pData;
                    delete node;

                    remaining--;
                }
            }

            LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
            return pMessage;
        }

        LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
        return NULL;
    }

    if (memcmp(node->pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JB, CNetwork::dword_85E69C) == 0) {
        CString v1;
        CString v2;
        CString v3;
        CString v4;
        CString v5;

        v1.Format("Messages have been misordered.  Please report this bug to Interplay.\n");
        v2.Format("It is very important that the numbers below are recorded correctly.\n");
        v3.Format("Communication Parameters: PN:%d FTS:%d TF:%d AE:%d NB:%d FE:%d\n",
            m_nPlayerNumber,
            m_nNextFrameToSend,
            m_nTooFar,
            m_nAckExpected,
            m_nNumBuffered,
            m_nFrameExpected);
        v4.Format("Message Prefix: %x %x %x %x %x %x %x %x\n",
            node->pData[0],
            node->pData[1],
            node->pData[2],
            node->pData[3],
            node->pData[4],
            node->pData[5],
            node->pData[6],
            node->pData[7]);
        v5.Format("%s %s %s %s",
            (LPCSTR)v1,
            (LPCSTR)v2,
            (LPCSTR)v3,
            (LPCSTR)v4);

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
        // __LINE__: 1807
        UTIL_ASSERT_MSG(FALSE, (LPCSTR)v5);
    }

    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
    return NULL;
}

// 0x7A3380
BYTE* CNetworkWindow::RemoveFromIncomingQueueSpecific(BYTE nSpecMsgType, BYTE nSpecMsgSubType, PLAYER_ID& idDPFrom, PLAYER_ID& idDPTo, DWORD& dwDataSize, BOOLEAN& bCompressed)
{
    EnterCriticalSection(&(g_pChitin->cNetwork.field_F52));

    if (m_lQueueIncomingMessages.IsEmpty()) {
        LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
        return NULL;
    }

    POSITION pos = m_lQueueIncomingMessages.GetHeadPosition();
    while (pos != NULL) {
        CNETWORKWINDOW_QUEUEENTRY* node = m_lQueueIncomingMessages.GetAt(pos);
        BYTE* pData = node->pData;
        if (memcmp(pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::MG, CNetwork::dword_85E69C) == 0) {
            pData += CNetwork::dword_85E694;
            if (pData[CNetwork::SPEC_MSG_FLAG] == CNetwork::SPEC_MSG_FLAG_ENABLED
                && pData[CNetwork::SPEC_MSG_TYPE] == nSpecMsgType
                && pData[CNetwork::SPEC_MSG_SUBTYPE] == nSpecMsgSubType) {
                idDPFrom = node->idFrom;
                idDPTo = node->idTo;
                dwDataSize = node->dwSize - CNetwork::dword_85E694;

                BYTE* pMessage = new BYTE[dwDataSize];
                if (pMessage != NULL) {
                    bCompressed = node->pData[5];
                    memcpy(pMessage, pData + CNetwork::dword_85E694, dwDataSize);

                    m_lQueueIncomingMessages.RemoveAt(pos);
                    delete node->pData;
                    delete node;
                }

                LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
                return pMessage;
            }
        }

        if (memcmp(pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JM, CNetwork::dword_85E69C) == 0) {
            idDPFrom = node->idFrom;
            idDPTo = node->idTo;

            int cnt = 0;
            for (int offset = CNetwork::dword_85E69C + CNetwork::dword_85E698; offset < CNetwork::dword_85E69C + CNetwork::dword_85E698 + CNetwork::dword_85E6A0; offset++) {
                cnt = pData[offset] + (cnt << 8);
            }

            pData += CNetwork::dword_85E68C;
            if (pData[CNetwork::SPEC_MSG_FLAG] == CNetwork::SPEC_MSG_FLAG_ENABLED
                && pData[CNetwork::SPEC_MSG_TYPE] == nSpecMsgType
                && pData[CNetwork::SPEC_MSG_SUBTYPE] == nSpecMsgSubType) {
                POSITION otherPos = pos;
                int remaining = cnt;

                dwDataSize = 0;

                while (otherPos != NULL && remaining > 0) {
                    node = m_lQueueIncomingMessages.GetAt(otherPos);
                    dwDataSize += node->dwSize + CNetwork::SPEC_MSG_HEADER_LENGTH;

                    if (remaining == cnt) {
                        dwDataSize -= CNetwork::dword_85E68C;
                    } else {
                        if (memcmp(node->pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JB, CNetwork::dword_85E69C) != 0) {
                            CString v1;
                            CString v2;
                            CString v3;
                            CString v4;
                            CString v5;

                            v1.Format("Messages have been misordered.  Please report this bug to Interplay.\n");
                            v2.Format("It is very important that the numbers below are recorded correctly.\n");
                            v3.Format("Communication Parameters: PN:%d FTS:%d TF:%d AE:%d NB:%d FE:%d\n",
                                m_nPlayerNumber,
                                m_nNextFrameToSend,
                                m_nTooFar,
                                m_nAckExpected,
                                m_nNumBuffered,
                                m_nFrameExpected);
                            v4.Format("Message Prefix: %x %x %x %x %x %x %x %x\n",
                                node->pData[0],
                                node->pData[1],
                                node->pData[2],
                                node->pData[3],
                                node->pData[4],
                                node->pData[5],
                                node->pData[6],
                                node->pData[7]);
                            v5.Format("%s %s %s %s",
                                (LPCSTR)v1,
                                (LPCSTR)v2,
                                (LPCSTR)v3,
                                (LPCSTR)v4);

                            // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
                            // __LINE__: 2049
                            UTIL_ASSERT_MSG(FALSE, (LPCSTR)v5);
                        }

                        dwDataSize -= CNetwork::dword_85E690;
                    }

                    remaining--;
                }

                if (remaining == 0) {
                    BYTE* pMessage = new BYTE[dwDataSize];
                    if (pMessage != NULL) {
                        DWORD dwOffset = 0;
                        DWORD dwHeaderLength;

                        otherPos = pos;
                        remaining = cnt;

                        while (remaining > 0) {
                            POSITION posToRemove = otherPos;
                            node = m_lQueueIncomingMessages.GetNext(otherPos);

                            if (remaining == cnt) {
                                bCompressed = node->pData[5];
                                dwHeaderLength = CNetwork::dword_85E68C;
                            } else {
                                dwHeaderLength = CNetwork::dword_85E690;
                            }

                            memcpy(pMessage + dwOffset,
                                node->pData + dwHeaderLength,
                                node->dwSize - dwHeaderLength);
                            dwOffset += node->dwSize - dwHeaderLength;

                            m_lQueueIncomingMessages.RemoveAt(posToRemove);
                            delete node->pData;
                            delete node;

                            remaining--;
                        }
                    }

                    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
                    return pMessage;
                }

                LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
                return NULL;
            } else {
                while (cnt - 1 > 0) {
                    m_lQueueIncomingMessages.GetNext(pos);
                    cnt--;
                }
            }
        }

        m_lQueueIncomingMessages.GetNext(pos);
    }

    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
    return NULL;
}

// 0x7A38B0
void CNetworkWindow::SendCall()
{
    m_bSomethingHappened = FALSE;

    if (m_nNumBuffered != 0) {
        return;
    }

    EnterCriticalSection(&(g_pChitin->cNetwork.field_F52));

    while (!m_lQueueOutgoingMessages.IsEmpty() && m_nNumBuffered == 0) {
        CNETWORKWINDOW_QUEUEENTRY* node = m_lQueueOutgoingMessages.RemoveHead();

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
        // __LINE__: 2286
        UTIL_ASSERT_MSG(node != NULL, "CNetworkWindow::SendCall: Null message being sent!");

        if (g_pChitin->cNetwork.m_idLocalPlayer == g_pChitin->cNetwork.GetPlayerID(m_nPlayerNumber)) {
            AddToIncomingQueue(node->idFrom,
                node->idTo,
                node->pData,
                node->dwSize);
        } else {
            m_nNumBuffered++;
            m_bSomethingHappened = TRUE;
            m_pOutgoingBuffers[0] = *node;
            node->pData = NULL;
            delete node;

            if (m_pOutgoingBuffers[0].dwSize < CNetwork::MAXIMAL_PACKET_SIZE) {
                DWORD dwRemainingSize = CNetwork::MAXIMAL_PACKET_SIZE - m_pOutgoingBuffers[0].dwSize;
                if (CNetwork::MAXIMAL_PACKET_SIZE != m_pOutgoingBuffers[0].dwSize
                    && m_pOutgoingBuffers[0].dwSize > CNetwork::dword_85E68C
                    && memcmp(m_pOutgoingBuffers[0].pData + CNetwork::dword_85E698, (LPCSTR)CNetwork::JM, CNetwork::dword_85E69C) == 0
                    && m_pOutgoingBuffers[0].pData[CNetwork::dword_85E698 + CNetwork::dword_85E69C] == 0
                    && m_pOutgoingBuffers[0].pData[CNetwork::dword_85E698 + CNetwork::dword_85E69C + 1] == 1) {
                    while (dwRemainingSize != 0) {
                        if (CheckOutgoingQueueForAppendableMsgs(dwRemainingSize) != TRUE) {
                            break;
                        }

                        CNETWORKWINDOW_QUEUEENTRY* newNode = !m_lQueueOutgoingMessages.IsEmpty()
                            ? m_lQueueOutgoingMessages.RemoveHead()
                            : NULL;

                        // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
                        // __LINE__: 2380
                        UTIL_ASSERT(newNode != NULL);

                        DWORD dwNewSize = m_pOutgoingBuffers[0].dwSize + newNode->dwSize;
                        BYTE* pNewData = new BYTE[dwNewSize];
                        if (pNewData == NULL) {
                            // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
                            // __LINE__: 2400
                            UTIL_ASSERT(FALSE);
                        }

                        memcpy(pNewData,
                            m_pOutgoingBuffers[0].pData,
                            m_pOutgoingBuffers[0].dwSize);
                        memcpy(pNewData + m_pOutgoingBuffers[0].dwSize,
                            newNode->pData,
                            newNode->dwSize);

                        delete m_pOutgoingBuffers[0].pData;
                        m_pOutgoingBuffers[0].pData = NULL;

                        if (newNode->pData != NULL) {
                            delete newNode->pData;
                            newNode->pData = NULL;
                        }

                        delete newNode;

                        m_pOutgoingBuffers[0].pData = pNewData;
                        m_pOutgoingBuffers[0].dwSize = dwNewSize;

                        if (dwNewSize < CNetwork::MAXIMAL_PACKET_SIZE) {
                            dwRemainingSize = CNetwork::MAXIMAL_PACKET_SIZE - dwNewSize;
                        } else {
                            dwRemainingSize = 0;
                        }
                    }
                }
            }

            FrameSend(0, m_nNextFrameToSend);
            m_nNextFrameToSend++;
        }
    }

    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
}

// 0x7A3B50
void CNetworkWindow::ReceiveCall(BYTE* pData, DWORD dwSize)
{
    BOOLEAN v1 = FALSE;

    EnterCriticalSection(&(g_pChitin->cNetwork.field_F52));

    BOOLEAN v2 = TRUE;
    m_bSomethingHappened = TRUE;

    if (pData[0] == 3) {
        AddToIncomingQueue(g_pChitin->cNetwork.GetPlayerID(m_nPlayerNumber),
            g_pChitin->cNetwork.m_idLocalPlayer,
            pData,
            dwSize);
    } else {
        WORD nFrame = pData[2] + (pData[1] << 8);
        WORD nAck = pData[4] + (pData[3] << 8);

        if (pData[0] == 0) {
            if (nFrame != m_nFrameExpected && m_bNoNak == TRUE) {
                FrameSend(2, 0);
            }

            if ((m_nFrameExpected <= nFrame && nFrame < m_nTooFar)
                || (m_nTooFar < m_nFrameExpected && m_nFrameExpected <= nFrame)
                || (nFrame < m_nTooFar && m_nTooFar < m_nFrameExpected)) {
                if (!m_pbArrived[0]) {
                    m_pbArrived[0] = TRUE;
                    m_pIncomingBuffers[0].idFrom = g_pChitin->cNetwork.GetPlayerID(m_nPlayerNumber);
                    m_pIncomingBuffers[0].idTo = g_pChitin->cNetwork.m_idLocalPlayer;
                    m_pIncomingBuffers[0].pData = pData;
                    m_pIncomingBuffers[0].dwSize = dwSize;

                    v1 = TRUE;

                    while (m_pbArrived[0] == TRUE) {
                        AddToIncomingQueue(m_pIncomingBuffers[0].idFrom,
                            m_pIncomingBuffers[0].idTo,
                            m_pIncomingBuffers[0].pData,
                            m_pIncomingBuffers[0].dwSize);
                        m_bNoNak = TRUE;
                        m_pbArrived[0] = FALSE;
                        m_pIncomingBuffers[0].pData = NULL;
                        m_pIncomingBuffers[0].dwSize = 0;
                        m_nFrameExpected++;
                        m_nTooFar++;
                        m_bAckTimerSet = TRUE;
                        m_nAckTimer = m_nPacketTimeout + GetTickCount();
                        if (m_nAckTimer > CNetworkWindow::MAX_TIMEOUT_TICK_COUNT) {
                            m_nAckTimer = 0;
                        }
                    }
                }
            }
        } else if (pData[0] == 2) {
            if ((m_nAckExpected <= nAck && nAck < m_nNextFrameToSend)
                || (m_nNextFrameToSend < m_nAckExpected && m_nAckExpected <= nAck)
                || (nAck < m_nNextFrameToSend && m_nNextFrameToSend < m_nAckExpected)) {
                FrameSend(0, nAck);
            }
        }

        while ((m_nAckExpected <= nAck && nAck < m_nNextFrameToSend)
            || (m_nNextFrameToSend < m_nAckExpected && m_nAckExpected <= nAck)
            || (nAck < m_nNextFrameToSend && m_nNextFrameToSend < m_nAckExpected)) {
            m_nNumBuffered--;
            m_pbTimeOutSet[0] = FALSE;
            m_pnTimeOut[0] = 0;

            if (m_pOutgoingBuffers[0].pData != NULL) {
                delete m_pOutgoingBuffers[0].pData;
                m_pOutgoingBuffers[0].pData = NULL;
            }

            m_pOutgoingBuffers[0].dwSize = 0;
            m_nAckExpected++;
        }

        v2 = v1;
    }

    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));

    // NOTE: Uninline.
    SetPlayerTimeout();

    if (!v2) {
        delete pData;
    }
}

// 0x7A3DF0
void CNetworkWindow::TimeoutCall()
{
    DWORD dwTickCount = GetTickCount();

    BOOLEAN v1 = FALSE;
    WORD nFrameNumber;
    if (m_pbTimeOutSet[0] && dwTickCount > m_pnTimeOut[0]) {
        v1 = TRUE;
        nFrameNumber = m_pOutgoingBuffers[0].pData[2] + (m_pOutgoingBuffers[0].pData[1] << 8);
    }

    if (v1 == TRUE) {
        FrameSend(0, nFrameNumber);
        m_bSomethingHappened = TRUE;
    }

    if (m_bAckTimerSet == TRUE && GetTickCount() >= m_nAckTimer) {
        FrameSend(1, 0);
        m_bSomethingHappened = TRUE;
    }

    if (m_nNoMessageTimeout < GetTickCount()) {
        if (g_pChitin->cNetwork.GetPlayerID(m_nPlayerNumber) != g_pChitin->cNetwork.m_idLocalPlayer) {
            FrameSend(1, 0);
            m_bSomethingHappened = TRUE;
        }

        // NOTE: Uninline.
        SetNoMessageTimeout();
    }

    if (m_bSomethingHappened == TRUE) {
        m_nNextEvent = GetTickCount();
        return;
    }

    BOOLEAN bHasNextEvent = FALSE;
    DWORD nNextEvent;
    if (m_bAckTimerSet == TRUE) {
        bHasNextEvent = TRUE;
        nNextEvent = m_nAckTimer;
    }

    if (m_pbTimeOutSet[0] == TRUE) {
        if (bHasNextEvent) {
            if (m_pnTimeOut[0] < nNextEvent) {
                nNextEvent = m_pnTimeOut[0];
            }
        } else {
            nNextEvent = m_pnTimeOut[0];
            bHasNextEvent = TRUE;
        }
    }

    if (!bHasNextEvent) {
        nNextEvent = -1;
    }

    m_nNextEvent = nNextEvent;
}

// NOTE: Inlined.
void CNetworkWindow::SetPlayerTimeout()
{
    DWORD dwTickCount = GetTickCount();
    DWORD dwMaxTickCount = GetTickCount() + DEFAULT_PLAYER_TIMEOUT;
    if (dwTickCount > dwMaxTickCount) {
        dwMaxTickCount = -1;
    }
    m_nPlayerTimeout = dwMaxTickCount;
}

// NOTE: Inlined.
void CNetworkWindow::SetNoMessageTimeout()
{
    DWORD dwTickCount = GetTickCount();
    DWORD dwMaxTickCount = GetTickCount() + DEFAULT_SENDPACKET_TIMEOUT;
    if (dwTickCount > dwMaxTickCount) {
        dwMaxTickCount = DWORD_MAX;
    }
    m_nNoMessageTimeout = dwMaxTickCount;
}

// -----------------------------------------------------------------------------

// 0x7A3FD0
CNetwork::CNetwork()
{
#if DPLAY_COMPAT
    InitDirectPlay();
#endif

    field_9D = 0;
    field_9E = 0;
    m_bDirectPlayAddressCreated = FALSE;
    field_796 = 0;
    InitializeCriticalSection(&field_F52);
    InitializeCriticalSection(&field_F6A);
    m_lpDirectPlay = NULL;
    m_lpDirectPlayLobby = NULL;
    m_nApplicationGuid = GUID_NULL;
    m_bApplicationGuidDefined = FALSE;
    field_19 = 0;
    m_bServiceProviderEnumerated = FALSE;
    m_bServiceProviderSelected = FALSE;
    m_nServiceProvider = -1;
    m_nTotalServiceProviders = 0;
    m_serviceProviderGuids[m_nTotalServiceProviders++] = GUID_NULL;
    m_bConnectionInitialized = FALSE;
    m_pServiceProviderConnections[0] = NULL;
    m_pServiceProviderConnections[1] = NULL;
    m_pServiceProviderConnections[2] = NULL;
    m_pServiceProviderConnections[3] = NULL;
    m_pServiceProviderConnections[4] = NULL;
    m_bModemEnumerated = 0;
    m_bModemAddressSelected = FALSE;
    m_nModemAddress = -1;
    m_nTotalModemAddresses = 0;
    m_sIPAddress = "";
    m_sPhoneNumber = "";
    m_nSerialBaudRate = 57600;
    m_nSerialPort = 1;
    m_nSerialFlowControl = DPCPA_RTSDTRFLOW;
    m_nSerialParity = 0;
    m_nSerialStopBits = 0;
    m_bSessionEnumerated = FALSE;

    for (INT nSession = 0; nSession < CNETWORK_MAX_SESSIONS; nSession++) {
        m_psSessionName[nSession] = "";
        m_pSessionGuid[nSession] = GUID_NULL;
        m_pbSessionPasswordRequired[nSession] = FALSE;
    }

    m_bSessionSelected = FALSE;
    m_nSession = -1;
    m_nTotalSessions = 0;
    m_guidSession = GUID_NULL;
    m_bSessionNameToMake = FALSE;
    m_sSessionNameToMake = "";
    m_bSessionPasswordEnabled = FALSE;
    m_sSessionPassword = "";
    m_bAllowNewConnections = TRUE;
    m_pLastSessionBuffer = NULL;
    m_dwLastSessionBufferSize = 0;
    m_bConnectionEstablished = FALSE;
    m_bIsHost = FALSE;
    field_6EA = 0;
    m_bSessionOptionsDefined = 0;
    m_nMaxPlayers = CNETWORK_MAX_PLAYERS;
    m_dwSessionFlags = 0;
    m_bPlayerNameToMake = FALSE;
    m_bPlayerCreated = FALSE;
    m_idLocalPlayer = 0;
    m_sLocalPlayerName = "";
    m_nHostPlayer = -1;
    m_nLocalPlayer = -1;
    m_nTotalPlayers = 0;

    for (INT nPlayerNumber = 0; nPlayerNumber < CNETWORK_MAX_PLAYERS; nPlayerNumber++) {
        m_pPlayerID[nPlayerNumber] = 0;
        field_772[nPlayerNumber] = 0;
        m_psPlayerName[nPlayerNumber] = "";
        m_pbPlayerEnumerateFlag[nPlayerNumber] = FALSE;
        m_pbPlayerVisible[nPlayerNumber] = FALSE;
        m_pSlidingWindow[nPlayerNumber].Initialize(nPlayerNumber);
    }

    m_SystemWindow.Initialize(-1);

    for (unsigned int m = 0; m <= 255; m++) {
        unsigned int v1 = m;
        for (unsigned int bit = 8; bit > 0; bit--) {
            if ((v1 & 1) != 0) {
                v1 >>= 1;
                v1 ^= 0xEDB88320;
            } else {
                v1 >>= 1;
            }
        }
        m_dwCRC32[m] = v1;
    }

    for (INT nSlot = 0; nSlot < CNETWORK_MAX_PLAYERS; nSlot++) {
        field_71A[nSlot] = FALSE;
    }

    m_pDirectPlayAddress = NULL;
}

// 0x7A4440
CNetwork::~CNetwork()
{
    if (m_bConnectionEstablished) {
        OnCloseSession();
    }

    m_bServiceProviderEnumerated = FALSE;

    for (INT nServiceProvider = 0; nServiceProvider < CNETWORK_MAX_SERVICE_PROVIDERS; nServiceProvider++) {
        if (m_pServiceProviderConnections[nServiceProvider] != NULL) {
            operator delete(m_pServiceProviderConnections[nServiceProvider]);
        }
    }

    if (m_nServiceProvider != SERV_PROV_NULL) {
        EnterCriticalSection(&field_F6A);

        if (m_lpDirectPlay != NULL) {
            m_lpDirectPlay->Release();
            m_lpDirectPlay = NULL;
        }

        if (m_lpDirectPlayLobby != NULL) {
            m_lpDirectPlayLobby->Release();
            m_lpDirectPlayLobby = NULL;
        }

        LeaveCriticalSection(&field_F6A);
    }

    DeleteCriticalSection(&field_F6A);
    DeleteCriticalSection(&field_F52);

#if DPLAY_COMPAT
    FreeDirectPlay();
#endif
}

// 0x7A4660
void CNetwork::AddModemAddressToList(LPCSTR lpAddress)
{
    m_psModemAddress[m_nTotalModemAddresses] = CString(lpAddress, strlen(lpAddress));
    m_nTotalModemAddresses++;
}

// 0x7A46E0
void CNetwork::AddServiceProviderToList(const CString& sServiceProviderName, const GUID& sServiceProviderGuid, LPVOID lpConnection, size_t size)
{
    if (m_pServiceProviderConnections[m_nTotalServiceProviders] != NULL) {
        operator delete(m_pServiceProviderConnections[m_nTotalServiceProviders]);
    }

    m_pServiceProviderConnections[m_nTotalServiceProviders] = operator new(size);
    if (m_pServiceProviderConnections[m_nTotalServiceProviders] != NULL) {
        memcpy(m_pServiceProviderConnections[m_nTotalServiceProviders], lpConnection, size);

        m_serviceProviderGuids[m_nTotalServiceProviders] = sServiceProviderGuid;
        m_serviceProviderNames[m_nTotalServiceProviders] = sServiceProviderName;

        m_nTotalServiceProviders++;
    }
}

// 0x7A4780
BOOLEAN CNetwork::CreateDirectPlayAddress(BOOLEAN bHostingGame)
{
    DPCOMPOUNDADDRESSELEMENT addressElements[3];
    DWORD dwElementCount = 0;
    char szIpAddress[MAX_STRING_LENGTH];
    WORD nPort;
    char szModemAddress[MAX_STRING_LENGTH];
    char szPhoneNumber[MAX_STRING_LENGTH];
    DPCOMPORTADDRESS com;
    HRESULT hr;

    if (m_bDirectPlayAddressCreated) {
        if (m_pDirectPlayAddress != NULL) {
            delete m_pDirectPlayAddress;
            m_bDirectPlayAddressCreated = FALSE;
        }
    }

    if (!m_bServiceProviderSelected
        || m_nServiceProvider < 0
        || m_nServiceProvider >= m_nTotalServiceProviders) {
        if (m_pDirectPlayAddress != NULL) {
            delete m_pDirectPlayAddress;
            m_bDirectPlayAddressCreated = FALSE;
        }

        return FALSE;
    }

    GUID serviceProviderGuid = m_serviceProviderGuids[m_nServiceProvider];

    if (IsEqualGUID(serviceProviderGuid, DPSPGUID_MODEM)) {
        addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
        addressElements[dwElementCount].dwDataSize = sizeof(GUID);
        addressElements[dwElementCount].lpData = (LPVOID)&DPSPGUID_MODEM;
        dwElementCount++;

        lstrcpyA(szModemAddress, "");
        if (m_bModemAddressSelected == TRUE
            && m_nModemAddress >= 1
            && m_nModemAddress < m_nTotalModemAddresses) {
            lstrcpynA(szModemAddress, m_psModemAddress[m_nModemAddress], MAX_STRING_LENGTH);

            addressElements[dwElementCount].guidDataType = DPAID_Modem;
            addressElements[dwElementCount].dwDataSize = lstrlenA(szModemAddress) + 1;
            addressElements[dwElementCount].lpData = szModemAddress;
            dwElementCount++;
        }

        if (m_sPhoneNumber.GetLength() > 0 && !bHostingGame) {
            lstrcpynA(szPhoneNumber, m_sPhoneNumber, MAX_STRING_LENGTH);

            addressElements[dwElementCount].guidDataType = DPAID_Phone;
            addressElements[dwElementCount].dwDataSize = lstrlenA(szPhoneNumber) + 1;
            addressElements[dwElementCount].lpData = szPhoneNumber;
            dwElementCount++;
        }
    } else if (IsEqualGUID(serviceProviderGuid, DPSPGUID_TCPIP)) {
        addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
        addressElements[dwElementCount].dwDataSize = sizeof(GUID);
        addressElements[dwElementCount].lpData = (LPVOID)&DPSPGUID_TCPIP;
        dwElementCount++;

        lstrcpyA(szIpAddress, "");
        lstrcpynA(szIpAddress, m_sIPAddress, MAX_STRING_LENGTH);

        if (m_sIPAddress.IsEmpty() && bHostingGame == TRUE) {
            m_sIPAddress = "127.0.0.1";
            lstrcpynA(szIpAddress, m_sIPAddress, MAX_STRING_LENGTH);
            m_sIPAddress = "";
        }

        addressElements[dwElementCount].guidDataType = DPAID_INet;
        addressElements[dwElementCount].dwDataSize = lstrlenA(szIpAddress) + 1;
        addressElements[dwElementCount].lpData = szIpAddress;
        dwElementCount++;

        nPort = g_pChitin->GetMultiplayerDirectPlayPort();
        if (nPort != 0) {
            addressElements[dwElementCount].guidDataType = DPAID_INetPort;
            addressElements[dwElementCount].dwDataSize = sizeof(WORD);
            addressElements[dwElementCount].lpData = &nPort;
            dwElementCount++;
        }
    } else if (IsEqualGUID(serviceProviderGuid, DPSPGUID_IPX)) {
        addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
        addressElements[dwElementCount].dwDataSize = sizeof(GUID);
        addressElements[dwElementCount].lpData = (LPVOID)&DPSPGUID_IPX;
        dwElementCount++;
    } else if (IsEqualGUID(serviceProviderGuid, DPSPGUID_SERIAL)) {
        addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
        addressElements[dwElementCount].dwDataSize = sizeof(GUID);
        addressElements[dwElementCount].lpData = (LPVOID)&DPSPGUID_SERIAL;
        dwElementCount++;

        com.dwComPort = m_nSerialPort;
        com.dwBaudRate = m_nSerialBaudRate;
        com.dwStopBits = m_nSerialStopBits;
        com.dwParity = m_nSerialParity;
        com.dwFlowControl = m_nSerialFlowControl;

        addressElements[dwElementCount].guidDataType = DPAID_ComPort;
        addressElements[dwElementCount].dwDataSize = sizeof(DPCOMPORTADDRESS);
        addressElements[dwElementCount].lpData = &com;
        dwElementCount++;
    } else {
        addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
        addressElements[dwElementCount].dwDataSize = sizeof(GUID);
        addressElements[dwElementCount].lpData = &serviceProviderGuid;
        dwElementCount++;
    }

    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlayLobby == NULL) {
        if (SendMessageA(g_pChitin->GetWnd()->GetSafeHwnd(), 0x405, (WPARAM)&m_lpDirectPlayLobby, 0) == 0) {
            if (m_pDirectPlayAddress != NULL) {
                delete m_pDirectPlayAddress;
                m_bDirectPlayAddressCreated = FALSE;
            }

            LeaveCriticalSection(&field_F6A);
            return FALSE;
        }
    }

    hr = m_lpDirectPlayLobby->CreateCompoundAddress(addressElements,
        dwElementCount,
        NULL,
        &m_pDirectPlayAddressSize);
    if (hr != DPERR_BUFFERTOOSMALL) {
        if (m_pDirectPlayAddress != NULL) {
            delete m_pDirectPlayAddress;
            m_bDirectPlayAddressCreated = FALSE;
        }

        LeaveCriticalSection(&field_F6A);
        return FALSE;
    }

    m_pDirectPlayAddress = new BYTE[m_pDirectPlayAddressSize];
    if (m_pDirectPlayAddress == NULL) {
        LeaveCriticalSection(&field_F6A);
        return FALSE;
    }

    hr = m_lpDirectPlayLobby->CreateCompoundAddress(addressElements,
        dwElementCount,
        m_pDirectPlayAddress,
        &m_pDirectPlayAddressSize);
    if (FAILED(hr)) {
        if (m_pDirectPlayAddress != NULL) {
            delete m_pDirectPlayAddress;
            m_bDirectPlayAddressCreated = FALSE;
        }

        LeaveCriticalSection(&field_F6A);
        return FALSE;
    }

    m_bDirectPlayAddressCreated = TRUE;

    LeaveCriticalSection(&field_F6A);
    return TRUE;
}

// 0x7A4D90
BOOLEAN CNetwork::CreateDirectPlayInterface(const GUID* guid, IDirectPlay4A** lplpDirectPlay4)
{
    GUID guidCopy = *guid;
    IDirectPlay* lpDirectPlay = NULL;
    IDirectPlay4A* lpDirectPlay4 = NULL;

    if (IsEqualGUID(guidCopy, GUID_NULL)) {
        HRESULT hr = CoCreateInstance(CLSID_DirectPlay,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_IDirectPlay4A,
            reinterpret_cast<LPVOID*>(&lpDirectPlay4));
        if (hr != S_OK) {
            // NOTE: Not used. Probably were a part of error reporting.
            switch (hr) {
            case REGDB_E_CLASSNOTREG:
                return FALSE;
            case REGDB_E_IIDNOTREG:
                return FALSE;
            }

            return FALSE;
        }
    } else {
        if (DirectPlayCreate(&guidCopy, &lpDirectPlay, NULL) != DP_OK) {
            return FALSE;
        }

        if (lpDirectPlay->QueryInterface(IID_IDirectPlay4A, reinterpret_cast<LPVOID*>(&lpDirectPlay4)) != DP_OK) {
            if (lpDirectPlay != NULL) {
                lpDirectPlay->Release();
            }
            return FALSE;
        }

        lpDirectPlay->Release();
    }

    *lplpDirectPlay4 = lpDirectPlay4;
    return TRUE;
}

// 0x7A4E80
BOOLEAN CNetwork::CreateDirectPlayLobbyInterface(IDirectPlayLobby3A** lplpDirectPlayLobby3)
{
    IDirectPlayLobby* lpDirectPlayLobby = NULL;
    IDirectPlayLobby3A* lpDirectPlayLobby3 = NULL;

    if (DirectPlayLobbyCreateA(NULL, &lpDirectPlayLobby, NULL, NULL, 0) != DP_OK) {
        return FALSE;
    }

    if (lpDirectPlayLobby->QueryInterface(IID_IDirectPlayLobby3A, reinterpret_cast<LPVOID*>(&lpDirectPlayLobby3)) != DP_OK) {
        if (lpDirectPlayLobby != NULL) {
            lpDirectPlayLobby->Release();
        }
        return FALSE;
    }

    lpDirectPlayLobby->Release();
    *lplpDirectPlayLobby3 = lpDirectPlayLobby3;
    return TRUE;
}

// 0x7A4F00
BOOLEAN CNetwork::HasModems()
{
    HKEY hSystem;
    HKEY hCurrentControlSet;
    HKEY hServices;
    HKEY hModem;
    HKEY hEnum;
    HKEY hClass;
    DWORD cSubKeys;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "System", 0, KEY_READ, &hSystem) != ERROR_SUCCESS) {
        return FALSE;
    }

    if (RegOpenKeyExA(hSystem, "CurrentControlSet", 0, KEY_READ, &hCurrentControlSet) != ERROR_SUCCESS) {
        RegCloseKey(hSystem);
        return FALSE;
    }

    if (RegOpenKeyExA(hSystem, "Services", 0, KEY_READ, &hServices) != ERROR_SUCCESS) {
        RegCloseKey(hCurrentControlSet);
        RegCloseKey(hSystem);
        return FALSE;
    }

    if (g_pChitin->dwPlatformId == VER_PLATFORM_WIN32_NT) {
        if (RegOpenKeyExA(hServices, "Modem", 0, KEY_READ, &hModem) != ERROR_SUCCESS) {
            RegCloseKey(hServices);
            RegCloseKey(hCurrentControlSet);
            RegCloseKey(hSystem);
            return FALSE;
        }

        if (RegOpenKeyExA(hModem, "Enum", 0, KEY_READ, &hEnum) != ERROR_SUCCESS) {
            RegCloseKey(hModem);
            RegCloseKey(hServices);
            RegCloseKey(hCurrentControlSet);
            RegCloseKey(hSystem);
            return FALSE;
        }

        RegCloseKey(hEnum);
        RegCloseKey(hModem);
        RegCloseKey(hServices);
        RegCloseKey(hCurrentControlSet);
        RegCloseKey(hSystem);
        return TRUE;
    } else {
        if (RegOpenKeyExA(hServices, "Class", 0, KEY_READ, &hClass) != ERROR_SUCCESS) {
            RegCloseKey(hServices);
            RegCloseKey(hCurrentControlSet);
            RegCloseKey(hSystem);
            return FALSE;
        }

        if (RegOpenKeyExA(hClass, "Modem", 0, KEY_READ, &hModem) != ERROR_SUCCESS) {
            RegCloseKey(hClass);
            RegCloseKey(hServices);
            RegCloseKey(hCurrentControlSet);
            RegCloseKey(hSystem);
            return FALSE;
        }

        if (RegQueryInfoKeyA(hModem, NULL, NULL, NULL, &cSubKeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) {
            RegCloseKey(hModem);
            RegCloseKey(hClass);
            RegCloseKey(hServices);
            RegCloseKey(hCurrentControlSet);
            RegCloseKey(hSystem);
            return FALSE;
        }

        RegCloseKey(hModem);
        RegCloseKey(hClass);
        RegCloseKey(hServices);
        RegCloseKey(hCurrentControlSet);
        RegCloseKey(hSystem);
        return cSubKeys != 0;
    }
}

// 0x7A58D0
static BOOL CALLBACK CNetworkEnumAddressCallback(REFGUID guidDataType, DWORD dwDataSize, LPCVOID lpData, LPVOID lpContext)
{
    if (IsEqualGUID(guidDataType, DPAID_Modem)) {
        LPCSTR lpAddress = (LPCSTR)lpData;
        while (lstrlenA(lpAddress) != 0) {
            g_pChitin->cNetwork.AddModemAddressToList(lpAddress);
            lpAddress += lstrlenA(lpAddress) + 1;
        }
    }

    return TRUE;
}

// 0x7A5150
void CNetwork::EnumerateModems()
{
    IDirectPlay4A* lpDirectPlay;
    LPVOID lpAddress = NULL;
    HRESULT hr;
    DWORD dwSize = 0;

    m_bModemEnumerated = TRUE;
    m_nTotalModemAddresses = 0;

    if (!HasModems()) {
        return;
    }

    for (INT nIndex = 0; nIndex < m_nTotalServiceProviders; nIndex++) {
        if (IsEqualGUID(m_serviceProviderGuids[nIndex], DPSPGUID_MODEM)) {
            // NOTE: Looks odd, probably some inlining.
            if (m_bServiceProviderEnumerated && nIndex < m_nTotalServiceProviders) {
                m_nServiceProvider = nIndex;
                m_bServiceProviderSelected = TRUE;
            }
        }
    }

    if (CreateDirectPlayAddress(FALSE)) {
        if (CreateDirectPlayInterface(&GUID_NULL, &lpDirectPlay)
            && lpDirectPlay->InitializeConnection(m_pDirectPlayAddress, 0) == DP_OK) {
            if (m_pDirectPlayAddress != NULL) {
                delete m_pDirectPlayAddress;
                // FIXME: `m_pDirectPlayAddress` is not nullified.

                m_bDirectPlayAddressCreated = FALSE;
            }
            m_bConnectionInitialized = TRUE;
        } else {
            if (m_pDirectPlayAddress != NULL) {
                delete m_pDirectPlayAddress;
                // FIXME: `m_pDirectPlayAddress` is not nullified.

                m_bDirectPlayAddressCreated = FALSE;
            }

            m_bConnectionInitialized = FALSE;
        }
    } else {
        m_bConnectionInitialized = FALSE;
    }

    if (m_bConnectionInitialized == TRUE) {
        hr = lpDirectPlay->GetPlayerAddress(0, NULL, &dwSize);
        if (hr == DPERR_BUFFERTOOSMALL) {
            lpAddress = new BYTE[dwSize];
            if (lpAddress != NULL) {
                hr = lpDirectPlay->GetPlayerAddress(0, lpAddress, &dwSize);
            } else {
                hr = DPERR_NOMEMORY;
            }
        }
    } else {
        hr = DP_OK;
    }

    m_bServiceProviderSelected = FALSE;
    m_nServiceProvider = -1;
    m_bConnectionInitialized = FALSE;

    if (lpDirectPlay != NULL) {
        lpDirectPlay->Release();
        lpDirectPlay = NULL;
    }

    if (lpAddress != NULL) {
        if (dwSize != 0) {
            if (hr == DP_OK) {
                EnterCriticalSection(&field_F6A);
                m_lpDirectPlayLobby->EnumAddress(CNetworkEnumAddressCallback,
                    lpAddress,
                    dwSize,
                    NULL);
                LeaveCriticalSection(&field_F6A);
            }
        }
        delete lpAddress;
    }
}

// 0x7A5930
static BOOL CALLBACK CNetworkEnumConnectionsCallback(LPCGUID lpguidSP, LPVOID lpConnection, DWORD dwConnectionSize, LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext)
{
    CString sServiceProviderName;

    if (IsEqualGUID(*lpguidSP, DPSPGUID_TCPIP)) {
        sServiceProviderName = "TCP/IP";
    } else if (IsEqualGUID(*lpguidSP, DPSPGUID_IPX)) {
        sServiceProviderName = "IPX";
    } else if (IsEqualGUID(*lpguidSP, DPSPGUID_MODEM)) {
        sServiceProviderName = "Modem";
    } else if (IsEqualGUID(*lpguidSP, DPSPGUID_SERIAL)) {
        sServiceProviderName = "Serial";
    }

    if (!sServiceProviderName.IsEmpty()) {
        g_pChitin->cNetwork.AddServiceProviderToList(sServiceProviderName,
            *lpguidSP,
            lpConnection,
            dwConnectionSize);
    }

    return TRUE;
}

// 0x7A5340
BOOLEAN CNetwork::EnumerateServiceProviders()
{
    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay != NULL) {
        m_lpDirectPlay->Release();
        m_lpDirectPlay = NULL;
    }

    if (!CreateDirectPlayInterface(&GUID_NULL, &m_lpDirectPlay)) {
        LeaveCriticalSection(&field_F6A);
        return FALSE;
    }

    if (m_lpDirectPlayLobby != NULL) {
        m_lpDirectPlayLobby->Release();
        m_lpDirectPlayLobby = NULL;
    }

    if (!SendMessageA(g_pChitin->GetWnd()->GetSafeHwnd(), 0x405, reinterpret_cast<WPARAM>(&m_lpDirectPlayLobby), 0)) {
        LeaveCriticalSection(&field_F6A);
        return FALSE;
    }

    m_bServiceProviderEnumerated = TRUE;
    m_bServiceProviderSelected = FALSE;
    m_nServiceProvider = -1;
    m_nTotalServiceProviders = 0;
    m_serviceProviderGuids[0] = GUID_NULL;
    m_nTotalServiceProviders++;

    m_lpDirectPlay->EnumConnections(&m_nApplicationGuid, CNetworkEnumConnectionsCallback, NULL, DPCONNECTION_DIRECTPLAY);
    LeaveCriticalSection(&field_F6A);

    for (INT nIndex = 0; nIndex < m_nTotalServiceProviders; nIndex++) {
        if (IsEqualGUID(m_serviceProviderGuids[nIndex], DPSPGUID_MODEM)) {
            g_pChitin->cNetwork.EnumerateModems();
        }
    }

    return TRUE;
}

// 0x7A5480
INT CNetwork::FindModemAddress(const CString& sAddress)
{
    if (!m_bModemEnumerated) {
        return -1;
    }

    for (INT nAddressNumber = 0; nAddressNumber < m_nTotalModemAddresses; nAddressNumber++) {
        if (m_psModemAddress[nAddressNumber].Compare(sAddress) == 0) {
            return nAddressNumber;
        }
    }

    return -1;
}

// 0x7A54E0
BOOLEAN CNetwork::GetModemAddress(INT nAddressNumber, CString& sAddress)
{
    if (!m_bModemEnumerated) {
        return FALSE;
    }

    if (!(nAddressNumber >= 0 && nAddressNumber < m_nTotalModemAddresses)) {
        return FALSE;
    }

    sAddress = m_psModemAddress[nAddressNumber];

    return TRUE;
}

// 0x7A5520
BOOLEAN CNetwork::GetServiceProviderType(INT nServiceProviderNumber, INT& nServiceProviderType)
{
    if (!(nServiceProviderNumber >= 0 && nServiceProviderNumber < m_nTotalServiceProviders)) {
        nServiceProviderType = SERV_PROV_NULL;
        return FALSE;
    }

    nServiceProviderType = SERV_PROV_NULL;

    if (IsEqualGUID(m_serviceProviderGuids[nServiceProviderNumber], DPSPGUID_IPX)) {
        nServiceProviderType = SERV_PROV_IPX;
        return TRUE;
    }

    if (IsEqualGUID(m_serviceProviderGuids[nServiceProviderNumber], DPSPGUID_SERIAL)) {
        nServiceProviderType = SERV_PROV_SERIAL;
        return TRUE;
    }

    if (IsEqualGUID(m_serviceProviderGuids[nServiceProviderNumber], DPSPGUID_MODEM)) {
        nServiceProviderType = SERV_PROV_MODEM;
        return TRUE;
    }

    if (IsEqualGUID(m_serviceProviderGuids[nServiceProviderNumber], DPSPGUID_TCPIP)) {
        nServiceProviderType = SERV_PROV_TCP_IP;
        return TRUE;
    }

    if (IsEqualGUID(m_serviceProviderGuids[nServiceProviderNumber], GUID_NULL)) {
        nServiceProviderType = SERV_PROV_NULL;
    }

    return TRUE;
}

// 0x7A5600
BOOLEAN CNetwork::InitializeConnectionToServiceProvider(BOOLEAN bHostingGame)
{
    if (!CreateDirectPlayAddress(bHostingGame)) {
        return FALSE;
    }

    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay == NULL) {
        if (SendMessageA(g_pChitin->GetWnd()->GetSafeHwnd(), 0x406, (WPARAM)&m_lpDirectPlay, 0) == 0) {
            if (m_pDirectPlayAddress != NULL) {
                delete m_pDirectPlayAddress;
                // FIXME: `m_pDirectPlayAddress` is not nullified.

                m_bDirectPlayAddressCreated = FALSE;
            }

            LeaveCriticalSection(&field_F6A);
            m_bConnectionInitialized = FALSE;
            return FALSE;
        }
    }

    HRESULT hr;
    if (m_nServiceProvider != 0) {
        hr = m_lpDirectPlay->InitializeConnection(m_pDirectPlayAddress, 0);
    }

    LeaveCriticalSection(&field_F6A);

    if (m_nServiceProvider != 0) {
        if (hr != DP_OK && hr != DPERR_ALREADYINITIALIZED) {
            if (m_pDirectPlayAddress != NULL) {
                delete m_pDirectPlayAddress;
                // FIXME: `m_pDirectPlayAddress` is not nullified.

                m_bDirectPlayAddressCreated = FALSE;
            }

            m_bConnectionInitialized = FALSE;
            return FALSE;
        }
    }

    if (m_pDirectPlayAddress != NULL) {
        delete m_pDirectPlayAddress;
        // FIXME: `m_pDirectPlayAddress` is not nullified.

        m_bDirectPlayAddressCreated = FALSE;
    }

    m_bConnectionInitialized = TRUE;
    return TRUE;
}

// 0x7A5720
void CNetwork::RemoveInitializeConnection()
{
    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay != NULL) {
        m_lpDirectPlay->Release();
        m_lpDirectPlay = NULL;
    }

    LeaveCriticalSection(&field_F6A);

    m_bConnectionInitialized = FALSE;
}

// 0x7A5760
BOOLEAN CNetwork::SelectModemAddress(INT nAddressNumber)
{
    if (!m_bModemEnumerated) {
        return FALSE;
    }

    if (!(nAddressNumber >= 0 && nAddressNumber < m_nTotalModemAddresses)) {
        return FALSE;
    }

    m_nModemAddress = nAddressNumber;
    m_bModemAddressSelected = TRUE;

    return TRUE;
}

// 0x7A57A0
BOOLEAN CNetwork::SelectServiceProvider(INT nServiceProviderNumber)
{
    if (!m_bServiceProviderEnumerated) {
        return FALSE;
    }

    if (!(nServiceProviderNumber >= 0 && nServiceProviderNumber < m_nTotalServiceProviders)) {
        return FALSE;
    }

    m_nServiceProvider = nServiceProviderNumber;
    m_bServiceProviderSelected = TRUE;

    return m_bServiceProviderEnumerated;
}

// 0x7A57D0
void CNetwork::SetApplicationOptions(BOOLEAN bKeepAlive, BOOLEAN bMigrateHost)
{
    m_bSessionOptionsDefined = TRUE;
    m_dwSessionFlags = 0;

    if (bKeepAlive == TRUE) {
        m_dwSessionFlags |= DPSESSION_KEEPALIVE;
    }
}

// 0x7A5800
void CNetwork::SetJoinEnabled(BOOLEAN bJoinEnabled)
{
    if (m_bAllowNewConnections != bJoinEnabled) {
        m_bAllowNewConnections = bJoinEnabled;

        g_pChitin->cGameSpy.sub_4D1EC0(TRUE);
    }
}

// 0x7A5830
BOOLEAN CNetwork::SetSerialBaudRate(UINT nBaudRate)
{
    switch (nBaudRate) {
    case 14400:
    case 19200:
    case 38400:
    case 56000:
    case 57600:
    case 115200:
    case 128000:
    case 256000:
        m_nSerialBaudRate = nBaudRate;
        return TRUE;
    }

    return FALSE;
}

// 0x7A5890
BOOLEAN CNetwork::SetSerialPort(UINT nPort)
{
    if (nPort != 0 || nPort > 4) {
        return FALSE;
    }

    m_nSerialPort = nPort;

    return TRUE;
}

// 0x7A58B0
void CNetwork::UnselectModemAddress()
{
    m_bModemAddressSelected = FALSE;
    m_nModemAddress = -1;
}

// 0x7A5A20
void CNetwork::CloseSession(BOOLEAN bAIResponsible)
{
    if (bAIResponsible != TRUE) {
        g_pChitin->OnMultiplayerSessionToClose();
        SleepEx(1000, FALSE);
        if (m_bConnectionEstablished == TRUE) {
            OnCloseSession();
        }
    } else {
        OnCloseSession();
    }
}

// 0x7A5A60
void CNetwork::OnCloseSession()
{
    INT nPlayer;

    if (!m_bConnectionEstablished) {
        return;
    }

    g_pChitin->OnMultiplayerSessionClose();

    if (m_bPlayerCreated == TRUE) {
        EnterCriticalSection(&field_F6A);

        HRESULT hr;
        if (m_lpDirectPlay != NULL) {
            hr = m_lpDirectPlay->DestroyPlayer(m_idLocalPlayer);
        } else {
            hr = DPERR_NOMEMORY;
        }

        LeaveCriticalSection(&field_F6A);

        if (hr == DP_OK) {
            m_bPlayerCreated = FALSE;
        }
    }

    for (nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        m_pPlayerID[nPlayer] = 0;
        m_psPlayerName[nPlayer] = "";
        m_pbPlayerEnumerateFlag[nPlayer] = FALSE;
        m_pbPlayerVisible[nPlayer] = FALSE;
    }

    m_nTotalPlayers = 0;

    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay != NULL) {
        m_lpDirectPlay->Close();
    }

    LeaveCriticalSection(&field_F6A);

    m_bConnectionInitialized = FALSE;
    m_bSessionEnumerated = FALSE;

    for (INT nSession = 0; nSession < CNETWORK_MAX_SESSIONS; nSession++) {
        m_psSessionName[nSession] = "";
        m_pSessionGuid[nSession] = GUID_NULL;
        m_pbSessionPasswordRequired[nSession] = FALSE;
    }

    m_bSessionSelected = FALSE;
    m_nSession = -1;
    m_nTotalSessions = 0;
    m_guidSession = GUID_NULL;
    m_bSessionNameToMake = FALSE;
    m_sSessionNameToMake = "";
    m_bAllowNewConnections = FALSE;
    m_bSessionPasswordEnabled = FALSE;
    m_sSessionPassword = "";

    EnterCriticalSection(&field_F6A);

    if (m_pLastSessionBuffer != NULL) {
        delete m_pLastSessionBuffer;
        m_pLastSessionBuffer = NULL;
    }

    m_dwLastSessionBufferSize = 0;

    LeaveCriticalSection(&field_F6A);

    m_bConnectionEstablished = FALSE;
    m_bIsHost = FALSE;
    field_6EA = 0;
    m_bSessionOptionsDefined = FALSE;
    m_nMaxPlayers = CNETWORK_MAX_PLAYERS;
    m_dwSessionFlags = 0;
    m_bPlayerNameToMake = FALSE;
    m_bPlayerCreated = FALSE;
    m_idLocalPlayer = 0;
    m_sLocalPlayerName = "";
    m_nHostPlayer = -1;
    m_nLocalPlayer = -1;
    m_nTotalPlayers = 0;

    for (nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        m_pPlayerID[nPlayer] = 0;
        m_psPlayerName[nPlayer] = "";
        m_pbPlayerEnumerateFlag[nPlayer] = FALSE;
        m_pbPlayerVisible[nPlayer] = FALSE;
        m_pSlidingWindow[nPlayer].Initialize(nPlayer);
    }

    m_SystemWindow.RemoveFromAllQueues();

    for (int index = 0; index < 6; index++) {
        field_71A[index] = FALSE;
    }
}

// 0x7A5D00
BOOLEAN CNetwork::CheckSessionStatus(BOOLEAN bInThreadLoop)
{
    HRESULT hr;
    DWORD dwSize = m_dwLastSessionBufferSize;
    INT nCurrentPlayers;
    INT nMaxPlayers;

    if (m_bConnectionEstablished != TRUE) {
        return TRUE;
    }

    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay != NULL) {
        hr = m_lpDirectPlay->GetSessionDesc(NULL, &dwSize);
    } else {
        hr = DPERR_NOMEMORY;
    }

    LeaveCriticalSection(&field_F6A);

    if (hr == DPERR_BUFFERTOOSMALL) {
        if (m_dwLastSessionBufferSize < dwSize) {
            EnterCriticalSection(&field_F6A);

            if (m_pLastSessionBuffer != NULL) {
                delete m_pLastSessionBuffer;
                m_pLastSessionBuffer = NULL;
            }

            m_pLastSessionBuffer = new BYTE[dwSize];
            m_dwLastSessionBufferSize = dwSize;

            LeaveCriticalSection(&field_F6A);
        }

        if (m_pLastSessionBuffer == NULL) {
            UTIL_ASSERT_MSG(FALSE, "CNetwork::CheckSessionStatus: Can't create session descriptor.");
        }

        EnterCriticalSection(&field_F6A);

        hr = m_lpDirectPlay->GetSessionDesc(m_pLastSessionBuffer, &dwSize);

        LeaveCriticalSection(&field_F6A);

        nCurrentPlayers = reinterpret_cast<DPSESSIONDESC2*>(m_pLastSessionBuffer)->dwCurrentPlayers;
        nMaxPlayers = reinterpret_cast<DPSESSIONDESC2*>(m_pLastSessionBuffer)->dwMaxPlayers;
    } else {
        if (m_nServiceProvider != 0) {
            nCurrentPlayers = 1;
            nMaxPlayers = 1;
        }
    }

    if (!bInThreadLoop && hr == DP_OK) {
        m_sessionDesc = *reinterpret_cast<DPSESSIONDESC2*>(m_pLastSessionBuffer);

        nMaxPlayers = m_sessionDesc.dwMaxPlayers;
        if (nMaxPlayers <= CNETWORK_MAX_PLAYERS) {
            m_nMaxPlayers = nMaxPlayers;
        }
    }

    if (bInThreadLoop == TRUE && m_bIsHost == TRUE && hr == DP_OK) {
        // TODO: Check.
        if ((nCurrentPlayers != CNETWORK_MAX_PLAYERS
                || nMaxPlayers != CNETWORK_MAX_PLAYERS)
            && nMaxPlayers != nCurrentPlayers + 1) {
            m_nMaxPlayers = max(nCurrentPlayers + 1, CNETWORK_MAX_PLAYERS);
            SetInSessionOptions();
        }
    }

    if (hr == DPERR_NOCONNECTION) {
        if (bInThreadLoop) {
            g_pChitin->OnMultiplayerSessionToClose();
            SleepEx(1000, FALSE);

            if (m_bConnectionEstablished == TRUE) {
                OnCloseSession();
            }
        } else {
            OnCloseSession();
        }

        return FALSE;
    }

    if (nCurrentPlayers != m_nTotalPlayers) {
        EnumeratePlayers(bInThreadLoop);
    }

    return TRUE;
}

// 0x7A6840
static BOOL CALLBACK CNetworkEnumSessionsCallback(LPCDPSESSIONDESC2 lpSessionDesc, LPDWORD lpdwTimeOut, DWORD dwFlags, LPVOID lpContext)
{
    CString sSessionName;

    if ((dwFlags & DPESC_TIMEDOUT) != 0) {
        return FALSE;
    }

    sSessionName = lpSessionDesc->lpszPasswordA;

    CNetwork* pNetwork = &(g_pChitin->cNetwork);
    if (pNetwork->m_nTotalSessions < CNETWORK_MAX_SESSIONS) {
        pNetwork->m_psSessionName[pNetwork->m_nTotalSessions] = sSessionName;
        pNetwork->m_pSessionGuid[pNetwork->m_nTotalSessions] = lpSessionDesc->guidInstance;
        pNetwork->m_pbSessionPasswordRequired[pNetwork->m_nTotalSessions] = (lpSessionDesc->dwFlags & DPSESSION_PASSWORDREQUIRED) != 0;
        pNetwork->m_nTotalSessions++;
    }

    return TRUE;
}

// 0x7A5F00
BOOLEAN CNetwork::EnumerateSessions(BOOLEAN a1, BOOLEAN a2)
{
    DPSESSIONDESC2 dpsd = { 0 };
    dpsd.dwSize = sizeof(dpsd);
    dpsd.guidApplication = m_nApplicationGuid;

    DPCAPS caps = { 0 };
    caps.dwSize = sizeof(caps);

    if (m_lpDirectPlay != NULL) {
        m_lpDirectPlay->GetCaps(&caps, 0);
    }

    DWORD dwTimeout = 0;
    if (!a1 && !a2) {
        dwTimeout = 3000;
    }

    DWORD dwFlags = DPENUMSESSIONS_AVAILABLE | DPENUMSESSIONS_PASSWORDREQUIRED;

    if (!IsEqualGUID(m_serviceProviderGuids[m_nServiceProvider], DPSPGUID_MODEM)
        && !IsEqualGUID(m_serviceProviderGuids[m_nServiceProvider], DPSPGUID_TCPIP)) {
        dwFlags |= DPENUMSESSIONS_RETURNSTATUS;
    }

    if (a2 == TRUE) {
        dwFlags |= DPENUMSESSIONS_STOPASYNC;
    } else if (a1 == TRUE) {
        dwFlags |= DPENUMSESSIONS_ASYNC;
    }

    if (m_bSessionEnumerated == TRUE) {
        for (INT nSession = 0; nSession < m_nTotalSessions; nSession++) {
            m_psSessionName[nSession] = "";
            m_pSessionGuid[nSession] = GUID_NULL;
            m_pbSessionPasswordRequired[nSession] = FALSE;
        }
        m_nTotalSessions = 0;
    }

    EnterCriticalSection(&field_F6A);

    HRESULT hr;
    if (m_lpDirectPlay != NULL) {
        do {
            hr = m_lpDirectPlay->EnumSessions(&dpsd,
                dwTimeout,
                CNetworkEnumSessionsCallback,
                NULL,
                dwFlags);
        } while (hr == DPERR_CONNECTING);
    } else {
        hr = DPERR_NOMEMORY;
    }

    LeaveCriticalSection(&field_F6A);

    if (hr != DP_OK) {
        m_bSessionEnumerated = FALSE;

        for (INT nSession = 0; nSession < CNETWORK_MAX_SESSIONS; nSession++) {
            m_psSessionName[nSession] = "";
            m_pSessionGuid[nSession] = GUID_NULL;
            m_pbSessionPasswordRequired[nSession] = FALSE;
        }

        return FALSE;
    }

    m_bSessionEnumerated = TRUE;

    if (m_bSessionSelected == TRUE) {
        m_bSessionSelected = FALSE;

        for (INT nSession = 0; nSession < CNETWORK_MAX_SESSIONS; nSession++) {
            if (IsEqualGUID(m_pSessionGuid[nSession], m_guidSession)) {
                m_nSession = nSession;
                m_bSessionSelected = TRUE;
            }
        }

        if (!m_bSessionSelected) {
            m_guidSession = GUID_NULL;
        }
    }

    return TRUE;
}

// 0x7A61D0
BOOLEAN CNetwork::sub_7A61D0()
{
    return TRUE;
}

// 0x7A61E0
BOOLEAN CNetwork::GetPasswordRequiredForSelectedSession()
{
    if (!(m_nSession >= 0 && m_nSession < m_nTotalSessions)) {
        return FALSE;
    }

    return m_pbSessionPasswordRequired[m_nSession];
}

// 0x7A6200
BOOLEAN CNetwork::GetSessionName(INT nSession, CString& sSessionName)
{
    if (!(nSession >= 0 && nSession < m_nTotalSessions)) {
        return FALSE;
    }

    sSessionName = m_psSessionName[nSession];

    return TRUE;
}

// 0x7A6230
BOOLEAN CNetwork::GetSessionGUID(INT nSession, GUID& sessionGuid)
{
    if (!(nSession >= 0 && nSession < m_nTotalSessions)) {
        return FALSE;
    }

    sessionGuid = m_pSessionGuid[nSession];

    return TRUE;
}

// 0x7A6270
BOOLEAN CNetwork::HostNewSession()
{
    char szSessionName[MAX_STRING_LENGTH];
    char szSessionPassword[MAX_STRING_LENGTH];

    if (m_bConnectionInitialized != TRUE) {
        return FALSE;
    }

    if (m_bConnectionEstablished) {
        return FALSE;
    }

    if (!m_bSessionNameToMake) {
        return FALSE;
    }

    memset(&m_sessionDesc, 0, sizeof(m_sessionDesc));
    m_sessionDesc.dwFlags = m_dwSessionFlags;
    m_sessionDesc.guidApplication = m_nApplicationGuid;
    m_sessionDesc.dwSize = sizeof(m_sessionDesc);
    m_sessionDesc.dwMaxPlayers = m_nMaxPlayers;

    memset(szSessionName, 0, sizeof(szSessionName));
    strncpy(szSessionName, m_sSessionNameToMake, m_sSessionNameToMake.GetLength());
    m_sessionDesc.lpszSessionNameA = szSessionName;

    if (m_bSessionPasswordEnabled == TRUE) {
        memset(szSessionPassword, 0, sizeof(szSessionPassword));
        strncpy(szSessionPassword, m_sSessionPassword, m_sSessionPassword.GetLength());
        m_sessionDesc.lpszPasswordA = szSessionPassword;
    }

    DWORD dwOpenFlags = DPOPEN_CREATE;
    if (!IsEqualGUID(m_serviceProviderGuids[m_nServiceProvider], DPSPGUID_MODEM)
        && !IsEqualGUID(m_serviceProviderGuids[m_nServiceProvider], DPSPGUID_TCPIP)) {
        dwOpenFlags |= DPOPEN_RETURNSTATUS;
    }

    if (m_nServiceProvider != 0) {
        EnterCriticalSection(&field_F6A);

        HRESULT hr;
        if (m_lpDirectPlay != NULL) {
            do {
                hr = m_lpDirectPlay->Open(&m_sessionDesc, dwOpenFlags);
            } while (hr == DPERR_CONNECTING);
        } else {
            hr = DPERR_NOMEMORY;
        }

        LeaveCriticalSection(&field_F6A);

        if (hr != DP_OK) {
            return FALSE;
        }
    }

    m_bAllowNewConnections = TRUE;
    m_bConnectionEstablished = TRUE;
    m_bIsHost = TRUE;
    m_nHostPlayer = -1;
    m_nTotalPlayers = 0;
    m_nLocalPlayer = -1;

    for (int index = 0; index < CNETWORK_MAX_PLAYERS; index++) {
        m_pPlayerID[index] = 0;
        m_psPlayerName[index] = "";
        m_pbPlayerEnumerateFlag[index] = FALSE;
        m_pbPlayerVisible[index] = FALSE;
        m_pSlidingWindow[index].Initialize(index);
    }

    m_SystemWindow.Initialize(-1);

    g_pChitin->OnMultiplayerSessionOpen(m_sJoinedGame, m_sDroppedGame, m_sLeftGame);

    return TRUE;
}

// 0x7A64B0
BOOLEAN CNetwork::JoinSelectedSession(INT& nErrorCode)
{
    char szSessionPassword[MAX_STRING_LENGTH];

    if (!m_bSessionSelected) {
        nErrorCode = ERROR_CANNOTCONNECT;
        return FALSE;
    }

    memset(&m_sessionDesc, 0, sizeof(m_sessionDesc));
    m_sessionDesc.dwSize = sizeof(m_sessionDesc);
    m_sessionDesc.guidInstance = m_guidSession;

    if (m_bSessionPasswordEnabled) {
        memset(szSessionPassword, 0, sizeof(szSessionPassword));
        strncpy(szSessionPassword, m_sSessionPassword, m_sSessionPassword.GetLength());
        m_sessionDesc.lpszPasswordA = szSessionPassword;
    }

    EnterCriticalSection(&field_F6A);

    HRESULT hr;
    if (m_lpDirectPlay != NULL) {
        do {
            hr = m_lpDirectPlay->Open(&m_sessionDesc, DPOPEN_JOIN);
        } while (hr == DPERR_CONNECTING);
    } else {
        hr = DPERR_NOMEMORY;
    }

    LeaveCriticalSection(&field_F6A);

    if (hr == DPERR_INVALIDPASSWORD) {
        nErrorCode = ERROR_INVALIDPASSWORD;
        return FALSE;
    }

    if (hr != DP_OK) {
        nErrorCode = ERROR_CANNOTCONNECT;
        return FALSE;
    }

    m_bConnectionEstablished = TRUE;
    m_bIsHost = FALSE;
    m_nHostPlayer = -1;
    m_nTotalPlayers = 0;
    m_nLocalPlayer = -1;

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        m_pPlayerID[nPlayer] = 0;
        m_psPlayerName[nPlayer] = "";
        m_pbPlayerEnumerateFlag[nPlayer] = FALSE;
        m_pbPlayerVisible[nPlayer] = FALSE;
        m_pSlidingWindow[nPlayer].Initialize(nPlayer);
    }

    m_SystemWindow.Initialize(-1);

    g_pChitin->OnMultiplayerSessionOpen(m_sJoinedGame, m_sDroppedGame, m_sLeftGame);

    return TRUE;
}

// 0x7A6680
BOOLEAN CNetwork::SelectSession(INT nSession)
{
    if (!m_bSessionEnumerated) {
        return FALSE;
    }

    if (!(nSession >= 0 && nSession < m_nTotalSessions)) {
        return FALSE;
    }

    m_nSession = nSession;
    m_guidSession = m_pSessionGuid[nSession];
    m_bSessionSelected = TRUE;

    return TRUE;
}

// 0x7A66E0
BOOLEAN CNetwork::SetInSessionOptions()
{
    char szSessionName[MAX_STRING_LENGTH];
    char szSessionPassword[MAX_STRING_LENGTH];

    if (m_bConnectionEstablished != TRUE) {
        return FALSE;
    }

    if (m_bIsHost != TRUE) {
        return FALSE;
    }

    m_sessionDesc.dwMaxPlayers = m_nMaxPlayers;

    memset(szSessionName, 0, sizeof(szSessionName));
    strncpy(szSessionName, m_sSessionNameToMake, m_sSessionNameToMake.GetLength());
    m_sessionDesc.lpszSessionNameA = szSessionName;

    if (m_bAllowNewConnections == TRUE) {
        m_sessionDesc.dwFlags = m_dwSessionFlags;
    } else {
        m_sessionDesc.dwFlags = m_dwSessionFlags | DPSESSION_JOINDISABLED | DPSESSION_NEWPLAYERSDISABLED;
    }

    if (m_bSessionPasswordEnabled == TRUE) {
        memset(szSessionPassword, 0, sizeof(szSessionPassword));
        strncpy(szSessionPassword, m_sSessionPassword, m_sSessionPassword.GetLength());
        m_sessionDesc.lpszPasswordA = szSessionPassword;
    }

    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay != NULL) {
        HRESULT hr = m_lpDirectPlay->SetSessionDesc(&m_sessionDesc, 0);
        if (hr != DP_OK) {
            LeaveCriticalSection(&field_F6A);
            return FALSE;
        }
    }

    LeaveCriticalSection(&field_F6A);
    return TRUE;
}

// 0x7A6800
void CNetwork::SetMaxPlayers(INT nMaxPlayers)
{
    if (nMaxPlayers <= 6) {
        m_nMaxPlayers = nMaxPlayers;
    }
}

// 0x7A6820
void CNetwork::UnselectSession()
{
    m_bSessionSelected = FALSE;
    m_nSession = -1;
}

// 0x7A6960
BOOLEAN CNetwork::CreatePlayer(INT& nErrorCode)
{
    if (m_bConnectionEstablished != TRUE) {
        m_bPlayerCreated = FALSE;
        return FALSE;
    }

    if (!m_bPlayerNameToMake) {
        m_bPlayerCreated = FALSE;
        return FALSE;
    }

    if (FindPlayerIDByName(m_sLocalPlayerName, TRUE) != 0) {
        m_bPlayerCreated = FALSE;
        nErrorCode = ERROR_PLAYEREXISTS;
        return FALSE;
    }

    DPNAME dpName;
    dpName.dwSize = sizeof(dpName);
    dpName.dwFlags = 0;
    dpName.lpszShortNameA = NULL;
    dpName.lpszLongNameA = NULL;

    char szPlayerName[256];
    memcpy(szPlayerName, m_sLocalPlayerName.GetBuffer(m_sLocalPlayerName.GetLength()), m_sLocalPlayerName.GetLength());
    szPlayerName[m_sLocalPlayerName.GetLength()] = '\0';

    dpName.lpszShortNameA = szPlayerName;
    dpName.lpszLongNameA = szPlayerName;

    DWORD dwPlayerFlags = 0;
    if (m_bIsHost == TRUE) {
        dwPlayerFlags = DPPLAYER_SERVERPLAYER;
    }

    if (m_nServiceProvider != SERV_PROV_NULL) {
        EnterCriticalSection(&field_F6A);

        HRESULT hr;
        if (m_lpDirectPlay != NULL) {
            hr = m_lpDirectPlay->CreatePlayer(&m_idLocalPlayer,
                &dpName,
                g_pChitin->field_180,
                NULL,
                0,
                dwPlayerFlags);
        } else {
            hr = DPERR_NOMEMORY;
        }

        LeaveCriticalSection(&field_F6A);

        if (hr == DPERR_NOCONNECTION || hr == DPERR_GENERIC) {
            m_bPlayerCreated = FALSE;
            nErrorCode = ERROR_CANNOTCONNECT;
            return FALSE;
        }

        if (hr != DP_OK) {
            m_bPlayerCreated = FALSE;
            nErrorCode = ERROR_CANNOTCREATEPLAYER;
            return FALSE;
        }

        AddPlayerToList(m_idLocalPlayer, m_sLocalPlayerName, m_bIsHost, TRUE);
    } else {
        INT nSlot;
        for (nSlot = 0; nSlot < CNETWORK_MAX_PLAYERS; nSlot++) {
            if (!field_71A[nSlot]) {
                break;
            }
        }

        if (nSlot >= CNETWORK_MAX_PLAYERS) {
            return FALSE;
        }

        m_idLocalPlayer = nSlot + 1;
        field_702[nSlot] = szPlayerName;
        field_71A[nSlot] = TRUE;
    }

    m_bPlayerCreated = TRUE;
    AddPlayerToList(m_idLocalPlayer, m_sLocalPlayerName, m_bIsHost, TRUE);

    nErrorCode = ERROR_NONE;
    return TRUE;
}

// 0x7A6BC0
BOOLEAN CNetwork::AddPlayerToList(PLAYER_ID dpID, const CString& sPlayerName, BOOLEAN bIsHost, BOOLEAN bMakeVisible)
{
    INT nPlayerNumber;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
    // __LINE__: 6907
    UTIL_ASSERT(dpID != 0);

    INT nFound = -1;
    BOOLEAN bFound = FALSE;

    for (nPlayerNumber = 0; nPlayerNumber < CNETWORK_MAX_PLAYERS; nPlayerNumber++) {
        if (bFound) {
            break;
        }

        if (nFound == -1 && m_pPlayerID[nPlayerNumber] == 0) {
            nFound = nPlayerNumber;
        }

        if (m_pPlayerID[nPlayerNumber] != 0) {
            if (dpID == m_pPlayerID[nPlayerNumber]) {
                bFound = TRUE;
                m_pbPlayerEnumerateFlag[nPlayerNumber] = TRUE;

                if (bIsHost == TRUE) {
                    m_nHostPlayer = nPlayerNumber;
                }
            }

            if (m_idLocalPlayer == m_pPlayerID[nPlayerNumber]) {
                m_nLocalPlayer = nPlayerNumber;
            }
        }
    }

    if (bFound) {
        return FALSE;
    }

    for (nPlayerNumber = 0; nPlayerNumber < CNETWORK_MAX_PLAYERS; nPlayerNumber++) {
        if (field_772[nPlayerNumber] == dpID) {
            return FALSE;
        }
    }

    if (nFound == -1) {
        return FALSE;
    }

    m_pPlayerID[nFound] = dpID;
    m_psPlayerName[nFound] = sPlayerName;
    m_pbPlayerVisible[nFound] = bMakeVisible;

    if (bIsHost == TRUE) {
        m_nHostPlayer = nFound;
    }

    if (dpID == m_idLocalPlayer) {
        m_nLocalPlayer = nFound;
    }

    m_pbPlayerEnumerateFlag[nFound] = TRUE;
    m_nTotalPlayers++;

    m_pSlidingWindow[nFound].Initialize(nFound);

    g_pChitin->OnMultiplayerPlayerJoin(m_pPlayerID[nFound], m_psPlayerName[nFound]);

    return TRUE;
}

// 0x7A6D10
BOOLEAN CNetwork::KickPlayer(PLAYER_ID dpID, BOOLEAN bAIResponsible)
{
    BOOLEAN v1;
    BOOLEAN v2;
    CString sKickedPlayerName;
    INT nPlayer;

    for (nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        if (m_pPlayerID[nPlayer] == dpID) {
            sKickedPlayerName = m_psPlayerName[nPlayer];
        }

        if (field_772[nPlayer] == dpID) {
            v1 = TRUE;
        }
    }

    if (RemovePlayerFromList(dpID, bAIResponsible) == TRUE) {
        if (v1 == TRUE) {
            v2 = TRUE;
        } else {
            for (nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
                if (field_772[nPlayer] == 0) {
                    field_772[nPlayer] = dpID;
                    v2 = TRUE;
                    break;
                }

                if (field_772[nPlayer] == dpID) {
                    v2 = TRUE;
                    break;
                }
            }
        }
    } else {
        v2 = FALSE;
    }

    if (v2 == TRUE) {
        CString sText;
        sText.Format(" %s: %s", (LPCSTR)sKickedPlayerName, (LPCSTR)m_sDroppedGame);
        sText.SetAt(0, sText.GetLength() - 1);

        BYTE* pData = CreateCopyMessage((LPCSTR)sText,
            sText.GetLength(),
            0,
            0,
            1);
        if (pData != NULL) {
            m_SystemWindow.AddToIncomingQueue(0,
                m_idLocalPlayer,
                pData,
                sText.GetLength() + 12);
        }
    }

    return v2;
}

// 0x7A6EA0
BOOLEAN CNetwork::RemovePlayerFromList(PLAYER_ID dpID, BOOLEAN bAIResponsible)
{
    INT nPlayerToRemove = -1;
    BOOLEAN bFound = FALSE;

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        if (m_pPlayerID[nPlayer] == dpID) {
            nPlayerToRemove = nPlayer;
            bFound = TRUE;
        }
    }

    if (bFound != TRUE) {
        return bFound;
    }

    if (nPlayerToRemove == m_nHostPlayer) {
        if (bAIResponsible != TRUE) {
            g_pChitin->OnMultiplayerSessionToClose();
            SleepEx(1000, FALSE);

            if (m_bConnectionEstablished == TRUE) {
                OnCloseSession();
            }
        } else {
            OnCloseSession();
        }
    } else {
        g_pChitin->OnMultiplayerPlayerLeave(m_pPlayerID[nPlayerToRemove], m_psPlayerName[nPlayerToRemove]);
        m_pSlidingWindow[nPlayerToRemove].ShutDown();
        m_pPlayerID[nPlayerToRemove] = 0;
        m_psPlayerName[nPlayerToRemove] = "";
        m_pbPlayerEnumerateFlag[nPlayerToRemove] = FALSE;
        m_pbPlayerVisible[nPlayerToRemove] = FALSE;
        m_nTotalPlayers--;
    }

    return TRUE;
}

// 0x7A7510
static BOOL CALLBACK CNetworkEnumPlayersCallback(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext)
{
    CString sPlayerName;

    if (dwPlayerType == DPPLAYERTYPE_PLAYER) {
        sPlayerName = lpName->lpszShortNameA;
        g_pChitin->cNetwork.AddPlayerToList(dpId,
            sPlayerName,
            (dwFlags & DPENUMPLAYERS_SERVERPLAYER) != 0,
            FALSE);
    }

    return TRUE;
}

// 0x7A6F80
void CNetwork::EnumeratePlayers(BOOLEAN bProtectList)
{
    if (!m_bConnectionEstablished) {
        return;
    }

    if (!bProtectList) {
        for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
            m_pPlayerID[nPlayer] = 0;
            m_psPlayerName[nPlayer] = "";
            m_pbPlayerVisible[nPlayer] = FALSE;
        }

        m_nTotalPlayers = 0;
    }

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        m_pbPlayerEnumerateFlag[nPlayer] = FALSE;
    }

    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay != NULL) {
        m_lpDirectPlay->EnumPlayers(NULL,
            CNetworkEnumPlayersCallback,
            NULL,
            0);
        LeaveCriticalSection(&field_F6A);

        if (bProtectList == TRUE) {
            for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
                if (m_pPlayerID[nPlayer] != 0 && !m_pbPlayerEnumerateFlag[nPlayer]) {
                    CString sLeavingGame;
                    CString sLeftPlayerName;

                    sLeftPlayerName = m_psPlayerName[nPlayer];
                    if (RemovePlayerFromList(m_pPlayerID[nPlayer], FALSE) == TRUE) {
                        sLeavingGame.Format(" %s: %s", (LPCSTR)sLeftPlayerName, (LPCSTR)m_sLeftGame);
                        sLeavingGame.SetAt(0, sLeavingGame.GetLength() - 1);

                        BYTE* pSystemMsg = CreateCopyMessage((LPCSTR)sLeavingGame,
                            sLeavingGame.GetLength(),
                            0,
                            0,
                            1);
                        if (pSystemMsg != NULL) {
                            m_SystemWindow.AddToIncomingQueue(0,
                                m_idLocalPlayer,
                                pSystemMsg,
                                sLeavingGame.GetLength() + 12);
                        }
                    } else {
                        for (INT nIndex = 0; nIndex < CNETWORK_MAX_PLAYERS; nIndex++) {
                            if (field_772[nIndex] == m_pPlayerID[nPlayer]) {
                                field_772[nIndex] = 0;
                            }
                        }
                    }
                }
            }
        }
    } else {
        LeaveCriticalSection(&field_F6A);
    }
}

// NOTE: Inlined.
BOOLEAN CNetwork::MakePlayerVisible(PLAYER_ID playerID)
{
    BOOLEAN bResult = FALSE;

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        if (m_pPlayerID[nPlayer] == playerID && !m_pbPlayerVisible[nPlayer]) {
            m_pbPlayerVisible[nPlayer] = TRUE;
            g_pChitin->OnMultiplayerPlayerVisible(playerID);

            bResult = TRUE;
        }
    }

    return bResult;
}

// 0x7A7160
BOOLEAN CNetwork::MakePlayersVisible()
{
    BOOLEAN bResult = FALSE;

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        if (m_pPlayerID[nPlayer] != 0 && !m_pbPlayerVisible[nPlayer]) {
            // NOTE: Uninline.
            bResult |= MakePlayerVisible(m_pPlayerID[nPlayer]);
        }
    }

    return bResult;
}

// 0x7A7220
PLAYER_ID CNetwork::GetPlayerID(INT nPlayerNumber)
{
    if (m_pbPlayerVisible[nPlayerNumber] == TRUE) {
        return m_pPlayerID[nPlayerNumber];
    } else {
        return 0;
    }
}

// 0x7A7240
void CNetwork::GetPlayerName(INT nPlayerNumber, CString& sPlayerName)
{
    if (m_pbPlayerVisible[nPlayerNumber] == TRUE) {
        sPlayerName = m_psPlayerName[nPlayerNumber];
    } else {
        sPlayerName = "";
    }
}

// 0x7A7280
PLAYER_ID CNetwork::GetRawPlayerID(INT nPlayerNumber)
{
    return m_pPlayerID[nPlayerNumber];
}

// 0x7A7290
void CNetwork::GetRawPlayerName(INT nPlayerNumber, CString& sPlayerName)
{
    sPlayerName = m_psPlayerName[nPlayerNumber];
}

// 0x7A72B0
PLAYER_ID CNetwork::FindPlayerIDByName(const CString& sPlayerName, BOOLEAN bInvisible)
{
    for (INT nPlayerNumber = 0; nPlayerNumber < CNETWORK_MAX_PLAYERS; nPlayerNumber++) {
        if (m_psPlayerName[nPlayerNumber].Compare(sPlayerName) == 0) {
            if (bInvisible || m_pbPlayerVisible[nPlayerNumber]) {
                return m_pPlayerID[nPlayerNumber];
            } else {
                return 0;
            }
        }
    }

    return 0;
}

// 0x7A7320
INT CNetwork::FindPlayerLocationByID(PLAYER_ID playerID, BOOLEAN bInvisible)
{
    if (playerID == 0) {
        return -1;
    }

    for (INT nPlayerNumber = 0; nPlayerNumber < CNETWORK_MAX_PLAYERS; nPlayerNumber++) {
        if (m_pPlayerID[nPlayerNumber] == playerID) {
            if (bInvisible || m_pbPlayerVisible[nPlayerNumber]) {
                return nPlayerNumber;
            } else {
                return -1;
            }
        }
    }

    return -1;
}

// 0x7A7360
INT CNetwork::FindPlayerLocationByName(const CString& sPlayerName, BOOLEAN bInvisible)
{
    if (sPlayerName.Compare("") == 0) {
        return -1;
    }

    for (INT nPlayerNumber = 0; nPlayerNumber < CNETWORK_MAX_PLAYERS; nPlayerNumber++) {
        if (m_psPlayerName[nPlayerNumber].Compare(sPlayerName) == 0) {
            if (bInvisible || m_pbPlayerVisible[nPlayerNumber]) {
                return nPlayerNumber;
            } else {
                return -1;
            }
        }
    }

    return -1;
}

// 0x7A7490
static BOOL CALLBACK CNetworkLobbyEnumAddressCallback(REFGUID guidDataType, DWORD dwDataSize, LPCVOID lpData, LPVOID lpContext)
{
    if (IsEqualGUID(guidDataType, DPAID_INet)) {
        g_pChitin->cNetwork.field_792 = CString((LPCSTR)lpData);
    }

    return TRUE;
}

// 0x7A73D0
void CNetwork::sub_7A73D0(CString& a1)
{
    HRESULT hr;
    DWORD dwSize;

    a1 = "";

    if (m_lpDirectPlay != NULL) {
        hr = m_lpDirectPlay->GetPlayerAddress(1, NULL, &dwSize);
        if (hr == DPERR_BUFFERTOOSMALL) {
            LPVOID pData = new BYTE[dwSize];

            // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
            // __LINE__: 7685
            UTIL_ASSERT(pData != NULL);

            hr = m_lpDirectPlay->GetPlayerAddress(1, pData, &dwSize);
            if (hr == DP_OK) {
                if (m_lpDirectPlayLobby != NULL) {
                    field_792 = "";
                    m_lpDirectPlayLobby->EnumAddress(CNetworkLobbyEnumAddressCallback,
                        pData,
                        dwSize,
                        NULL);
                    a1 = field_792;
                }
            }
        }
    }
}

// 0x7A75B0
INT CNetwork::ThreadLoop()
{
    INT nPlayer;

    if (m_bConnectionEstablished == TRUE && m_nServiceProvider != SERV_PROV_NULL) {
        for (nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
            if (m_pPlayerID[nPlayer] != 0
                && m_pSlidingWindow[nPlayer].m_bInitialized == TRUE) {
                m_pSlidingWindow[nPlayer].SendCall();
            }
        }

        SlidingWindowReceive();
        SlidingWindowTimeouts();
        CheckSessionStatus(TRUE);
    }

    DWORD dwNextEvent = GetTickCount() + 10;

    for (nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        if (m_pSlidingWindow[nPlayer].m_bInitialized == TRUE
            && m_pSlidingWindow[nPlayer].m_nNextEvent <= dwNextEvent) {
            dwNextEvent = m_pSlidingWindow[nPlayer].m_nNextEvent;
        }
    }

    INT nDelta = max(min(dwNextEvent - GetTickCount(), 10), 0);

    if (!m_bConnectionEstablished) {
        nDelta = -1;
    }

    return nDelta;
}

// 0x7A7670
void CNetwork::SlidingWindowReceive()
{
    PLAYER_ID dpIDFrom;
    DWORD dwSize;
    BYTE* pData = FetchFrame(dpIDFrom, dwSize);
    while (pData != NULL) {
        BOOLEAN bDeleted = FALSE;

        if (dpIDFrom != DPID_SYSMSG) {
            if (dwSize >= 10) {
                DWORD dwReceivedCrc = pData[9]
                    + (pData[8] << 8)
                    + (pData[7] << 16)
                    + (pData[6] << 24);
                DWORD dwExpectedCrc = 0;

                pData[6] = 0;
                pData[7] = 0;
                pData[8] = 0;
                pData[9] = 0;

                for (DWORD k = 0; k < dwSize; k++) {
                    dwExpectedCrc = m_dwCRC32[(dwExpectedCrc & 0xFF) ^ pData[k]] ^ (dwExpectedCrc >> 8);
                }

                if (dwReceivedCrc == dwExpectedCrc) {
                    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
                        if (m_pPlayerID[nPlayer] == dpIDFrom
                            && m_pPlayerID[nPlayer] != 0
                            && m_pSlidingWindow[nPlayer].m_bInitialized == TRUE) {
                            // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
                            // __LINE__: 7940
                            UTIL_ASSERT_MSG(dpIDFrom != 0, "CNetwork::SlidingWindowReceive:  System message in application read.");

                            m_pSlidingWindow[nPlayer].ReceiveCall(pData, dwSize);
                            bDeleted = TRUE;
                        }
                    }
                }
            }
        } else {
            HandleSystemMessage(pData, dwSize);
        }

        if (!bDeleted) {
            delete pData;
        }

        pData = FetchFrame(dpIDFrom, dwSize);
    }
}

// 0x7A77D0
void CNetwork::SlidingWindowTimeouts()
{
    if (m_bConnectionEstablished == TRUE) {
        for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
            if (m_pPlayerID[nPlayer] != 0
                && m_pSlidingWindow[nPlayer].m_bInitialized == TRUE) {
                m_pSlidingWindow[nPlayer].TimeoutCall();
                if (m_nHostPlayer == m_nLocalPlayer) {
                    if (m_nHostPlayer != nPlayer
                        && m_pSlidingWindow[nPlayer].m_nPlayerTimeout < GetTickCount()) {
                        KickPlayer(m_pPlayerID[nPlayer], FALSE);
                    }
                } else {
                    if (m_nHostPlayer == nPlayer
                        && m_pSlidingWindow[nPlayer].m_nPlayerTimeout < GetTickCount()) {
                        g_pChitin->OnMultiplayerSessionToClose();
                        SleepEx(1000, FALSE);
                        if (m_bConnectionEstablished == TRUE) {
                            OnCloseSession();
                        }
                    }
                }
            }
        }
    }
}

// 0x7A7890
BYTE* CNetwork::FetchFrame(PLAYER_ID& idFrom, DWORD& dwSize)
{
    BYTE* pData = new BYTE[MINIMAL_PACKET_SIZE];
    if (pData == NULL) {
        return NULL;
    }

    HRESULT hr;
    DPID from;
    DPID to;
    DWORD dwDataSize = MINIMAL_PACKET_SIZE;

    EnterCriticalSection(&(g_pChitin->cNetwork.field_F6A));

    while (1) {
        hr = g_pChitin->cNetwork.m_lpDirectPlay->Receive(&from,
            &to,
            0,
            pData,
            &dwDataSize);
        if (hr != DPERR_BUFFERTOOSMALL) {
            break;
        }

        delete pData;

        pData = new BYTE[dwDataSize];
        if (pData == NULL) {
            hr = DPERR_NOMEMORY;
            break;
        }
    }

    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F6A));

    if (hr != DP_OK) {
        dwSize = 0;
        delete pData;
        return NULL;
    }

    idFrom = from;
    dwSize = dwDataSize;
    return pData;
}

// 0x7A7980
BOOLEAN CNetwork::HandleSystemMessage(BYTE* pData, DWORD dwSize)
{
    switch (reinterpret_cast<DPMSG_GENERIC*>(pData)->dwType) {
    case DPSYS_CREATEPLAYERORGROUP:
        if (1) {
            DPMSG_CREATEPLAYERORGROUP* msg = reinterpret_cast<DPMSG_CREATEPLAYERORGROUP*>(pData);

            CString sText;
            CString sPlayerName;

            PLAYER_ID dpId = msg->dpId;

            sPlayerName = msg->dpnName.lpszShortNameA;
            if (AddPlayerToList(dpId, sPlayerName, FALSE, FALSE) == TRUE) {
                sText.Format(" %s: %s", (LPCSTR)sPlayerName, (LPCSTR)m_sJoinedGame);
                sText.SetAt(0, sText.GetLength() - 1);

                BYTE* pMessage = CreateCopyMessage(sText,
                    sText.GetLength(),
                    0,
                    0,
                    1);
                if (pMessage != NULL) {
                    m_SystemWindow.AddToIncomingQueue(0,
                        m_idLocalPlayer,
                        pMessage,
                        sText.GetLength() + 12);
                }
            }
        }
        return TRUE;
    case DPSYS_DESTROYPLAYERORGROUP:
        if (1) {
            DPMSG_DESTROYPLAYERORGROUP* msg = reinterpret_cast<DPMSG_DESTROYPLAYERORGROUP*>(pData);

            CString sText;
            CString sPlayerName;

            PLAYER_ID dpId = msg->dpId;

            sPlayerName = msg->dpnName.lpszShortNameA;
            if (RemovePlayerFromList(dpId, FALSE) == TRUE) {
                sText.Format(" %s: %s", (LPCSTR)sPlayerName, (LPCSTR)m_sLeftGame);
                sText.SetAt(0, sText.GetLength() - 1);

                BYTE* pMessage = CreateCopyMessage(sText,
                    sText.GetLength(),
                    0,
                    0,
                    1);
                if (pMessage != NULL) {
                    m_SystemWindow.AddToIncomingQueue(0,
                        m_idLocalPlayer,
                        pMessage,
                        sText.GetLength() + 12);
                }
            } else {
                for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
                    if (field_772[nPlayer] == dpId) {
                        field_772[nPlayer] = 0;
                    }
                }
            }
        }
        return TRUE;
    case DPSYS_SESSIONLOST:
        g_pChitin->OnMultiplayerSessionToClose();
        SleepEx(1000, FALSE);
        if (m_bConnectionEstablished == TRUE) {
            OnCloseSession();
        }
        return TRUE;
    case DPSYS_HOST:
    case DPSYS_SETPLAYERORGROUPNAME:
    case DPSYS_SETSESSIONDESC:
        return TRUE;
    }

    return FALSE;
}

// 0x7A7BF0
void CNetwork::AddMessageToWindow(PLAYER_ID idTo, DWORD dwFlags, BYTE* pData, DWORD dwSize)
{
    // NOTE: Uninline.
    INT nPlayer = FindPlayerLocationByID(idTo, TRUE);

    if (nPlayer == -1) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
        // __LINE__: 8339
        UTIL_ASSERT_MSG(FALSE, "CNetwork::AddMessageToWindow: Invalid SendTo ID.");
    }

    BOOLEAN bRaw = (dwFlags & SEND_RAW) != 0;

    INT nPackets;
    if (dwSize + 16 >= MAXIMAL_PACKET_SIZE) {
        nPackets = dwSize / MAXIMAL_PACKET_SIZE + 1;
        while (nPackets >= 2 && dwSize - (nPackets - 1) * MAXIMAL_PACKET_SIZE < MINIMAL_PACKET_SIZE) {
            nPackets--;
        }
    } else {
        nPackets = 1;
    }

    DWORD dwOffset = 0;
    DWORD dwRemainingSize = dwSize;
    for (INT nPacket = 0; nPacket < nPackets; nPacket++) {
        DWORD dwChunkSize = MAXIMAL_PACKET_SIZE;
        if (nPacket == nPackets - 1) {
            dwChunkSize = dwRemainingSize;
        }

        if (nPacket != 0) {
            BYTE* pMessage = CreateCopyMessage(pData + dwOffset,
                dwChunkSize,
                bRaw,
                TRUE,
                0);

            EnterCriticalSection(&(g_pChitin->cNetwork.field_F52));

            CNETWORKWINDOW_QUEUEENTRY* pEntry = new CNETWORKWINDOW_QUEUEENTRY();
            pEntry->idFrom = m_idLocalPlayer;
            pEntry->idTo = idTo;
            pEntry->pData = pMessage;
            pEntry->dwSize = dwChunkSize + 12;
            m_pSlidingWindow[nPlayer].m_lQueueOutgoingMessages.AddTail(pEntry);

            LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
        } else {
            BYTE* pMessage = CreateCopyMessage(pData + dwOffset,
                dwChunkSize,
                bRaw,
                TRUE,
                nPackets);

            EnterCriticalSection(&(g_pChitin->cNetwork.field_F52));

            CNETWORKWINDOW_QUEUEENTRY* pEntry = new CNETWORKWINDOW_QUEUEENTRY();
            pEntry->idFrom = m_idLocalPlayer;
            pEntry->idTo = idTo;
            pEntry->pData = pMessage;
            pEntry->dwSize = dwChunkSize + 16;
            m_pSlidingWindow[nPlayer].m_lQueueOutgoingMessages.AddTail(pEntry);

            LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
        }

        dwOffset += dwChunkSize;
        dwRemainingSize -= dwChunkSize;
    }
}

// 0x7A7DF0
BYTE* CNetwork::CreateCopyMessage(const void* lpData, DWORD dwDataSize, BOOLEAN bCompressed, unsigned char a4, INT nFrame)
{
    DWORD dwNewDataSize;
    BYTE* pByteNewData;

    if (a4 == TRUE) {
        if (nFrame == 0) {
            dwNewDataSize = dwDataSize + 12;
        } else {
            dwNewDataSize = dwDataSize + 16;
        }

        pByteNewData = new BYTE[dwNewDataSize];

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
        // __LINE__: 8516
        UTIL_ASSERT_MSG(pByteNewData != NULL, "CNetwork::CreateCopyMessage: new failed.");

        pByteNewData[5] = bCompressed;

        if (nFrame == 0) {
            memcpy(pByteNewData + 10, (LPCSTR)JB, 2);
            memcpy(pByteNewData + 12, lpData, dwDataSize);
        } else {
            memcpy(pByteNewData + 10, (LPCSTR)JM, 2);
            pByteNewData[12] = static_cast<BYTE>(nFrame >> 8);
            pByteNewData[13] = static_cast<BYTE>(nFrame);
            pByteNewData[14] = static_cast<BYTE>(dwDataSize >> 8);
            pByteNewData[15] = static_cast<BYTE>(dwDataSize);
            memcpy(pByteNewData + 16, lpData, dwDataSize);
        }
    } else {
        dwNewDataSize = dwDataSize + 12;
        pByteNewData = new BYTE[dwNewDataSize];
        if (pByteNewData != NULL) {
            pByteNewData[0] = 3;
            pByteNewData[1] = 3;
            pByteNewData[2] = 3;
            pByteNewData[5] = bCompressed;
            memcpy(pByteNewData + 10, (LPCSTR)MG, 2);
            memcpy(pByteNewData + 12, lpData, dwDataSize);
        }
    }

    return pByteNewData;
}

// 0x7A7F20
BYTE* CNetwork::FetchMessage(INT& nMsgFrom, INT& nMsgTo, DWORD& dwSize)
{
    PLAYER_ID idDPFrom;
    PLAYER_ID idDPTo;
    BYTE* pData;
    BYTE* pUncompressedData;
    BOOLEAN bCompressed;

    if (m_SystemWindow.m_bInitialized == TRUE
        && m_SystemWindow.CheckIncomingQueue() == TRUE) {
        pData = m_SystemWindow.RemoveFromIncomingQueue(idDPFrom,
            idDPTo,
            dwSize,
            bCompressed);

        nMsgFrom = -1;
        nMsgTo = m_nLocalPlayer;

        if (!bCompressed) {
            return pData;
        }

        pUncompressedData = UncompressMessage(pData, dwSize);
        delete pData;
        return pUncompressedData;
    }

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        if (m_pPlayerID[nPlayer] != 0
            && m_pSlidingWindow[nPlayer].m_bInitialized
            && m_pSlidingWindow[nPlayer].CheckIncomingQueue() == TRUE) {
            pData = m_pSlidingWindow[nPlayer].RemoveFromIncomingQueue(idDPFrom,
                idDPTo,
                dwSize,
                bCompressed);

            nMsgFrom = nPlayer;
            nMsgTo = m_nLocalPlayer;

            if (!bCompressed) {
                return pData;
            }

            pUncompressedData = UncompressMessage(pData, dwSize);
            delete pData;
            return pUncompressedData;
        }
    }

    return NULL;
}

// 0x7A8060
BYTE* CNetwork::FetchSpecificMessage(const CString& sPlayerName, BYTE nSpecMsgType, BYTE nSpecMsgSubType, DWORD& dwSize)
{
    // NOTE: Uninline.
    INT nPlayer = FindPlayerLocationByName(sPlayerName, FALSE);
    if (nPlayer == -1) {
        return NULL;
    }

    if (m_pSlidingWindow[nPlayer].m_bInitialized != TRUE) {
        return NULL;
    }

    if (m_pSlidingWindow[nPlayer].CheckIncomingQueueSpecific(nSpecMsgType, nSpecMsgSubType) != TRUE) {
        return NULL;
    }

    PLAYER_ID idDPFrom;
    PLAYER_ID idDPTo;
    DWORD dwDataSize;
    BOOLEAN bCompressed;
    BYTE* pData = m_pSlidingWindow[nPlayer].RemoveFromIncomingQueueSpecific(nSpecMsgType,
        nSpecMsgSubType,
        idDPFrom,
        idDPTo,
        dwDataSize,
        bCompressed);
    if (!bCompressed) {
        return pData;
    }

    BYTE* pUncompressedData = UncompressMessage(pData, dwDataSize);
    delete pData;
    return pUncompressedData;
}

// NOTE: Trailing underscore prevents clashes with `PeekMessage` macro.
//
// 0x7A8150
BOOLEAN CNetwork::PeekMessage_()
{
    if (!m_bConnectionEstablished) {
        return FALSE;
    }

    if (m_SystemWindow.m_bInitialized == TRUE
        && m_SystemWindow.CheckIncomingQueue() == TRUE) {
        return TRUE;
    }

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        if (m_pPlayerID[nPlayer] != 0
            && m_pSlidingWindow[nPlayer].m_bInitialized == TRUE
            && m_pSlidingWindow[nPlayer].CheckIncomingQueue() == TRUE) {
            return TRUE;
        }
    }

    return FALSE;
}

// 0x7A81C0
BOOLEAN CNetwork::PeekSpecificMessage(const CString& sPlayerName, BYTE nSpecMsgType, BYTE nSpecMsgSubType)
{
    if (sPlayerName == "") {
        return FALSE;
    }

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        if (m_psPlayerName[nPlayer] == sPlayerName
            && m_pbPlayerVisible[nPlayer] == TRUE) {
            // NOTE: Probably inlining.
            if (nPlayer != -1
                && m_pSlidingWindow[nPlayer].m_bInitialized == TRUE
                && m_pSlidingWindow[nPlayer].CheckIncomingQueueSpecific(nSpecMsgType, nSpecMsgSubType) == TRUE) {
                return TRUE;
            } else {
                return FALSE;
            }
        }
    }

    return FALSE;
}

// NOTE: Trailing underscore prevents clashes with `SendMessage` macro.
//
// 0x7A8250
BOOLEAN CNetwork::SendMessage_(const CString& sPlayerName, DWORD dwFlags, BYTE* pData, DWORD dwSize)
{
    INT nPlayer;

    if (m_nServiceProvider == SERV_PROV_NULL) {
        return TRUE;
    }

    BYTE* pCompressedData;
    BOOLEAN bCompressed = FALSE;

    PLAYER_ID idTo = 0;
    if ((dwFlags & SEND_ALL_PLAYERS) == 0) {
        // NOTE: Uninline.
        idTo = FindPlayerIDByName(sPlayerName, (dwFlags & SEND_JOINING_PLAYERS) != 0);

        if (idTo == 0) {
            return FALSE;
        }
    }

    if ((dwFlags & SEND_RAW) == 0 && dwSize >= MINIMAL_PACKET_SIZE) {
        DWORD nCompressedLength = dwSize + 16;

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
        // __LINE__: 8937
        UTIL_ASSERT_MSG(nCompressedLength <= STATIC_MESSAGE_SIZE, "CNetwork::SendMessage() method, nCompressedLength > STATIC_MESSAGE_SIZE.");

        pCompressedData = CNetwork::STATIC_MESSAGE_BUFFER;
        bCompressed = TRUE;

        int err = CUtil::Compress(pCompressedData + 4,
            &nCompressedLength,
            pData,
            dwSize,
            7);

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
        // __LINE__: 8944
        UTIL_ASSERT(err == 0);

        nCompressedLength += 4;

        pCompressedData[0] = static_cast<BYTE>(dwSize >> 24);
        pCompressedData[1] = static_cast<BYTE>(dwSize >> 16);
        pCompressedData[2] = static_cast<BYTE>(dwSize >> 8);
        pCompressedData[3] = static_cast<BYTE>(dwSize);
    }

    if (m_lpDirectPlay == NULL || m_idLocalPlayer == idTo) {
        return FALSE;
    }

    if (idTo != 0) {
        if (bCompressed) {
            AddMessageToWindow(idTo, dwFlags | SEND_RAW, pCompressedData, dwSize);
        } else {
            AddMessageToWindow(idTo, dwFlags, pData, dwSize);
        }
    } else {
        for (nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
            if (((dwFlags & SEND_JOINING_PLAYERS) != 0 || m_pbPlayerVisible[nPlayer])
                && m_pPlayerID[nPlayer] != 0
                && m_pPlayerID[nPlayer] != m_idLocalPlayer) {
                if (bCompressed) {
                    AddMessageToWindow(m_pPlayerID[nPlayer],
                        dwFlags | SEND_RAW,
                        pCompressedData,
                        dwSize);
                } else {
                    AddMessageToWindow(m_pPlayerID[nPlayer],
                        dwFlags,
                        pData,
                        dwSize);
                }
            }
        }
    }

    return TRUE;
}

// 0x7A84F0
BOOLEAN CNetwork::SendSpecificMessage(const CString& sPlayerName, DWORD dwFlags, BYTE nSpecMsgType, BYTE nSpecMsgSubType, LPVOID lpData, DWORD nDataSize)
{
    BOOLEAN bSuccess;

    if (m_nServiceProvider == SERV_PROV_NULL) {
        return TRUE;
    }

    BYTE* pMessage = STATIC_MESSAGE_BUFFER;
    BYTE* pMessageDynamicBuffer = NULL;
    DWORD dwSize = nDataSize + SPEC_MSG_HEADER_LENGTH;
    if ((dwFlags & SEND_RAW) == 0 && nDataSize >= MINIMAL_PACKET_SIZE) {
        dwSize += 16;
        if (dwSize > STATIC_MESSAGE_SIZE) {
            pMessageDynamicBuffer = new BYTE[dwSize];
            pMessage = pMessageDynamicBuffer;

            // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
            // __LINE__: 9156
            UTIL_ASSERT(pMessage != NULL);
        }

        pMessage[SPEC_MSG_FLAG] = SPEC_MSG_FLAG_ENABLED;
        pMessage[SPEC_MSG_TYPE] = nSpecMsgType;
        pMessage[SPEC_MSG_SUBTYPE] = nSpecMsgSubType;

        int err = CUtil::Compress(pMessage + 7,
            &dwSize,
            reinterpret_cast<BYTE*>(lpData),
            nDataSize,
            7);

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
        // __LINE__: 9166
        UTIL_ASSERT(err == 0);

        pMessage[SPEC_MSG_HEADER_LENGTH] = static_cast<BYTE>(nDataSize >> 24);
        pMessage[SPEC_MSG_HEADER_LENGTH + 1] = static_cast<BYTE>(nDataSize >> 16);
        pMessage[SPEC_MSG_HEADER_LENGTH + 2] = static_cast<BYTE>(nDataSize >> 8);
        pMessage[SPEC_MSG_HEADER_LENGTH + 3] = static_cast<BYTE>(nDataSize);

        bSuccess = SendMessage_(sPlayerName,
            dwFlags | SEND_RAW | SEND_GUARANTEED,
            pMessage,
            dwSize + 7);
    } else {
        if (dwSize > STATIC_MESSAGE_SIZE) {
            DYNAMIC_MESSAGE_SIZE = dwSize;

            pMessageDynamicBuffer = new BYTE[dwSize];
            pMessage = pMessageDynamicBuffer;

            // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
            // __LINE__: 9191
            UTIL_ASSERT(pMessage != NULL);
        }

        pMessage[SPEC_MSG_FLAG] = SPEC_MSG_FLAG_ENABLED;
        pMessage[SPEC_MSG_TYPE] = nSpecMsgType;
        pMessage[SPEC_MSG_SUBTYPE] = nSpecMsgSubType;

        if (nDataSize != 0) {
            // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
            // __LINE__: 9206
            UTIL_ASSERT_MSG(lpData != NULL, "CNetwork::SendSpecificMessage:  Data size != 0, message = NULL.");
            memcpy(pMessage + SPEC_MSG_HEADER_LENGTH, lpData, nDataSize);
        }

        bSuccess = SendMessage_(sPlayerName,
            dwFlags | SEND_GUARANTEED,
            pMessage,
            dwSize);
    }

    if (pMessageDynamicBuffer != NULL) {
        delete pMessageDynamicBuffer;
    }

    return bSuccess;
}

// 0x7A86E0
BYTE* CNetwork::UncompressMessage(BYTE* pData, DWORD& dwSize)
{
    DWORD dwUncompressedSize;
    BYTE* pUncompressedData;
    int err;

    if (pData[SPEC_MSG_FLAG] == 255) {
        dwUncompressedSize = (pData[SPEC_MSG_HEADER_LENGTH] << 24)
            + (pData[SPEC_MSG_HEADER_LENGTH + 1] << 16)
            + (pData[SPEC_MSG_HEADER_LENGTH + 2] << 8)
            + pData[SPEC_MSG_HEADER_LENGTH + 3];

        pUncompressedData = new BYTE[dwUncompressedSize + SPEC_MSG_HEADER_LENGTH];
        pUncompressedData[SPEC_MSG_FLAG] = pData[SPEC_MSG_FLAG];
        pUncompressedData[SPEC_MSG_TYPE] = pData[SPEC_MSG_TYPE];
        pUncompressedData[SPEC_MSG_SUBTYPE] = pData[SPEC_MSG_SUBTYPE];

        err = CUtil::Uncompress(pUncompressedData + SPEC_MSG_HEADER_LENGTH,
            &dwUncompressedSize,
            pData + 7,
            dwSize - 7);
        if (err != 0) {
            if (err != -5) {
                CString sError;
                sError.Format("z_uncompress returned %d", err);
                sError.Format("Uncompress in network layer failed.  Error code %d.\n", err);
                sError += "Please report this error and look at icewind2.log file, too!";

                // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
                // __LINE__: 9320
                UTIL_ASSERT_MSG(FALSE, (LPCSTR)sError);
            }

            delete pUncompressedData;

            dwUncompressedSize = 2 * ((pData[SPEC_MSG_HEADER_LENGTH] << 24) + (pData[SPEC_MSG_HEADER_LENGTH + 1] << 16) + (pData[SPEC_MSG_HEADER_LENGTH + 2] << 8) + pData[SPEC_MSG_HEADER_LENGTH + 3]);

            pUncompressedData = new BYTE[dwUncompressedSize + SPEC_MSG_HEADER_LENGTH];
            pUncompressedData[SPEC_MSG_FLAG] = pData[SPEC_MSG_FLAG];
            pUncompressedData[SPEC_MSG_TYPE] = pData[SPEC_MSG_TYPE];
            pUncompressedData[SPEC_MSG_SUBTYPE] = pData[SPEC_MSG_SUBTYPE];

            err = CUtil::Uncompress(pUncompressedData + SPEC_MSG_HEADER_LENGTH,
                &dwUncompressedSize,
                pData + 7,
                dwSize - 7);
            if (err != 0) {
                CString sError;

                // FIXME: Useless.
                sError.Format("z_uncompress returned %d", err);

                sError.Format("Uncompress in network layer failed.  Error code %d.\n", err);
                sError += "Please report this error and look at icewind2.log file, too!";

                // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
                // __LINE__: 9359
                UTIL_ASSERT_MSG(FALSE, (LPCSTR)sError);
            }

            // FIXME: Not used.
            CString sError;
            sError.Format("Network Layer: size of %d succeeded, half size failed\n", err);
        }

        dwSize = dwUncompressedSize + SPEC_MSG_HEADER_LENGTH;
        return pUncompressedData;
    } else {
        dwUncompressedSize = (pData[0] << 24)
            + (pData[1] << 16)
            + (pData[2] << 8)
            + pData[3];

        pUncompressedData = new BYTE[dwUncompressedSize + SPEC_MSG_HEADER_LENGTH];

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
        // __LINE__: 9384
        UTIL_ASSERT(pUncompressedData != NULL);

        err = CUtil::Uncompress(pUncompressedData,
            &dwUncompressedSize,
            pData + 4,
            dwSize - 4);
        if (err != 0) {
            if (err != -5) {
                CString sError;

                // FIXME: Useless.
                sError.Format("z_uncompress returned %d", err);

                sError.Format("Uncompress in network layer failed.  Error code %d.\n", err);
                sError += "Please report this error and look at icewind2.log file, too!";

                // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
                // __LINE__: 9396
                UTIL_ASSERT_MSG(FALSE, (LPCSTR)sError);
            }

            delete pUncompressedData;

            dwUncompressedSize = 2 * ((pData[0] << 24) + (pData[1] << 16) + (pData[2] << 8) + pData[3]);

            pUncompressedData = new BYTE[dwUncompressedSize];

            // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
            // __LINE__: 9419
            UTIL_ASSERT(pUncompressedData != NULL);

            err = CUtil::Uncompress(pUncompressedData,
                &dwUncompressedSize,
                pData + 4,
                dwSize - 4);
            if (err != 0) {
                CString sError;

                // FIXME: Useless.
                sError.Format("z_uncompress returned %d", err);

                sError.Format("Uncompress in network layer failed.  Error code %d.\n", err);
                sError += "Please report this error and look at icewind2.log file, too!";

                // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
                // __LINE__: 9431
                UTIL_ASSERT_MSG(FALSE, (LPCSTR)sError);
            }

            // FIXME: Not used.
            CString sError;
            sError.Format("Network Layer: size of %d succeeded, half size failed\n", err);
        }

        dwSize = dwUncompressedSize;
        return pUncompressedData;
    }
}

// 0x452B40
INT CNetwork::GetServiceProvider()
{
    return m_nServiceProvider;
}

// 0x452B50
BOOLEAN CNetwork::GetSessionOpen()
{
    return m_bConnectionEstablished;
}

// 0x452B60
BOOLEAN CNetwork::GetSessionHosting()
{
    return m_bIsHost;
}

// NOTE: Inlined.
PLAYER_ID CNetwork::GetHostPlayerID()
{
    return m_nHostPlayer != -1 ? m_pPlayerID[m_nHostPlayer] : 0;
}

// NOTE: Inlined.
void CNetwork::GetHostPlayerName(CString& sHostName)
{
    if (m_nHostPlayer != -1) {
        sHostName = m_psPlayerName[m_nHostPlayer];
    } else {
        sHostName = "";
    }
}

#if DPLAY_COMPAT

static HRESULT WINAPI FakeDirectPlayCreate(LPGUID, LPDIRECTPLAY*, IUnknown*)
{
    return DPERR_GENERIC;
}

static HRESULT WINAPI FakeDirectPlayLobbyCreateA(LPGUID, LPDIRECTPLAYLOBBYA*, IUnknown*, LPVOID, DWORD)
{
    return DPERR_GENERIC;
}

void CNetwork::InitDirectPlay()
{
    hDirectPlayDLL = LoadLibraryA("dplayx");
    if (hDirectPlayDLL != NULL) {
        DirectPlayCreate = (DirectPlayCreateFunc*)GetProcAddress(hDirectPlayDLL, "DirectPlayCreate");
        DirectPlayLobbyCreateA = (DirectPlayLobbyCreateFunc*)GetProcAddress(hDirectPlayDLL, "DirectPlayLobbyCreateA");
    }

    if (DirectPlayCreate == NULL) {
        DirectPlayCreate = FakeDirectPlayCreate;
    }

    if (DirectPlayLobbyCreateA == NULL) {
        DirectPlayLobbyCreateA = FakeDirectPlayLobbyCreateA;
    }
}

void CNetwork::FreeDirectPlay()
{
    if (hDirectPlayDLL != NULL) {
        FreeLibrary(hDirectPlayDLL);
        hDirectPlayDLL = NULL;
    }
}

#endif
