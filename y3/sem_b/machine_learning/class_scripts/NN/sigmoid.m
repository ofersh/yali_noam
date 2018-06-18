function g = sigmoid(z)
% SIGMOID computes a sigmoid function for an input argument z.
% Usage: g = sigmoid(z)

g = zeros(size(z));

g=1./(1+exp(-z));

end
