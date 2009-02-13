#include "XCvMTest.h"

CXCvMTest::CXCvMTest(int nA, int nB) : CXCVM(nA, nB)
{
   // may not be in need when indices of ranks
   // of the sample are given. However, this is not
   // the usual case. Normally, only samples are given

   m_indices = new int[m_nA+m_nB];
   m_indices--;  
}

CXCvMTest::~CXCvMTest()
{ delete [] (++m_indices); }

const double CXCvMTest::operator()(const int* IndicesOfRanks) const
{
   return ComputeStatistic(IndicesOfRanks);
}

const double CXCvMTest::operator()(const double* Sample)
{
   return ComputeStatistic(Sample);
}

const double CXCvMTest::ComputeStatistic(const int* IndicesOfRanks) const
{
   int64_t h = 0;
   double zeta = 0;   
   for(int iRank=1; iRank<=m_nA+m_nB; iRank++){

      IndicesOfRanks[iRank] <= m_nA ? h += m_nP : h -= m_nQ; 
      zeta += h*h;
   }   

   return zeta*m_dCoe;
}

const double CXCvMTest::ComputeStatistic(const double* sample) 
{	
   for(int i=1; i<=m_nA+m_nB; i++) m_indices[i] = i;
   std::sort(m_indices+1, m_indices+1+m_nA+m_nB, CXSampleRanker(sample));
   return ComputeStatistic(m_indices);
}

// Definition of the class CXSampleRanker

CXSampleRanker::CXSampleRanker(const double * x) : m_x(x) {}

inline bool CXSampleRanker::operator()(int i, int j) const
{ return m_x[i] <= m_x[j]; }
