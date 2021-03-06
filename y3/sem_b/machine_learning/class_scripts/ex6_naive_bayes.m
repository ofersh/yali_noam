clc; clear
addpath('materials')

% Initiazling the train and test matrices

[spmatrix, train_tokenlist, trainCategory] = readMatrix( 'MATRIX.TRAIN' );
[spmatrix, test_tokenlist, TestCategory] = readMatrix( 'MATRIX.TEST' );

trainMatrix = full(spmatrix);
numTrainDocs = size(trainMatrix, 1); % number of training ducuments
numTokens = size(trainMatrix, 2); % number of training tokens
testMatrix = full(spmatrix);
numTestDocs = size(testMatrix, 1); % number of training ducuments
numTokens = size(testMatrix, 2); % number of training tokens

token_words = string(split(train_tokenlist)); % Creating the list of all the words

trainCategory = full(trainCategory);
sub_mat = trainMatrix(1:5,1:10);
non_zero_trainMat = sum(trainMatrix~=0);
n_cells = size(trainMatrix, 1) * size(trainMatrix, 2);
news_index = find(token_words=='news');
spam_index = find(token_words=='spam');
spam_indices = trainCategory==1;
num_spams = sum(spam_indices);
not_spam_indices = trainCategory==0;
not_spams = sum(not_spam_indices);
p1 = sum(trainCategory==1)/length(trainCategory);
p0 = 1 - p1;

%% Part 1 - Learning the data
fprintf('Amount of words the list contains: %g\n', numTokens)
fprintf('Number of values that does not equal to 0 in trainMatrix  %g\n', non_zero_trainMat)
fprintf('Percentage of values that does not equal to 0 in trainMatrix  %g', non_zero_trainMat / n_cells)
fprintf('How many documents in the training group?  %g\n', numTrainDocs)
fprintf('How many documents in the test group? %g\n', numTestDocs)
fprintf('The 10th word in tokenlist is %s\n', token_words(10))
fprintf('The value of the 5th word in the 10th document is %g\n', trainMatrix(10,5));
fprintf('The value of the 101th word in the 502th document is %g\n', trainMatrix(502,101));
figure(1)
imagesc(trainMatrix(1:100,1:100))
fprintf('news appears: %g | spam appears: %g\n', news_index, spam_index)

% Remove spam and news words from the matrices and fix the number of tokens
trainMatrix(:,[news_index, spam_index]) = [];
testMatrix(:,[news_index, spam_index]) = [];
numTokens = numTokens - 2;

% Change the matrices to binary
trainMatrixbin = trainMatrix > 0;
testMatrixbin = testMatrix > 0;

figure(2)
imagesc(trainMatrixbin(1:100,1:100))

% Find most common word
num_words_occurences = sum(trainMatrixbin);
common_word_app = max(num_words_occurences);
common_word_ind = find(num_words_occurences==common_word_app);
common_word_in_doc_val = max(max(trainMatrix));
[common_word_in_doc_doc, common_word_in_doc_ind] = find(trainMatrix==common_word_in_doc_val);
common_word_in_doc_word = token_words(common_word_in_doc_ind);

fprintf('most common word. ind: %g | #appearances: %g\n', common_word_ind, common_word_app)
fprintf('#appearances of word 700: %g\n', num_words_occurences(700));
fprintf('The word that appears most in a document:\nword: %s | ind: %g | doc: %g | val: %g \n'...
    , common_word_in_doc_word, common_word_in_doc_ind, common_word_in_doc_doc, common_word_in_doc_val)

%% Part 2 - Probabilities Calculation (practice)
fprintf('#Spam Emails: %g\n', sum(trainCategory==1))
fprintf('p1 = %g\n' , p1)
fprintf('p0 = %g\n' , p0)
fprintf('P(j=2|i=1) = %g\n', sum(trainMatrixbin(spam_indices, 2)) / num_spams)
fprintf('P(j=2|i=0) = %g\n', sum(trainMatrixbin(not_spam_indices, 2)) / not_spams)
fprintf('1 - P(j|i=1)\n')

%% Part 3 - Probabilities Calculation (prediction)
P_word_when_spam = sum(trainMatrixbin(spam_indices, :)) / num_spams;
P_word_when_not_spam = sum(trainMatrixbin(not_spam_indices, 2)) / not_spams;

fprintf('P(x|y=1) = %g\n', prod(P_word_when_spam))

py1_x = prod(P_word_when_spam * p1) / (prod(P_word_when_spam * p1) + prod(P_word_when_not_spam * p0));





