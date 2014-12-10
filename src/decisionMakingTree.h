#ifndef DECISIONMAKINGTREE_H
#define DECISIONMAKINGTREE_H

#include "informationGain.h"
#include "node.h"
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <memory>

#define THRESHOLD 0.45
#define THRESHOLDRATIO 0.60

class DecisonMakingTree {
public:
	DecisonMakingTree() { }
	DecisonMakingTree(Table &table_, int sourceIndex_ = 0) {
		root = shared_ptr<Node> (new Node(0, sourceIndex_));
		root->table = new Table(table_);
	}

	~DecisonMakingTree() { }

	DecisonMakingTree& operator= (DecisonMakingTree &tree) {
		informationGain = tree.informationGain;
		root = tree.root;
		return *this;
	}

	void initTree(Table &table, int sourceIndex_) {
		root = shared_ptr<Node> (new Node(0, sourceIndex_));
		root->table = new Table(table);
	}

	// get the frequence of each classes
	map<string, int> getClassesAndFrequence(shared_ptr<Node> &root_) {
		map<string, int> classesAndFrequence;
		if (root_ != nullptr && root_->table != nullptr) {
			Table tableTemp = *(root_->table);
			vector<string> classesCol = tableTemp.getCol(root_->sourceIndex);
			for (auto &i : classesCol) {
				classesAndFrequence[i]++;
			}
		}
		return 	classesAndFrequence;
	}

	// get the sign of each node
	string findSign(shared_ptr<Node> &root_) {
		if (root_ == nullptr || root_->table == nullptr)
			return "";
		map<string, int> classesAndFrequence = getClassesAndFrequence(root_);

		string classSign = "";
		int fre = -1;
		// the feature value of the one has the max number of elements
		for (auto &i : classesAndFrequence) {
			if (fre < i.second) {
				fre = i.second;
				classSign = i.first;
			}
		}
		return classSign;
	}

	// the classes has only one kind
	bool isOneClassesNode(shared_ptr<Node> &root_) {
		map<string, int> classesAndFrequence = getClassesAndFrequence(root_);
		if (classesAndFrequence.size() == 1)
			return true;
		return false;
	}

	void ID3(shared_ptr<Node> &root_) {
		if (isTheSingleClasses(root_))
			return;

		// if the feature set is null, make the node a single node
		if (root_->table->getColNum() > 1) {
			setInformationGain(root_);
			map<double, int> conditionalEntropyAndIndex;
			int size = root_->table->getColNum();
			for (int i = 0; i < size; ++i) {
				if (i == root_->sourceIndex)
					continue;
				informationGain.setIFindex(i);
				conditionalEntropyAndIndex[1 - informationGain.getInformationGain()] = i;
			}
			// the first one is the feature best
			root_->featureIndex = (conditionalEntropyAndIndex.begin())->second;
			root_->featureName = root_->table->getColName(root_->featureIndex);


			// if the maximal gain is small than threshold, make the node a single node
			if ((1 - conditionalEntropyAndIndex.begin()->first) < THRESHOLD) {
				root_->sign = findSign(root_);
				return;
			}
			// cut the table
			cutTable(root_);
			// process the sub tree
			for (auto &i : root_->subNode) {
				ID3(i);
			}
		} else if (root_->table->getColNum() == 1) {
			root_->sign = findSign(root_);
		}
	}

	void C4_5(shared_ptr<Node> &root_) {
		if (isTheSingleClasses(root_))
			return;

		// if the feature set is null, make the node a single node
		if (root_->table->getColNum() > 1) {
			setInformationGain(root_);
			map<double, int> conditionalEntropyAndIndex;
			int size = root_->table->getColNum();
			for (int i = 0; i < size; ++i) {
				if (i == root_->sourceIndex)
					continue;
				informationGain.setIFindex(i);
				conditionalEntropyAndIndex[1 - informationGain.getInformationGainRatio()] = i;
			}
			// the first one is the feature best
			root_->featureIndex = (conditionalEntropyAndIndex.begin())->second;
			root_->featureName = root_->table->getColName(root_->featureIndex);
			// if the maximal gain is small than threshold, make the node a single node
			if ((1 - conditionalEntropyAndIndex.begin()->first) < THRESHOLDRATIO) {
				root_->sign = findSign(root_);
				return;
			}
			// cut the table
			cutTable(root_);
			// process the sub tree
			for (auto &i : root_->subNode) {
				C4_5(i);
			}
		} else if (root_->table->getColNum() == 1) {
			root_->sign = findSign(root_);
		}
	}

	// refresh the information gain calculator
	void setInformationGain (shared_ptr<Node> &root_) {
		Table tableTemp = *(root_->table);
		informationGain.setTable(tableTemp);
		informationGain.setSourceIndex(root_->sourceIndex);
	}

	bool isTheSingleClasses(shared_ptr<Node> &root_) {
		if (root_ == nullptr || root_->table == nullptr)
			return true;

		// the source col of table has only one classes
		if (isOneClassesNode(root_)) {
			root_->sign = findSign(root_);
			return true;
		}
		return false;
	}

	// cut the table of root
	void cutTable(shared_ptr<Node> &root_) {
		Table tableTemp = *(root_->table);
		map<string, vector<Row> > subTable;
		vector<string> bestFeatureCol = tableTemp.getCol(root_->featureIndex);

		// erase the column of the best feature
		tableTemp.eraseCol(root_->featureIndex);
		int index = 0;

		// get the elements of each classes
		for (auto &i : bestFeatureCol) {
			subTable[i].push_back(tableTemp.getRow(index++));
		}

		// set the sub tree
		for (auto &i : subTable) {
			Table *t = new Table();
			for (auto &j : i.second) {
				t->addRow(j);
			}
			t->setColName(tableTemp.getNameRow());
			int sourceIndexTemp = root_->sourceIndex;
			if (sourceIndexTemp > root_->featureIndex)
				sourceIndexTemp--;

			shared_ptr<Node> n = shared_ptr<Node> (new Node(0, sourceIndexTemp));
			n->featureValue = i.first;
			n->table = t;
			root_->subNode.push_back(n);
		}
		delete root_->table;
	}

	void decisionMakingTreeID3() {
		ID3(root);
	}
	void decisionMakingTreeC45() {
		C4_5(root);
	}

	shared_ptr<Node> &getRoot(){
		return root;
	}

private:
	InformationGain informationGain;
	shared_ptr<Node> root;
};

#endif