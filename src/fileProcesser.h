/**
 * @file fileProcess.h
 * @description file process class
 * @author Zhiwang Xie
 * @mail xiezhiw3@gmail.com
 * @github https://github.com/xiezhw3
 * @data Dec 18 2014
 **/

#ifndef FILEPROCESS_H
#define FILEPROCESS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class FileProcesser {
public:
	vector<vector<string> > readFileFormTrin(const string &filePath) {
		vector<vector<string> > readResult;
		ifstream in(filePath);
		if (!in.is_open()){ 
			cout << "Error opening file" << endl; 
			exit (1); 
		}
		char line[1024];

		// get each feature
		while (in.getline(line, sizeof(line))) {
			for (auto &i : line) {
				if (i != '\0') {
					if (i == ',')
						i = ' ';
				} else {
					break;
				}
			}
			stringstream result(line);
			vector<string> words;
			while (result) {
				string s = "";
				result >> s;
				words.push_back(s);
			}
			readResult.push_back(words);
		}
		in.close();
		return readResult;
	}

	vector<string> readFileFormPredict(const string &filePath) {
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

	void writeToFile(const string &filePath, vector<string> &result) {
		ofstream out(filePath);
		if (!out.is_open()){ 
			cout << "Error opening file" << endl; 
			exit (1); 
		}

		for (auto &i : result) {
			out << i << endl;
		}

		out.close();
	}
private:
	
};

#endif