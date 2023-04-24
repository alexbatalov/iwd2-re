#ifndef CDUNGEONMASTER_H_
#define CDUNGEONMASTER_H_

#include "CBaldurEngine.h"

class CDungeonMaster : public CBaldurEngine {
public:
    CDungeonMaster();
    ~CDungeonMaster();
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0020 */ void EngineInitialized() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
};

#endif /* CDUNGEONMASTER_H_ */
