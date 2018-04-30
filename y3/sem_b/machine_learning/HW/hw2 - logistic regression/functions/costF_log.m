function [J, grad] = costF_log(theta , X, y)
% As requested 1.b.3
    m = length(y);
    theta = theta(:);
    z = theta' * X';
        
    htheta = sigmoid(z);
    
    J = (-1/m) * (y'*log(htheta') + (1 - y') * log(1 - htheta'));
    
    grad = 1/m * X' * (y'-htheta)'; 
end
