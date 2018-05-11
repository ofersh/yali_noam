clear, clc, close all

rng(0)
data(:,1) = rand(30,1);
data(:,2) = 3.4 + 1.2 * data(:,1);
data(:,2) = data(:,2) + 0.2*rand(size(data(:,1)));
data = sortrows(data,1);

% Original Data

figure
axes('LineWidth',0.6,...
    'FontName','Helvetica',...
    'FontSize',8,...
    'XAxisLocation','Origin',...
    'YAxisLocation','Origin');
line(data(:,1),data(:,2),...
    'LineStyle','None',...
    'Marker','o');
axis equal

data(:,1) = data(:,1)-mean(data(:,1));
data(:,2) = data(:,2)-mean(data(:,2));
data
% The task is to find the unit vector pointing into the direction with the largest variance 
% within the bivariate data set data.

C = cov(data)

[V,D] = eig(C)

% The rotation helps to create new variables which are uncorrelated, 
% i.e. the covariance is zero for all pairs of the new variables. 
% The decorrelation is achieved by diagonalizing the covariance matrix C. 
% Display the data together with the eigenvectors representing the new coordinate system.

figure
axes('LineWidth',0.6,...
    'FontName','Helvetica',...
    'FontSize',8,...
    'XAxisLocation','Origin',...
    'YAxisLocation','Origin');
line(data(:,1),data(:,2),...
    'LineStyle','None',...
    'Marker','o');
line([0 V(1,1)],[0 V(2,1)],...
    'Color',[0.8 0.5 0.3],...
    'LineWidth',0.75);
line([0 V(1,2)],[0 V(2,2)],...
    'Color',[0.8 0.5 0.3],...
    'LineWidth',0.75);
axis equal

norm(V(:,1))
norm(V(:,2))
dot(V(:,1),V(:,2))

% Calculating the data set in the new coordinate system. 
% We need to flip newdata left/right since the second column is the one with the larges eigenvalue.

newdata = V * data';
newdata = newdata';
newdata = fliplr(newdata)

% Display the newdata together with the new coordinate system.

figure
axes('LineWidth',0.6,...
    'FontName','Helvetica',...
    'FontSize',8,...
    'XAxisLocation','Origin',...
    'YAxisLocation','Origin')
line(newdata(:,1),newdata(:,2),...
    'LineStyle','None',...
    'Marker','o');
axis equal

% Do the same experiment using the MATLAB function PCA. We get same values for newdata and variance.

[coeff,newdatapca,latend,tsquared,variance] = pca(data);
newdatapca
variance

% The new data are decorrelated.

corrcoef(newdata)

olddata=(V^-1)*newdata' ;
olddata'