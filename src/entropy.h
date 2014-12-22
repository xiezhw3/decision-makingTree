/**
 * @file entropy.h
 * @description calculate the entropy
 * @author Zhiwang Xie
 * @mail xiezhiw3@gmail.com
 * @github https://github.com/xiezhw3
 * @data Dec 18 2014
 **/

#ifndef ENTROPY_H
#define ENTROPY_H

#include <vector>
#include "table.h"
#include <map>
#include <cmath>
#include <string>

class Entropy {
public:
	Entropy() {
		isSourceprobabilitySet = false;
		sourceEntropy = -1;
	}
	Entropy (Table &table_, int sourceIndex_ = 0):sourceIndex(sourceIndex_) {
		table = table_;
		isSourceprobabilitySet = false;
		sourceEntropy = -1;
	}

	void setTable(Table &table_) {
		table = table_;
	}

	void setSourceIndex(int sourceIndex_) {
		sourceIndex = sourceIndex_;
	}

	map<string, double> calSourceLikelihoodProbability(int IFIndex) {
		map<string, double> sourceProbability;
		auto col = table.getCol(IFIndex);
		map<string, int> frequency;
		int sum = 0;
		for (auto &i : col) {
			frequency[i]++;
			++sum;			
		}
		if (sum != 0) {
			for (auto &i : frequency) {
				sourceProbability[i.first] = ((double)i.second / (double)sum);
			}
		}
		return sourceProbability;
	}

	map<string, map<string, double> > getConditionalProbability (int sourceIndex, int IFIndex) {
		auto colSource = table.getCol(sourceIndex);
		auto colIF = table.getCol(IFIndex);
		map<string, vector<string> > differentClassesNum;
		int index = 0;
		for (auto &i : colIF) {
			differentClassesNum[i].push_back(colSource[index++]);
		}
		map<string, map<string, double> > conditionalProbability;
		for (auto &i : differentClassesNum) {
			map<string, int> frequency;
			for (auto &j : i.second) {
				frequency[j]++;
			}
			size_t size = i.second.size();
			if (size != 0) {
				for (auto &j : frequency) {
					conditionalProbability[i.first][j.first] = ((double)j.second / (double)size);
				}
			} else {
				conditionalProbability[i.first][0] = 0.0;
			}
		}
		return conditionalProbability;
	}

	double calEntropy(map<string, double> elementAndProbability) {
		double entropy = 0;
		for (auto &i : elementAndProbability) {
			entropy += (-(i.second * log2(i.second)));
		}
		return entropy;
	}

	double getConditionalEntropy(int IFIndex) {
		auto conditionalProbability = getConditionalProbability(sourceIndex, IFIndex);
		auto sourceProbability = calSourceLikelihoodProbability(IFIndex);
		double conditionalEntropy = 0; 
		for (auto &i : sourceProbability) {
			conditionalEntropy += ((i.second) * calEntropy(conditionalProbability[i.first]));
		}
		return conditionalEntropy;
	}

	double getEmpiricalEntropy(int IFIndex) {
		return getSourceEntropy(IFIndex);
	}

	double getSourceEntropy(int IFIndex) {
		auto sourceProbability = calSourceLikelihoodProbability(IFIndex);
		sourceEntropy = calEntropy(sourceProbability);
		return sourceEntropy;
	}

private:
	Table table;
	int sourceIndex;
	bool isSourceprobabilitySet;
	double sourceEntropy;
};

#endif