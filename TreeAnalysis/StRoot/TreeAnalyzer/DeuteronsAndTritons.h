#ifndef DEUTERONSANDTRITONS_H
#define DEUTERONSANDTRITONS_H




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
    const Double_t zLow = -0.2;
    const Double_t zHigh = 0.2;
    const Double_t msquaredLow = 3.1518;
    const Double_t msquaredHigh = 3.8842;


    
    
    Double_t momentum = this->p;
    Bool_t deuteron = false;

    if (momentum >= 0.4 && momentum < 3.0)
    {
        if      (momentum >= 0.4 && momentum < 0.5 && zDeuteron > -0.476112 && zDeuteron < 0.248539) deuteron = true;
        else if (momentum >= 0.5 && momentum < 0.6 && zDeuteron > -0.445644 && zDeuteron < 0.311067) deuteron = true;
        else if (momentum >= 0.6 && momentum < 0.7 && zDeuteron > -0.43008  && zDeuteron < 0.331624) deuteron = true;
        else if (momentum >= 0.7 && momentum < 0.8 && zDeuteron > -0.416061 && zDeuteron < 0.341399) deuteron = true;
        else if (momentum >= 0.8 && momentum < 0.9 && zDeuteron > -0.404842 && zDeuteron < 0.338091) deuteron = true;
        else if (momentum >= 0.9 && momentum < 1.0 && zDeuteron > -0.37419  && zDeuteron < 0.337724) deuteron = true;
        else if (momentum >= 1.0 && momentum < 1.1 && zDeuteron > -0.32986  && zDeuteron < 0.332241) deuteron = true;
        else if (momentum >= 1.1 && momentum < 1.2 && zDeuteron > -0.332995 && zDeuteron < 0.325582) deuteron = true;
        else if (momentum >= 1.2 && momentum < 1.3 && zDeuteron > -0.306145 && zDeuteron < 0.319532) deuteron = true;
        else if (momentum >= 1.3 && momentum < 1.4 && zDeuteron > -0.275987 && zDeuteron < 0.313227) deuteron = true;
        else if (momentum >= 1.4 && momentum < 1.5 && zDeuteron > -0.250464 && zDeuteron < 0.301911) deuteron = true;
        else if (momentum >= 1.5 && momentum < 1.6 && zDeuteron > -0.215135 && zDeuteron < 0.302149) deuteron = true;
        else if (momentum >= 1.6 && momentum < 1.7 && zDeuteron > -0.176733 && zDeuteron < 0.308644) deuteron = true;
        else if (momentum >= 1.7 && momentum < 1.8 && zDeuteron > -0.160866 && zDeuteron < 0.29673) deuteron = true;
        else if (momentum >= 1.8 && momentum < 1.9 && zDeuteron > -0.149249 && zDeuteron < 0.281362) deuteron = true;
        else if (momentum >= 1.9 && momentum < 2.0 && zDeuteron > -0.0830817 && zDeuteron < 0.273483) deuteron = true;
        else if (momentum >= 2.0 && momentum < 2.1 && zDeuteron > -0.065219 && zDeuteron < 0.269654) deuteron = true;
        else if (momentum >= 2.1 && momentum < 2.2 && zDeuteron > -0.04952  && zDeuteron < 0.265074) deuteron = true;
        else if (momentum >= 2.2 && momentum < 2.3 && zDeuteron > -0.0358834 && zDeuteron < 0.258749) deuteron = true;
        else if (momentum >= 2.3 && momentum < 2.4 && zDeuteron > -0.0218641 && zDeuteron < 0.25294) deuteron = true;
        else if (momentum >= 2.4 && momentum < 2.5 && zDeuteron > -0.0114193 && zDeuteron < 0.244108) deuteron = true;
        else if (momentum >= 2.5 && momentum < 2.6 && zDeuteron > -0.000659632 && zDeuteron < 0.205416) deuteron = true;
        else if (momentum >= 2.6 && momentum < 2.7 && zDeuteron > 0.010662  && zDeuteron < 0.198006) deuteron = true;
        else if (momentum >= 2.7 && momentum < 2.8 && zDeuteron > 0.0203815 && zDeuteron < 0.189092) deuteron = true;
        else if (momentum >= 2.8 && momentum < 2.9 && zDeuteron > 0.0313737 && zDeuteron < 0.181285) deuteron = true;
        else if (momentum >= 2.9 && momentum < 3.0 && zDeuteron > 0.0446902 && zDeuteron < 0.174561) deuteron = true;
    }

    else if(this->tofBeta > 0)
    {
        Double_t msquared = (pow(momentum,2) * ((1/pow(this->tofBeta,2)) - 1));

        if (zDeuteron > zLow && zDeuteron < zHigh && msquared > msquaredLow && msquared < msquaredHigh)
        {
            deuteron = true;
        }
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