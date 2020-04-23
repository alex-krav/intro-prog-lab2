#ifndef ALGOFUNC_H
#define ALGOFUNC_H

#include <map>
#include <vector>
#include <string>

using namespace std;
typedef pair<string, int> kvPair;

vector<kvPair> get_topN_grades(map<string, vector<int>>);

#endif