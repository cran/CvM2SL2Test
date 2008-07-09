\name{cvmts.pval}
\alias{cvmts.pval}
\title{Computing Exact P-value for Cramer-von Mises Two Sample Tests}
\description{
The Cramer-von Mises two sample test is to test
whether two independent samples were drawn from the same 
population. The function cvmts.pval() evaluates the p-value
for given test statistic.
}
\usage{
cvmts.pval(cvmstats, m, n)
}
\arguments{
  \item{cvmstats}{an R object holding a list of computed Cramer-von Mises
                  test scores.}
  \item{m}{sample size of the first sample.}
  \item{n}{sample size of the second sample.}
}
\value{The returned value the p-value(s)}
\references{Yaunhui Xiao, Alexander Gordon and Andrei Yakovlev (2007), 
A C++ program for the Cramer-von Mises two sample test, 
Journal of Statistical Software, 17(8),
url{http://www.jstatsoft.org}
}
\note{
The function cvmts.pval() first construct the distribution
function, which is represented as seqeunce of tables in my implementation.
This step may be slow, depending the sample sizes n and m as well as 
the capacity of the computer. Once the distribution function is established, 
the function us convolution operation to compute the p-value(s) for given
Cramer-von Mises test statistics. So, if you have a sequence of pairs
of samples of the same sample sizes n and m, it is best to compute
the test scores for all pairs of samples, and then call this function. 
If you compute the p-values seperately, the process may be slow.
}
\author{
Yuanhui Xiao, Department of Mathematics and Statistics, 
Georgia State University, Atlanta, Georgia, 30302
\email{matyxx@langate.gsu.edu}
}
\seealso{cvmts.pval}
\examples{

## sample size of the first sample
n <- 10

## create a sample x of size n from the normal distribution with mean 0 and 
## standard deviation 1
x <- rnorm(n, 0, 1)

## sample size of the second sample
m <- 10

## create a sample y of size m from the normal distribution with mean 1 and
## standard deviation 1
y <- rnorm(m, 1, 1)

## compute the Cramer-von Mises test statistic
 cvm <- cvmts.test(x, y)

## compute the p-value for the test.
 pval <- cvmts.pval(cvm, n, m)

## Now suppose x is a list of samples of the same size (n), and y is a list 
##   of samples of the same size (m),  and you want to test whether each pair
##   (x[i], y[i]) were drawn from the same population, for i = 1, 2, ...

## a bad way to use cvmts.pval()

##   for(i <- 1; i<=length(x); i++){

##      cvm  <- cvmts.test(x[i], y[i])
##      pval <- cvmts.pval(cvm, n, m)
##   }

## Why? In each call to the function cvmts.pval(), in the first step established is 
## the distribution of the Cramer-von Mises test statistics under the 
## assumption that the two sample were drawn from the same population. Then 
## the distribution is used to calculate the p-value. The first step may
## be expensive if the sample sizes n and m are large. 
   
## I prefer the following way

##  initialize   
#    cvms <- seq(1, length(x)) 

##  compute test scores
#   for(i <- 1; i<=length(x); i++){
#     cvms[i] <- cvmts.test(x[i], y[i])
#   }

#   compute p-values
#    pvals <- cvmts.pval(cvms, n, m)
}
\keyword{nonparametric}
