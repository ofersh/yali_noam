close ALL
%x=imread('figures2.jpg') ;
x3=imread('septagon.tif') ;
x=x3(:,:,1) ;
img=edge(x,'canny',0.4) ;
[acc,theta,r]=hough(img,'RhoResolution',0.5,'Theta',-90:0.5:89); 
para=[r theta] ;

figure, imshow(x)
figure, imshow(img)
figure, imshow(acc,[],'XData',theta,'YData',r,...
    'InitialMagnification','fit');
xlabel('\theta'), ylabel('\rho');
axis on, axis normal;