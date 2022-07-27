# MATLAB Files for the Final RSSI Tests

The following files were used for the post processing of the data collected during the RSSI tests. Although many tests were conducted, the data files are the files corresponding to the final data sets that were used for the SURE program poster.

* convertData: this file reads in the data txt files and creates the corresponding plots that represent the gradual change in the RSSI as the distance between a peripheral and central increase
* extractDataExtraLong: this function takes in the data files and computes the average RSSI over the various measured distances from the central. It then outputs these final averaged RSSI values to be plotted
* *.txt: these are the data files for various measured fixed distances from the central
