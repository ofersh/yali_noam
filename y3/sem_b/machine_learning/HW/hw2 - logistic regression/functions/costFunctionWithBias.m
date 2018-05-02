function [ J, grad ] = costFunctionWithBias( theta , X, y, lambda )

% As requested 1.b.3
    m = length(y);
    theta = theta(:);
    z = theta' * X';

    htheta = sigmoid(z);
    
    bias = lambda/(2*m) * sum(theta.^2);
    J = (-1/m) * (y'*log(htheta') + (1 - y') * log(1 - htheta')) + bias;
    
    grad_bias = (lambda/m) * theta;
    grad = 1/m * X' * (y'-htheta)' + grad_bias; 

end

