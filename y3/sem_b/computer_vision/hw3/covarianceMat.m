function [ S ] = covarianceMat(X)

 meanX = mean(X);
 [rows, cols] = size(X);
 S = zeros(cols, cols);
 
 for i=1:rows 
     S  = S + (X(i,:) - meanX)' * (X(i,:) - meanX);
 end
 
 S = S/(rows-1);
end

