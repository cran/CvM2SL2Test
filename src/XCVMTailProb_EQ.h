/**
     Class CXCVMTailProb_EQ:  Compute the tail probability for
	                       given Cramer-von Mises test score
						   for the case m = n.

     Author: Yuanhui Xiao
     Revised date: 07/08/2008

     Copyright (c) 2008 Yuanhui Xiao
*/

#include "XCVMTailProb.h"
#include "XFreqFunct.h"

#ifndef CXCVMTailProb_EQ_H
#define CXCVMTailProb_EQ_H

class CXCVMTailProb_EQ : public CXCVMTailProb
{
public:

  CXCVMTailProb_EQ(int nA); // constructor
  
  virtual const double operator()(const double cvm) const;
     // compute the tail probability for given cvm

  virtual const double operator()(const long Q) const;
     // compute the tail frequence for given Q

protected:

  void TabulateFreqFuncts();   // tabulates the tables at middle stage
};
#endif
