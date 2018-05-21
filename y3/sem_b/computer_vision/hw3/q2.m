%% Q2
clear
close all
clc

%% A: Covariance Matrix
X = [7 4 3
    4 1 8
    6 3 5
    8 6 1
    8 5 7
    7 2 9
    5 3 3
    9 5 8
    7 4 5
    8 2 2];
S = covarianceMat(X)

%% B: Covariance matrix Eigen values and vectors
[eigVect, eigVals] = eig(S)


%% C: Sorting Eigen Vectors by Eigen Values descending
eigVectOrg = eigVect;
d = diag(eigVals);
[~, ind] = sort(d, 'descend');
eigVect = eigVect(:,ind)

%% D: Mapped Data using Covariance Eigen vectors
mappedX = (X * eigVectOrg)

fprintf("\t\ta * eig1 + b * eig2 + c * eig3 = (mappedX1 mappedX2 mappedX3)\n")
n = size(X,1);
for i=1:n
    fprintf("%g * (%4.2f %4.2f %4.2f) + %g * (%4.2f %4.2f %4.2f) + %g * (%4.2f %4.2f %4.2f) = (%4.1f %4.1f %4.1f)\n", ...
        X(i,1), eigVectOrg(1,:), X(i,2), eigVectOrg(2,:), X(i,3), eigVectOrg(3,:), mappedX(i,:));
end

%% E: Show the new Data is linear independent
% The covariance matrix is diagonal

mappedS = covarianceMat(mappedX)

%% F: Show original Data as linear combination of new Data and Eigen Vectors

fprintf("\t\ta * eig1 + b * eig2 + c * eig3 = (X1 X2 X3)\n")
n = size(X,1);
eigVectInverse = eigVectOrg^-1;
for i=1:n
    fprintf("%g * (%4.2f %4.2f %4.2f) + %g * (%4.2f %4.2f %4.2f) + %g * (%4.2f %4.2f %4.2f) = (%4.1f %4.1f %4.1f)\n", ...
        mappedX(i,1), eigVectInverse(1,:), mappedX(i,2), eigVectInverse(2,:), mappedX(i,3), eigVectInverse(3,:), X(i,:));
end
%% G: Map data to one feature data.

reductionMappedX = X * eigVect(:,1:2)

%%
% *The Feature Reduction Error is:*
err = min(diag(eigVals))
