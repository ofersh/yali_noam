[featureVector,hogVisualization] = extractHOGFeatures(img);

figure(1);
imshow(img); 
hold on;
plot(hogVisualization);