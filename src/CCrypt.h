#ifndef CCRYPT_H_
#define CCRYPT_H_

#include "mfc.h"

class CCrypt {
public:
    static const CHAR ENCRYPT_HEADER[];
    static const CHAR ENCRYPT_KEY[];

    BOOL DecryptText(CHAR* pszText, INT& nSize);
};

#endif /* CCRYPT_H_ */
