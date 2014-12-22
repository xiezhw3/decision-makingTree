/**
 * @file calResult.cpp
 * @description calculate the result of algorithm
 * @author Zhiwang Xie
 * @mail xiezhiw3@gmail.com
 * @github https://github.com/xiezhw3
 * @data Dec 18 2014
 **/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "fileProcesser.h" 

using namespace std;


double getPrecisionRate(const string &filePath1, const string &filePath2) {
	FileProcesser fileProcess;
	vector<string> predictResult = fileProcess.readFileFormPredict(filePath1);
	vector<string> sourceresult = fileProcess.readFileFormPredict(filePath2);
	int rightNum;
	int size = predictResult.size();
	for (int i = 0; i != size; ++i)
		if (predictResult[i] == sourceresult[i])
			rightNum++;
	return (double)rightNum / (double)(size);
}

void writeToFile(const string &filePath, double n) {
	ofstream out(filePath, ios::app);
	if (!out.is_open()){ 
		cout << "Error opening file" << endl; 
		exit (1); 
	}

	out << n << endl;

	out.close();
}

int main(int argc, char const *argv[])
{
	if (argc != 4) {
		cout << "Please run the tree maker in this model: [cal] [predict result file] \
				[source result file] [result out file]" << endl;
	} else {
		double res = getPrecisionRate(argv[1], argv[2]);
		writeToFile(argv[3], res);
	}
	return 0;
}