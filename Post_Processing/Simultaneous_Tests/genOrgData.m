function [binData] = genOrgData(numPoints)
% This function generates the control data. For experiementing, this file
% creates a list form 1-numPoints in binary that data sets can be compared
% to
% 
% numPoints : number of points being compared 

    binData = cell(numPoints,1);
    for currVal = 1:numPoints
        binaryVal = dec2bin(currVal);

        % convert to a 16bit string
        [~, length] = size(binaryVal);
        addZero = 16 - length;
        buf = zeros(1,addZero);
        buf1 = mat2str(buf);
        buf2 = extract(buf1,'0');
        buf3 = strjoin(buf2);
        finalBuf = erase(buf3," ");
        binData{currVal,1} = strcat(finalBuf,binaryVal);
    end
end