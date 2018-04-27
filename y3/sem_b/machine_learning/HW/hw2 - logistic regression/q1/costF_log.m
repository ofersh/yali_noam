function [J, grad] = costF_log(theta , X, y)
    fprintf('X size is (%g, %g)\n', size(X))
    fprintf('Theta size is (%g, %g)\n', size(theta))
    m = length(y);
    theta = theta(:);
    z = theta' * X';
    
    sigmoid = @(z) 1./(1+exp(z));
    
    htheta = sigmoid(z);
    
    J = (-1/m) * (y'*log(htheta') + (1 - y') * log(1 - htheta'));
    grad = 1/m * X' * (htheta - y)'; 
end
