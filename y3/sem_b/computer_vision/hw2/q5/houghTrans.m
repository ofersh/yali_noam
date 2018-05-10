function  houghTrans(x, y )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

    theta = 0:180;
    theta = deg2rad(theta);
    r =  x * cos(theta) + y * sin(theta);
    scatter(theta, r);

end

