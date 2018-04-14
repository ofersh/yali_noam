function [J, grad] = cost_log(theta , X, y)
    m = length(y);
    theta = theta(:);
    y = 0;
    J = 0;
    grad = zeros(size(theta));
    z = theta' * X;
    
    sigmoid = @(z) 1./(1+exp(z));
    
    htheta = sigmoid(z);
    
    J = -1/ (m * (y'*log(htheta) + (1 - y') * log(1 - htheta)));
    grad = 1/m * X' * (htheta - y);
    
end
