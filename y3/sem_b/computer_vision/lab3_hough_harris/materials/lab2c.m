close ALL
x3=imread('coins.png') ;
x=x3(:,:,1) ;
img=edge(x,'canny',0.4) ; 
[centers, radii, metric] = imfindcircles(img,[20 50]);
[centers radii]
centers=round(centers) ;
[m,n]=size(centers) ;
for i=1:m
    img(centers(i,2),centers(i,1))=255 ;
end

figure, imshow(x,'InitialMagnification','fit');
figure, imshow(img,'InitialMagnification','fit');
% axis on, axis normal ;
