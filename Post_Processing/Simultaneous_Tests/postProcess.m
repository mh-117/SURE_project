% For post processing the data from multiple peripherals simultaneously
% Note: This post process currently codes for 2 peripherals. Adjust the
% columns for orgData to match the number of peripherals as well as the if
% ch(1,1) == letter to match the letter names of the peripherals being
% analyzed.
% Note: Also will need to adjust the number of rows according to how many
% data points were being sent from the peripherals


% generate dataset to compare the values to
controlData = genOrgData(500);

% post processing .txt files that are in the form A 0000000000000001 etc
filename = '500pt_test_3000ms.txt';
data = readlines(filename);

% post processing .xlsx files (ie data taken from the serial monitor)
% !! Ran out of time to code but ideally could comment out the lines above for
% processing the .txt files and instead could include lines for processing
% excel spreadsheets 

% organize data 
[totalPts, ~] = size(data);

orgData = cell(500,2); %2 columns, 500 rows
counterA = 1;
counterB = 1;
for i=1:totalPts-1
    currLine = data(i,1);
    ch = currLine.char();

    % see if first letter is the tag 
    if ch(1,1) == 'A'
        % just save the binary string 
        binStr = split(currLine);
        orgData{counterA,1} = binStr(2,1);
        counterA = counterA + 1;
    elseif ch(1,1) == 'B'
        % just save the binary string 
        binStr = split(currLine);
        orgData{counterB,2} = binStr(2,1);
        counterB = counterB + 1;
    end
end

[~,peripherals] = size(orgData);
mismatchedResults = {};
for i = 1:peripherals
    mismatchedResults{1,i} = compare(controlData,orgData(:,i));
end