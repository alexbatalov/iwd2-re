#include "CSearchBitmap.h"

// 0x84EBE0
const BYTE CSearchRequest::STATE_WAITING = 0;

// 0x84EBE1
const BYTE CSearchRequest::STATE_PROCESSING = 1;

// 0x84EBE2
const BYTE CSearchRequest::STATE_NO_TARGET = 2;

// 0x84EBE3
const BYTE CSearchRequest::STATE_DONE = 3;

// 0x84EBE4
const BYTE CSearchRequest::STATE_STALE = 4;

// 0x84EBE5
const BYTE CSearchRequest::STATE_ERROR = 5;

// 0x8AE1D8
LONG CSearchRequest::MINNODES = 500;

// 0x8AE1DC
LONG CSearchRequest::MAXNODES = 4000;

// 0x8AE1E0
LONG CSearchRequest::MINNODESBACK = 200;

// 0x8AE1E4
LONG CSearchRequest::MAXNODESBACK = 1000;

// 0x5492E0
void SearchThreadMain(void* userInfo)
{
    // TODO: Incomplete.
}
