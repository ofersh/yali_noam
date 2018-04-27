close ALL
x3=imread('septagon.tif') ;
%x3=imread('hex.jpg') ;
x=x3(:,:,1) ;
img=edge(x,'canny',0.4) ; 
[acc,theta,r]=hough(img,'RhoResolution',2,'Theta',-90:89); 
NUMPEAKS=10 ;
PEAKS = houghpeaks(acc,NUMPEAKS,'Threshold',40,'NHoodSize',[9 9]) ;
[m,n]=size(PEAKS);
for i=1:m    % marking peaks
  PEAKS(i,3)=acc(PEAKS(i,1),PEAKS(i,2))
  acc(PEAKS(i,1)-1:PEAKS(i,1)+1,PEAKS(i,2)-1:PEAKS(i,2)+1)=64 ;
end
figure, imshow(x)
figure, imshow(img)
figure, imshow(acc,[],'XData',theta,'YData',r,...
   'InitialMagnification','fit');
xlabel('\theta'), ylabel('\rho');
axis on, axis normal ;
x1 = theta(PEAKS(:,2)); 
y1 = r(PEAKS(:,1));
figure, plot(x1,y1,'s','color','black');
