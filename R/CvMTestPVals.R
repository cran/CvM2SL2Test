 cvmts.pval = function(cvmstats, m, n)
.C("CvMTestPVal", 
as.integer(m), 
as.integer(n), 
as.double(cvmstats), 
as.integer( length(cvmstats) ),
pvals = double( length(cvmstats) ))$pvals
#{
# Purpose: compute the p-values for a set of 
# Cramer-von Mises test scores, assuming the 
# test scores are computed from a set of pairs
# samples with sizes m and n
# arguments: cvmstats -- a list of test scores
#            m, n -- sample sizes
# output:
#          a set of p-values

#  len <- length(cvmstats)
#  OutPut = .C("CvMTestPVal", as.integer(m), as.integer(n), 
#                    as.double(cvmstats), as.integer(len),
#      pvals = as.double(len))

#  return(OutPut$pvals)
#}