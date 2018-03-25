clear
close ALL
f=imread('septagon.tif') ;
histogram(f)
fn=imnoise(f,'gaussian',0,0.038) ;  % adding Gaussian noise with mean 0 and variance (50/255)^2=0.038
figure, imshow(fn)
figure, histogram(fn)
Tn=graythresh(fn) ;
gn=im2bw(fn,Tn) ;
figure,imshow(gn)
% smooth the image and repeat
h=fspecial('average',5) ;
fa=imfilter(fn, h, 'replicate') ; % averaging to reduce noise
figure, imshow(fa)
figure, imhist(fa)   % histogram after averaging
Ta=graythresh(fa) ;  % calculate global threshold for the image after averaging
ga=im2bw(fa,Ta) ;   % thresholded image
figure, imshow(ga)
