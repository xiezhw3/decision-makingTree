/**
 * @file pruningOfTheTree.h
 * @description Make purning of the tree
 * @author Zhiwang Xie
 * @mail xiezhiw3@gmail.com
 * @github https://github.com/xiezhw3
 * @data Dec 18 2014
 **/

#ifndef PRUNINGOFTREE_H
#define PRUNINGOFTREE_H

#include "node.h"
#include "entropy.h"
#include "decisionMakingTree.h"
#include <map>
#include <vector>
#include <stack>

#define ALPHA 0.01

class PruningOfTree{
public:
	PruningOfTree() { }
	~PruningOfTree() { }

	void setTree(DecisonMakingTree &tree_) {
		tree = tree_;
	}

	// in here, use shared_par will be better
	void pruningTree(shared_ptr<Node> &TreeRoot) {
		if (TreeRoot == nullptr || (TreeRoot->subNode.size() == 0))
			return;
		for (auto &i : TreeRoot->subNode) {
			if (i->subNode.size() != 0) {
				pruningTree(i);
			}
		}

		double beforeCutSubTree = getEmpiricalEntropyOfTree(tree.getRoot());
		vector< shared_ptr<Node> > subTree = TreeRoot->subNode;

		// cut the sub tree
		stack< shared_ptr<Node> > s;
		s.push(TreeRoot);
		TreeRoot->table = new Table();
		while (!s.empty()) {
			shared_ptr<Node> current = s.top();
			s.pop();
			if (current->subNode.size() == 0) {
				*(TreeRoot->table) = TreeRoot->table->addSource(*(current->table), TreeRoot->sourceIndex);
			} else {
				for (auto &i : current->subNode) {
					s.push(i);
				}
			}
		}

		TreeRoot->sign = tree.findSign(TreeRoot);
		TreeRoot->subNode.clear();

		double afterCutSubTree = getEmpiricalEntropyOfTree(tree.getRoot());

		if (afterCutSubTree <= beforeCutSubTree) {
			deleteSubTree(subTree);
		} else {
			TreeRoot->subNode = subTree;
			TreeRoot->sign = "";
			delete TreeRoot->table;
		}
	}

	void deleteSubTree(vector< shared_ptr<Node> > &subTree) {
		for (auto &i : subTree) {
			stack< shared_ptr<Node>> s;
			s.push(i);
			while (!s.empty()) {
				shared_ptr<Node> current = s.top();
				s.pop();
				if (current->subNode.size() == 0) {
					delete current->table;
				} else {
					for (auto &j : current->subNode) {
						s.push(j);
					}
				}
			}
		}
	}

	double getEmpiricalEntropyOfTree(shared_ptr<Node> &root_) {
		double entropyOfTree = 0.0;
		int leafNum = 0;
		stack< shared_ptr<Node> > s;
		s.push(root_);
		while (!s.empty()) {
			shared_ptr<Node> current = s.top();
			s.pop();
			if (current->subNode.size() == 0) {
				leafNum++;
				setInformationGain(current);
				entropyOfTree += (current->table->getRowNum()) * entropy.getEmpiricalEntropy(current->sourceIndex);
			} else {
				for (auto &i : current->subNode) {
					s.push(i);
				}
			}
		}
		return entropyOfTree + ALPHA * leafNum;
	}

	void setInformationGain (shared_ptr<Node> &root_) {
		entropy.setTable(*(root_->table));
		entropy.setSourceIndex(root_->sourceIndex);
	}

	void makePruningTree () {
		pruningTree(tree.getRoot());
	}

private:
	Entropy entropy;
	DecisonMakingTree tree;
};

#endif