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
        Bool_t FoundWithDeuteronToF;
        Bool_t FoundWithTritonToF;

    public:
        DeuteronsAndTritons();
        DeuteronsAndTritons(Double_t p, Double_t dEdx, Double_t tofBeta, Double_t zDeuteron, Double_t zTriton, Bool_t FoundWithDeuteronToF, Bool_t FoundWithTritonToF);

        Bool_t GetFoundWithDeuteronToF();
        Bool_t GetFoundWithTritonToF();
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
    this->FoundWithDeuteronToF = false;
    this->FoundWithTritonToF = false;
}

DeuteronsAndTritons::DeuteronsAndTritons(Double_t p, Double_t dEdx, Double_t tofBeta, Double_t zDeuteron, Double_t zTriton, Bool_t FoundWithDeuteronToF, Bool_t FoundWithTritonToF)
{
    this->p = p;
    this->dEdx = dEdx;
    this->tofBeta = tofBeta;
    this->zDeuteron = zDeuteron;
    this->zTriton = zTriton;
    this->FoundWithDeuteronToF = FoundWithDeuteronToF;
    this->FoundWithTritonToF = FoundWithTritonToF;
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
        if      (momentum >= 0.4 && momentum < 0.5 && zDeuteron > -0.457382 && zDeuteron < 0.242462) deuteron = true;
        else if (momentum >= 0.5 && momentum < 0.6 && zDeuteron > -0.466459 && zDeuteron < 0.351599) deuteron = true;
        else if (momentum >= 0.6 && momentum < 0.7 && zDeuteron > -0.470831 && zDeuteron < 0.42232) deuteron = true;
        else if (momentum >= 0.7 && momentum < 0.8 && zDeuteron > -0.444896 && zDeuteron < 0.431071) deuteron = true;
        else if (momentum >= 0.8 && momentum < 0.9 && zDeuteron > -0.41775 && zDeuteron < 0.433538) deuteron = true;
        else if (momentum >= 0.9 && momentum < 1.0 && zDeuteron > -0.383326 && zDeuteron < 0.432292) deuteron = true;
        else if (momentum >= 1.0 && momentum < 1.1 && zDeuteron > -0.348029 && zDeuteron < 0.423747) deuteron = true;
        else if (momentum >= 1.1 && momentum < 1.2 && zDeuteron > -0.311353 && zDeuteron < 0.412294) deuteron = true;
        else if (momentum >= 1.2 && momentum < 1.3 && zDeuteron > -0.274978 && zDeuteron < 0.400221) deuteron = true;
        else if (momentum >= 1.3 && momentum < 1.4 && zDeuteron > -0.245267 && zDeuteron < 0.386873) deuteron = true;
        else if (momentum >= 1.4 && momentum < 1.5 && zDeuteron > -0.226685 && zDeuteron < 0.367814) deuteron = true;
        else if (momentum >= 1.5 && momentum < 1.6 && zDeuteron > -0.197705 && zDeuteron < 0.36102) deuteron = true;
        else if (momentum >= 1.6 && momentum < 1.7 && zDeuteron > -0.164459 && zDeuteron < 0.361021) deuteron = true;
        else if (momentum >= 1.7 && momentum < 1.8 && zDeuteron > -0.152733 && zDeuteron < 0.341901) deuteron = true;
        else if (momentum >= 1.8 && momentum < 1.9 && zDeuteron > -0.144453 && zDeuteron < 0.320815) deuteron = true;
        else if (momentum >= 1.9 && momentum < 2.0 && zDeuteron > -0.081677 && zDeuteron < 0.309557) deuteron = true;
        else if (momentum >= 2.0 && momentum < 2.1 && zDeuteron > -0.0672646 && zDeuteron < 0.303883) deuteron = true;
        else if (momentum >= 2.1 && momentum < 2.2 && zDeuteron > -0.0547535 && zDeuteron < 0.297419) deuteron = true;
        else if (momentum >= 2.2 && momentum < 2.3 && zDeuteron > -0.0439074 && zDeuteron < 0.288592) deuteron = true;
        else if (momentum >= 2.3 && momentum < 2.4 && zDeuteron > -0.0325191 && zDeuteron < 0.279506) deuteron = true;
        else if (momentum >= 2.4 && momentum < 2.5 && zDeuteron > -0.0242708 && zDeuteron < 0.26676) deuteron = true;
        else if (momentum >= 2.5 && momentum < 2.6 && zDeuteron > -0.0155828 && zDeuteron < 0.224273) deuteron = true;
        else if (momentum >= 2.6 && momentum < 2.7 && zDeuteron > -0.00620805 && zDeuteron < 0.213198) deuteron = true;
        else if (momentum >= 2.7 && momentum < 2.8 && zDeuteron > 0.00128208 && zDeuteron < 0.201287) deuteron = true;
        else if (momentum >= 2.8 && momentum < 2.9 && zDeuteron > 0.0246083 && zDeuteron < 0.175939) deuteron = true;
        else if (momentum >= 2.9 && momentum < 3.0 && zDeuteron > 0.0493664 && zDeuteron < 0.152104) deuteron = true;
    }

    else if(this->tofBeta > 0)
    {
        Double_t msquared = (pow(momentum,2) * ((1/pow(this->tofBeta,2)) - 1));

        if (zDeuteron > zLow && zDeuteron < zHigh && msquared > msquaredLow && msquared < msquaredHigh)
        {
            deuteron = true;

            this->FoundWithDeuteronToF = true;
        }
    }

    return deuteron;
}

