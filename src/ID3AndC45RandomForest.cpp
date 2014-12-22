/**
 * @file ID3AndC45RandomForest.cpp
 * @description The random forest algorithm
 * @author Zhiwang Xie
 * @mail xiezhiw3@gmail.com
 * @github https://github.com/xiezhw3
 * @data Dec 18 2014
 **/

#include <iostream>
#include "predictWithMultiTree.h"
#include "fileProcesser.h" 

vector<string> getRightResult(const string &filePath) {
	vector<string> rightResult;
	FileProcesser fileProcess;
	vector<vector<string> > readResult = fileProcess.readFileFormTrin(filePath);
	for (auto &i : readResult) {
		rightResult.push_back(*(i.begin()));
	}
	return rightResult;
}

void ID3(const string &argv1, const string &argv2, const string &argv3) {
	FileProcesser fileProcess;
	PredictWithMultiTree predictTree;
	predictTree.getDecisionMakingTreeList(argv1, 10, 0);
	vector<string> result = predictTree.getPredictResult(argv2);

	vector<string> rightResult = getRightResult(argv2);
	string outN = "data/rightResult";
	outN += argv3;
	fileProcess.writeToFile(outN, rightResult);

	outN = "data/predictResultOfID3";
	outN += argv3;
	fileProcess.writeToFile(outN, result);
}

void C45(const string &argv1, const string &argv2, const string &argv3) {
	FileProcesser fileProcess;
	PredictWithMultiTree predictTree;
	predictTree.getDecisionMakingTreeList(argv1, 10, 1);
	vector<string> result = predictTree.getPredictResult(argv2);

	vector<string> rightResult = getRightResult(argv2);
	string outN = "data/rightResult";
	outN += argv3;
	fileProcess.writeToFile(outN, rightResult);

	outN = "data/predictResultOfC45";
	outN += argv3;
	fileProcess.writeToFile(outN, result);
}

int main(int argc, char const *argv[])
{
	if (argc != 4) {
		cout << "Please run the tree maker in this model: [main]\
			[chain data file] [predict data file] [file num]" << endl;
	} else {
		ID3(argv[1], argv[2], argv[3]);
		C45(argv[1], argv[2], argv[3]);
	}

	return 0;
}