/**
 * @file table.h
 * @description The table struct of the tree
 * @author Zhiwang Xie
 * @mail xiezhiw3@gmail.com
 * @github https://github.com/xiezhw3
 * @data Dec 18 2014
 **/

#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>

using namespace std;

class Row{
public:
	Row() { colNum = -1; }
	Row(const vector<string> &e): element(e) {
		colNum = e.size();
	}

	Row(vector<string> &e): element(e) {
		colNum = e.size();
	}

	Row(const Row &row) {
		if (this == &row)
			return;
		element = row.element;
		colNum = row.colNum;
	}

	Row(Row &row) {
		if (this == &row)
			return;
		element = row.element;
		colNum = row.colNum;
	}

	Row& operator= (const Row &row) {
		if (this != &row) {
			element = row.element;
			colNum = row.colNum;
		}
		return *this;
	}

	Row& operator= (Row &row) {
		if (this != &row) {
			element = row.element;
			colNum = row.colNum;
		}
		return *this;
	}

	void setRow(vector<string> &e) {
		colNum = e.size();
		element = e;
	}

	void insert(int index, string &value) {
		auto iter = element.begin() + index;
		if (iter <= element.end())
			element.insert(iter, value);
		else
			element.push_back(value);
		colNum++;
	}

	void erase(int index) {
		auto iter = element.begin() + index;
		if (iter < element.end()) {
			element.erase(iter);
			colNum--;
		}
	}

	int getColNum() const {
		return colNum;
	}

	vector<string> getElements() const {
		return element;
	}

	string getElement(int index) const {
		if (index >= 0 && index < colNum)
			return element[index];
		return "";
	}

private:
	vector<string> element;
	int colNum;
};

class Table {
public:
	Table() {
		colNum = 0;
		rowNum = 0;
	}

	Table(const Table& t) {
		if (this == &t)
			return;
		tableElement = t.tableElement;
		colName = t.colName;
		colNum = t.colNum;
		rowNum = t.rowNum;
	}

	Table& operator= (const Table& t) {
		if (this != &t) {
			tableElement = t.tableElement;
			colName = t.colName;
			colNum = t.colNum;
			rowNum = t.rowNum;
		}

		return *this;
	}

	Table& operator+ (Table& t) {
		if (colNum != t.colNum)
			exit(1);
		int size = t.getRowNum();
		for (int i = 0; i != size; ++i)
			tableElement.push_back(t.getRow(i));
		colNum = t.colNum;
		rowNum += t.rowNum;
		colName = t.colName;

		return *this;
	}

	Table& addSource(Table& t, int colIndex) {
		if (colNum != 1) {
			tableElement.clear();
			colNum = 1;
			vector<string> v; v.push_back("col"); colName = Row(v);
			rowNum = 0;
		}

		vector<string> v = t.getCol(colIndex);
		for (auto &i : v) {
			tableElement.push_back(Row(v));
		}
		rowNum += t.rowNum;
		return *this;
	}

	Table getTable() const {
		return *this;
	}

	bool addRow(Row &row) {
		if (colNum == 0 && rowNum == 0) {
			tableElement.push_back(row);
			colNum = row.getColNum();
		} else {
			if (row.getColNum() != colNum)
				return false;

			tableElement.push_back(row);
		}
		rowNum++;
		return true;
	}

	bool addRow(const Row &row) {
		if (colNum == 0 && rowNum == 0) {
			tableElement.push_back(row);
			colNum = row.getColNum();
		} else {
			if (row.getColNum() != colNum)
				return false;

			tableElement.push_back(row);
		}
		rowNum++;
		return true;
	}

	bool eraseRow(int index) {
		auto iter = tableElement.begin() + index;
		if (rowNum <= 0)
			return false;

		if (iter < tableElement.end()) {
			tableElement.erase(iter);
			rowNum--;
			return true;
		}
		return false;
	}

	bool eraseCol(int colNumIndex) {
		if (colNumIndex > colNum || colNum <= 0)
			return false;
		for (auto &i : tableElement) {
			i.erase(colNumIndex);
		}
		colName.erase(colNumIndex);
		colNum--;
		return true;
	}

	Row getRow(int index) const {
		if (index >= 0 && index < rowNum)
			return tableElement[index];
		return Row();
	}

	Row getNameRow() {
		return colName;
	}

	vector<string> getCol(int index) {
		vector<string> col;
		if (index >= 0 && index < colNum) {
			for (auto &i : tableElement)
				col.push_back(i.getElement(index));
		}
		return col;
	}

	int getRowNum() const {
		return rowNum;
	}

	int getColNum() const {
		return colNum;
	}

	string getColName(int index) {
		return colName.getElement(index);
	}

	void setColName(const Row &row) {
		colName = row;
	}

	void setColName(Row &row) {
		colName = row;
	}

private:
	vector<Row> tableElement;
	Row colName;
	int colNum;
	int rowNum;
};

#endif