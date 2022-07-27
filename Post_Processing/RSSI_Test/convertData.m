% ! For RSSI testing !
% This file is the post processing step for conducting the RSSI tests. By
% including all the files recorded for a test, the data will be extracted
% and averaged to then create a final plot of the RSSI values over a range
% of distances. There are many tests included here (Test A-J), but Test I
% and Test J are the final plots that will be used for the poster. All
% other tests are commented out but will be kept in this file. 

% Final data structure for all the tests taken 
rssiSets = {};

% initializing all filenames
% TEST A: no obstacles (13pts)
filenamesA = {'test1.txt','test2.txt','test3.txt','test4.txt','test5.txt','test6.txt','test7.txt','test8.txt','test9.txt','test10.txt','test11.txt','test12.txt','test13.txt'};
%rssiSets{1,1} = extractData(13,filenamesA);


% TEST B: no obstacles (14pts)
filenamesB = {'test1-.txt','test2-.txt','test3-.txt','test4-.txt','test5-.txt','test6-.txt','test14-.txt','test7-.txt','test8-.txt','test9-.txt','test10-.txt','test11-.txt','test12-.txt','test13-.txt'};
%rssiSets{1,2} = extractData(14,filenamesB);


% TEST C: saline (8pts)
filenamesC = {'stest14.txt','stest7.txt','stest8.txt','stest9.txt','stest10.txt','stest11.txt','stest12.txt','stest13.txt'};
%rssiSets{1,3} = extractData(8,filenamesC);


% TEST D: saline (8pts)
filenamesD = {'stest14-.txt','stest7-.txt','stest8-.txt','stest9-.txt','stest10-.txt','stest11-.txt','stest12-.txt','stest13-.txt'}; %,'sbtest13-.txt'}; %last file was when I stood in front
%rssiSets{1,4} = extractData(8,filenamesD);

% TEST E: w/o saline, 500pts
filenamesE = {'ltest1.txt','ltest2.txt','ltest3.txt','ltest4.txt','ltest5.txt','ltest6.txt','ltest14.txt','ltest7.txt','ltest8.txt','ltest9.txt','ltest10.txt','ltest11.txt','ltest12.txt','ltest13.txt'};
%rssiSets{1,5} = extractDataLong(11,filenamesE);

% TEST F: w/o saline, 500pts, w/ filter
filenamesF = {'ftest1.txt','ftest2.txt','ftest3.txt','ftest4.txt','ftest5.txt','ftest6.txt','ftest14.txt','ftest7.txt','ftest8.txt','ftest9.txt','ftest10.txt','ftest11.txt','ftest12.txt','ftest13.txt'};
%rssiSets{1,6} = extractDataLong(11,filenamesF);

% TEST G: saline, 500pts (6pts)
filenamesG = {'sltest14.txt','sltest7.txt','sltest8.txt','sltest9.txt','sltest10.txt','sltest11.txt'};
%rssiSets{1,7} = extractDataLong(6,filenamesG);

% TEST H: saline, 500pts, w/ filter (6pts)
filenamesH = {'sftest14.txt','sfest7.txt','sftest8.txt','sfftest9.txt','sftest10.txt','sftest11.txt'};
%rssiSets{1,8} = extractDataLong(6,filenamesH);

% TEST I: w/o saline, 1000pts (6pts)
filenamesI = {'hltest14r.txt','hltest7.txt','hltest8rr.txt','hltest9r.txt','hltest10.txt','hltest11r.txt'};
rssiSets{1,9} = extractDataExtraLong(6,filenamesI);

% TEST J: w/ saline, 1000pts (6pts)
filenamesJ = {'hlstest14r.txt','hlstest7.txt','hlstest8r.txt','hlstest9.txt','hlstest10.txt','hlstest11r.txt'};
rssiSets{1,10} = extractDataExtraLong(6,filenamesJ);


% ---- Graphing----
figure(1)

% Distances from central
x1 = [1,1.5,2.3,3,5,7.3,30.2,44.6,78,180.7,280.1,336,476];
%x2 = [1,1.5,2.3,3,5,7.3,19.7,30.2,44.6,78,180.7,280.1,336,476];
x2 = [1,1.5,2.3,3,5,7.3,19.7,30.2,44.6,78,180.7];
x3 = [19.7,30.2,44.6,78,180.7,280.1,336,476];
x4 = [19.7,30.2,44.6,78,180.7,280.1,336,476];
x5 = [19.7,30.2,44.6,78,120,180.7];


hold on
title('RSSI Test','FontSize',15);
xlabel('Distance From Central (cm)','FontSize',15); 
ylabel('RSSI Value (dBm)','FontSize',15); 

%plot(x1,rssiSets{1,1},'-o','DisplayName','Test A, 180pt, w/o saline');

%plot(x2,rssiSets{1,2},'-o','DisplayName','Test B, 180pts each distance, w/o saline');

%plot(x2,rssiSets{1,5},'-o','DisplayName','Test E, 500pts each distance, w/o saline');

%plot(x2,rssiSets{1,6},'-o','DisplayName','Test F, 500pts each distance, w/o saline, w/filter');


%plot(x3,rssiSets{1,3},'-o','DisplayName','Test C, 180pt, w/ saline');

xlim([15 190])
ylim([-70 -47])

%plot(x4,rssiSets{1,4},'-o','DisplayName','Test D, 180pts each distance, w/ saline');


%plot(x5,rssiSets{1,7},'-o','DisplayName','Test G, 500pts each distance, w/ saline');
%plot(x5,rssiSets{1,8},'-o','DisplayName','Test H, 500pts each distance, w/ saline, w/ filter');

plot(x5,rssiSets{1,9},'-o','DisplayName','Test I, 1000pts each distance, w/o saline');
plot(x5,rssiSets{1,10},'-o','DisplayName','Test J, 1000pts each distance, w/ saline');

hold off
legend('FontSize',15)
