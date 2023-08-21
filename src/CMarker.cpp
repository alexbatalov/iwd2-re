#include "CMarker.h"

#include "CUtil.h"

// 0x85C17A
const BYTE CMarker::RECTICLE = 0;

// 0x85C17B
const BYTE CMarker::ELLIPSE = 1;

// 0x7668D0
CMarker::CMarker()
{
    field_6 = 0;
    m_nRecticleCounter = 0;
    field_4 = 0;
    field_5 = 0;
    m_type = ELLIPSE;

    memset(field_A, 0, sizeof(field_A));

    field_22 = 0;
}

// 0x7670D0
BYTE CMarker::SetType(BYTE nType)
{
    switch (nType) {
    case RECTICLE:
        m_type = RECTICLE;
        m_nRecticleCounter++;
        break;
    case ELLIPSE:
        if (m_nRecticleCounter > 0) {
            m_nRecticleCounter--;
            if (m_nRecticleCounter == 0) {
                m_type = ELLIPSE;
            }
        }
        break;
    }

    return m_type;
}
