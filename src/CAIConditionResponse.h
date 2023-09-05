#ifndef CAICONDITIONRESPONSE_H_
#define CAICONDITIONRESPONSE_H_

#include "CAICondition.h"
#include "CAIResponse.h"

class CAIConditionResponse {
public:
    CAIConditionResponse();
    CAIConditionResponse(const CAICondition& condition, const CAIResponseSet& responseSet);
    ~CAIConditionResponse();

    void Read(CString sLine);

    /* 0000 */ CAICondition m_condition;
    /* 001C */ CAIResponseSet m_responseSet;
};

#endif /* CAICONDITIONRESPONSE_H_ */
