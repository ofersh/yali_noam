% Generating non-linear data
load_p1_a

num_correct=0;
[n,d]=size(X);
theta=zeros(d,1);
k=0;
is_first_iter=1;
current_index=1;

while num_correct<n
  xt=X(current_index,:)';
  yt=y(current_index,:);
  
  a=sign(yt*theta'*xt)
    
    if is_first_iter==1 | a<0
        num_correct=0;
        theta=theta+xt*yt;
        is_first_iter=0;
        k=k+1;
    else
        num_correct=num_correct+1;
    end
    
    current_index=current_index+1;
    plot_points_and_classifier(X,y,theta);
    figure(1)
    pause(0.1)
    
    if current_index>n
        current_index=1;
    end
    
end
        
        
    
    
    