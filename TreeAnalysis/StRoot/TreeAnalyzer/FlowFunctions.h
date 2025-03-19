#ifndef FLOWFUNCTIONS_H
#define FLOWFUNCTIONS_H

#include <iostream>
#include <cmath>

namespace FlowFunctions
{
    Double_t Pt(Double_t px, Double_t py)
    {
        return (sqrt(pow(px, 2) + pow(py, 2)));
    }

    Double_t P(Double_t px, Double_t py, Double_t pz)
    {
        return (sqrt(pow(px,2) + pow(py,2) + pow(pz,2)));
    }

    Double_t Eta(Double_t px, Double_t py, Double_t pz)
    {
        Double_t p = P(px, py, pz);

        return (0.5*log((p + pz)/(p - pz)));
    }

    Double_t QP(Double_t q, Double_t px, Double_t py, Double_t pz)
    {
        return (q*sqrt(pow(px,2) + pow(py,2) + pow(pz,2)));
    }

    Double_t Phi(Double_t px, Double_t py)
    {
        return (atan2(py, px));
    }

    Double_t MSquared(Double_t px, Double_t py, Double_t pz, Double_t tofBeta)
    {
        return ((pow(px,2) + pow(py,2) + pow(pz,2)) * ((1/pow(tofBeta,2)) - 1));
    }

    Double_t Energy(Double_t px, Double_t py, Double_t pz, Double_t mass)
    {
        return (sqrt(pow(px,2) + pow(py,2) + pow(pz,2) + pow(mass,2)));
    }

    Double_t Y(Double_t px, Double_t py, Double_t pz, Double_t mass)
    {
        Double_t energy = Energy(px, py, pz, mass);

        return (atanh(pz/energy));
    }

    Double_t V_n(Double_t n, Double_t px, Double_t py, Double_t Psi_n)
    {
        Double_t phi = Phi(px, py);

        return (cos(n*(phi - Psi_n)));
    }    
}

#endif