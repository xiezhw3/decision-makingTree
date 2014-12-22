/**
 * @file predict.h
 * @description Predict the result with decision-making tree
 * @author Zhiwang Xie
 * @mail xiezhiw3@gmail.com
 * @github https://github.com/xiezhw3
 * @data Dec 18 2014
 **/


#ifndef PREDICTWITHMULTITREE_H
#define PREDICTWITHMULTITREE_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "fileProcesser.h"
#include "decisionMakingTree.h"
#include "table.h"
#include "pruningOfTheTree.h"
#include "predict.h"

using namespace std;

class PredictWithMultiTree {
public:
	void getDecisionMakingTreeList(const string &filePath, int treeAmount = 1, int treeNum = 0) {
		treeList.clear();
		vector<vector<string> > fileContant = fileProcess.readFileFormTrin(filePath);

		size_t size = fileContant.size();
		//int rowNum = (size / treeAmount) >= 100 ? size / treeAmount : (size >= 100 ? 100 : size);
		int rowNum = size - treeAmount;
		if (treeAmount <= 0)
			treeAmount = 1;

		for (int i = 0; i <= treeAmount; ++i) {
			if (i == treeAmount)
				rowNum = size;
			Table table;
			vector<vector<string> > data = getRandomRow(fileContant, i, rowNum);
			getTable(fileContant, table);
			if (treeNum == 0)
				treeList.push_back(getDecisionMakingTreeID3(table));
			else
				treeList.push_back(getDecisionMakingTreeC45(table));
		}
	}

	void getTable(vector<vector<string> > &readResult, Table &table) {
		int colNum = 0;
		vector<string> colName;
		for (auto &i : readResult) {
			i.erase(i.end() - 1);
			table.addRow(i);

			if (colNum == 0) {
				colNum = i.size();
				colName = createColName(colNum);
			}
		}
		table.setColName(Row(colName));
	}

	// get the test data
	void getPredictData(vector<vector<string> > &readResult, Table &table) {
		int colNum = 0;
		vector<string> colName;
		for (auto &i : readResult) {
			i.erase(i.end() - 1);
			i.erase(i.begin());
			table.addRow(i);

			if (colNum == 0) {
	 			colNum = i.size();
	 			colName = createColName(colNum);
			}
		}
		table.setColName(Row(colName));
	}

	vector<string> createColName(int colNum) {
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

	vector<vector<string> > getRandomRow(vector<vector<string> > source, int seed, int rowNum) {
		size_t size = source.size();
		if (size < rowNum)
			rowNum = size;

		vector<vector<string> > result;
		for (int i = 0; i < rowNum; ++i) {
			srand(time(0) + seed);
	    	int index = rand() % source.size();
	    	result.push_back(source[index]);
	    	source.erase(source.begin() + index);
		}

		return result;
	}



	DecisonMakingTree getDecisionMakingTreeID3(Table &table) {
		PruningOfTree pruning;
		DecisonMakingTree decisionMakingTree;

		decisionMakingTree.initTree(table, 0);
		decisionMakingTree.decisionMakingTreeID3();
		//pruning.setTree(decisionMakingTree);
		//pruning.makePruningTree();
		return decisionMakingTree;
	}

	DecisonMakingTree getDecisionMakingTreeC45(Table &table) {
		PruningOfTree pruning;
		DecisonMakingTree decisionMakingTree;

		decisionMakingTree.initTree(table, 0);
		decisionMakingTree.decisionMakingTreeC45();
		//pruning.setTree(decisionMakingTree);
		//pruning.makePruningTree();
		return decisionMakingTree;
	}

	vector<string> getPredictResultFromTree(vector<vector<string> > &readResult, DecisonMakingTree &decisionMakingTree) {
		Table predictTable;
		
		getPredictData(readResult, predictTable);

		Predict predict;
		predict.setTable(predictTable);
		predict.setTree(decisionMakingTree);
		vector<string> predictResult = predict.getResult();
		return predictResult;
	}

	void getPredictResultFromTreeList(const string &filePath) {
		vector<vector<string> > readResult = fileProcess.readFileFormTrin(filePath);
		bool first = true;
		size_t size = treeList.size();
		if (size != 0) {
			for (auto &i : treeList) {
				vector<vector<string> > readResultTemp = readResult;
				vector<string> predictResultOneTree = getPredictResultFromTree(readResultTemp, i);
				int index = 0;
				for (auto &j : predictResultOneTree) {
					if (first) {
						map<string, int> mapper;
						mapper[j]++;
						//cout << mapper.begin()->first << endl;
						predictResultAll.push_back(mapper);
						//cout << predictResultAll.size() << endl;
					} else {
						predictResultAll[index][j]++;
						if (index == (size - 1))
							predictResultAll[index][j] += 3;
						index++;
					}
				}
				first = false;
			}
		}
	}

	vector<string> getPredictResult(const string &filePath) {
		getPredictResultFromTreeList(filePath);
		vector<string> result;
		for (auto &i : predictResultAll) {
			int times = 0;
			string featureValue = "";
			for (auto &j : i) {
				if (times < j.second) {
					times = j.second;
					featureValue = j.first;
				}
			}
			result.push_back(featureValue);
		}
		return result;
	}

private:
	vector<DecisonMakingTree> treeList;
	FileProcesser fileProcess;
	vector< map<string, int> > predictResultAll;
};

#endif