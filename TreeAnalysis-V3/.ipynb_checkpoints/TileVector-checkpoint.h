#ifndef TILEVECTOR_H
#define TILEVECTOR_H

#include "TVector3.h"
#include "/star/u/mcgordon/VnFromEPD/StRoot/StEpdUtil/StEpdGeom.h"



class TileVector
{
    private:
        StEpdGeom* epdGeom;
        Int_t EPDID;
        Double_t vx;
        Double_t vy;
        Double_t vz;
        Int_t InnerEPDHighRing;
        Int_t OuterEPDLowRing;

    public:
        TileVector();
        TileVector(StEpdGeom* epdGeom, Int_t EPDID, Double_t vx, Double_t vy, Double_t vz, Int_t InnerEPDHighRing, Int_t OuterEPDLowRing);

        Double_t EPDEta();
        Double_t EPDPhi();
        Int_t EPDSector();
        Int_t EPDRow();
        Bool_t IsInnerEPD();
        Bool_t IsOuterEPD();
};


TileVector::TileVector()
{
    this->epdGeom = NULL;
    this->EPDID = 0;
    this->vx = 0;
    this->vy = 0;
    this->vz = 0;
    this->InnerEPDHighRing = 0;
    this->OuterEPDLowRing = 0;
}

TileVector::TileVector(StEpdGeom* epdGeom, Int_t EPDID, Double_t vx, Double_t vy, Double_t vz, Int_t InnerEPDHighRing, Int_t OuterEPDLowRing)
{
    this->epdGeom = epdGeom;
    this->EPDID = EPDID;
    this->vx = vx;
    this->vy = vy;
    this->vz = vz;
    this->InnerEPDHighRing = InnerEPDHighRing;
    this->OuterEPDLowRing = OuterEPDLowRing;
}

Double_t TileVector::EPDEta()
{
    TVector3 VertexVector(this->vx, this->vy, this->vz);

    TVector3 TileVector = epdGeom->TileCenter(this->EPDID) - VertexVector;
    
    return TileVector.Eta();
}

Double_t TileVector::EPDPhi()
{
    TVector3 VertexVector(this->vx, this->vy, this->vz);

    TVector3 TileVector = epdGeom->TileCenter(this->EPDID) - VertexVector;

    return TileVector.Phi();
}

Int_t TileVector::EPDSector()
{
    return TMath::Abs(this->EPDID/100);
}

Int_t TileVector::EPDRow()
{
    Int_t absID = TMath::Abs(this->EPDID);
    Int_t tileNum = absID % 100;
    Int_t rowNum = 0;

    if (tileNum == 1) rowNum = 1;
    else if (tileNum == 2 || tileNum == 3) rowNum = 2;
    else if (tileNum == 4 || tileNum == 5) rowNum = 3;
    else if (tileNum == 6 || tileNum == 7) rowNum = 4;
    else if (tileNum == 8 || tileNum == 9) rowNum = 5;
    else if (tileNum == 10 || tileNum == 11) rowNum = 6;
    else if (tileNum == 12 || tileNum == 13) rowNum = 7;
    else if (tileNum == 14 || tileNum == 15) rowNum = 8;
    else if (tileNum == 16 || tileNum == 17) rowNum = 9;
    else if (tileNum == 18 || tileNum == 19) rowNum = 10;
    else if (tileNum == 20 || tileNum == 21) rowNum = 11;
    else if (tileNum == 22 || tileNum == 23) rowNum = 12;
    else if (tileNum == 24 || tileNum == 25) rowNum = 13;
    else if (tileNum == 26 || tileNum == 27) rowNum = 14;
    else if (tileNum == 28 || tileNum == 29) rowNum = 15;
    else if (tileNum == 30 || tileNum == 31) rowNum = 16;

    return rowNum;
}

Bool_t TileVector::IsInnerEPD()
{
    Int_t RowNum = EPDRow();

    return ((RowNum >= 1) && (RowNum <= this->InnerEPDHighRing));
}

Bool_t TileVector::IsOuterEPD()
{
    Int_t RowNum = EPDRow();

    return ((RowNum >= this->OuterEPDLowRing) && (RowNum <= 16));
}

#endif