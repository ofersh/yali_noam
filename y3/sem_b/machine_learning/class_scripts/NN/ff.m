function [p, detectp] = ff(Theta1, Theta2, X)
%ff_predict employs forward propagation on a 3 layer  networks and determine the labels of the inputs 
% Input arguments 
%   Theta1 - matrix of parameters (weights)  
% between the input and the first hidden %layer
%   Theta2 - matrix of parameters (weights)  
% between the hidden layer and the output 
% layer (or another hidden layer)
%   X - input matrix
% Output arguments:
%   p - the predicted labels of the inputs 
% Usage: [p, detectp] = ff(Theta1, Theta2, X)

X = [ones(length(X),1) X];

Z2 = Theta1 * X';
a2o = sigmoid(Z2);
a2o = [ones(1, size(a2o,2)); a2o];
Z3 = Theta2 * a2o;
hx = sigmoid(Z3);

p = hx;

