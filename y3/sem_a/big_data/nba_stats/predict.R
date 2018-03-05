library(dplyr)
library(data.table)
library(caret)
library(rpart)


# read all csv files into one data.table
read.files <- function(){
  files <- list.files(pattern = '\\.csv')
  tables <- lapply(files, read.csv, header = TRUE)
  combined.df <- do.call(rbind , tables)
  return(data.table(combined.df))
}

# prepare data table with only DEFICIT, PCT and OUTCOME statistics.
data <- read.files()
outcome=data$OUTCOME
data = data[ ,(grepl('(?:DEFICIT|PCT|OUTCOME).*(?<!M)$', names(data), perl = T)), with=F]
data = data[complete.cases(data)]
data[,DEFICIT_REB:=NULL]

data$OUTCOME = as.factor(data$OUTCOME)
# generate data partition for training and testing
inTrain = createDataPartition(data$OUTCOME, p=0.7, list = FALSE)
training = data[inTrain,]
testing = data[-inTrain,]

# train the algoritham on genrated data.
dtree = train(OUTCOME~., method="rpart", data=training, na.action = na.pass)
print(dtree$ finalModel)

# predict using decision tree.
prediction = predict(dtree, newdata = testing)
print(prediction)

# check using confusion matrix how good is the prediction.
cm = confusionMatrix(prediction, testing$OUTCOME)
print(cm)

# grow a decision tree for visualization.
fit <- rpart(OUTCOME~., method = "class", data=data)

printcp(fit)
plotcp(fit)
summary(fit)
plot(fit, uniform = TRUE, main="Classification Tree for nba stats")
text(fit, use.n = TRUE, all = TRUE, cex=.8)