#ifndef NODE_H
#define NODE_H

struct Node{
	Node(int fi = 0, int s = 0):featureIndex(fi), sourceIndex(s), table(nullptr), 
								sign(""), featureName(""), featureValue("") { }
	int featureIndex;
	int sourceIndex;
	string featureName;
	string featureValue;
	string sign;
	Table *table;
	vector< Node* > subNode;
};

#endif