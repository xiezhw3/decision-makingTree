/**
 * @file node.h
 * @description The node struct of the tree
 * @author Zhiwang Xie
 * @mail xiezhiw3@gmail.com
 * @github https://github.com/xiezhw3
 * @data Dec 18 2014
 **/

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
	vector< shared_ptr<Node> > subNode;
};

#endif