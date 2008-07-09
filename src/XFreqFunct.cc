#include "XFreqFunct.h"

// implementation of class CXFreqFunct

CXFreqFunct::CXFreqFunct(int nodes)
{
   m_nNodes = nodes;
   m_nodes = new CXNode[m_nNodes];
   m_nodes--;
}

CXFreqFunct::CXFreqFunct(const CXFreqFunct & FreqFunct)
{
   m_nNodes = FreqFunct.m_nNodes;
   m_nodes = new CXNode[m_nNodes];   
   m_nodes--;

   for(int i=1; i<=m_nNodes; i++)
      m_nodes[i] = FreqFunct.m_nodes[i];   
}

CXFreqFunct::~CXFreqFunct()
{
   delete [] (++m_nodes);
}

CXFreqFunct::CXNode::CXNode()
{
   m_iV = 0;
   m_dF = 1;
}

const long CXFreqFunct::CXNode::GetValue() const
{
   return m_iV;
}

const double CXFreqFunct::CXNode::GetFreq() const
{
   return m_dF;
}

inline const CXFreqFunct::CXNode & 
CXFreqFunct::CXNode::operator+=(long id2)
{
   m_iV += id2; 
   return *this;
}

inline const CXFreqFunct::CXNode & 
CXFreqFunct::CXNode::operator+=(const CXNode &node)
{
   m_dF += node.m_dF; 
   return *this;
}

inline const CXFreqFunct::CXNode & 
CXFreqFunct::CXNode::operator*=(int iNum)
{
   m_dF *= iNum;
   return *this;
}

inline bool CXFreqFunct::CXNode::operator==(const CXNode &Node) const
{
   return (m_iV == Node.m_iV);  
}

inline bool CXFreqFunct::CXNode::operator<(const CXNode &Node) const
{
   return (m_iV < Node.m_iV);  
}

inline bool CXFreqFunct::CXNode::operator==(const long Node) const
{
   return m_iV == Node;  
}

inline bool CXFreqFunct::CXNode::operator<=(const long Node) const
{
   return m_iV <= Node;
}

inline bool CXFreqFunct::CXNode::operator>=(const long Node) const
{
   return m_iV >= Node;  
}

inline bool CXFreqFunct::CXNode::operator<(const long Node) const
{
   return m_iV < Node;  
}

inline CXFreqFunct::iterator CXFreqFunct::begin()
{
   return m_nodes+1;
}

inline CXFreqFunct::iterator CXFreqFunct::end()
{
   return m_nodes+1+m_nNodes;
}

inline CXFreqFunct::const_iterator CXFreqFunct::begin() const
{
   return m_nodes+1;
}
   
inline CXFreqFunct::const_iterator CXFreqFunct::end() const
{
   return m_nodes+1+m_nNodes;
}

CXFreqFunct::reference CXFreqFunct::operator[](int i) 
{
   return m_nodes[i];
}

CXFreqFunct::const_reference CXFreqFunct::operator[](int i) const
{
   return m_nodes[i];
}

inline CXFreqFunct::reference CXFreqFunct::GetAt(int i) 
{
   return m_nodes[i];
}

inline CXFreqFunct::const_reference CXFreqFunct::GetAt(int i) const
{
   return m_nodes[i];
}

const CXFreqFunct &
CXFreqFunct::operator=(const CXFreqFunct &FreqFunct)
{  
   if(this != &FreqFunct){

      if(m_nNodes != FreqFunct.m_nNodes){

         delete [] (++m_nodes);
         m_nNodes = FreqFunct.m_nNodes;
         m_nodes = new CXNode[m_nNodes];         
         m_nodes--;
      }

      for(int i=1; i<=m_nNodes; i++)
        m_nodes[i] = FreqFunct.m_nodes[i];
   }
   return *this;
}

const CXFreqFunct &
CXFreqFunct::operator+=(const CXFreqFunct &ff) 
{
   CXFreqFunct Temp(GetNodes() + ff.GetNodes());
   std::merge(begin(), end(), ff.begin(), ff.end(), Temp.begin());
   Temp.MergeTo(*this);

   return *this;
}

const CXFreqFunct &
CXFreqFunct::operator*=(int iF)
{
   for(int i=1; i<=m_nNodes; i++)
      m_nodes[i] *= iF;  

   return *this;
}

