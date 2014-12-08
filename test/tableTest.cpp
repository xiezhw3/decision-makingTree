#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "table.h"

using namespace std;

void testRow() {
	cout << "----------------- Row test ---------------" << endl;
	vector<string> r{"republican","n","y","n","y","y","n","n","n","n","n","?","?","y","y","n","n"};
	// --- test constructor 1-----
	Row row(r);
	int i;
	for (i = 0; i != 17; ++i) {
		if (row.getElement(i) != r[i]) {
			cout << "contructor Row(vector<string> &e) error" << endl;
			break;
		}
	}
	if (i == 17)
		cout << "contructor Row(vector<string> &e) ok" << endl;

	// --- test constructor 2-----
	Row row2(row);
	for (i = 0; i != 17; ++i) {
		if (row2.getElement(i) != r[i]) {
			cout << "contructor Row(const Row &row) error" << endl;
			break;
		}
	}
	if (i == 17)
		cout << "contructor Row(const Row &row) ok" << endl;

	// ---- test operator = ------
	Row row3 = row;
	for (i = 0; i != 17; ++i) {
		if (row3.getElement(i) != r[i]) {
			cout << "operator = error" << endl;
			break;
		}
	}
	if (i == 17)
		cout << "operator = ok" << endl;

	// ---- test setRow -----
	Row row4;
	row4.setRow(r);
	for (i = 0; i != 17; ++i) {
		if (row4.getElement(i) != r[i]) {
			cout << "setRow error" << endl;
			break;
		}
	}
	if (i == 17)
		cout << "setRow ok" << endl;

	// ----- test insert element ------
	string a("wc");
	row.insert(0, a);
	if (row.getElement(0) == a) {
		for (i = 1; i != 18; ++i) {
			if (row.getElement(i) != r[i - 1]) {
				cout << "insert error" << endl;
				break;
			}
		}
		if (i == 18)
			cout << "insert ok" << endl;
	} else {
		cout << "insert error" << endl;
	}

	// ---- test erase ----
	row.erase(0);
	row.erase(16);
	for (i = 0; i != 16; ++i) {
		if (row.getElement(i) != r[i]) {
			cout << "erase error" << endl;
			break;
		}
	}
	if (i == 16)
		cout << "erase ok" << endl;
}

void testTable() {
	cout << "----------------- table test ---------------" << endl;
	Table table;
	vector<string> v1 {"democrat","n","y","n","y","y","y","n","n","n","n","n","n","?","y","y","y"};
	vector<string> v2 {"republican","n","y","n","y","y","y","n","n","n","n","n","n","y","y","?","y"};
	vector<string> v3 {"republican","n","y","n","y","y","y","n","n","n","n","n","y","y","y","n","y"};
	vector<string> v4 {"democrat","y","y","y","n","n","n","y","y","y","n","n","n","n","n","?","?"};

	// ---- test addRow -----
	table.addRow(Row(v1));
	table.addRow(Row(v2));
	table.addRow(Row(v3));
	table.addRow(Row(v4));
	if (table.getRowNum() != 4 || table.getColNum() != 17)
		cout << "addRow error" << endl;
	Row row = table.getRow(1);
	int i;
	for (i = 0; i != 17; ++i) {
		if (row.getElement(i) != v2[i]) {
			cout << "addRow error" << endl;
			break;
		}
	}
	if (i == 17)
		cout << "addRow ok" << endl;

	// ----- test erase row ------
	table.eraseRow(1);
	if (table.getRowNum() != 3 || table.getColNum() != 17)
		cout << "eraseRow error" << endl;
	row = table.getRow(1);
	for (i = 0; i != 17; ++i) {
		if (row.getElement(i) != v3[i]) {
			cout << "eraseRow error" << endl;
			break;
		}
	}
	if (i == 17)
		cout << "eraseRow ok" << endl;

	// ----- test erase col ------
	table.eraseCol(0);
	if (table.getRowNum() != 3 || table.getColNum() != 16)
		cout << "eraseCol error" << endl;
	row = table.getRow(1);
	for (i = 0; i != 16; ++i) {
		if (row.getElement(i) != v3[i + 1]) {
			cout << "eraseCol error" << endl;
			break;
		}
	}
	if (i == 16)
		cout << "eraseCol ok" << endl;

	// ----- test constructor1 ------
	Table table2(table);
	if (table2.getRowNum() != 3 || table2.getColNum() != 16)
		cout << "constructor1 error" << endl;
	row = table2.getRow(1);
	for (i = 0; i != 16; ++i) {
		if (row.getElement(i) != v3[i + 1]) {
			cout << "constructor1 error" << endl;
			break;
		}
	}
	if (i == 16)
		cout << "constructor1 ok" << endl;

	// ----- test operator = -------
	Table table3 = table;
	if (table3.getRowNum() != 3 || table3.getColNum() != 16)
		cout << "constructor1 error" << endl;
	row = table3.getRow(1);
	for (i = 0; i != 16; ++i) {
		if (row.getElement(i) != v3[i + 1]) {
			cout << "constructor1 error" << endl;
			break;
		}
	}
	if (i == 16)
		cout << "constructor1 ok" << endl;
}

int main(int argc, char const *argv[])
{
	testRow();
	testTable();
	return 0;
}