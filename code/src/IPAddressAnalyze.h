/*
 *  Created on: 05 April, 2024
 *      Author: okarera
 */

#ifndef IPADDRESSANALYZE_H_
#define IPADDRESSANALYZE_H_

#include <iostream>
#include <fstream>
#include <limits.h>
#include <math.h>
#include <unistd.h>
#include "./util/GetMemUsage.h"
#include "./util/LogManager.h"

class IPAddressAnalyzer{
	/**
	 * This function must take as input a file stream that is open, read the next line
	 * and return an integer if it is valid.
	 *
        a. If there are any lines with no inputs, those lines must be skipped.
        b. If there are any lines that contain a non-integer input, those lines must be skipped.
 	 	 If end of file is reached, it must throw an end of file error
	 */
	static int readNextItemFromFile(FILE* inputFileStream);


public:
	/**
	 *
	 *
	 * @param inputFilePath Path of the input file.
	 * @param outputFilePath Path of the output file.
	 * @param topN Number of
	 *
	 * If the input file cannot be read throw an error of type ios_base::failure
	 * If the output file cannot be generated, then throw an error of type ios_base::failure
	 */
	static void getMostFrequentIPAddress(char* inputFilePath, char* outputFilePath, int n);
};

#endif /* IPADDRESSANALYZE_H_ */
