function [J, grad] = costF_log(theta , X, y)
    [J, grad] = costFunctionWithBias(theta , X, y, 0);
end
