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
    
    
    Float_t MomentumBins[50] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5.0, 5.1, 5.2, 5.3, 5.4};

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
        deuteron = false;
    }
               
    Float_t zMean[50] = {-0.0832867, -0.0557943, -0.0302878, -0.0154656, 0.00222155, 0.0147798, 0.0243567, 0.0327773, 0.0387324, 0.0372758, 0.0461688, 0.061474, 0.057022, 0.0480333, 0.0454707, 0.0466773, 0.0473922, 0.0470951, 0.0481996, 0.0468892, 0.0464752, 0.0473581, 0.0467947, 0.0465219, 0.0474517, 0.0474816, 0.0454535, 0.0349253, 0.0282318, 0.0248662, 0.0246939, 0.0265303, 0.0284592, 0.0294229, 0.0296879, 0.0322723, 0.0364428, 0.0406073, 0.0451247, 0.0497799, 0.0550221, 0.061172, 0.0669082, 0.0711066, 0.0890019, 0.0902058, 0.0907085, 0.0915537, 0.0914749, 0.0874104};
           
    Float_t lowZ[30] = {-0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.27, -0.24, -0.21, -0.18, -0.16, -0.13, -0.11, -0.09, -0.07, -0.05, -0.04, -0.04, -0.03, -0.02, -0.01, -0.02, -0.04, -0.06, -0.08, -0.1, -0.12};

    Float_t highZ[30] = {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.29, 0.29, 0.27, 0.28, 0.22, 0.26, 0.24, 0.22, 0.21, 0.19, 0.17, 0.13, 0.14, 0.12, 0.11, 0.13, 0.13, 0.12, 0.11, 0.09, 0.08};
           
    Float_t zModified = this->zDeuteron - zMean[Bin];
           
    Double_t msquared = (pow(momentum,2) * ((1/pow(this->tofBeta,2)) - 1));
           
    if((momentum < 0.8) && (zModified >= -0.3) && (zModified < 0.3))
    {
        deuteron = true;
    }
    else if((momentum >= 0.8) && (momentum < 3.1) && (zModified > lowZ[Bin - 3]) && (zModified < highZ[Bin - 3]))
    {
        deuteron = true;
    }
    else if((momentum >= 3.1) && (zModified >= -0.4) && (zModified < 0.4) && (msquared >= msquaredLow) && (msquared <= msquaredHigh))
    {
        deuteron = true;
    }

    return deuteron;
}

Bool_t DeuteronsAndTritons::IsTriton()
{
    const Double_t zLow = -0.2;
    const Double_t zHigh = 0.2;
    const Double_t msquaredLow = 7.0142;
    const Double_t msquaredHigh = 8.7578;



    Double_t momentum = this->p;
    Bool_t triton = false;

    if (momentum >= 1.0 && momentum < 4.0)
    {
        if      (momentum >= 1.0 && momentum < 1.1 && zTriton > -0.332011 && zTriton < 0.251103) triton = true;
        else if (momentum >= 1.1 && momentum < 1.2 && zTriton > -0.310412 && zTriton < 0.296090) triton = true;
        else if (momentum >= 1.2 && momentum < 1.3 && zTriton > -0.293322 && zTriton < 0.334467) triton = true;
        else if (momentum >= 1.3 && momentum < 1.4 && zTriton > -0.270550 && zTriton < 0.373857) triton = true;
        else if (momentum >= 1.4 && momentum < 1.5 && zTriton > -0.248412 && zTriton < 0.406237) triton = true;
        else if (momentum >= 1.5 && momentum < 1.6 && zTriton > -0.228044 && zTriton < 0.333261) triton = true;
        else if (momentum >= 1.6 && momentum < 1.7 && zTriton > -0.210093 && zTriton < 0.343588) triton = true;
        else if (momentum >= 1.7 && momentum < 1.8 && zTriton > -0.190900 && zTriton < 0.332586) triton = true;
        else if (momentum >= 1.8 && momentum < 1.9 && zTriton > -0.183153 && zTriton < 0.334197) triton = true;
        else if (momentum >= 1.9 && momentum < 2.0 && zTriton > -0.166020 && zTriton < 0.323303) triton = true;
        else if (momentum >= 2.0 && momentum < 2.1 && zTriton > -0.102334 && zTriton < 0.307724) triton = true;
        else if (momentum >= 2.1 && momentum < 2.2 && zTriton > -0.091053 && zTriton < 0.294345) triton = true;
        else if (momentum >= 2.2 && momentum < 2.3 && zTriton > -0.076457 && zTriton < 0.285978) triton = true;
        else if (momentum >= 2.3 && momentum < 2.4 && zTriton > -0.055669 && zTriton < 0.253769) triton = true;
        else if (momentum >= 2.4 && momentum < 2.5 && zTriton > -0.035848 && zTriton < 0.254487) triton = true;
        else if (momentum >= 2.5 && momentum < 2.6 && zTriton > -0.027266 && zTriton < 0.249350) triton = true;
        else if (momentum >= 2.6 && momentum < 2.7 && zTriton > -0.028152 && zTriton < 0.236713) triton = true;
        else if (momentum >= 2.7 && momentum < 2.8 && zTriton > -0.027867 && zTriton < 0.227672) triton = true;
        else if (momentum >= 2.8 && momentum < 2.9 && zTriton > -0.024675 && zTriton < 0.222215) triton = true;
        else if (momentum >= 2.9 && momentum < 3.0 && zTriton > -0.019179 && zTriton < 0.227362) triton = true;
        else if (momentum >= 3.0 && momentum < 3.1 && zTriton > -0.013267 && zTriton < 0.236052) triton = true;
        else if (momentum >= 3.1 && momentum < 3.2 && zTriton > -0.007851 && zTriton < 0.246071) triton = true;
        else if (momentum >= 3.2 && momentum < 3.3 && zTriton > -0.006311 && zTriton < 0.254907) triton = true;
        else if (momentum >= 3.3 && momentum < 3.4 && zTriton > 0.019834  && zTriton < 0.244291) triton = true;
        else if (momentum >= 3.4 && momentum < 3.5 && zTriton > 0.031221  && zTriton < 0.273652) triton = true;
        else if (momentum >= 3.5 && momentum < 3.6 && zTriton > 0.068248  && zTriton < 0.257484) triton = true;
        else if (momentum >= 3.6 && momentum < 3.7 && zTriton > 0.088804  && zTriton < 0.260799) triton = true;
        else if (momentum >= 3.7 && momentum < 3.8 && zTriton > 0.091490  && zTriton < 0.271776) triton = true;
        else if (momentum >= 3.8 && momentum < 3.9 && zTriton > 0.106161  && zTriton < 0.285652) triton = true;
        else if (momentum >= 3.9 && momentum < 4.0 && zTriton > 0.103653  && zTriton < 0.299234) triton = true;
    }

    else if(this->tofBeta > 0)
    {
        Double_t msquared = (pow(momentum,2) * ((1/pow(this->tofBeta,2)) - 1));

        if (zTriton > zLow && zTriton < zHigh && msquared > msquaredLow && msquared < msquaredHigh)
        {
            triton = true;
        }
    }

    return triton;
}

#endif