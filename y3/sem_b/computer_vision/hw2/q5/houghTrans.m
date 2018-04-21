function  houghTrans(x, y )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

    theta = 0:180;
    r =  x * cos(theta) + y * sin(theta);
    
    plot(theta, r);
    

end

