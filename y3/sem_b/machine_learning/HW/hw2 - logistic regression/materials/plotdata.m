function []=plotdata(X,y);
% Plotting the data (X rows) and the labels (y)
figure(1)
plot(X(y==0,1),X(y==0,2),'ko','MarkerFaceColor', 'g')
hold on
plot(X(y==1,1),X(y==1,2),'kd', 'MarkerFaceColor', 'r')
grid
figure(1)
hold off