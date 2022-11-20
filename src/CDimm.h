#ifndef CDIMM_H_
#define CDIMM_H_

class CDimm {
public:
    CDimm();
    ~CDimm();

    void DestroyKeyTable();
    void DumpAll();

    /* 00D6 */ int field_D6;
    /* 00DE */ int field_DE;
};

#endif /* CDIMM_H_ */
