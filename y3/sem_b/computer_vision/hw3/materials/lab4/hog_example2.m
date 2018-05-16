I1a = imread('hex.jpg');
I1=I1a(:,:,1) ;
I1=255-I1 ;
[hog1,visualization] = extractHOGFeatures(I1,'CellSize',[16 16],'NumBins',3);

figure(1)
subplot(1,2,1);
imshow(I1);
subplot(1,2,2);
plot(visualization);
