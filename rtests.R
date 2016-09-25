## 
install.packages("Matrix")
library(Matrix)
m <- matrix(runif(16), byrow = TRUE, nrow=4)
LU <- lu(m)
expand(LU)
