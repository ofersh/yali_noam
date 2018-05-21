%% Q1
clear
close all
clc

%% A: Covariance Matrix
X = [2.5 2.4
    0.5 0.7
    2.2 2.9
    1.9 2.2
    3.1 3
    2.3 2.7
    2 1.6
    1 1.1
    1.5 1.6
    1.1 0.9];

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

%% E: Show the new Data is linear independent
% The covariance matrix is diagonal

mappedS = covarianceMat(mappedX)

%% F: Show original Data as linear combination of new Data and Eigen Vectors

fprintf("\t\ta * eig1 + b * eig2 = (X1 X2)\n")
n = size(X,1);
for i=1:n
    fprintf("%6.3f * (%5.3f %5.3f) + %5.3f * (%5.3f %5.3f) = (%.1f %.1f)\n", ...
        mappedX(i,1), eigVectOrg(1,:),mappedX(i,2), eigVectOrg(2,:), X(i,:));
end

%% G: Map data to one feature data.

singleMappedX = X * eigVect(:,1)

%%
% *The Feature Reduction Error is:*
err = min(diag(eigVals))
