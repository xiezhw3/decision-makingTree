#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<string> readFile(const string &filePath) {
	vector<string> readResult;
	ifstream in(filePath);
	if (!in.is_open()){ 
		cout << "Error opening file" << endl; 
		exit (1); 
	}

	char line[1024];
	while (in.getline(line, sizeof(line))) {
		string word(line);
		readResult.push_back(word);
	}
	in.close();
	return readResult;
}

void getRandomFile(vector<string> &sourceDataSet, vector<string> &dataSet, vector<string> &testData, int seed) {
	testData.clear();
	dataSet.clear();
	dataSet = sourceDataSet;
	for (int i = 0; i < 100; ++i) {
		srand(time(0) + seed);
    	int index = rand() % dataSet.size();
    	testData.push_back(dataSet[index]);
    	dataSet.erase(dataSet.begin() + index);
	}
}

void writeToFile(const string &filePath, vector<string> &data) {
	ofstream out(filePath);
	if (!out.is_open()){ 
		cout << "Error opening file" << endl; 
		exit (1); 
	}
	for (auto &i : data)
		out << i << endl;
	out.close();
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

		vector<string> sourceDataSet = readFile(argv[1]);
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
			writeToFile(dataSetFile, dataSet);
			writeToFile(testDataFile, testData);
		}
	}
	return 0;
}