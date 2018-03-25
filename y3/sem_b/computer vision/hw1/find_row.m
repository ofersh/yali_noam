function [begin, ending] = find_row(pic, starting_row)
% find_row will find written rows borders.

[nrows, ncols] = size(pic); 

rows_projection = sum(pic,2); % Sum columns 
rows_projection = rows_projection < ncols-1; % Find non empty rows.

% first non empty row is start of writing.
begin = find(rows_projection(starting_row:end)==1, 1) + starting_row -1;

if isempty(begin)
    ending=[];
    return
end
% first empty row + beginning is ending of writing.
ending = find(rows_projection(begin+1:end) == 0, 1) + begin;
end

