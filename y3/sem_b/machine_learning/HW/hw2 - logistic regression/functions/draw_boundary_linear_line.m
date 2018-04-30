function draw_boundary_linear_line( X, theta )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

    minX1 = min(X(:,2));
    maxX1 = max(X(:,2));
    
    X2 = @(x1) -(theta(2)*x1 + theta(1)) / theta(3);
    
    line([minX1 maxX1], [X2(minX1) X2(maxX1)]);
end

