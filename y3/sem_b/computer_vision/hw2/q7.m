%% Question 7
% create 3, 4 shaped matrix.
three = zeros(7,5); three(1, 1:5) = 1; three(2, 4) = 1; 
three(3,3) = 1; three(4,4) = 1; three(5, 5) = 1; 
three(6, [1 5]) = 1; three(7,2:4) = 1;
four = zeros(7,5); four(1,4) = 1; four(2,[3,4]) = 1; 
four(3,[2,4]) = 1; four(4,[1,4]) = 1; four(5,:) = 1; 
four([6,7],4) = 1;
moments = [ 0,0; 0,1; 1,0; 1,1; 0,2; 2,0 ]'; % moments matrix.
%% A: 
% 3 and 4 figures Moments calculations.
fprintf("For 3 the moments are:\n");
for ij = moments
        M = getMoment(three, ij(1), ij(2));
        fprintf("M(%g,%g) = %g\n", ij(1),ij(2),M);
end
fprintf("For 4 the moments are:\n");
for ij = moments
        M = getMoment(four, ij(1), ij(2));
        fprintf("M(%g,%g) = %g\n", ij(1),ij(2),M);
end
%% B: 
% Centers Calculation.

x3Center = getMoment(three, 1,0)/getMoment(three, 0,0);
y3Center = getMoment(three, 0,1)/getMoment(three, 0,0);

fprintf("For 3 (xCenter, yCenter) is:(%.3g,%.3g)\n", ...
    x3Center,y3Center);

x4Center = getMoment(four, 1,0)/getMoment(four, 0,0);
y4Center = getMoment(four, 0,1)/getMoment(four, 0,0);

fprintf("For 4 (xCenter, yCenter) is:(%.3g,%.3g)\n", ...
    x4Center,y4Center);
%% C: 
% Calculate moments with centralization.

fprintf("For 3 the centralized moments are:\n");
for ij = moments
        M = getMoment(three, ij(1), ij(2), 'center');
        fprintf("M(%g,%g) = %.3g\n", ij(1),ij(2),M);
end

fprintf("\nFor 4 the centralized moments are:\n");
for ij = moments
        M = getMoment(four, ij(1), ij(2), 'center');
        fprintf("M(%g,%g) = %.3g\n", ij(1),ij(2),M);
end
%% Moment Calculation Function:
% 
%   function [ M ] = getMoment(mat,i, j, center)
% Calculate matrix i,j Moment considering center of mat as (0,0)
% mat - Input Matrix
% i - x degree of moment
% j - y degree of moment
% centralize - optinal default false.
% if ~exist('center','var')
%     xCenter = 0;
%     yCenter = 0;
% else
%     M00 = getMoment(mat, 0, 0);
%     M01 = getMoment(mat, 0, 1);
%     M10 = getMoment(mat, 1, 0);
%     xCenter = M10/M00;
%     yCenter = M01/M00;
% end
%     center = floor( size(mat) /2);
%     Xaxis = -center(2):center(2);
%     Yaxis = -center(1):center(1);
%     M = 0;
%     for x = Xaxis
%        for y = Yaxis 
%            x_mat = x + center(2) + 1;
%            y_mat = y + center(1) + 1;
%            M = M + mat(y_mat,x_mat) * (x - xCenter)^i * (y - yCenter)^j; 
%        end
%     end
% end
% 