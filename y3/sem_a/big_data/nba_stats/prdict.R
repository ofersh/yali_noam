library(data.table)
library(dplyr)
library(mclust)
library(randomcoloR)
library(FactoMineR)

teams=fread("all.csv")
true.label=teams$OUTCOME
#features=teams[ ,grepl("(?:DEFICIT)", names(teams)), with=F]
#features=teams[,-c(names(teams) %in% c('TEAM_NAME','OUTCOME') ),with= F]
oliver = teams[,c('OUTCOME', 'FT_PCT', 'TO', 'OREB', 'PF')]

pca=prcomp(features[,-1], scale. = T)
data=pca$x
clust=kmeans(data,2)
rand.ind=adjustedRandIndex(true.label, clust$cluster)
