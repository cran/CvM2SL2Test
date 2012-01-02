cvmts.test = function(x, y)
.C("CvMTestStat", 
as.double(x), 
as.integer(length(x)), 
as.double(y), 
as.integer(length(y)), 
testscore = double(1))$testscore
#{
# Purpose: compute the Cramer-von Mises test score for the two samples x and y
# Arguments: x -- a sample
#            y -- anothe sample
# Output:    the Cramer-von Mises test score

#   OutPut = .C("CvMTestStat", as.double(x), as.integer(length(x)), 
#                    as.double(y), as.integer(length(y)), 
#      testscore = as.double(1))

#  return (OutPut$testscore)   
#}