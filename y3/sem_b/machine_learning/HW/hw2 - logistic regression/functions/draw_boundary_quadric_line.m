function draw_boundary_quadric_line( X, theta )

    minX1 = min(X(:,2));
    maxX1 = max(X(:,2));

    Xaxis = linspace(minX1, maxX1, 10000);
    
    x2 = @(x1) -(theta(1) + theta(2) * x1 + theta(4) * x1.^2) / theta(3);
    
    X2 = x2(Xaxis);

    plot(Xaxis, X2, 'k');
end

