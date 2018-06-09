function [ margin ] = decision_boundry_line_with_borders( theta, X, color, model_name)

    theta = theta(:);

    x2 = @(x1) theta(1) * x1/-theta(2);
    minX = min(X(:,1));
    maxX = max(X(:,1));
    
    closest_point = min(abs(X * theta));
    margin = closest_point/norm(theta);
    
    hyperplane = sprintf('%s: HyperPlane', model_name);
    margin_str = sprintf('%s: Margin', model_name);
    subplot(1,2,1)
    h1 = line([minX maxX], [x2(minX) x2(maxX)], 'color', color, 'DisplayName', hyperplane );
    subplot(1,2,2)
    h2 =line([minX maxX], [x2(minX) x2(maxX)] + margin, 'color', color, 'LineStyle','--','DisplayName', margin_str);
    line([minX maxX], [x2(minX) x2(maxX)] - margin, 'color', color, 'LineStyle','--', 'DisplayName', '')
    ylim([-3 3]); xlim([-2 2]);
end

