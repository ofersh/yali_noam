library(data.table)
library(dplyr)
library(ggplot2)
library(mclust)

match = fread("all.csv")

# organize data
# outcome - The outcome of a match
# deficty table - each row contains data of a team in a certain match.
outcome=match$OUTCOME
deficity_table = match[ ,(grepl('(?:DEFICIT|PCT).*(?<!M)$', names(match), perl = T)), with=F]
deficity_table[,DEFICIT_PF:=1-DEFICIT_PF][, DEFICIT_TO:=1-DEFICIT_TO]


# Plotting data in pairs, trying to find correlation between features.
# plot(deficity_table, col=outcome+2

# scale data.
scaled_data = scale(deficity_table)

# picked what apeers to be the strongest feature:
# DEFICIT_DREB - Defensieve rebound.
# Finding most correlated features with DEFICIT_DREB

pair.correlation = function(tb, feature, thresh){
  len = ncol(tb)
  correlated = vector()
  correlated[1] = feature
  i = 2
  for ( m in 1:len ) {
    if (m == feature ){
       next()
    }
    clust = kmeans(scaled_data[, c(feature, m)], 2)
    rand.index = adjustedRandIndex(outcome, clust$cluster)
    if( rand.index > thresh){
      correlated[i] = m
      i = i + 1
    }
  }
  return(correlated)
}

DREB.corr = pair.correlation(scaled_data, 8, 0.15)
print(DREB.corr)

# Find the best combinations from picked features.

brute.force.F.S <- function(dt, true.lables, chosen_features)
{
  if ( length(chosen_features) == 1 ){
    print("Only one feature. No work here.")
    return(chosen_features)
  }
  selected.features = vector()
  max.rand.index = -Inf
  for (m in c(1:length(chosen_features))) {
    combs = combn(chosen_features, m) # for each Combination.
    for (i in c(1:ncol(combs))) {
      features = combs[, i]
      clust = kmeans(dt[, features] , 2)
      current.rand.index = adjustedRandIndex(true.lables, clust$cluster)
      if (current.rand.index > max.rand.index) {
        max.rand.index = current.rand.index
        selected.features = features
      }
    }
  }
  print('for')
  print(selected.features)
  print(paste0("rand index: ", max.rand.index))
  return(selected.features) 
}


selected_features = brute.force.F.S(scaled_data, outcome, DREB.corr)


outcome.to.featurs = function(dt, true.lables, chosen_features ){
  num_feat = length(chosen_features)
  dt = dt[,chosen_features, with = F]
  dt[,OUTCOME:=true.lables]
  diff_dt=dt[seq(2,nrow(dt),2),]-dt[seq(1,nrow(dt)-1,2),]
  diff_dt=sign(diff_dt)
  
  
  diff_dt[,SUM_ALL:=rowSums(diff_dt)][,SUM_FEATURES:=rowSums(diff_dt[,1:num_feat, with = F])]
  diff_dt=diff_dt[abs(SUM_FEATURES)==(num_feat)]
  won_features = nrow(diff_dt)
  diff_dt=diff_dt[abs(SUM_ALL)==(num_feat+1)]
  won_games = nrow(diff_dt)
  print("present data:")
  print(chosen_features)
  print(paste0("won features: ", won_features, " won games: ", won_games))
  print(paste0("score: ", won_games / won_features))
  print('---------------------------------------')
}

for (m in c(1:length(selected_features))) {
  combs = combn(selected_features, m) # for each Combination.
  for (i in c(1:ncol(combs))) {
    features = combs[, i]
    outcome.to.featurs(as.data.table(scaled_data), outcome, features)
  }
}



