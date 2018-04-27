clc, clear;

load emaildata1.mat;

pos_ind = find(y==1);
neg_ind = find(y==0);

scatter(X(pos_ind,1),X(pos_ind,2),'go', 'filled'), hold on
scatter(X(neg_ind,1),X(neg_ind,2),'rd', 'filled')