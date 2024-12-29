#ifndef DEUTERONSANDTRITONS_H
#define DEUTERONSANDTRITONS_H

//#include "/star/u/mcgordon/VnFromEPD/StRoot/StBichsel/dEdxParameterization.cxx"
#include "/star/u/mcgordon/VnFromEPD/StRoot/StBichsel/Bichsel.h"
#include "/star/u/mcgordon/VnFromEPD/StRoot/StBichsel/Bichsel.cxx"
//#include "/star/u/mcgordon/VnFromEPD/bichselComparison.cxx"



class DeuteronsAndTritons
{
    private:
        Double_t p;
        Double_t dEdx;
        Double_t tofBeta;
        Double_t zDeuteron;
        Double_t zTriton;

    public:
        DeuteronsAndTritons();
        DeuteronsAndTritons(Double_t p, Double_t dEdx, Double_t tofBeta, Double_t zDeuteron, Double_t zTriton);

        Bool_t IsDeuteron();
        Bool_t IsTriton();

};

DeuteronsAndTritons::DeuteronsAndTritons()
{
    this->p = 0;
    this->dEdx = 0;
    this->tofBeta = 0;
    this->zDeuteron = 0;
    this->zTriton = 0;
}

DeuteronsAndTritons::DeuteronsAndTritons(Double_t p, Double_t dEdx, Double_t tofBeta, Double_t zDeuteron, Double_t zTriton)
{
    this->p = p;
    this->dEdx = dEdx;
    this->tofBeta = tofBeta;
    this->zDeuteron = zDeuteron;
    this->zTriton = zTriton;
}



Bool_t DeuteronsAndTritons::IsDeuteron()
{
    const Double_t msquaredLow = 2.8;
    const Double_t msquaredHigh = 4.8;    
    
    Double_t momentum = this->p;
    Bool_t deuteron = false;
    
    
    Float_t MomentumBins[51] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5.0, 5.1, 5.2, 5.3, 5.4, 200};

    Int_t Bin = -1;

    for(Int_t index = 0; index < 50; index++)
    {
        if((momentum >= MomentumBins[index]) && (momentum < MomentumBins[index + 1]))
        {
            Bin = index;
        }
    }

    if(Bin == -1)
    {        
        return deuteron;
    }
               
    Float_t zMean[50] = {-0.0832867, -0.0557943, -0.0302878, -0.0154656, 0.00222155, 0.0147798, 0.0243567, 0.0327773, 0.0387324, 0.0372758, 0.0461688, 0.061474, 0.057022, 0.0480333, 0.0454707, 0.0466773, 0.0473922, 0.0470951, 0.0481996, 0.0468892, 0.0464752, 0.0473581, 0.0467947, 0.0465219, 0.0474517, 0.0474816, 0.0454535, 0.0349253, 0.0282318, 0.0248662, 0.0246939, 0.0265303, 0.0284592, 0.0294229, 0.0296879, 0.0322723, 0.0364428, 0.0406073, 0.0451247, 0.0497799, 0.0550221, 0.061172, 0.0669082, 0.0711066, 0.0890019, 0.0902058, 0.0907085, 0.0915537, 0.0914749, 0.0874104};
           
    Float_t lowZ[30] = {-0.27 , -0.27 , -0.27 , -0.27 , -0.27 , -0.27 , -0.27 , -0.27 , -0.27 , -0.24, -0.22, -0.20, -0.18, -0.16, -0.13, -0.11, -0.09, -0.07, -0.05, -0.04 , -0.04, -0.03, -0.02, -0.01, -0.02, -0.04, -0.06, -0.08, -0.1 , -0.12};

    Float_t highZ[30] = {0.27 , 0.27 , 0.27 , 0.27 , 0.27 , 0.27 , 0.27 , 0.27 , 0.27 , 0.27, 0.27, 0.27, 0.27, 0.26, 0.25, 0.24, 0.22, 0.21, 0.19, 0.17, 0.14, 0.13, 0.12, 0.11, 0.13, 0.13, 0.12, 0.11, 0.09, 0.08};
           
    Float_t zModified = this->zDeuteron - zMean[Bin];
           
    Double_t msquared = (pow(momentum,2) * ((1/pow(this->tofBeta,2)) - 1));
           
    if((momentum < 0.8) && (zModified >= -0.3) && (zModified < 0.3))
    {
        deuteron = true;
    }
    else if((momentum >= 0.8) && (momentum < 3.2) && (zModified > lowZ[Bin - 3]) && (zModified < highZ[Bin - 3]))
    {
        deuteron = true;
    }
    else if((momentum >= 3.2) && (zModified >= -0.4) && (zModified < 0.4) && (msquared >= msquaredLow) && (msquared <= msquaredHigh))
    {
        deuteron = true;
    }

    return deuteron;
}






