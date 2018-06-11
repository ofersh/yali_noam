function [trainInput_n, testInput_n] = normalizeTrainAndTest(trainInput, testInput)
% normalizeTrainAndTest normalizes train and test data
% Input arguments:
% trainInput - train  matrix of feature vectors (each column is a feature
% vector.
% testInput - test matrix of feature vectors
% Output arguments:
% trainInput_n - train matrix of feature vectors after scaling
% testInput_n - test matrix of feature vectors after scaling
% Usage: [trainInput testInput]=normalizeTrainAndTest(trainInput,testInput);
%
[r1 c1] = size(trainInput);
[r2 c2] = size(testInput);
min1=min(trainInput);
max1=max(trainInput);
save min1max1 min1 max1;
mmin1=repmat(min1',1,r1);
mmax1=repmat(max1',1,r1);
mmin2=repmat(min1',1,r2);
mmax2=repmat(max1',1,r2);
trainInput_n=(trainInput-mmin1')./(mmax1'-mmin1');
testInput_n=(testInput-mmin2')./(mmax2'-mmin2');