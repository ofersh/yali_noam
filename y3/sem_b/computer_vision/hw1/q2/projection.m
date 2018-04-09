clear all, clc;

header = ['Question 2\n'...
          'Distinguishing objects by using vertical and horizontal projections\n\n\n'];
      
fprintf(header)


pic =  imread('text.bmp');
[nrows, ncols] = size(pic);
figure; imshow(pic)

ending = 0;
while true
    % work on each row of letters.
    [begin, ending] = find_row(pic, ending+1); % find row borders.
    if isempty(begin)
        break
    end
    
    col_indices = find_letters(pic, begin, ending); % find letters borders.
    
    % mark borders on pic.
    begin = begin -2; 
    pic([begin ending],:) = 0;
    pic(begin:ending, col_indices) = 0;
end

figure(1); imshow(pic)
