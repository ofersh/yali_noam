%%
%% 1
clc; clear; close all;
load handWrittenDigits.mat

%% 2
dig_reshape = @(X) reshape(X, [20 20]);
num = dig_reshape(X(2700,:));
% imagesc(num), colormap('gray');

load myTheta.mat


p = ff(Theta1, Theta2, X);

[val , ind] = max(p);

result = ind;
m = size(X,1);
Pcorrect = sum(result(:) == y)/m * 100;
fprintf('performance on training set: %f \n',Pcorrect);