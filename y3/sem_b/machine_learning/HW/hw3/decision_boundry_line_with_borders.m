function [ margin ] = decision_boundry_line_with_borders( theta, X, color)

    theta = theta(:);

    x2 = @(x1) theta(1) * x1/-theta(2);
    minX = min(X(:,1));
    maxX = max(X(:,1));
    
    closest_point = min(abs(X * theta));
    margin = closest_point/norm(theta);
    
    line([minX maxX], [x2(minX) x2(maxX)], 'color', color)
    line([minX maxX], [x2(minX) x2(maxX)] + margin, 'color', color, 'LineStyle','--')
    line([minX maxX], [x2(minX) x2(maxX)] - margin, 'color', color, 'LineStyle','--')

end

