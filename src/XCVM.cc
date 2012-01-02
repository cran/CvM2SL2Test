#include "XCVM.h"

CXCVM::CXCVM(int nA, int nB)
{
   m_nA = nA; 
   m_nB = nB;

   int nGCD = GCD(); 
   m_nL = m_nA/nGCD*m_nB;

   m_nP = m_nL/m_nA;
   m_nQ = m_nL/m_nB;

   m_dCoe = (1.0/m_nP)*(1.0/m_nQ);
   m_dCoe /= (m_nA+m_nB);
   m_dCoe /= (m_nA+m_nB);
}

CXCVM::~CXCVM() {}

const int64_t CXCVM::ToInt(const double dStat) const
{
   double iStat = dStat/m_dCoe;

   // find the integer closer to iStat   

   double dCeil = std::ceil( iStat );
   double dFloor = std::floor( iStat );

   return (dFloor+dCeil < 2*iStat) ? 	 
	   static_cast<int64_t>(dCeil) : static_cast<int64_t>(dFloor);
}

const double CXCVM::ToDouble(const int64_t iStat) const
{ return iStat*m_dCoe; }

const int CXCVM::GCD()
{
   int m = m_nA;
   int n = m_nB;

   while(1){

      m %= n;
      if(0 == m) return n;

      n %= m;
      if(0 == n) return m;      
   }
}

