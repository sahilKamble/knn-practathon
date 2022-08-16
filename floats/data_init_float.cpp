#include "defns.h"
// void make_data_uniform(float A[][dims]) {
//     //random generator from SO
//     random_device rd; // obtain a random number from hardware
//     mt19937 gen(rd()); // seed the generator
//     uniform_float_distribution<> distr(min_range, max_range); // define the range
//     for(float i = 0; i < data_size; i++) {
//         for(float j = 0; j < dims; j++) {
//             A[i][j] = distr(gen);
//         }
//     }
//     return;
// }
//does a float to float conversion after generation 
//probably not right then :(
void make_data_gaussian(float A[][dims]) {
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
    float (*data)[dims]; 
    data = (float (*)[dims])malloc(sizeof(float[data_size][dims]));
    // make_data_uniform(data);
    make_data_gaussian(data);
    ofstream f;
    f.open ("data_float.txt");
    for (int i = 0 ; i < data_size ; i++)
    {
        for (int j = 0 ; j < dims ; j++)
        {
            f << data[i][j] << ',';
        }
    }
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "\nWrote " << dims*data_size << " floats;" << "Time taken " << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    free(data);
    f.close();
}