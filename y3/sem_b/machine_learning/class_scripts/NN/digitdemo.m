function []=digitdemo(X,y,row,col,t,flag)
% digitdemo for handwritten digit demonstration
% Input arguments
% X - the digit images, each row represents one image
% y - the digit labels
% row - number of digit rows in a matrix presenation
% col - number of digit columns in a matrix presenation
% t - time of pause between each digit
%   flag - if flag==0, the function present each digit at a time
%          otherwise the digits are presented on a matrix of row x col
% Usage: digitdemo(X,y,row,col,t,flag)
% Example: digitdemo(X,y,5,5,1,1) 

clf
% load ex3data1

if nargin<6, flag=1; end
if nargin<5,t=0.2; end
if nargin<4,col=1; end
if nargin<3,row=1; end


colormap('gray')
m=size(X,1);
num_pixels=size(X,2);
imagew=sqrt(num_pixels);
imagel=imagew;
r=randperm(m);

for k=1:row*col
    x1=reshape(X(r(k),:),imagew,imagel);
    if flag==0
        imagesc(x1)
        axis off
        axis('square')
        s=sprintf('"%d"',y(r(k)));
        title(s);
    else
        subplot(row,col,k)
        imagesc(x1)
        axis off
        axis('square')
        s=sprintf('"%d"',y(r(k)));
        title(s);
    end
    figure(1)
    pause(t)
end

