function Theta = InitializeParam(Lin, Lout,factor)
%InitializeParam  randomly initialize the parameters of a layer with Lin
%incoming inputs and Lout outputs 
% Input arguments: 
%   Lin - the number of incoming inputs to the layer
%   Lout - the number of output connections 
% Output arguments:
%   Theta - the initial weight matrix, whose size is Lout x Lin+1 (the +1 is for the bias.
%
% Usage: Theta = InitializeParam(Lin, Lout)
%  

if nargin<3, factor=sqrt(6/(Lin+Lout)); end
Theta = zeros(Lout, Lin+1);
Theta=2*factor*(rand(Lout, Lin+1)-0.5);

