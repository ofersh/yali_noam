clear, clc;

header = ['Question 1\n'...
          'Spot different objects in the picture using Region Grow algorithm\n\n\n'];
      
fprintf(header)

pic =  imread('cell.bmp');
gray_pic = rgb2gray(pic);
seg_pic = gray_pic;
[nrows, ncols] = size(gray_pic(:,:,1));
val = 1;
for x = 2:ncols-1
   for y = 2:nrows-1
      if seg_pic(x,y) == 0
          seg_pic = region_grow(seg_pic, val, x, y);
          val = val + 10;
      end 
   end
end

figure(1); imshow(seg_pic); colormap('gray');
figure(2); h = histogram(seg_pic), title('Different brightness for each object.');
num_of_object = sum(h.Values~=0)-1;
fprintf('Our Calculation Result: Number of Objects is %d\n', num_of_object)
[L, num] = bwlabel(double(~gray_pic));
fprintf('BWLabel Result: Number of Objects is %d\n', num_of_object)



function [gray_pic] = region_grow(gray_pic, val, x, y)
    gray_pic(x,y) = val;
    [nrows, ncols] = size(gray_pic);
    for i = -1:1
        for j= -1:1
            if x+i < 1 || y+j < 1 
                continue
            end
            if x+i > nrows || y+j > ncols
                break
            end
            if gray_pic(x+i, y+j)==0
               gray_pic = region_grow(gray_pic, val, x+i, y+j);
            end
        end
    end
end


