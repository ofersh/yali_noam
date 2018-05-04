%% Question 5
% Hough Transformation

clc; clear all, close all;

nPoints = 1:3;
%% A:
% Draw one point transformation
x = 20; y = 10;
figure('Name','One point');
houghTrans(x, y);
title('One point')


%% B:
% Draw transformation of points in thbe same line
figure('Name','Same line');
y = @(x) 2*x;
for point = nPoints
   houghTrans(point, y(point)); hold on 
end
title('Same line')

%% C:
% Draw parallel lines trasformation
figure('Name','Parallel lines');
y1 = @(x) x;
y2 = @(x) x+10;
for point = nPoints
   houghTrans(point, y1(point)); hold on 
end
for point = nPoints
   houghTrans(point, y2(point)); hold on 
end
title('Parallel lines')

% Draw vertical lines trasformation
figure('Name','Perpendicular Lines');
for point = nPoints
   houghTrans(point, 0); hold on 
end
for point = nPoints
   houghTrans(0, point); hold on 
end
title('Perpendicular lines')


%% Hough Tranformation Function:
%   function  houghTrans(x, y )
%      theta = 0:180;
%      r =  x * cos(theta) + y * sin(theta);
%      plot(theta, r);
% 
%   end






