#ifndef FLOWFUNCTIONS_H
#define FLOWFUNCTIONS_H

#include <iostream>
#include <cmath>

namespace FlowFunctions
{
    double Pt(double px, double py)
    {
        return (sqrt(pow(px, 2) + pow(py, 2)));
    }

    double P(double px, double py, double pz)
    {
        return (sqrt(pow(px,2) + pow(py,2) + pow(pz,2)));
    }

    double Eta(double px, double py, double pz)
    {
        double p = P(px, py, pz);

        return (0.5*log((p + pz)/(p - pz)));
    }

    double QP(double q, double px, double py, double pz)
    {
        return (q*sqrt(pow(px,2) + pow(py,2) + pow(pz,2)));
    }

    double Phi(double px, double py)
    {
        return (atan2(py, px));
    }

    double MSquared(double px, double py, double pz, double tofBeta)
    {
        return ((pow(px,2) + pow(py,2) + pow(pz,2)) * ((1/pow(tofBeta,2)) - 1));
    }

    double Energy(double px, double py, double pz, double mass)
    {
        return (sqrt(pow(px,2) + pow(py,2) + pow(pz,2) + pow(mass,2)));
    }

    double Y(double px, double py, double pz, double mass)
    {
        double energy = Energy(px, py, pz, mass);

        return (atanh(pz/energy));
    }

    double V_n(double n, double px, double py, double Psi_n)
    {
        double phi = Phi(px, py);

        return (cos(n*(phi - Psi_n)));
    }
    
}

#endif