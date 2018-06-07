clc; clear;

[spmatrix, tokenlist, trainCategory] = readMatrix( 'MATRIX.TRAIN' );
trainMatrix = full(spmatrix);
numTrainDocs = size(trainMatrix, 1); % number of training ducuments
numTokens = size(trainMatrix, 2); % number of training tokens
fprintf('רשמו כמה מלים מכילה הרשימה %g\n', numTokens)
sub_mat = trainMatrix(1:5,1:10);
n_cells = 50;
fprintf('מהו מספר הערכים שאינם 0 במטריצה trainMatrix  %g\n', sum(sub_mat(:)==0))
fprintf('מהו אחוז הערכים שאינם 0 במטריצה trainMatrix  %g', sum(sum(sub_mat)) / n_cells)
fprintf(' כמה מסמכים יש בקבוצת האימון?  %g\n', numTrainDocs)

[spmatrix, tokenlist, TestCategory] = readMatrix( 'MATRIX.TEST' );
testMatrix = full(spmatrix);
numTestDocs = size(testMatrix, 1); % number of training ducuments
numTokens = size(testMatrix, 2); % number of training tokens
fprintf('כמה מסמכים יש בקבוצת המבחן? %g\n', numTestDocs)
token_words = string(split(tokenlist));

fprintf('The 10th word in tokenlist is %s\n', token_words(10))
fprintf('The value of the 5th word in the 10th document is %g\n', trainMatrix(10,5));
fprintf('The value of the 101th word in the 502th document is %g\n', trainMatrix(502,101));
figure(1)
imagesc(trainMatrix(1:100,1:100))
news_index = find(token_words=='news');
spam_index = find(token_words=='spam');
fprintf('news appears: %g | spam appears: %g\n', news_index, spam_index)
trainMatrix(:,[news_index, spam_index]) = [];
testMatrix(:,[news_index, spam_index]) = [];
numTokens = numTokens - 2;
trainMatrixbin = trainMatrix > 0;
testMatrixbin = testMatrix > 0;

figure(2)
imagesc(trainMatrixbin(1:100,1:100))

num_words_occurences = sum(trainMatrixbin);
common_word_app = max(num_words_occurences);
common_word_ind = find(num_words_occurences==common_word_app);
fprintf('most common word. ind: %g | #appearances: %g\n', common_word_ind, common_word_app)
fprintf('#appearances of word 700: %g\n', num_words_occurences(700));
common_word_in_doc_val = max(max(trainMatrix));
[common_word_in_doc_doc, common_word_in_doc_ind] = find(trainMatrix==common_word_in_doc_val);
common_word_in_doc_word = token_words(common_word_in_doc_ind);
fprintf('The word that appears most in a document:\nword: %s | ind: %g | doc: %g | val: %g \n'...
    , common_word_in_doc_word, common_word_in_doc_ind, common_word_in_doc_doc, common_word_in_doc_val)
trainCategory = full(trainCategory);
fprintf('#Spam Emails: %g\n', sum(trainCategory==1))
spam_indices = trainCategory==1;
num_spams = sum(spam_indices);
not_spam_indices = trainCategory==0;
not_spams = sum(not_spam_indices);
p1 = sum(trainCategory==1)/length(trainCategory);
p0 = 1 - p1;

fprintf('p1 = %g\n' , p1)
fprintf('p0 = %g\n' , p0)
fprintf('P(j=2|i=1) = %g\n', sum(trainMatrixbin(spam_indices, 2)) / num_spams)
fprintf('P(j=2|i=0) = %g\n', sum(trainMatrixbin(not_spam_indices, 2)) / not_spams)
fprintf('1 - P(j|i=1)\n')

P_word_when_spam = [];
P_word_when_not_spam = [];
for i=1:numTokens
   pi1 = sum(trainMatrixbin(spam_indices, i)) / num_spams;
   pi0 = sum(trainMatrixbin(not_spam_indices, 2)) / not_spams;
   P_word_when_spam = [P_word_when_spam pi1];
   P_word_when_not_spam = [P_word_when_not_spam pi1];
end

fprintf('P(x|y=1) = %g\n', prod(P_word_when_spam))

py1_x = prod(P_word_when_spam * p1) / (prod(P_word_when_spam * p1) + prod(P_word_when_not_spam * p0));





