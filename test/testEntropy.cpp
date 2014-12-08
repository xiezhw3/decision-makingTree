#include <iostream>
#include "entropy.h"
#include "table.h"
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	Entropy entropy;
	Table table;
	vector<string> v1  {"qingnian", "1", "1", "1", "1"};
	vector<string> v2  {"qingnian", "1", "1", "2", "1"};
	vector<string> v3  {"qingnian", "2", "1", "2", "2"};
	vector<string> v4  {"qingnian", "2", "2", "1", "2"};
	vector<string> v5  {"qingnian", "1", "1", "1", "1"};
	vector<string> v6  {"zhongnian", "1", "1", "1", "1"};
	vector<string> v7  {"zhongnian", "1", "1", "2", "1"};
	vector<string> v8  {"zhongnian", "2", "2", "2", "2"};
	vector<string> v9  {"zhongnian", "1", "2", "3", "2"};
	vector<string> v10 {"zhongnian", "1", "2", "3", "2"};
	vector<string> v11 {"laonian", "1", "2", "3", "2"};
	vector<string> v12 {"laonian", "1", "2", "2", "2"};
	vector<string> v13 {"laonian", "2", "1", "2", "2"};
	vector<string> v14 {"laonian", "2", "1", "3", "2"};
	vector<string> v15 {"laonian", "1", "1", "1", "1"};

	table.addRow(Row(v1 ));
	table.addRow(Row(v2 ));
	table.addRow(Row(v3 ));
	table.addRow(Row(v4 ));
	table.addRow(Row(v5 ));
	table.addRow(Row(v6 ));
	table.addRow(Row(v7 ));
	table.addRow(Row(v8 ));
	table.addRow(Row(v9 ));
	table.addRow(Row(v10));
	table.addRow(Row(v11));
	table.addRow(Row(v12));
	table.addRow(Row(v13));
	table.addRow(Row(v14));
	table.addRow(Row(v15));

	// ---- test setTable ---
	entropy.setTable(table);
	entropy.setSourceIndex(4);
	int i;
	for (i = 0; i != 4; ++i) {
		cout << entropy.getSourceEntropy(4) - entropy.getConditionalEntropy(i) << endl;
	}

	return 0;
}