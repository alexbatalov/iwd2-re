#ifndef CVIDBLITTER_H_
#define CVIDBLITTER_H_

class CVidBlitter {
public:
    typedef void(Func1)(int, int, int, int, int, int);

    CVidBlitter();

    /* 0000 */ unsigned char field_0;
    /* 0001 */ unsigned char field_1;
    /* 0002 */ unsigned char field_2;
    /* 0003 */ unsigned char field_3;
    /* 0004 */ unsigned char field_4;
    /* 00DE */ int field_DE;
    /* 00E2 */ int field_E2;
    /* 00E6 */ unsigned char field_E6;
    /* 00E8 */ Func1* field_E8;
    /* 00EC */ Func1* field_EC;
    /* 00F0 */ Func1* field_F0;
    /* 00F4 */ Func1* field_F4;
    /* 00F8 */ Func1* field_F8;
    /* 00FC */ Func1* field_FC;
};

#endif /* CVIDBLITTER_H_ */
