frepcomgen <- function(n,m){
  mat <- matrix(nrow = m+2, ncol = n+2)      # generam o matrice cu m+2 linii si n+2 coloane in care vom construi repartitia comuna
  maxrangen <- 6*n
  sumcol = c()    # sumcol[j] reprezinta suma elementelor de pe coloana j pana la elementul mat[i,j]
  sumlin = c()    # sumlin[i] reprezinta suma elementelor de pe linia i pana la elementul mat[i,j]
  for(i in 1:(n+1))    
  { 
    sumcol[i] <- 0    #initilizam ambiii vectori cu 0 pe toate pozitiile
    sumlin[i] <- 0    
  }

  for(index in 1:n+1)
  {
    mat[1,index] <- index - 1   ## creez X 
  }
  
  for(index in 1:m+1)
  {
    mat[index,1] <- index - 1   ## creez Y
  }
  
  maxvalue <- 1/n
  sum <- 0
  for(index in 2:n){
    x <- runif(1,0.1,maxvalue)           # generz un numar random intre 0.1 si maxvalue
    x = format(round(x, 2), nsmall = 2) # se rotunjeste numarul generat cu precizie 2
    mat[m+2,index] <- x             ## generez pi
    sum <- sum + as.numeric(x)           # facem suma tuturor elementelor puse pana la acest moment
  }
  mat[m+2,n+1] <- 1-sum              # pe ultima pozitie va fi 1 - sum
  
  maxvalue <- 1/m
  sum <- 0
  for(index in 2:m){
    x <- runif(1,0.1,maxvalue)
    x = format(round(x, 2), nsmall = 2)    ## generez qi
    mat[index,n+2] <- x
    sum <- sum + as.numeric(x)      # Analog ca la pi
  }
  mat[m+1,n+2] <- 1-sum
  for(i in 2:m){
    maxvalue <- as.numeric(mat[i,n+2])  
    sum <- 0
    for(j in 2:n){
      x <- runif(1,0.01,maxvalue)
      x = format(round(x, 2), nsmall = 2)   # folosim precizie de 2 zecimale (pentru varianta fara rotunjire comentati aceasta linie)
      if((as.numeric(sumcol[j]) + as.numeric(x) + (m - i)*0.01) > mat[m+2,j] || as.numeric(sumlin[i])+as.numeric(x) +(n-j)*0.01 > mat[i,n+2])
      {# verificam daca putem plasa numarul generat pe pozitia pe care ne aflam (adica daca suma totala nu depaseste elementul pi sau qj)
      
        x <- 0.01   # daca elementul generat este prea mare, plasam elementul minim posibil pe pozitia pe care ne aflam.
        # elementul minim posibil este 0.01 deoarece folosim precizie de 2 zecimale
      }
      
      mat[i,j] = x
      sumcol[j] <- sumcol[j] + as.numeric(x)
      sumlin[i] <- sumlin[i] + as.numeric(x)  #actualizam sumlin si sumcol
      sum <- sum + as.numeric(x)
    }
  }
  return(mat)   # returnam  matricea care reprezinta repartitia comuna
}

fcomplrepcom <- function(mat)
{
  n = ncol(mat) - 2
  m = nrow(mat) - 2
  for(i in 2:m){
    sum <- 0
    for(j in 2:n){
      sum <- sum + as.numeric(mat[i,j])   # calculam suma elementelor care exista pe linia i
    }
    mat[i,n+1] = round(as.numeric(mat[i,n+2]) - sum,2)  # valoarea cautata pentru pozitia lipsa de pe linia i este pi - sum
  }
  for(i in 2:(n+1))
  {
    sum <- 0
    for(j in 2:m)
    {
      sum <- sum + as.numeric(mat[j,i])
    }
    mat[m+1,i] <- round(as.numeric(mat[m+2,i]) - sum,2)   # analog pentru coloana j
  }
  return(mat)
}
fverind <- function(matt_resolved)
{
  n <- ncol(X) - 2
  m <- ncol(Y) - 2
  ok <- 1
  for(i in (2:n))
  {
    for(j in (2:m))
    {
      if(as.numeric(matt_resolved[i,n+2]) * as.numeric(matt_resolved[m+2,j]) != as.numeric(matt_resolved[i,j]))  # verificam daca exista i si j pentru care p(i) * q(j) != PI(i,j)  
      {
        ok <- 0   # daca da, ok devine 0.
      }
    }
  }
  return(ok)  # returneaza ok
}
fvernecor <- function(cov) # primeste valoarea covariantei
{
  if(cov == 0)   
  {
    print("Variabilele sunt necorelate")   # daca covarianta are valoarea 0 atunci X si Y sunt necorelate
  }else{
    print("Variabilele nu sunt necorelate")  # daca covarianta este diferita de 0 atunci X si Y  nu sunt necorelate
  }
}
#a)
matt <- frepcomgen(3,3)   # creeaza repartitia incompleta pentru variabilele X de lungime n si Y de lungime m
#b)
matt_resolved <- fcomplrepcom(matt)   # completeaza repartitia incompleta
#c)
Ex <- 0
Ey <- 0 
n = ncol(matt_resolved)
m = nrow(matt_resolved)
X <- matrix(nrow = 2, ncol = n)
Y <- matrix(nrow = 2, ncol = m)    

for(i in 2:(n-1))
{
  Ex <- Ex + as.numeric(matt_resolved[1,i])*as.numeric(matt_resolved[m,i])   # calculeaza E(x)
  X[2,i-1] <- as.numeric(matt_resolved[m,i])    # Genereaza X folosind repartitia comuna completa
  X[1,i-1] <- i-1
}

for(i in 2:(m-1))
{
  Ey <- Ey + as.numeric(matt_resolved[i,1])*as.numeric(matt_resolved[i,n])  #Analog pentru Y
  Y[2,i-1] <- as.numeric(matt_resolved[i,n])
  Y[1,i-1] <- i-1
}

Exy <- 0

for( i in 2:(m-1))
{
 
  for(j in 2:(n-1))
  {
    Exy <- Exy +as.numeric(matt_resolved[i,j]) * as.numeric(matt_resolved[i,1]) * as.numeric(matt_resolved[1,j])  # Calculeaza E(XY) folosind repartitia comuna
  }
}

cov <- Exy - Ex*Ey   # Calculeaza covarianta folosind formula
print(-15*cov)    # cov(5X,-3Y) = -15cov(X,Y) 


pX <-X[2,1] + X[2,2]
print("P(0<X<3/Y>2):")
print(pX)

pX1 <- 0
if(n >= 7)
{
  for(i in 7:(n-2))
  {
    
    pX1 <- pX1 +X[2,i] #Calculam P(X>6)
  }
}

pY1 <- 0
# Calculam P(Y>7)
if(m >= 7)
{
  for(i in 1:6)
  {
    pY1 <- pY1 +Y[2,i]
  }
}else{
  for(i in 1:(m-2))
  {
    pY1 <- pY1 + Y[2,i]
  }
}
print("P(X>6,Y<7):")
print(pX1*pY1)

if(fverind(matt_resolved) == 1)  # In functie de rezultatul functiei fverind afisam:
{
  print("X si Y sunt independente")
}else{
  print("X si Y nu sunt independente")
}
fvernecor(cov)
