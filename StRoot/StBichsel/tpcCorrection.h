#ifndef tpcCorrection_st_h
#define tpcCorrection_st_h
#include "Rtypes.h"

struct tpcCorrection_st {
    Int_t    type;      // 1st number (0)
    Int_t    nrows;     // 2nd number (10)
    Int_t    idx;       // 3rd number (2)
    Int_t    npar;      // 4th number (4)
    Int_t    OffSet;    // 5th number (0)
    Double_t min;       // 6th number (2.30)
    Double_t max;       // 7th number (4.79)
    Double_t a[10];     // 8th item (The array of 10 coefficients)
};
#endif

