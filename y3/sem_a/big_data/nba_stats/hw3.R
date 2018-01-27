library('data.table')
library('mclust')
library(FactoMineR)

file_name = "C:/Users/yali/Documents/R_ws/big_data/hw/hw_3/HTRU2/HTRU_2.csv"
pulsar_data = fread(file_name)

q1 = function(pulsar_data){
  # brute_force_feature_selection
  num.features = 1:8
  res = list()
  
  for(i in num.features){
    best.rand = vector()
    
    # genterate all the combinations of a set of numbers
    combination = combn(length(num.features), i)
    num.combination = 1:ncol(combination)
    
    # Calculate the k_means and rand index for a given amount of features
    for(c in num.combination){
      k = kmeans(pulsar_data[,combination[,c],with=FALSE],2)
      rand.score = adjustedRandIndex(k$cluster, pulsar_data$V9) # col number 9 is where the results are
      best.rand = append(best.rand, rand.score)
    }
    res[i] = max(best.rand)
  }
  
  for(r in 1:length(res)){
    print(paste('#features = ',r,' | best score = ', res[r]))
  }
}

q2 = function(pulsar_data){
  # PCA
  num.features = 1:8
  pulsar_data.pca = prcomp(pulsar_data[,1:8], scale. = TRUE)
  
  for( i in num.features){
    k = kmeans(pulsar_data.pca$x[,1:i], 2)
    rand.score = adjustedRandIndex(k$cluster, pulsar_data$V9)
    print(paste('#features = ',i,' | score = ',rand.score ))
  }
  
}

q3 = function(pulsar_data){
  # Plot the two features with the greatest variance
  pulsar_data.pca = prcomp(pulsar_data[,1:8], scale. = TRUE)
  plot(pulsar_data.pca$x[,1:2], col = pulsar_data$V9+3)
  
  # Calculate the variance represented by the two features
  s = summary(pulsar_data.pca)$sdev^2
  print(paste('the varince of the two first dimension is: ', cumsum(s/sum(s))[2]))
}

q4 = function(pulsar_data){
  # Plotting dependency between features after PCA
  pulsar.pca = PCA(pulsar_data, scale.unit=TRUE, graph=T,quanti.sup=c(9: 9))
}

q1(pulsar_data)
q2(pulsar_data)
q3(pulsar_data)
q4(pulsar_data)