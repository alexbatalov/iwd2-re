#include "CCrypt.h"

// 0x85EB88
const CHAR CCrypt::ENCRYPT_HEADER[] = {
    '\xFF',
    '\xFF',
};

// 0x85EB8C
const CHAR CCrypt::ENCRYPT_KEY[] = {
    '\x88',
    '\xA8',
    '\x8F',
    '\xBA',
    '\x8A',
    '\xD3',
    '\xB9',
    '\xF5',
    '\xED',
    '\xB1',
    '\xCF',
    '\xEA',
    '\xAA',
    '\xE4',
    '\xB5',
    '\xFB',
    '\xEB',
    '\x82',
    '\xF9',
    '\x90',
    '\xCA',
    '\xC9',
    '\xB5',
    '\xE7',
    '\xDC',
    '\x8E',
    '\xB7',
    '\xAC',
    '\xEE',
    '\xF7',
    '\xE0',
    '\xCA',
    '\x8E',
    '\xEA',
    '\xCA',
    '\x80',
    '\xCE',
    '\xC5',
    '\xAD',
    '\xB7',
    '\xC4',
    '\xD0',
    '\x84',
    '\x93',
    '\xD5',
    '\xF0',
    '\xEB',
    '\xC8',
    '\xB4',
    '\x9D',
    '\xCC',
    '\xAF',
    '\xA5',
    '\x95',
    '\xBA',
    '\x99',
    '\x87',
    '\xD2',
    '\x9D',
    '\xE3',
    '\x91',
    '\xBA',
    '\x90',
    '\xCA',
};

// 0x7C87B0
BOOL CCrypt::DecryptText(CHAR* pszText, INT& nSize)
{
    INT nKeySize = static_cast<INT>(sizeof(ENCRYPT_KEY));
    INT nHeaderSize = static_cast<INT>(sizeof(ENCRYPT_HEADER));

    if (nSize < nKeySize) {
        return FALSE;
    }

    if (memcmp(pszText, ENCRYPT_HEADER, nHeaderSize) != 0) {
        return FALSE;
    }

    nSize -= nHeaderSize;

    for (INT i = 0; i < nSize; i++) {
        pszText[i] = pszText[i + 2];
    }

    INT nResult = 0;
    for (INT j = 0; j < nSize; j++) {
        pszText[j] ^= ENCRYPT_KEY[nResult];
        nResult += 1;
        nResult %= nKeySize;
    }

    return TRUE;
}
