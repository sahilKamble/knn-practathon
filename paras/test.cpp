#include "bits/stdc++.h"
#include <random>
#include <chrono>
#include <cstdio>
#include <ctime>

using namespace std;

#define filename "data.csv"
#define datasize 1e7

void create(int rows) {
    normal_distribution<float> distribution(0, 100);
    ofstream fout;
    fout.open(filename);
    string line;
    random_device rand;
    default_random_engine generator(rand());
    for (int i = 1; i <= rows; i++) {
        line = "";
        // string line = "";
        for (int i = 1; i < 100; i++) {
            // Insert the data to file
            line += to_string((int)distribution(generator)) + ",";
        }
        line += to_string((int)distribution(generator)) + "\n";
        fout << line;
    }
}

void read(vector<vector<int> > &data) {
    ifstream fin;
    string line, word;
    vector<int> row;
    fin.open(filename);
    while (!fin.eof()) {
        row.clear();

        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);

        // used for breaking words
        stringstream s(line);
        while (getline(s, word, ',')) {

            // add all the column data
            // of a row to a vector
            // cout << word;
            row.push_back(stod(word));
        }
        data.push_back(row);
    }
}

int main() {
    vector<vector<int> > data;
    auto wcts = std::chrono::system_clock::now();
    create(datasize);
    // read(data);
    chrono::duration<double> wctduration = (chrono::system_clock::now() - wcts);
    cout << "Finished in " << wctduration.count() << " seconds [Wall Clock]"
         << std::endl;
    // cout << accumulate(data[10].begin(), data[10].end(), 0.0) /
    // data[10].size();
    return 0;
}