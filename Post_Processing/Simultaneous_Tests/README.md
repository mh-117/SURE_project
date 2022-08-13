# MATLAB Files for Data From the M:1 Simultaneous Data Transfer Tests

The following files were used for the post processing of the data collected during the M:1 tests. Since the incoming data from the peripherals are all tagged with the peripheral's corresponding label, code was created to organize all the data into columns according to the data's tag. Once organized in a data structure, the data is then analyzed for packet loss. 

* postProcess.m: main code for post processing the test data files. Will need to adjust code depending on whether the test data file is a txt file or excel sheet
* genOrgData.m: function that generates the control data. During testing, data that was incremented by 1 for the set number of data points acted as the control data. Therefore, this file creates this control data format. When testing with more complicated data sets, this function might not have to be used. 
* compare.m: function that will compare two input lists. For the purpose of post processing, this will compare the test data set to the expected data set 
