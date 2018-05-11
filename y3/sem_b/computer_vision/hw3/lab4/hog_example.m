clear
close ALL
%img = imread('cameraman.tif');
%img = imread('circles.jpg');
img = imread('gantrycrane.png');
[m,n,k]=size(img) ;
zer=zeros(m,n) ;
[featureVector,hogVisualization] = extractHOGFeatures(img,'CellSize',[16 16]);
figure, imshow(img); 
hold on;
plot(hogVisualization);