/*
	calculate the precision rate
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> readFile(const string &filePath) {
	vector<string> readResult;
	ifstream in(filePath);
	if (!in.is_open()){ 
		cout << "Error opening file" << endl; 
		exit (1); 
	}

	char line[1024];
	while (in.getline(line, sizeof(line))) {
		string word(line);
		readResult.push_back(word);
	}
	in.close();
	return readResult;
}

double getPrecisionRate(const string &filePath1, const string &filePath2) {
	vector<string> predictResult = readFile(filePath1);
	vector<string> sourceresult = readFile(filePath2);
	int rightNum;
	int size = predictResult.size();
	for (int i = 0; i != size; ++i)
		if (predictResult[i] == sourceresult[i])
			rightNum++;
	return (double)rightNum / (double)(size);
}

void writeToFile(const string &filePath, double n) {
	ofstream out(filePath, ios::app);
	if (!out.is_open()){ 
		cout << "Error opening file" << endl; 
		exit (1); 
	}

	out << n << endl;

	out.close();
}

int main(int argc, char const *argv[])
{
	if (argc != 4) {
		cout << "Please run the tree maker in this model: [cal] [predict result file] \
				[source result file] [result out file]" << endl;
	} else {
		double res = getPrecisionRate(argv[1], argv[2]);
		writeToFile(argv[3], res);
	}
	return 0;
}