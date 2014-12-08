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
		cout << "Error opening file"; 
		exit (1); 
	}
	char line[1024];

	int colNum = 0;
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

void getTableFromFile(const string &filePath, Table &table) {
	int colNum = 0;
	vector<vector<string> > readResult = readFile(filePath);
	for (auto &i : readResult) {
		i.erase(i.end() - 1);
		table.addRow(i);

		if (colNum == 0)
			colNum = i.size();
	}
	vector<string> colName;
	for (int i = 0; i != colNum; ++i) {
		string a = "col";
		a.push_back(char(i + '0'));
		colName.push_back(a);
	}
	table.setColName(Row(colName));
}

void getPredictFile(const string &filePath, Table &table, vector<string> &rightResult) {
	int colNum = 0;
	vector<vector<string> > readResult = readFile(filePath);
	rightResult.clear();
	for (auto &i : readResult) {
		i.erase(i.end() - 1);
		rightResult.push_back(*(i.begin()));
		i.erase(i.begin());
		table.addRow(i);

		if (colNum == 0)
			colNum = i.size();
	}
	vector<string> colName;
	for (int i = 0; i != colNum; ++i) {
		string a = "col";
		a.push_back(char(i + '0'));
		colName.push_back(a);
	}
	table.setColName(Row(colName));
}

void writeToFile(const string &filePath, vector<string> &result) {
	ofstream out(filePath);
	if (!out.is_open()){ 
		cout << "Error opening file"; 
		exit (1); 
	}

	for (auto &i : result) {
		out << i << endl;
	}

	out.close();
}

int main(int argc, char const *argv[])
{
	if (argc < 3 || argc > 3) {
		cout << "Please run the tree maker in this model: [tree maker] [chain data file] [predict data file]" << endl;
	} else {
		Table table, predictTable;
		PruningOfTree pruning;
		Predict predict;
		vector<string> rightResult;
		getTableFromFile(argv[1], table);

		DecisonMakingTree decisionMakingTree;
		decisionMakingTree.initTree(table, 0);
		decisionMakingTree.decisionMakingTreeID3();
		pruning.setTree(decisionMakingTree);
		pruning.makePruningTree();
		getPredictFile(argv[2], predictTable, rightResult);
		writeToFile("rightResult.txt", rightResult);

		predict.setTable(predictTable);
		predict.setTree(decisionMakingTree);
		vector<string> predictResult = predict.getResult();
		writeToFile("predictResultOfID3.txt", predictResult);


		DecisonMakingTree decisionMakingTree2;
		decisionMakingTree2.initTree(table, 0);
		decisionMakingTree2.decisionMakingTreeC45();
		pruning.setTree(decisionMakingTree2);
		pruning.makePruningTree();
		
		predict.setTable(predictTable);
		predict.setTree(decisionMakingTree2);
		predictResult = predict.getResult();
		writeToFile("predictResultOfC45.txt", predictResult);
	}
	return 0;
}