Bool_t DeuteronsAndTritons::GetFoundWithDeuteronToF()
{
    return this->FoundWithDeuteronToF;
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
        if      (momentum >= 1.0 && momentum < 1.1 && zTriton > -0.2329 && zTriton < 0.345216) triton = true;
        else if (momentum >= 1.1 && momentum < 1.2 && zTriton > -0.218777 && zTriton < 0.382275) triton = true;
        else if (momentum >= 1.2 && momentum < 1.3 && zTriton > -0.209594 && zTriton < 0.410163) triton = true;
        else if (momentum >= 1.3 && momentum < 1.4 && zTriton > -0.195037 && zTriton < 0.440988) triton = true;
        else if (momentum >= 1.4 && momentum < 1.5 && zTriton > -0.18092 && zTriton < 0.471448) triton = true;
        else if (momentum >= 1.5 && momentum < 1.6 && zTriton > -0.167469 && zTriton < 0.373638) triton = true;
        else if (momentum >= 1.6 && momentum < 1.7 && zTriton > -0.157289 && zTriton < 0.378014) triton = true;
        else if (momentum >= 1.7 && momentum < 1.8 && zTriton > -0.146496 && zTriton < 0.377613) triton = true;
        else if (momentum >= 1.8 && momentum < 1.9 && zTriton > -0.135984 && zTriton < 0.370302) triton = true;
        else if (momentum >= 1.9 && momentum < 2.0 && zTriton > -0.121631 && zTriton < 0.35764) triton = true;
        else if (momentum >= 2.0 && momentum < 2.1 && zTriton > -0.0611372 && zTriton < 0.335492) triton = true;
        else if (momentum >= 2.1 && momentum < 2.2 && zTriton > -0.0537701 && zTriton < 0.316951) triton = true;
        else if (momentum >= 2.2 && momentum < 2.3 && zTriton > -0.0445911 && zTriton < 0.310131) triton = true;
        else if (momentum >= 2.3 && momentum < 2.4 && zTriton > -0.029612 && zTriton < 0.280664) triton = true;
        else if (momentum >= 2.4 && momentum < 2.5 && zTriton > -0.0143456 && zTriton < 0.281164) triton = true;
        else if (momentum >= 2.5 && momentum < 2.6 && zTriton > -0.00866211 && zTriton < 0.273235) triton = true;
        else if (momentum >= 2.6 && momentum < 2.7 && zTriton > -0.0124118 && zTriton < 0.256431) triton = true;
        else if (momentum >= 2.7 && momentum < 2.8 && zTriton > -0.0141391 && zTriton < 0.241653) triton = true;
        else if (momentum >= 2.8 && momentum < 2.9 && zTriton > -0.0132944 && zTriton < 0.238389) triton = true;
        else if (momentum >= 2.9 && momentum < 3.0 && zTriton > -0.00954423 && zTriton < 0.24264) triton = true;
        else if (momentum >= 3.0 && momentum < 3.1 && zTriton > -0.00519959 && zTriton < 0.250064) triton = true;
        else if (momentum >= 3.1 && momentum < 3.2 && zTriton > -0.00113935 && zTriton < 0.259228) triton = true;
        else if (momentum >= 3.2 && momentum < 3.3 && zTriton > 0.000480187 && zTriton < 0.266394) triton = true;
        else if (momentum >= 3.3 && momentum < 3.4 && zTriton > 0.0299518 && zTriton < 0.25718) triton = true;
        else if (momentum >= 3.4 && momentum < 3.5 && zTriton > 0.0465172 && zTriton < 0.288088) triton = true;
        else if (momentum >= 3.5 && momentum < 3.6 && zTriton > 0.0860199 && zTriton < 0.279754) triton = true;
        else if (momentum >= 3.6 && momentum < 3.7 && zTriton > 0.00890145 && zTriton < 0.279047) triton = true;
        else if (momentum >= 3.7 && momentum < 3.8 && zTriton > 0.03 && zTriton < 0.360241) triton = true;
        else if (momentum >= 3.8 && momentum < 3.9 && zTriton > 0.0445011 && zTriton < 0.362315) triton = true;
        else if (momentum >= 3.9 && momentum < 4.0 && zTriton > 0.00688811 && zTriton < 0.361806) triton = true;
    }

    else if(this->tofBeta > 0)
    {
        Double_t msquared = (pow(momentum,2) * ((1/pow(this->tofBeta,2)) - 1));

        if (zTriton > zLow && zTriton < zHigh && msquared > msquaredLow && msquared < msquaredHigh)
        {
            triton = true;

            this->FoundWithTritonToF = true;
        }
    }

    return triton;
}

Bool_t DeuteronsAndTritons::GetFoundWithTritonToF()
{
    return this->FoundWithTritonToF;
}

#endif
