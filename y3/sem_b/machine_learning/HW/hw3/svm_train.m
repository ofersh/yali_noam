function [theta] = svm_train( X, y )

d = size(X,2);
H = eye(d);
f = zeros(d,1);
Dy = diag(y);
A = Dy*X;
b = ones(size(y));

theta = quadprog(H, f, -A, -b);


end

