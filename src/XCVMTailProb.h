/**
     Class CXCVMTailProb:  Compute the tail probability for
	                       given Cramer-von Mises test score.

     Subclasses: 1) CXCVMTailProb_EQ   for the case m = n
                 2) CXCVMTailProb_NE1  for the case m+n is even (and m != n)
                 3) CXCVMTailProb_NE2  for the case m+n is odd  (and m != n)

     Author: Yuanhui Xiao
     Revised date: 07/08/2008

     Copyright (c) 2008 Yuanhui Xiao
*/

#include "XCVM.h"
#include "XFreqFunct.h"

#ifndef CXCVMTailProb_H
#define CXCVMTailProb_H

#include <iostream>

class CXCVMTailProb : public CXCVM
{
public:

  CXCVMTailProb(int nA, int nB); // constructor
  virtual ~CXCVMTailProb(); 

  virtual const double operator()(const double cvm) const;
     // compute the tail probability for given cvm

  virtual const double operator()(const int64_t Q) const = 0;
     // compute the tail frequence for given Q
  
protected:

	void TabulateFreqFuncts(int iStep);

protected:

  CXFreqFunct* m_functs;
  double m_dFreqSum; // sum of refequencies, which is equal to {m+n \choose m}
};

#endif
