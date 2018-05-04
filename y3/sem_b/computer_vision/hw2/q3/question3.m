%% Question 3
% Calculating the circularity for each object in the images:
%  cell1.bmp, cell2.bmp
clc, clear all;

%% cell1.bmp
image = imread('cell1.bmp');
[seg_im, vals] = segmentation(image);
for val=vals(1 : end-1)
    c = circularity(seg_im, val);
    fprintf('For object of value %3g the circularity is %.3g\n', val, c)
end

%% cell2.bmp
image = imread('cell2.bmp');
[seg_im, vals] = segmentation(image);
for val=vals(1 : end-1)
    c = circularity(seg_im, val);
    fprintf('For object of value %3g the circularity is %.3g\n', val, c)
end


%% Calculating Circularity Function:
%   function [ c ] = circularity( image, val )
% % circularity Calculates circularity for segmented shape.
% % c = circularity calculation.
% % image = segmented image.
% % val = segmented shape value.
% 
%   area = length(find(image == val));
%   perim = myPerim(image, val);
%   c = (4*pi*area)/perim^2;
%   end

%% Laplace perimeter Calculation Function
%   function [ perim ] = myPerim( image, val )
%      perim = 0;
%      [nrows, ncols] = size(image);
%      for x = 1:ncols
%          for y = 1:nrows
%              if image(y, x) == val
%                  k = 0;
%                  for i = -1:1
%                      for j = -1:1
%                          if x+i < 1 || y+j < 1 
%                              continue
%                          end
%                          if image(y+j, x+i) == 255
%                              k = k + 1;
%                              break;
%                          end
%                      end
%                      if k ~= 0
%                          break
%                      end
%                  end
%                  if k ~= 0
%                      perim = perim + 1;
%                      k = 0;
%                  end
%              end
%          end
%      end
% 
%   end

