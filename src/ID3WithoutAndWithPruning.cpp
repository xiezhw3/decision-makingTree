/**
 * @file ID3WithoutAndWithPruning.cpp
 * @description The algorithm of ID3 with and without pruning
 * @author Zhiwang Xie
 * @mail xiezhiw3@gmail.com
 * @github https://github.com/xiezhw3
 * @data Dec 18 2014
 **/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "decisionMakingTree.h"
#include "table.h"
#include "pruningOfTheTree.h"
#include "predict.h"
#include "fileProcesser.h" 

using namespace std;

// colunm name is in the form colN, N is a number represents the
// location of the column, begin from 1 
vector<string> getColName(int colNum) {
	vector<string> colName;
	for (int i = 0; i != colNum; ++i) {
		string a = "col";
		int j = i;
		while (j) {
			a.push_back(char(j % 10 + '0'));
			j /= 10;
		}
		colName.push_back(a);
	}
	return colName;
}

// form a table with the chaining data
void getTableFromFile(const string &filePath, Table &table) {
	int colNum = 0;
	FileProcesser fileProcess;
	vector<vector<string> > readResult = fileProcess.readFileFormTrin(filePath);
	vector<string> colName;
	for (auto &i : readResult) {
		i.erase(i.end() - 1);
		table.addRow(i);

		if (colNum == 0) {
			colNum = i.size();
			colName = getColName(colNum);
		}
	}
	table.setColName(Row(colName));
}

// get the test data
void getPredictFile(const string &filePath, Table &table, vector<string> &rightResult) {
	int colNum = 0;
	FileProcesser fileProcess;
	vector<vector<string> > readResult = fileProcess.readFileFormTrin(filePath);
	rightResult.clear();
	vector<string> colName;
	for (auto &i : readResult) {
		i.erase(i.end() - 1);
		rightResult.push_back(*(i.begin()));
		i.erase(i.begin());
		table.addRow(i);

		if (colNum == 0) {
 			colNum = i.size();
 			colName = getColName(colNum);
		}
	}
	table.setColName(Row(colName));
}

void ID3processWithoutPruning (const string &chainingDataPath, const string &predictFile, const string &filenum) {
	Table table, predictTable;
	PruningOfTree pruning;
	Predict predict;
	vector<string> rightResult;
	FileProcesser fileProcess;
	getTableFromFile(chainingDataPath, table);

	DecisonMakingTree decisionMakingTree;
	decisionMakingTree.initTree(table, 0);
	decisionMakingTree.decisionMakingTreeID3();
	getPredictFile(predictFile, predictTable, rightResult);
	string outN = "data/rightResult";
	outN += filenum;
	fileProcess.writeToFile(outN, rightResult);

	predict.setTable(predictTable);
	predict.setTree(decisionMakingTree);
	vector<string> predictResult = predict.getResult();
	outN = "data/predictResultOfID3WithoutPruning";
	outN += filenum;
	fileProcess.writeToFile(outN, predictResult);
}

void ID3processWithPruning (const string &chainingDataPath, const string &predictFile, const string &filenum) {
	Table table, predictTable;
	PruningOfTree pruning;
	Predict predict;
	vector<string> rightResult;
	FileProcesser fileProcess;
	getTableFromFile(chainingDataPath, table);

	DecisonMakingTree decisionMakingTree;
	decisionMakingTree.initTree(table, 0);
	decisionMakingTree.decisionMakingTreeID3();
	pruning.setTree(decisionMakingTree);
	pruning.makePruningTree();
	getPredictFile(predictFile, predictTable, rightResult);
	string outN = "data/rightResult";
	outN += filenum;
	fileProcess.writeToFile(outN, rightResult);

	predict.setTable(predictTable);
	predict.setTree(decisionMakingTree);
	vector<string> predictResult = predict.getResult();
	outN = "data/predictResultOfID3WithPruning";
	outN += filenum;
	fileProcess.writeToFile(outN, predictResult);
}

int main(int argc, char const *argv[])
{
	if (argc != 4) {
		cout << "Please run the tree maker in this model: [tree maker]\
			[chain data file] [predict data file] [file num]" << endl;
	} else {
		ID3processWithoutPruning(argv[1], argv[2], argv[3]);
		ID3processWithPruning(argv[1], argv[2], argv[3]);
	}
	return 0;
}