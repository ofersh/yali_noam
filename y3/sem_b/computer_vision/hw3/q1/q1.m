% A
X = [2.5 2.4
     0.5 0.7
     2.2 2.9
     1.9 2.2
     3.1 3
     2.3 2.7
     2 1.6
     1 1.6 
     1.5 1.6 
     1.1 0.9];
 
 S = covarianceMat(X);
 
 % B
 [eigVect, eigVals] = eig(S);
 
 
 % C
 eigVectOrg = eigVect;
 d = diag(eigVals);diag(eigVals);
 [out, ind] = sort(d, 'descend');
 eigVect = eigVect(:,ind);
 [out, ind] = sort(d, 'descend');
 eigVect = eigVect(:,ind);
 
 
 % D 
 mappedX = (eigVectOrg' * X')';
 mappedS = covarianceMat(mappedX);
 
 % E
 disp(mappedS)
 
 
 
 