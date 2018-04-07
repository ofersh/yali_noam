function [ J ] = cost_computation( X, y, theta )
% calculate the cost of given theta.
% with Mean square distance
    m = length(y);
    err = y' - theta * X';
    J=1/(2*m)*sum(err.^2);
end

