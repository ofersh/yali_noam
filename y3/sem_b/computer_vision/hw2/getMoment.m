function [ M ] = getMoment(mat,i, j, centeralize)
% Calculate matrix i,j Moment considering center of mat as (0,0)
% mat - Input Matrix
% i - x degree of moment
% j - y degree of moment
% centralize - optinal default false.

if ~exist('centeralize','var')
    xCenter = 0;
    yCenter = 0;
else
    M00 = getMoment(mat, 0, 0);
    M01 = getMoment(mat, 0, 1);
    M10 = getMoment(mat, 1, 0);
    xCenter = M10/M00;
    yCenter = M01/M00;
end
    center = floor(size(mat) /2);
    Xaxis = -center(2):center(2);
    Yaxis = -center(1):center(1);
    M = 0;
    for x = Xaxis
       for y = Yaxis 
           x_mat = x + center(2) + 1;
           y_mat = y + center(1) + 1;
           M = M + mat(y_mat,x_mat) * (x - xCenter)^i * (y - yCenter)^j; 
       end
    end
end


