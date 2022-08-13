function [mismatched] = compare(controlData,testData)
% compares two lists of data values with the first entry being the expected
% values while the second entry is the test data to be evaluated

% this function will return a list of the data values that were expected
% but missing from the test data

% controlData: expected data values
% testData: data to be evaluated

    mismatched = {};        %empty cell array
    [numData, ~] = size(controlData);

    testIndex = 1;          % in case t, hold the position
    mismatchedIndex = 1;    % index for the elements that were lost
    for i = 1:numData
        comparison = (controlData{i,1} == testData{testIndex,1});
        if ~any(comparison == 0)     
            %if match 
            testIndex = testIndex + 1;
        else
            %if no match
            mismatched{mismatchedIndex,1} = controlData{i,1};
            mismatchedIndex = mismatchedIndex + 1;
        end
    end

end