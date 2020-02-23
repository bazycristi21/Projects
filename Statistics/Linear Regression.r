## A
## Mean, Var, Quartile, Boxplot

meanAirFlow <- mean(stackloss$Air.Flow)
meanWaterTemp <- mean(stackloss$Water.Temp)
meanAcidConc <- mean(stackloss$Acid.Conc.)
meanStackLoss <- mean(stackloss$stack.loss)

print(paste("meanAirFlow:", meanAirFlow))
print(paste("meanWaterTemp:", meanWaterTemp))
print(paste("meanAcidConc:", meanAcidConc))
print(paste("meanStackLoss:", meanStackLoss))

varAirFlow <- var(stackloss$Air.Flow)
varWaterTemp <- var(stackloss$Water.Temp)
varAcidConc <- var(stackloss$Acid.Conc.)
varStackLoss <- var(stackloss$stack.loss)

print(paste("varAirFlow:", varAirFlow))
print(paste("varWaterTemp:", varWaterTemp))
print(paste("varAcidConc:", varAcidConc))
print(paste("varStackLoss:", varStackLoss))

quanAirFlow <- quantile(stackloss$Air.Flow)
quanWaterTemp <- quantile(stackloss$Water.Temp)
quanAcidConc <- quantile(stackloss$Acid.Conc.)
quanStackLoss <- quantile(stackloss$stack.loss)

print(quanAirFlow)
print(quanWaterTemp)
print(quanAcidConc)
print(quanStackLoss)

#par(mfrow=c(1, 1))
boxplot(stackloss$Air.Flow, col="magenta", main="Air.Flow")
boxplot(stackloss$Water.Temp, col="magenta", main="Water.Temp")
boxplot(stackloss$Acid.Conc., col="magenta", main="Acid.Conc.")
boxplot(stackloss$stack.loss, col="magenta", main="stack.loss")

cor(stackloss)
##B


##Create trainingData and testData


set.seed(100)
trainingRowIndex <- sample(1:nrow(stackloss), 0.8*nrow(stackloss))
trainingData <- stackloss[trainingRowIndex, ]
testData <- stackloss[-trainingRowIndex, ]

##Simple Regression, stack.loss ~ Air.Flow


lmMod <- lm(stack.loss ~ Air.Flow, data=trainingData)
stackLossPred <- predict(lmMod, testData)

AIC(lmMod)
BIC(lmMod)
summary(lmMod)

print(stackLossPred)

actualsPreds <- data.frame(cbind(actuals=testData$stack.loss, predicteds=stackLossPred))
correlationAccuracy <- cor(actualsPreds)
print(correlationAccuracy)
head(actualsPreds)
minMaxAccuaracy <- mean(apply(actualsPreds, 1, min) / apply(actualsPreds, 1, max))
minMaxAccuaracy
mape <- mean(abs((actualsPreds$predicteds - actualsPreds$actuals))/actualsPreds$actuals)
mape

##Multiple Regression, stack.loss ~ Air.Flow + Water.Temp + Acid.Conc.


lmModMultiple <- lm(stack.loss ~ Air.Flow + Water.Temp + Acid.Conc., data=trainingData)
stackLossPredMult <- predict(lmModMultiple, testData)

AIC(lmModMultiple)
BIC(lmModMultiple)
summary(lmModMultiple)

actualsPredsMult <- data.frame(cbind(actuals=testData$stack.loss, predicteds=stackLossPredMult))
correlationAccuracyMult <- cor(actualsPredsMult)
print(correlationAccuracyMult)
head(actualsPredsMult)
minMaxAccuaracyMult <- mean(apply(actualsPredsMult, 1, min) / apply(actualsPredsMult, 1, max))
minMaxAccuaracyMult
mapeMult <- mean(abs((actualsPredsMult$predicteds - actualsPredsMult$actuals))/actualsPredsMult$actuals)
mapeMult

##Multiple Regression, stack.loss ~ Air.Flow + Water.Cant

t <- seq(5, 45, 2)
xAdd <- 147 * dnorm(t, 12, 7)
hist(stackloss$stack.loss, main="Histogram of Stackloss", xlab="Water.Cant")
lines(t, 147 * dnorm(t, 12, 7), col="magenta")
newModelTrainingData <-data.frame(trainingData, Water.Cant=xAdd[trainingRowIndex])
newModelTestData <- data.frame(testData, Water.Cant=xAdd[-trainingRowIndex])
lmAddMultiple <- lm(stack.loss ~ Air.Flow + Water.Cant, data=newModelTrainingData)
stackLossPredNewModel <- predict(lmAddMultiple, newModelTestData)

AIC(lmAddMultiple)
BIC(lmAddMultiple)

summary(lmAddMultiple)

actualsPredNewModel <- data.frame(cbind(actuals=newModelTestData$stack.loss, predicteds=stackLossPredNewModel))
correlationNewModel <- cor(actualsPredNewModel)
print(correlationNewModel)
head(actualsPredNewModel)
minMaxAccuaracyNew <- mean(apply(actualsPredNewModel, 1, min) / apply(actualsPredNewModel, 1, max))
minMaxAccuaracyNew
mapeNew <- mean(abs((actualsPredNewModel$predicteds - actualsPredNewModel$actuals))/actualsPredNewModel$actuals)
mapeNew

##C

cauchySec <- seq(-10, 10, by=0.01)
plot(cauchySec, pcauchy(cauchySec), col="blue")
lines(cauchySec, dcauchy(cauchySec), col="magenta")
