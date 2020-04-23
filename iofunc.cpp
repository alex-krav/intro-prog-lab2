#include "iofunc.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
namespace fs = filesystem;

map<string, vector<int>> read_votes_from_csv(string path) {
	map<string, vector<int>> country_votes;

	for (const auto& entry : fs::directory_iterator(path)) {
		auto file = entry.path();
		cout << "reading: " << file << endl;

		ifstream input(file);
		if (input.is_open())
		{
			string line;
			getline(input, line); // skip number

			while (getline(input, line))
			{
				string country, vote;
				vector<int> votes;
				stringstream ss(line);
				getline(ss, country, ',');

				while (ss.good())
				{
					getline(ss, vote, ',');
					votes.push_back(stoi(vote));
				}
				country_votes[country] = votes;
			}

			input.close();
		}
		else cout << "Unable to open input file: " << file << endl;
	}

	return country_votes;
}

void save_results(vector<kvPair> grades, string file) {
	cout << "saving results to: " << file << endl;
	ofstream output(file, ios_base::trunc);

	if (output.is_open())
	{
		for (const auto& pair : grades) 
			output << pair.first << ',' << pair.second << endl;

		output.close();
	}
	else cout << "Unable to open output file " << file << endl;
}