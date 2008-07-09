\name{cvmts.test}
\alias{cvmts.test}
\title{Computing Cramer-von Mises Two Sample Test Statistics}
\description{
The Cramer-von Mises two sample test is to test
whether two independent samples were drawn from the same 
population.
}
\usage{
cvmts.test(x, y)
}
\arguments{
  \item{x}{an R object for the first sample, which is a vector}
  \item{y}{an R object for the second sample, which is also a vector} 
}
\value{score of the Cramer-von Mises two-sample test for given samples
}
\author{Yuanhui Xiao
Department of Mathematics and Statistics
Georgia State University
Atlanta, GA 30302
\email{matyxx@langate.gsu.edu}
}
\seealso{cvmts.test}
\examples{
## create a sample x of size 10 from the normal distribution with mean 0 and 
## standard deviation 1
x <- rnorm(10, 0, 1)

## create a sample y of size 10 from the normal distribution with mean 1 and
## standard deviation 1
y <- rnorm(10, 1, 1)


## Call the function to get the Cramer-von Mises test statistic
 cvm <- cvmts.test(x, y)
}
\keyword{nonparametric}
