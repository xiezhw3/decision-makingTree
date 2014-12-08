#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "decisionMakingTree.h"
#include "table.h"
#include "pruningOfTheTree.h"
#include "predict.h"

using namespace std;

vector<vector<string> > readFile(const string &filePath) {
	vector<vector<string> > readResult;
	ifstream in(filePath);
	if (!in.is_open()){ 
		cout << "Error opening file" << endl; 
		exit (1); 
	}
	char line[1024];

	// get each feature
	while (in.getline(line, sizeof(line))) {
		for (auto &i : line) {
			if (i != '\0') {
				if (i == ',')
					i = ' ';
			} else {
				break;
			}
		}
		stringstream result(line);
		vector<string> words;
		while (result) {
			string s = "";
			result >> s;
			words.push_back(s);
		}
		readResult.push_back(words);
	}
	in.close();
	return readResult;
}

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
	vector<vector<string> > readResult = readFile(filePath);
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
	vector<vector<string> > readResult = readFile(filePath);
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



void writeToFile(const string &filePath, vector<string> &result) {
	ofstream out(filePath);
	if (!out.is_open()){ 
		cout << "Error opening file" << endl; 
		exit (1); 
	}

	for (auto &i : result) {
		out << i << endl;
	}

	out.close();
}

void ID3process (const string &chainingDataPath, const string &predictFile, const string &filenum) {
	Table table, predictTable;
	PruningOfTree pruning;
	Predict predict;
	vector<string> rightResult;
	getTableFromFile(chainingDataPath, table);

	DecisonMakingTree decisionMakingTree;
	decisionMakingTree.initTree(table, 0);
	decisionMakingTree.decisionMakingTreeID3();
	pruning.setTree(decisionMakingTree);
	pruning.makePruningTree();
	getPredictFile(predictFile, predictTable, rightResult);
	string outN = "data/rightResult";
	outN += filenum;
	writeToFile(outN, rightResult);

	predict.setTable(predictTable);
	predict.setTree(decisionMakingTree);
	vector<string> predictResult = predict.getResult();
	outN = "data/predictResultOfID3";
	outN += filenum;
	writeToFile(outN, predictResult);
}

void C45process (const string &chainingDataPath, const string &predictFile, const string &filenum) {
	Table table, predictTable;
	PruningOfTree pruning;
	Predict predict;
	vector<string> rightResult;
	getTableFromFile(chainingDataPath, table);

	DecisonMakingTree decisionMakingTree;
	decisionMakingTree.initTree(table, 0);
	decisionMakingTree.decisionMakingTreeC45();
	pruning.setTree(decisionMakingTree);
	pruning.makePruningTree();
	getPredictFile(predictFile, predictTable, rightResult);
	string outN = "data/rightResult";
	outN += filenum;
	writeToFile(outN, rightResult);

	predict.setTable(predictTable);
	predict.setTree(decisionMakingTree);
	vector<string> predictResult = predict.getResult();
	outN = "data/predictResultOfC45";
	outN += filenum;
	writeToFile(outN, predictResult);
}

int main(int argc, char const *argv[])
{
	if (argc != 4) {
		cout << "Please run the tree maker in this model: [tree maker]\
			[chain data file] [predict data file] [file num]" << endl;
	} else {
		ID3process(argv[1], argv[2], argv[3]);
		C45process(argv[1], argv[2], argv[3]);
	}
	return 0;
}