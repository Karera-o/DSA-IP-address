/*
 *  Created on: 05 April, 2024
 *      Author: okarera
 */
#include "IPAddressAnalyze.h"

int IPAddressAnalyzer::readNextItemFromFile(FILE* inputFileStream){
	if (! inputFileStream){
		std::string message("Cannot open input file for reading");
		throw std::invalid_argument(message.c_str());
	}

}


// void IPAddressAnalyzer::getMostFrequentIPAddress(char* inputFilePath, char* outputFilePath, int n){
// 	FILE* inFileStream = fopen(inputFilePath, "r");
// 	if (! inFileStream){
// 		char message[1024];
// 		sprintf(message, "Cannot open input file for reading: %s", inputFilePath);
// 		throw std::ios_base::failure(message);
// 	}

// 	FILE* outFileStream = fopen(outputFilePath, "w");
// 	if (! outFileStream){
// 		char message[1024];
// 		sprintf(message, "Cannot open output file for writing: %s", outputFilePath);
// 		throw std::ios_base::failure(message);
// 	}

// 	LogManager::writePrintfToLog(LogManager::Level::Status,
// 			"IPAddressAnalyzer::getMostFrequentIPAddress",
// 			"Starting to process file %s", inputFilePath);

// 	fflush(outFileStream);
// 	fclose(outFileStream);

// 	fclose(inFileStream);
// }

struct IPAddressCount {
    std::string ip;
    int count;
};

// Function prototypes
int indexOfIP(IPAddressCount* ipCounts, int size, std::string ip);
void insertSorted(IPAddressCount* ipCounts, IPAddressCount newIPCount, int& size, int maxSize);

void IPAddressAnalyzer::getMostFrequentIPAddress(char* inputFilePath, char* outputFilePath, int n) {
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Cannot open input file for reading\n";
        return;
    }

    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Cannot open output file for writing\n";
        return;
    }

    IPAddressCount* ipCounts = new IPAddressCount[10000]; // Arbitrary size for demonstration
    int totalIPs = 0; // Tracks the total number of unique IPs encountered

    std::string line;
    while (getline(inputFile, line)) {
        std::string ip = line.substr(0, line.find(","));
        int count = std::stoi(line.substr(line.find(",") + 1));

        int index = indexOfIP(ipCounts, totalIPs, ip);
        if (index != -1) { // IP found, update count
            ipCounts[index].count += count;
            // Ensure the list remains sorted after update
            insertSorted(ipCounts, ipCounts[index], totalIPs, 10000);
        } else { // New IP, add to list
            if (totalIPs < 10000) { // Prevent overflow
                IPAddressCount newIPCount = {ip, count};
                insertSorted(ipCounts, newIPCount, totalIPs, 10000);
            }
        }
    }

    // Output the top n IPs
    for (int i = 0; i < n && i < totalIPs; ++i) {
        outputFile << i+1 << ", " << ipCounts[i].ip << ", " << ipCounts[i].count << "\n";
    }

    delete[] ipCounts;
    inputFile.close();
    outputFile.close();
}

int indexOfIP(IPAddressCount* ipCounts, int size, std::string ip) {
    for (int i = 0; i < size; ++i) {
        if (ipCounts[i].ip == ip) {
            return i;
        }
    }
    return -1; // Not found
}

void insertSorted(IPAddressCount* ipCounts, IPAddressCount newIPCount, int& size, int maxSize) {
    int i;
    for (i = size - 1; (i >= 0 && ipCounts[i].count < newIPCount.count); i--) {
        if (i < maxSize - 1) {
            ipCounts[i + 1] = ipCounts[i];
        }
    }
    if (i < maxSize - 1) {
        ipCounts[i + 1] = newIPCount;
    }
    if (size < maxSize) {
        size++;
    }
}