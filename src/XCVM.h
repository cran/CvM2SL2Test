/**
    Class CXCVM: a base class

    Author: Yuanhui Xiao
    Revised date:  12/06/2005

    Copyright (c) 2006 Yuanhui Xiao
*/

#ifndef CXCVM_H
#define CXCVM_H

#include <cmath>

class CXCVM{

public:

  CXCVM(int nA=1, int nB=1); // nA and nB are sample sizes
  virtual ~CXCVM();
  
protected:

  const long   ToInt(const double dStat) const; // convert T2 to zeta
  const double ToDouble(const long iStat) const; // convert zeta to T2

  const int GCD(); // return the great common divisor using Euclidean algorithm

protected:

  int m_nA, m_nB; // sample sizes
  long m_nL;       // least common multiple of m_nA and m_nB
  long m_nP, m_nQ; // m_nP = m_nL/m_nA, m_nQ = m_nL/m_nB
  
  double m_dCoe;  // coefficient 
};
#endif



