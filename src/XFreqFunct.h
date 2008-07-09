/**
     class CXFreqFunct --- Frequency tabl or frequency function

     Author: Yuanhui Xiao
     Date:   05/06/2005

     Copyright (c) 2006 Yuanhui Xiao
*/

#ifndef CXFreqFunct_H
#define CXFreqFunct_H

#include <cmath>
#include <algorithm>

// Class CXFreqFunct

class CXFreqFunct{

public:

   explicit CXFreqFunct(int areas=1);
   CXFreqFunct(const CXFreqFunct & FreqFuncte);
   ~CXFreqFunct();

   class CXNode{ // the pair of an integer and its frequency

	 friend class CXFreqFunct;

     public:

      CXNode();

      const long GetValue() const;
      const double GetFreq() const;	  

	  operator const long() const { return m_iV; }
      
      const CXNode &operator+=(long v); // adds iV to the value of the pair  

      const CXNode &operator+=(const CXNode &Node); // adds freqs, summe same value
      const CXNode &operator*=(int iF); // the freq is multiplied by iF

	      // The methods below only compare the values, no matter what the freqs are.
      bool operator==(const CXNode &Node) const;     
      bool operator<( const CXNode &Node) const;    
      
      bool operator==(const long Node) const; 
      bool operator<=(const long Node) const;
      bool operator>=(const long Node) const;
      bool operator<( const long Node) const;         

	 protected:

      long   m_iV; // the integer or value
      double m_dF; // the frequency, which may be huge.
                   // So it is represented as double in
                   // instead of int.
   };

   typedef CXFreqFunct::CXNode* iterator;
   typedef const CXFreqFunct::CXNode* const_iterator;

   typedef CXFreqFunct::CXNode& reference;
   typedef const CXFreqFunct::CXNode& const_reference;

   iterator begin();
   iterator end();

   const_iterator begin() const;
   const_iterator end() const;

   reference operator[](int i);  // accesses the i-th pair or node
   const_reference operator[](int i) const; 

   reference GetAt(int i);  // accesses the i-th pair or node
   const_reference GetAt(int i) const; 

   const CXFreqFunct & operator=(const CXFreqFunct &);  // assignement  
   const CXFreqFunct & operator+=(const CXFreqFunct &); // sum of frequency functions 
   const CXFreqFunct & operator*=(int iF); // each freq is multiplied by iF
   const CXFreqFunct & operator+=(long iV); // shift the freq. funct or table
   
   const int Size()     const;    // gets the number of pairs or nodes
   const int GetNodes() const;   // gets the number of pairs or nodes
   void ReSetNodes(int nNewNodes); // reset the number of nodes or pair in the table

   const int MinIndexNotLessThan(long Q) const; // finds the smallest index of the pair or node
                                         // whose value is not less than Q
   const int MinIndexNotLessThan(long Q, int LB, int UB) const;
                                           // Same as above, but the search is restricted
                                           // in the range (LB, UB)
   const double SumFreqs(int LB, int UB) const;  // computes the sum of the frequencies 
                                           // of the nodes or pairs whose values fall in
                                           // the range (LB, UB)
   void ToCumus(int iLast=0);  // forms the cumulative frequency table
   void ToTails(int iFirst=1); // forms the tail frequency table

protected:

   void MergeTo(CXFreqFunct &merged);

protected:

   CXNode* m_nodes; // the array holding the nodes or pairs. It is 1-based. 
   int m_nNodes;    // number of nodes
};

/*
   Class CXTailConvolution: Find the sum of frequencies of 
   values in the convolution of two frequency functions larger than 
   or equal to a given value Q.
*/

struct CXTailConvolution {

	const double 
		operator()(const CXFreqFunct & F, int Q) const;
	     // A table convoluts itself

	const double 
		operator()(const CXFreqFunct &F1, const CXFreqFunct &F2, int Q) const;
	    // Convolute two tables

protected:

	const double
		helper(const CXFreqFunct &F1, int n1, int S1, 
               const CXFreqFunct &F2, int n2, int S2, int Q) const;				
};

#endif
