x=imread('cir.bmp') ;
imshow(x)
y=radon(x,0) ;
figure(2)
plot(y)