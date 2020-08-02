# Reading datasheet
train=read.csv("axisbank/train.csv")
test=read.csv("axisbank/test.csv")
final=read.csv("axisbank/test.csv")

# Removing the app_id no need of that because it does't affect datasheet
train=train[,c(-1)]

# Removing the app_id no. and and seriel no. need of that because it does't affect datasheet
test=test[,c(-1,-2)]

# from summary get the median value
summary(train$var_d2)

# Preprosessing
# Datasheet has outilier,NA's 

# imputing the median value instead of outlier '-1' and '0'
# median of var_d2 column in train file is 778
# Why median
# the difference between the value of outlier and maximum value is too large

train$var_d2[train$var_d2== -1]=778   
train$var_d2[train$var_d2== 0]=778
train$var_d2[is.na(train$var_d2)] = 778

# from summary get the median value
summary(test$var_d2)

#imuting the median value instead of outlier '-1' and '0'
# median of var_d2 column in train file is 778
# Why median
# the difference between the value of outlier and maximum value is too large
test$var_d2[test$var_d2== -1]=778  
test$var_d2[test$var_d2== 0]=778
test$var_d2[is.na(test$var_d2)] = 778



# converted categorical into numerical so that NA's get some value both in test and train file
# to train model easy

train$var_d1=as.numeric(factor(train$var_d1))
train$var_d3=as.numeric(factor(train$var_d3))
train$var_d4=as.numeric(factor(train$var_d4))
train$var_d5=as.numeric(factor(train$var_d5))
train$var_d6=as.numeric(factor(train$var_d6))
train$var_d7=as.numeric(factor(train$var_d7))
train$var_d8=as.numeric(factor(train$var_d8))
train$var_d11=as.numeric(factor(train$var_d11))

# similary in test file also to predict value

test$var_d1=as.numeric(factor(test$var_d1))
test$var_d3=as.numeric(factor(test$var_d3))
test$var_d4=as.numeric(factor(test$var_d4))
test$var_d5=as.numeric(factor(test$var_d5))
test$var_d6=as.numeric(factor(test$var_d6))
test$var_d7=as.numeric(factor(test$var_d7))
test$var_d8=as.numeric(factor(test$var_d8))
test$var_d11=as.numeric(factor(test$var_d11))

?h2o
#This is a package for running H2O via its REST API from within R.
#To communicate with a H2O instance, the version of the R package 
#must match the version of H2O. When connecting to a new H2O cluster,
#it is necessary to re-run the initializer.
#The operation will be done on the server associated with the data 
#object where H2O is running, not within the R environment).
library(h2o)

#initializer
# active connection to an H2O cluste
h2o.init(nthreads = -1)

# using random forest model with h2o.ai
model=h2o.randomForest(y='target',ntree=2350,training_frame = as.h2o(train))

# summary of model
#to check MSE,RMSE, MAE, RMSLE, Mean Residual Deviance
summary(model)

# Predicting target value using trained model
prob_pred=h2o.predict(model,newdata = as.h2o(test))

# Converting environment into dataframe
p=as.data.frame(prob_pred)

# Column bind test file named final(loaded above) with p dataframe
# named it testing
testing=cbind(final,p)

# Selecting only app_id and predicted value of testing file
# stored in testing
testing=testing[,c(2,167)]

# Exporting testing as FINAL name
write.csv(testing, file = "FINAL.csv")

# shuting down h2o 
h2o.shutdown()
Y

#######################################################