const CXFreqFunct &
CXFreqFunct::operator+=(long iV)
{
  for(int i=1; i<=m_nNodes; i++)
     m_nodes[i] += iV;
   
  return *this;
}

inline const int CXFreqFunct::Size() const
{
   return m_nNodes;
}

inline const int CXFreqFunct::GetNodes() const
{
   return m_nNodes;
}

void CXFreqFunct::ReSetNodes(int nNewNodes)
{
  if(m_nNodes != nNewNodes){

     delete [] (++m_nodes);
     m_nNodes = (nNewNodes <= 0 ? 1 : nNewNodes);
     m_nodes = new CXNode[m_nNodes];
     m_nodes--;
  }
  m_nNodes = nNewNodes;
}

const int CXFreqFunct::MinIndexNotLessThan(long Q, int LB, int UB) const
{
    if(m_nodes[LB] >= Q){

	return LB;

    }else if(m_nodes[UB] < Q){
  
        return UB+1;

    }else{  // binary search

	int M, L=LB, U = UB;
	while(U-L > 1){
			
	   M = (L+U)/2;
	   if(m_nodes[M] == Q)
              return M;
	   else if(m_nodes[M] <= Q)
	      L = M;
	   else
	      U = M;
	}

	return (m_nodes[U]<Q ? U+1 : U);
    }
}

const int CXFreqFunct::MinIndexNotLessThan(long Q) const
{ return MinIndexNotLessThan(Q, 1, m_nNodes); }

const double CXFreqFunct::SumFreqs(int LB, int UB) const
{
    double dSum = 0.0;
    for(int i=LB; i<=UB; i++)
       dSum += m_nodes[i].GetFreq();

    return dSum;
}

void CXFreqFunct::ToCumus(int iLast) 
{
   if(iLast == 0)
      iLast = m_nNodes;

   for(int i=2; i<=iLast; i++)
      m_nodes[i].m_dF += m_nodes[i-1].m_dF;   
}

void CXFreqFunct::ToTails(int iFirst)
{
   for(int i=m_nNodes-1; i>=iFirst; i--)
      m_nodes[i].m_dF += m_nodes[i+1].m_dF;
}

void CXFreqFunct::MergeTo(CXFreqFunct &Merged)
{
   int n = GetNodes();
   CXFreqFunct temp(n);

   temp[1] = GetAt(1);
   int i, iM=1;
   for(i=2; i<=n; i++){

     if(GetAt(i) == temp[iM])
       temp[iM] += GetAt(i);
     else
       temp[++iM] = GetAt(i);     
   }   

   Merged.ReSetNodes(iM);
   for(i=1; i<=iM; i++)
     Merged[i] = temp[i];
}

// implementation of class CXConvolution

const double CXTailConvolution::
operator()(const CXFreqFunct &F, int Q) const
{
	const int n = F.Size();
    const int S0 = F.MinIndexNotLessThan(Q-F[n]);

	return helper(F, n, S0, F, n, S0, Q);
}
	     
const double CXTailConvolution::
operator()(const CXFreqFunct &F1, const CXFreqFunct &F2, int Q) const
{
	const int n1 = F1.Size();
	const int n2 = F2.Size();
	const int S1 = F1.MinIndexNotLessThan(Q-F2[n2]);     
	const int S2 = F2.MinIndexNotLessThan(Q-F1[n1]);

	if(n1-S1 <= n2-S2 )		
		return helper(F1, n1, S1, F2, n2, S2, Q);
    else		
		return helper(F2, n2, S2, F1, n1, S1, Q);	
}
	
const double CXTailConvolution::
helper(const CXFreqFunct &F1, int n1, int S1, 
       const CXFreqFunct &F2, int n2, int S2, int Q) const
{
	int LB = n2+1, UB;
	double dFreq = 0, dSumFreq = 0;
	for(int i=S1; i<=n1; i++){
         
		UB = LB-1;
		LB = F2.MinIndexNotLessThan(Q-F1[i], S2, UB); 
		dSumFreq += F2.SumFreqs(LB, UB);
		dFreq += dSumFreq*F1[i].GetFreq();
		if(LB == S2){
      
			dFreq += dSumFreq*F1.SumFreqs(i+1, n1);
			break;
		}
	}      
	return dFreq;
}