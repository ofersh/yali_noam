library(data.table)
library(dplyr)
library(ggplot2)
library(FactoMineR)
library(mclust)

match = fread("all.csv")

deficity_table =match[ ,(grepl("(?:OUTCOME|NAME|DEFICIT)", names(match))), with=F]
hist(deficity_table[OUTCOME==1, DEFICIT_REB], breaks = 50)

deficity_table[,DEFICIT_FGA:=NULL][,DEFICIT_FGM:=NULL][,DEFICIT_REB:=NULL]

#x=PCA(deficity_table[,c(-1,-3)], quanti.sup = 1, ncp = 8 )
# y=prcomp(deficity_table[,c(-1)])

main=deficity_table[, names(deficity_table) %in% c('OUTCOME', 'DEFICIT_FGA', 'DEFICIT_FG2A', 'DEFICIT_REB', 'DEFICIT_OREB'), with=F]
diff=main[seq(2,nrow(main),2),]-main[seq(1,nrow(main)-1,2),]

main_opt=deficity_table[, names(deficity_table) %in% c('OUTCOME', 'DEFICIT_FTM', 'DEFICIT_FTA', 'DEFICIT_PF', 'DEFICIT_TO', 'DEFICIT_STL'), with=F]
diff_opt=main_opt[seq(2,nrow(main_opt),2),]-main_opt[seq(1,nrow(main_opt)-1,2),]
diff_opt[,DEFICIT_PF:=-1*DEFICIT_PF][,DEFICIT_PF:=-1*DEFICIT_PF]
diff_opt=sign(diff_opt)
diff_opt[,SUM:=rowSums(diff_opt[,-1])]
diff_OPT=diff_OPT[abs(SUM)==5,]


