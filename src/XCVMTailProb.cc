#include "XCVMTailProb.h"

CXCVMTailProb::CXCVMTailProb(int nA, int nB)
              : CXCVM((nA<=nB?nA:nB), (nA<=nB?nB:nA))
{
   double* coes = new double[m_nA+1];

   int u, v;
   for(v=0; v<=m_nA; v++)
      coes[v] = 1.0;

   for(u=1; u<=m_nB; u++)
     for(v=1; v<=m_nA; v++)
        coes[v] += coes[v-1];

   m_dFreqSum = coes[m_nA]; 
     // which is {m+n \choose m}
   
   delete [] coes;   
}

CXCVMTailProb::~CXCVMTailProb()
{ delete [] m_functs; }

const double CXCVMTailProb::operator()(const double cvm) const
{ return operator()(ToInt(cvm))/m_dFreqSum; }

void CXCVMTailProb::TabulateFreqFuncts(int iStep)
{
   m_functs = new CXFreqFunct[m_nA+1];

   int u, v;
   int64_t d, iAdd;

   // initialize
   iAdd = 0;
   for(v=1; v<=m_nA; v++){

      d = m_nP*v;
      iAdd += d*d;
      m_functs[v] += iAdd;
   }

   // full v-loops        
   for(u=1; u<=iStep-m_nA; u++){

      d = -m_nQ*u; 
      m_functs[0] += d*d;
      for(v=1; v<=m_nA; v++){
          
         m_functs[v] += m_functs[v-1];
         d = m_nP*v-m_nQ*u;
         m_functs[v] += d*d;
      }
   }

    // non-full v-loops
   for(u=iStep-m_nA+1; u<=iStep; u++){

      d = -m_nQ*u;
      m_functs[0] += d*d;
      for(v=1; v<=iStep-u; v++){

         m_functs[v] += m_functs[v-1];
         d = m_nP*v-m_nQ*u;
         m_functs[v] += d*d;
      }
   }
}


