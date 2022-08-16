#include "headers.h"

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
        int i = 0;
        int j = 0;
        stringstream s(line);
        while (getline(s, word, ',')) {

            // add all the column data
            // of a row to a vector
            // cout << word;
            data[j][i] = stoi(word);
            i++;
            i = i % 100;
            // row.push_back(stoi(word));
        }
        // data.push_back(row);
        j++;
        
    }
}

int distance(vector<int> &x1, vector<int> &x2) {
    int sum = 0;
    for (int i = 0; i < features; i++) {
        sum += (x1[i] - x2[i]) * (x1[i] - x2[i]);
    }
    return sum;
}

priority_queue<pair<int, int> > brute(vector<vector<int> > &data,
                                     vector<int> &query) {
    priority_queue<pair<int, int> > max_heap;
    for (int i = 0; i < k; i++) {
        max_heap.push(make_pair(distance(query, data[i]), i));
    }

    for (int i = k; i < datasize; i++) {
        int dist = distance(query, data[i]);
        max_heap.push(make_pair(dist, i));
        max_heap.pop();
    }

    return max_heap;
}

int main() {
    vector<vector<int> > data(datasize, vector<int> (features));
    read(data);

    vector<int> query(features);
    normal_distribution<float> distribution(0, 100);
    random_device rand;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    for (int i = 0; i < features; i++) {
        query[i] = (int)distribution(generator);
    }
    cout << "query generated" << endl;
    auto wcts = std::chrono::system_clock::now();
    auto results = brute(data, query);
    chrono::duration<double> wctduration = (chrono::system_clock::now() - wcts);
    cout << "Finished in " << wctduration.count() << " seconds [Wall Clock]"
         << std::endl;

    while (!results.empty()) {
        cout << results.top().second << " " << sqrt(results.top().first)
             << endl;
        results.pop();
    }

    return 0;
}