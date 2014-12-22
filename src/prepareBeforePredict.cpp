/**
 * @file prepareBeforePredict.cpp
 * @description The data predict before all algotithm
 * @author Zhiwang Xie
 * @mail xiezhiw3@gmail.com
 * @github https://github.com/xiezhw3
 * @data Dec 18 2014
 **/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "fileProcesser.h" 

using namespace std;

void getRandomFile(vector<string> &sourceDataSet, vector<string> &dataSet, vector<string> &testData, int seed) {
	testData.clear();
	dataSet.clear();
	dataSet = sourceDataSet;
	for (int i = 0; i < 335; ++i) {
		srand(time(0) + seed);
    	int index = rand() % dataSet.size();
    	testData.push_back(dataSet[index]);
    	dataSet.erase(dataSet.begin() + index);
	}
}

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		cout << "Please run the tree maker in this model: [cal] [dataSet file] [splitNum]" << endl;
	} else {
		int times = 0;
		for (int i = 0; i != 32; ++i) {
			if (argv[2][i] == '\0')
				break;
			times = times * 10 + (int)(argv[2][i] - '0');
		}
		FileProcesser fileProcess;
		vector<string> sourceDataSet = fileProcess.readFileFormPredict(argv[1]);
		for (int i = 0; i != times; ++i) {
			vector<string> dataSet, testData;
			getRandomFile(sourceDataSet, dataSet, testData, i);
			string dataSetFile("data/dataSet"), testDataFile("data/testData");
			int j = i + 1, index = 0;
			char num[1024];
			while (j) {
				num[index++] = j % 10 + '0';
				j /= 10;
			}
			for (j = index - 1; j >= 0; --j) {
				dataSetFile.push_back(num[j]);
				testDataFile.push_back(num[j]);
			}
			fileProcess.writeToFile(dataSetFile, dataSet);
			fileProcess.writeToFile(testDataFile, testData);
		}
	}
	return 0;
}