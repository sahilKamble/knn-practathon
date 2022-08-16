#include "defns.h"
void make_data_uniform(int A[][dims]) {
    //random generator from SO
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(min_range, max_range); // define the range
    for(int i = 0; i < data_size; i++) {
        for(int j = 0; j < dims; j++) {
            A[i][j] = distr(gen);
        }
    }
    return;
}
//does a float to int conversion after generation 
//probably not right then :(
void make_data_gaussian(int A[][dims]) {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    normal_distribution<float> distri(mean, std_dev); 
    for(int i = 0; i < data_size; i++) {
        for(int j = 0; j < dims; j++) {
            A[i][j] = distri(gen);
        }
    }
    return;
}
int main() {
    auto start = chrono::steady_clock::now();
    int (*data)[dims]; 
    data = (int (*)[dims])malloc(sizeof(int[data_size][dims]));
    // make_data_uniform(data);
    make_data_gaussian(data);
    ofstream f;
    f.open ("data.txt");
    for (int i = 0 ; i < data_size ; i++)
    {
        for (int j = 0 ; j < dims ; j++)
        {
            f << data[i][j] << ',';
        }
    }
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "\nWrote " << dims*data_size << " ints;" << "Time taken " << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    free(data);
    f.close();
}