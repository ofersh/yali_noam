function [indices] = find_letters(pic, row_start, row_end)
%find_letters will find indices of letters in given row borders.

% create the working section.
section = pic(row_start:row_end,:); 
[nrows ncols] = size(section);

cols_projection = sum(section); % Sum all rows.
empty_cols = cols_projection == nrows; % find empty columns

% using diff we find the cols which letter ends and starts.
indices = find(abs(diff(empty_cols)) == 1 );


end

