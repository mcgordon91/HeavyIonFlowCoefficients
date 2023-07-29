#!/usr/bin/env python
# coding: utf-8

# In[ ]:


from math import sqrt, pow, log, atanh, atan2, sin, cos, exp

def Pt(px, py):
    return (sqrt(pow(px, 2) + pow(py, 2)))

def P(px, py, pz):
    return (sqrt(pow(px,2) + pow(py,2) + pow(pz,2)))

def Eta(px, py, pz):
    p = P(px, py, pz)
    
    return (0.5*log((p + pz)/(p - pz)))

def QP(q, px, py, pz):
    return (q*sqrt(pow(px,2) + pow(py,2) + pow(pz,2)))

def Phi(px, py):
    return (atan2(py, px))

def MSquared(px, py, pz, tofBeta):
    return ((pow(px,2) + pow(py,2) + pow(pz,2)) * ((1/pow(tofBeta,2)) - 1))

def Energy(px, py, pz, mass):
    return (sqrt(pow(px,2) + pow(py,2) + pow(pz,2) + pow(mass,2)))

def Y(px, py, pz, mass):
    energy = Energy(px, py, pz, mass)
    
    return (atanh(pz/energy))

def V_n(n, px, py, Psi_n):
    phi = Phi(px, py)
    
    return (cos(n*(phi - Psi_n)))

