library('datasets')

# 2
plot(iris, col = iris$Species)
# 3
iris2 = data.frame(scale(iris[,1:4]))
iris2 = cbind(iris2, "Species" = iris$Species)

# 4
iris_pca = prcomp(iris2[,1:4])
summ_iris = summary(iris_pca)

# 5
screeplot(summ_iris)
plot(iris_pca$x, col = iris2$Species)

# 6
scatterplot3d(iris_pca$x[,1:3])

# 7
for(x in 1:4) {
  k = kmeans(iris_pca$x[,1:x], center =3)
  cat(x, "\t", adjustedRandIndex(k$cluster, iris2$Species),"\n")
  
}


