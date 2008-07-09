#include "XCVMTailProb_NE2.h"

CXCVMTailProb_NE2::CXCVMTailProb_NE2(int nA, int nB)
                  :CXCVMTailProb(nA, nB)
{ TabulateFreqFuncts((m_nA+m_nB)/2); }

const double CXCVMTailProb_NE2::operator()(const double cvm) const
{ return operator()(ToInt(cvm))/m_dFreqSum; }

const double CXCVMTailProb_NE2::operator()(const long Q) const
{		
	CXTailConvolution con; 

	double dFreq = 0.0;
	if(0 == m_nA%2){

		for(int i=m_nA-1; i>=m_nA/2; i--){
              
			dFreq += con(m_functs[i+1], m_functs[m_nA-i-1], Q);
			dFreq += con(m_functs[i], m_functs[m_nA-1-i], Q);                
		}

		dFreq *= 2;
		dFreq += con(m_functs[m_nA/2], Q);
	}else{
             
		dFreq += con(m_functs[m_nA], m_functs[0], Q);
		for(int i=m_nA-1; i>=(m_nA+1)/2; i--){

			dFreq += con(m_functs[i], m_functs[m_nA-1-i], Q);
			dFreq += con(m_functs[i], m_functs[m_nA-i], Q);
		}

		dFreq *= 2;
		dFreq += con(m_functs[(m_nA-1)/2], Q);               
	} 

	return dFreq;
}
