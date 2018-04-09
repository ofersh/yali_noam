
pic =  imread('cell.bmp');
[nrows, ncols] = size(pic);
val = 1;
for x = 1:ncols
   for y = 1:nrows
      if pic(x,y) == 0
          region_grow(val, x, y);
          val = val + 1;
      end 
   end
end

function [] = region_grow(val, x, y)
    pic(x,y)=val;
    for i = -1:1
        for j= -1:1
            if pic(x+i, y+j)==0
               region_grow(val, x+i, y+j)
            end
        end
    end
end