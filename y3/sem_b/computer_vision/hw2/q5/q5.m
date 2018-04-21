clc; clear all;

nPoints = 1:3;
% a)
% Draw one point transformation
x = 20; y = 10;
figure('Name','One point');
houghTrans(x, y);


% b)
% Draw transformation of points in thbe same line
figure('Name','Same line');
y = @(x) 2*x;
for point = nPoints
   houghTrans(point, y(point)); hold on 
end

% c)

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

% Draw vertical lines trasformation
figure('Name','Perpendicular Lines');
for point = nPoints
   houghTrans(point, 0); hold on 
end
for point = nPoints
   houghTrans(0, point); hold on 
end




