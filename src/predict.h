/**
 * @file predict.h
 * @description Predict the result by feature 
 * @author Zhiwang Xie
 * @mail xiezhiw3@gmail.com
 * @github https://github.com/xiezhw3
 * @data Dec 18 2014
 **/

#ifndef PREDICT_H
#define PREDICT_H

#include "table.h"
#include "decisionMakingTree.h"
#include <map>
#include <cstdlib>
#include <ctime>

class Predict {
public:
	Predict() { }
	Predict(Table &table_, DecisonMakingTree &tree_) {
		table = table_;
		tree = tree_;
		hasPredict = false;
	}

	void setTable(Table &table_) {
		table = table_;
		hasPredict = false;
	}

	void setTree(DecisonMakingTree &tree_) {
		tree = tree_;
		hasPredict = false;
	}

	void predict() {
		predictResult.clear();
		Row NameRow = table.getNameRow();
		int size = NameRow.getColNum();
		map<string, int> featureValueMapindex;
		for (int i = 0; i < size; ++i)
			featureValueMapindex[NameRow.getElement(i)] = i;

		int rowNum = table.getRowNum();

		for (int i = 0; i != rowNum; ++i) {
			Row row = table.getRow(i);
			
			shared_ptr<Node> nodeTemp = tree.getRoot();
			while (nodeTemp != nullptr && nodeTemp->subNode.size() != 0) {
				// string featureColName = j->featureName; 
				string featureValue = row.getElement(featureValueMapindex[nodeTemp->featureName]);

				bool findSubtree = false;

				// int maxSubTree = 0;
				for (auto &j : nodeTemp->subNode) {
					if (featureValue == j->featureValue) {
						nodeTemp = j;
						findSubtree = true;
						break;
					}
				}

				// if the value of the feature not found in the tree
				// thouse a sub tree randomly
				if (!findSubtree) {
					std::srand(std::time(0));
    				int random_variable = std::rand() % nodeTemp->subNode.size();
					nodeTemp = nodeTemp->subNode[random_variable];
				}
			}
			if (nodeTemp != nullptr)
				predictResult.push_back(nodeTemp->sign);
			else
				predictResult.push_back("?");
		}
		hasPredict = true;
	}

	vector<string> getResult() {
		if (!hasPredict)
			predict();
		return predictResult;
	}
private:
	Table table;
	DecisonMakingTree tree;
	vector<string> predictResult;
	bool hasPredict;
};

#endif