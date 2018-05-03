close ALL
%img = imread('septagon.tif');
img = imread('hex.jpg');

[ x, y, scores, Ix, Iy ] = harris_corners( img );
figure,  imshow(img) 
hold on
for i = 1:scores
  plot(x(i), y(i), 'r+');
end                                                     
hold off

function [ x, y, scores, Ix, Iy ] = harris_corners(img)
% HARRIS_CORNERS Extracts points with a high degree of 'cornerness' from
% RGB image matrix of type uint8
%   Input - image = NxMx3 RGB image matrix
%   Output - x = nx1 vector denoting the x location of each of n
%                detected corners 
%            y = nx1 vector denoting the y location of each of n 
%                detected corners
%            scores = number of corners found
%            Ix = A matrix with the same number of rows and columns as the
%            input image, storing the gradients in the x-direction at each
%            pixel
%            Iy = A matrix with the same nuimber of rwos and columns as the
%            input image, storing the gradients in the y-direction at each
%            pixel


G = rgb2gray(img);

% convert to double
G2 = im2double(G);

% create X and Y Sobel filters
horizontal_filter = [1 0 -1; 2 0 -2; 1 0 -1];
vertical_filter = [1 2 1; 0 0 0 ; -1 -2 -1];

% using imfilter to get our gradient in each direction
filtered_x = imfilter(G2, horizontal_filter);
filtered_y = imfilter(G2, vertical_filter);

% store the values in our output variables, for clarity
Ix = filtered_x;
Iy = filtered_y;

f = fspecial('gaussian');
Ix2 = imfilter(Ix.^2, f);
Iy2 = imfilter(Iy.^2, f);
Ixy = imfilter(Ix.*Iy, f);

% set empirical constant between 0.04-0.06
k = 0.04;

num_rows = size(img,1);
num_cols = size(img,2);

% create a matrix to hold the Harris values
H = zeros(num_rows, num_cols);

% % get our matrix M for each pixel
for y = 3:size(img,1)-2         % avoid edges
    for x = 3:size(img,2)-2     % avoid edges  
        Ix2_matrix = Ix2(y-2:y+2,x-2:x+2);
        Ix2_mean = sum(Ix2_matrix(:));
        
        % Iy2 mean
        Iy2_matrix = Iy2(y-2:y+2,x-2:x+2);
        Iy2_mean = sum(Iy2_matrix(:));
        
        % Ixy mean
        Ixy_matrix = Ixy(y-2:y+2,x-2:x+2);
        Ixy_mean = sum(Ixy_matrix(:));
        
        % compute R, using te matrix we just created
        Matrix = [Ix2_mean, Ixy_mean; 
                  Ixy_mean, Iy2_mean];
        R1 = det(Matrix) - (k * trace(Matrix)^2);
        
        % store the R values in our Harris Matrix
        H(y,x) = R1;
       
    end
end

% set threshold of 'cornerness' relative to the average R score
avg_r = mean(mean(H));
threshold = abs(100 * avg_r);

[row, col] = find(H > threshold);

y = row;
x = col;
scores=length(x) 
end

