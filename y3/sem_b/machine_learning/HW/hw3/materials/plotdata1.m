function plotdata1(X,y,theta,b)
% plotdata1 plot the data and a pre-defined linear decision boundary
% Input arguments: X - data points, each row is one sample
%                  y - the corresponding labels
%                  theta - the parameters of the decision boundary
%                  b - bias or threshold
% Usage: plotdata1(X,y,theta,b)
% 
    
    if nargin<=3, b=0; end

    plot(X(y==1,1), X(y==1,2),'ro');
    hold on;
    plot(X(y==-1,1), X(y==-1,2),'bx');
    v = axis;
    xmin = v(1);
    xmax = v(2);
    ymin = -(xmin*theta(1)+b)/theta(2);
    ymax2 = -(xmax*theta(1)+b)/theta(2);
    plot([xmin, xmax], [ymin, ymax2],'g','Linewidth',2);
    axis('tight'),grid
    figure(1)
    hold off;

