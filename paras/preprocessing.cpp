#include "headers.h"

void create(int rows) {
    normal_distribution<float> distribution(0, 100);
    ofstream fout;
    fout.open(filename);
    string line;
    random_device rand;
    for (int i = 1; i <= rows; i++) {
        line = "";
        default_random_engine generator(rand());
        // string line = "";
        for (int i = 1; i < features; i++) {
            // Insert the data to file
            line += to_string((int)distribution(generator)) + ',';
        }
        line += to_string((int)distribution(generator)) + '\n';
        fout << line;
    }
}

int main() {
    create(datasize);
    return 0;
}