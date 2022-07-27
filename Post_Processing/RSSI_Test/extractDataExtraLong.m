function [rssiVal] = extractDataExtraLong(dataPts,filenames)
% ! For RSSI testing !

rssiVal = zeros(1,dataPts);
for i=1:dataPts   
    fileID = fopen(filenames{1,i},'r');
    currFile = filenames{1,i};
    formatSpec = '%f';
    data = fscanf(fileID,formatSpec);

    % just take first 1000 values...
    finalDataSet = zeros(1,1000);
    [total, ~] = size(data);
    offset = total - 1000;

    for j=1:1000
        finalDataSet(1,j) = data(offset+j,1);
    end
    average = mean(finalDataSet);
    M = mode(finalDataSet,'all');
    rssiVal(1,i) = average;
    fclose(fileID);
end

end