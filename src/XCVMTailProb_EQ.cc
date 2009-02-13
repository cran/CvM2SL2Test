#include "XCVMTailProb_EQ.h"

CXCVMTailProb_EQ::CXCVMTailProb_EQ(int nA) 
                 : CXCVMTailProb(nA, nA) 
{ TabulateFreqFuncts(); }

const double CXCVMTailProb_EQ::operator()(const double cvm) const
{ return operator()(ToInt(cvm))/m_dFreqSum; }

const double CXCVMTailProb_EQ::operator()(const int64_t Q) const
{
	CXTailConvolution con;   

	double dFreq = 0.0;   
	for(int i=0; i<(m_nA+1)/2; i++){
      
		int64_t d = 2*i-m_nA;      
		dFreq += con(m_functs[i], Q+d*d);		     
	}
	dFreq *= 2;
   
	if(0 == m_nA%2)    
		dFreq += con(m_functs[m_nA/2], Q);		 

	return dFreq;
}

void CXCVMTailProb_EQ::TabulateFreqFuncts()
{
   m_functs = new CXFreqFunct[m_nA/2+1];

   int u, v;
   int64_t d;   

  // full v-loops     

   for(u=1; u<=m_nA/2; u++){

      d = -u;
      m_functs[0] += d*d;        
      for(v=1; v<u; v++){

         m_functs[v] += m_functs[v-1];
         d = v-u;
         m_functs[v] += d*d;
       }
       m_functs[u] = m_functs[u-1];
       m_functs[u] *= 2;
   }

   // non-full v-loops

   for(u=m_nA/2+1; u<=m_nA; u++){

     d = -u;      
     m_functs[0] += (d*d);

     for(v=1; v<=m_nA-u; v++){

       m_functs[v] += m_functs[v-1];
       d = v-u;
       m_functs[v] += d*d;
     }        
   } 
}
