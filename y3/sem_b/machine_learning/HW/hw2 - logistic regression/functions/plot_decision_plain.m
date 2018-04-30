function plot_decision_plain( X, y, theta, decision_plain )

    scatter_data([X(:,2) X(:,3)], y)
    
    decision_plain(X, theta);

end

