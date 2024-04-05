/*
 *  Created on: 05 April, 2024
 *      Author: okarera
 */
#include "IPAddressAnalyze.h"

#define MAX_IPS 10000
#define MAX_IP_LENGTH 16

int IPAddressAnalyzer::readNextItemFromFile(FILE* inputFileStream) {
    if (!inputFileStream) {
        std::string message("Cannot open input file for reading");
        throw std::invalid_argument(message.c_str());
    }

    return -1;
}

struct IPData {
    char ip[MAX_IP_LENGTH];
    unsigned int count;
} ipData[MAX_IPS];

unsigned int totalIPs = 0;

void manualStrcpy(char* dest, const char* src) {
    while ((*dest++ = *src++));
}

int manualStrcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (unsigned char)(*str1) - (unsigned char)(*str2);
}

void addOrUpdateIP(const char* ip, unsigned int count) {
    for (unsigned int i = 0; i < totalIPs; ++i) {
        bool isSameIP = true;
        for (int j = 0; ip[j] != '\0' || ipData[i].ip[j] != '\0'; ++j) {
            if (ip[j] != ipData[i].ip[j]) {
                isSameIP = false;
                break;
            }
        }
        if (isSameIP) {
            ipData[i].count += count;
            return;
        }
    }
    if (totalIPs < MAX_IPS) {
        manualStrcpy(ipData[totalIPs].ip, ip);
        ipData[totalIPs].count = count;
        totalIPs++;
    }
}

void sortIPData() {
    for (unsigned int i = 1; i < totalIPs; i++) {
        IPData key = ipData[i];
        int j = i - 1;

        while (j >= 0 && (ipData[j].count < key.count ||
                          (ipData[j].count == key.count && manualStrcmp(ipData[j].ip, key.ip) > 0))) {
            ipData[j + 1] = ipData[j];
            j--;
        }
        ipData[j + 1] = key;
    }
}

void IPAddressAnalyzer::getMostFrequentIPAddress(char* inputFilePath, char* outputFilePath, int n) {
    FILE* inFileStream = fopen(inputFilePath, "r");
    if (!inFileStream) {
        fprintf(stderr, "Cannot open input file for reading: %s\n", inputFilePath);
        return;
    }

    FILE* outFileStream = fopen(outputFilePath, "w");
    if (!outFileStream) {
        fprintf(stderr, "Cannot open output file for writing: %s\n", outputFilePath);
        fclose(inFileStream);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), inFileStream)) {
        char ip[MAX_IP_LENGTH] = {0};
        unsigned int count;
        sscanf(line, "%[^,], %u", ip, &count);
        addOrUpdateIP(ip, count);
    }

    fclose(inFileStream);

    sortIPData();

    unsigned int currentRank = 0;
    unsigned int previousCount = 0;
    unsigned int uniqueCountsPrinted = 0;

    for (unsigned int i = 0; i < totalIPs && uniqueCountsPrinted < n; ++i) {
        if (ipData[i].count != previousCount) {
            currentRank++;
            previousCount = ipData[i].count;
            if (currentRank > n)
                break;
        }
        fprintf(outFileStream, "%d, %s, %u\n", currentRank, ipData[i].ip, ipData[i].count);
    }

    fclose(outFileStream);
}