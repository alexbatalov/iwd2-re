#ifndef CSCREENMOVIES_H_
#define CSCREENMOVIES_H_

#include "CBaldurEngine.h"

class CScreenMovies : public CBaldurEngine {
public:
    CScreenMovies();
    ~CScreenMovies();

    void StartMovies(INT nEngineState);
};

#endif /* CSCREENMOVIES_H_ */
