close ALL
%x3=imread('coins.png') ;
x3=imread('coins.jpg') ;
x=x3(:,:,1) ;
img=edge(x,'canny',0.4) ; 
%[centers, radii, metric] = imfindcircles(img,[20 50]);
[acc, centers, radii] = CircularHough_Grd(x,[20 50],10,20);
centers=uint16(centers) ;
[centers radii] 
[m,n]=size(centers) 
for i=1:m
    img(centers(i,2)-1:centers(i,2)+1,centers(i,1)-1:centers(i,1)+1)=255 ;
end

figure, imshow(x,'InitialMagnification','fit');
figure, imshow(img,'InitialMagnification','fit');
figure, imshow(acc,[],'InitialMagnification','fit');
%figure(2); imagesc(acc); colormap('gray'); axis image;
%  hold on;
%  plot(circen(:,1), circen(:,2), 'r+');
%  for k = 1 : size(circen, 1),
%      DrawCircle(circen(k,1), circen(k,2), cirrad(k), 32, 'b-');
%  end
%  hold off;
%  title(['Raw Image with Circles Detected ', ...
%      '(center positions and radii marked)']);