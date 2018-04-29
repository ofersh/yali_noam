function draw_boundary_quadric_line( X, theta )

    minX2 = min(X(:,3));
    maxX2 = max(X(:,3));

    drawX2 = linspace(minX2, maxX2, 1000);
    
    X1 = @(x2) -(theta(1) + theta(3) * x2 + theta(4) * x2.^2) / theta(2);
    
    drawX1 = X1(drawX2);

    plot(drawX2, drawX1);
end

