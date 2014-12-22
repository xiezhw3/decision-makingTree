/**
 * @file informationGain.h
 * @description Caculate the infoemationGain of the decision-making tree
 * @author Zhiwang Xie
 * @mail xiezhiw3@gmail.com
 * @github https://github.com/xiezhw3
 * @data Dec 18 2014
 **/

#ifndef INFORMATIONGAIN_H
#define INFORMATIONGAIN_H

#include <iostream>
#include <vector>
#include "entropy.h"

class InformationGain {
public:
	InformationGain() {
		sourceIndex = -1;
		IFIndex = -1;
		isSetTable = false;
		isUpdatedInformationGain = false;
	}

	InformationGain(const Table &t, int sourceIndex_ = 0, int IFIndex_ = 0) {
		table = t;
		sourceIndex = sourceIndex_;
		IFIndex = IFIndex_;
		entropy.setTable(table);
		entropy.setSourceIndex(sourceIndex);
		isSetTable = true;
		isUpdatedInformationGain = false;
	}

	void setTable(const Table &table_) {
		table = table_;
		entropy.setTable(table);
		isSetTable = true;
	}

	void setSourceIndex(const int sourceIndex_) {
		sourceIndex = sourceIndex_;
		entropy.setSourceIndex(sourceIndex);
	}

	void setIFindex(int IFIndex_) {
		IFIndex = IFIndex_;
		isUpdatedInformationGain = false;
	}

	bool calInformationGain() {
		if (!isSetTable || sourceIndex == -1 || IFIndex == -1)
			return false;
		informationGain = entropy.getSourceEntropy(sourceIndex) - entropy.getConditionalEntropy(IFIndex);
		isUpdatedInformationGain = true;
		return true;
	}

	double getInformationGain() {
		if (!isUpdatedInformationGain) {
			if (!calInformationGain()) {
				return 0;
			}
		}
		return informationGain;
	}

	double getInformationGainRatio() {
		if (!isUpdatedInformationGain) {
			if (!calInformationGain()) {
				return 0;
			}
		}
		return informationGain / entropy.getSourceEntropy(sourceIndex);
	}
	
private:
	double informationGain;
	bool isUpdatedInformationGain;
	Entropy entropy;
	Table table;
	bool isSetTable;
	int sourceIndex;
	int IFIndex;
};

#endif