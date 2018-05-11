X = [ 4 2 0.6; 4.2 2.1 0.59; 3.9 2 0.58; 4.3 2.1 0.62; 4.1 2.2 0.63];
meanX = mean(X);
n = 5;
S = zeros(3,3);
for i=1:n
    Xt = X(i,:) - meanX;
    S = S + Xt'*Xt;
end

S = S/(n-1)