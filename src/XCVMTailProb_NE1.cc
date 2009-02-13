#include "XCVMTailProb_NE1.h"

CXCVMTailProb_NE1::CXCVMTailProb_NE1(int nA, int nB)
                 :CXCVMTailProb(nA, nB)
{ TabulateFreqFuncts((m_nA+m_nB)/2); }

const double CXCVMTailProb_NE1::operator()(const double cvm) const
{ return operator()(ToInt(cvm))/m_dFreqSum; }

const double CXCVMTailProb_NE1::operator()(const int64_t Q) const
{
	CXTailConvolution con;      
	double dFreq = 0;   
	for(int i=m_nA; i>=m_nA/2+1; i--){
    
		int64_t d = (m_nP+m_nQ)*(2*i-m_nA)/2;
		dFreq += con(m_functs[i], m_functs[m_nA-i], Q+d*d);						
	}

	dFreq *= 2;
	if(0 == m_nA%2)
		dFreq += con(m_functs[m_nA/2], Q);

	return dFreq;
}
