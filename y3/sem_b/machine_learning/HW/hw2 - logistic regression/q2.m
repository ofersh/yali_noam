addpath(addpath([genpath('./functions') genpath('./materials')]))

data = load('email_data.txt');
X = data(:, [1, 2]); y = data(:, 3);
