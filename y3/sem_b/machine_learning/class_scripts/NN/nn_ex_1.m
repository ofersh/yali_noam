% nn learning
% This script demonstrate nn learning using backpropagation algorithm
% (using batch learning) on various data sets
%


clear ; close all; clc

% Loading and visualising the data                    
load('ex3data1.mat');
% Initalization of the parameters 
m = size(X, 1); % number of training examples
InputLayerSize  = size(X,2);  % 
HiddenLayerSize = 15;   %  hidden units
numLabels = 10;          % 10 labels for 10 digits, the label '10' is for digit 0.

% digitdemo % visualizing the data
% pause

% loading the (predefined) parameters
load('myTheta.mat');

p = ff_predict(Theta1, Theta2, X);

fprintf('\n Training Set Accuracy: %f\n', sum(p == y)/m * 100);
pause

% training the network using backpropagation algorithm
%
Theta1 = InitializeParam(InputLayerSize, HiddenLayerSize);
Theta2= InitializeParam(HiddenLayerSize, numLabels);
%load myTheta
p = ff_predict(Theta1, Theta2, X);
fprintf('\nTraining Set Accuracy: %f \n', sum(p == y)/m * 100);
max_iter=20000;
alpha=7;
Lambda=1;
[J, Theta1,Theta2] = bp(Theta1, Theta2, X,y,max_iter,alpha, Lambda);

% Performance of the trained nn on training set:
p = ff_predict(Theta1, Theta2, X);
fprintf('\n Trained net performance on training set: %f \n', sum(p == y)/m * 100);

                          
                          