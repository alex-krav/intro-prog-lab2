#ifndef IOFUNC_H
#define IOFUNC_H

#include <map>
#include <vector>
#include <string>

using namespace std;
typedef pair<string, int> kvPair;

map<string, vector<int>> read_votes_from_csv(string);
vector<kvPair> get_topN_grades(map<string, vector<int>>);
void save_results(vector<kvPair>, string);

#endif
