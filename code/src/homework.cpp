/*
 * homework.cpp
 *
 *  Created on: 05 April, 2024
 *      Author: okarera
 */

#include "homework.h"

int main(int argc, char** argv) {
	LogManager::resetLogFile();
	LogManager::writePrintfToLog(LogManager::Level::Status,
			"main", "In main file.");

	int peakMem1 = getPeakRSS();
	int currMem1 = getCurrentRSS();
	printf("peakRSS = %d, currMem=%d\n", peakMem1, currMem1);
	printf("sizeof(bool) = %d \n", (int)sizeof(bool));
	printf("sizeof(int) = %d \n", (int)sizeof(int));
	printf("sizeof(char) = %d \n", (int)sizeof(char));
	printf("INT_MIN = %d, INT_MAX =%d\n", INT_MIN, INT_MAX);

	auto start = std::chrono::high_resolution_clock::now();

	char inputPath[1024], outputPath[1024];

	sprintf(inputPath, "%s", argv[1]);
	sprintf(outputPath, "%s", argv[2]);
	int topN = atoi(argv[3]);
	IPAddressAnalyzer::getMostFrequentIPAddress(inputPath, outputPath, topN);


	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	printf("run time =%d microseconds\n", (int) duration.count());


	int peakMem2 = getPeakRSS();
	int currMem2 = getCurrentRSS();
	printf("peakRSS = %d, currMem=%d\n", peakMem2, currMem2);
	printf("Diff peakRSS = %d, currMem=%d\n", peakMem2-peakMem1, currMem2-currMem1);


}
