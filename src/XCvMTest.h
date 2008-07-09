/**
     Class CXCvMTest: Computing the Cramer-von Mises test score
	                 for given two sample
         
	 Author: Yuanhui Xiao
     Revised date: 07/08/2008

     Copyright (c) 2008 Yuanhui Xiao
*/

#include "XCVM.h"

#include <algorithm>
#include <functional>

#ifndef CXCvMTest_H
#define CXCvMTest_H

#define TINY 1.0e-100

class CXCvMTest : public CXCVM {

public:

  CXCvMTest(int nA=1, int nB=1);
  virtual ~CXCvMTest();

  // Both () operators are different names for the methods
  // ComputeStatistic() given below
  const double operator()(const int* IndicesOfRanks) const;

  const double operator()(const double* sample);

protected:

  const double ComputeStatistic(const int * IndicesOfRanks) const;
      // IndicesOfRanks is 1- instead of 0-based,
      // so accessing IndicesOfRanks[0] is an error.
      
  const double ComputeStatistic(const double* sample); 
      // Only observed values are given
      // Note the array is one-based, see the note above
     
protected:

  int *m_indices;   // indices for ranks
};

// class CXSampleRanker: a predicate comparing indices
// based on the corresponding sample values. An auxiliary
// class for sorting data

struct CXSampleRanker{

  const double * m_x;    // sample, the array is 1-based

  CXSampleRanker(const double * x);
  bool operator()(int i, int j) const; 
    // compare the i-th and the j-th values of the sample                                          
};

#endif
