#include <iostream>
#include "iofunc.h"

using namespace std;

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
	vector<kvPair> country_grades = get_topN_grades(country_votes);
	save_results(country_grades, out_file);

	return 0;
}