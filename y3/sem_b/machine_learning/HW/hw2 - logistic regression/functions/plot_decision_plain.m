function plot_decision_plain( X, y, theta, decision_plain )

    pos_ind = find(y==1);
    neg_ind = find(y==0);
    
    feat1 = X(:,2);
    feat2 = X(:,3);
    
    scatter(feat1(pos_ind), feat2(pos_ind),'go', 'filled'), hold on
    scatter(feat1(neg_ind), feat2(neg_ind),'rd', 'filled'), hold on
    xlabel('feat1'), ylabel('feat2')
    
    decision_plain(X, theta);

end

