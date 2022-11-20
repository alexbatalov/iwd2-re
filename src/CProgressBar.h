#ifndef CPROGRESSBAR_H_
#define CPROGRESSBAR_H_

class CProgressBar {
public:
    // NOTE: The `Initialize` function is called in implicit part of `CChitin`
    // constructor, but the constructor itself is inlined.
    CProgressBar()
    {
        Initialize();
    }

    void Initialize();
};

#endif /* CPROGRESSBAR_H_ */
