#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;
namespace fs = filesystem;
typedef pair<string, int> kvPair;

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " DIRECTORY" << endl;
		return 1;
	}
	string path = argv[1];
	cout << "processing directory: " << path << endl;
	
	map<string, vector<int>> country_votes;
	int size = 0;
	for (const auto& entry : fs::directory_iterator(path)) {
		auto file = entry.path();
		cout << "reading: " << file << endl;
		ifstream input(file);
		if (input.is_open())
		{
			string line, country, substr;
			int n; input >> n; size += n;
			getline(input, line);

			for (int i = 0; i < n; ++i) {
				vector<int> votes;
				getline(input, line);
				stringstream ss(line);
				getline(ss, country, ',');
				while (ss.good())
				{
					getline(ss, substr, ',');
					votes.push_back(stoi(substr));
				}				
				country_votes[country] = votes;
			}
			
			input.close();
		}
		else cout << "Unable to open input file: " << file << endl;
	}
	
	map<string, int> country_grades, one_country_votes;
	for (const auto& pair : country_votes) {
		country_grades[pair.first] = 0;
	}
	for (int i = 0; i < size; ++i) {
		for (const auto& pair : country_votes) {
			one_country_votes[pair.first] = pair.second[i];
		}
		vector<kvPair> vec;
		copy(one_country_votes.begin(),
			one_country_votes.end(),
			back_inserter<vector<kvPair>>(vec));
		sort(vec.begin(), vec.end(),
			[](const kvPair& l, const kvPair& r) {
				return l.second > r.second;
			});
		vector<int> grades = { 12,10,8,7,6,5,4,3,2,1 };
		for (int j = 0; j < 10; ++j) {
			country_grades[vec[j].first] += grades[j];
		}
	}
	vector<kvPair> vec;
	copy(country_grades.begin(),
		country_grades.end(),
		back_inserter<vector<kvPair>>(vec));
	sort(vec.begin(), vec.end(),
		[](const kvPair& l, const kvPair& r) {
			return l.second > r.second;
		});

	string out = "results.csv";
	cout << "saving results to: " << out << endl;
	ofstream output(out, ios_base::trunc);
	if (output.is_open())
	{
		for (int i = 0; i < 10; ++i) {
			output << vec[i].first << ',' << vec[i].second << endl;
		}
		output.close();
	}
	else cout << "Unable to open output file " << out << endl;

	return 0;
}