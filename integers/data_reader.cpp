#include "defns.h"
int main() {
    auto start = chrono::steady_clock::now();
    int (*data)[dims]; 
    data = (int (*)[dims])malloc(sizeof(int[data_size][dims]));
    string line;
    ifstream f;
    f.open ("data.txt");
    for (int i = 0 ; i < data_size ; i++)
    {
        for (int j = 0 ; j < dims ; j++)
        {
            getline(f, line,',');
            data[i][j] = stoi(line);
        }
    } 
    
    for (int i = 0 ; i < 10 ; i++)
    {
        for (int j = 0 ; j < 10 ; j++)
        {
            cout << data[i][j] << " ";
        }
        cout << "\n";
    } 
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "\nRead " << dims*data_size << " ints;" << "Time taken " << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    free(data);
    f.close();
}