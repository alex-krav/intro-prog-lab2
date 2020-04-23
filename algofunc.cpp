#include "iofunc.h"
#include <iostream>
#include <algorithm>

using namespace std;

int TOP_N = 10;
vector<int> GRADES = { 12,10,8,7,6,5,4,3,2,1 };

vector<kvPair> get_topN_grades(map<string, vector<int>> country_votes) {
	map<string, int> country_grades, one_country_votes;

	// init grades
	for (const auto& pair : country_votes) {
		country_grades[pair.first] = 0;
	}

	for (int i = 0; i < country_votes.size(); ++i) {
		// get one country votes
		for (const auto& pair : country_votes) {
			one_country_votes[pair.first] = pair.second[i];
		}

		// sort countries by votes in one column descending
		vector<kvPair> vec;
		copy(one_country_votes.begin(),
			one_country_votes.end(),
			back_inserter<vector<kvPair>>(vec));
		sort(vec.begin(), vec.end(),
			[](const kvPair& l, const kvPair& r) {
				return l.second > r.second;
			});

		// add grades to TOP_N countries
		for (int j = 0; j < TOP_N; ++j) {
			country_grades[vec[j].first] += GRADES[j];
		}
	}

	// sort countries by grades and return TOP_N
	vector<kvPair> vec;
	copy(country_grades.begin(),
		country_grades.end(),
		back_inserter<vector<kvPair>>(vec));
	sort(vec.begin(), vec.end(),
		[](const kvPair& l, const kvPair& r) {
			if (l.second != r.second)
				return l.second > r.second;
			return l.first < r.first;
		});
	vec.resize(TOP_N);
	return vec;
}