Bool_t DeuteronsAndTritons::IsTriton()
{
    const Double_t msquaredLow = 6.4;
    const Double_t msquaredHigh = 9.4;    
    
    Double_t momentum = this->p;
    Bool_t triton = false;
    
    
    Float_t MomentumBins[51] = {0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5.0, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 200};

    Int_t Bin = -1;

    for(Int_t index = 0; index < 50; index++)
    {
        if((momentum >= MomentumBins[index]) && (momentum < MomentumBins[index + 1]))
        {
            Bin = index;
        }
    }

    if(Bin == -1)
    {        
        return triton;
    }
               
    Float_t zMean[50] = {-0.100565, -0.0772472, -0.0540842, -0.0354157, -0.024151, -0.00949696, 0.00395854, 0.0141392, 0.0216796, 0.0308508, 0.037244, 0.0414534, 0.0437564, 0.0433574, 0.0463866, 0.0564772, 0.0671244, 0.0682989, 0.0591002, 0.0517172, 0.0466687, 0.0446803, 0.0429786, 0.0413944, 0.0374969, 0.0329913, 0.0293219, 0.0277725, 0.0273808, 0.0286301, 0.0268645, 0.0154856, 0.00582204, 0.00838099, 0.0068412, 0.00721719, 0.00911347, 0.0352896, 0.0109075, -0.00487009, -0.00230797, -0.00122419, 0.000160571, 0.00184267, 0.0031727, 0.00564543, 0.00782452, 0.012463, 0.0169764, 0.0399578};
           
    Float_t lowZ[34] = {-0.26, -0.26, -0.26, -0.26, -0.26, -0.25, -0.24, -0.24, -0.23, -0.21, -0.2, -0.18, -0.16, -0.14, -0.12, -0.11, -0.1, -0.09, -0.08, -0.07, -0.05, -0.04, -0.03, -0.02, 0.01, 0.03, 0.04, 0.04, 0.05, 0.04, 0.04, 0.04, 0.04, 0.04};

    Float_t highZ[34] = {0.27, 0.27, 0.27, 0.27, 0.27, 0.27, 0.27, 0.27, 0.27, 0.27, 0.25, 0.24, 0.21, 0.2, 0.22, 0.2, 0.21, 0.22, 0.23, 0.23, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29};
           
    Float_t zModified = this->zTriton - zMean[Bin];
           
    Double_t msquared = (pow(momentum,2) * ((1/pow(this->tofBeta,2)) - 1));
           
    if((momentum < 1.2) && (zModified >= -0.26) && (zModified < 0.3))
    {
        triton = true;
    }
    else if((momentum >= 1.2) && (momentum < 4.2) && (zModified > lowZ[Bin - 4]) && (zModified < highZ[Bin - 4]))
    {
        triton = true;
    }
    else if((momentum >= 4.2) && (zModified >= -0.3) && (zModified < 0.3) && (msquared >= msquaredLow) && (msquared <= msquaredHigh))
    {
        triton = true;
    }

    return triton;
}

#endif