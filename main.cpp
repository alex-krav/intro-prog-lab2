#include <iostream>
#include "iofunc.h"
#include "algofunc.h"

using namespace std;

const int TOP_NUM = 10;
const vector<int> GRADES = { 12,10,8,7,6,5,4,3,2,1 };

int main(int argc, char* argv[])
{
	string out_file = "results.csv";
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " DIRECTORY" << endl;
		return 1;
	}
	string in_dir = argv[1];

	cout << "processing directory: " << in_dir << endl;
	map<string, vector<int>> country_votes = read_votes_from_csv(in_dir);
	vector<kvPair> country_grades = get_topN_grades(country_votes, TOP_NUM, GRADES);
	save_results(country_grades, out_file);

	return 0;
}