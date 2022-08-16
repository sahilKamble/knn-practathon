#include "defns.h"
#include "lsh.h"

void make_hyperplanes(float hps[][dims]) {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_real_distribution<float> distr(min_range, max_range); // define the range
    for(int i = 0; i < nh; i++) {
        for(int j = 0; j<dims; j++) {
            hps[i][j] = distr(gen);
        }
    }
    return;
}
float dot_p(float a[], float b[]) {
    float sum = 0; 
    for(int i = 0; i < dims; i++) {
        sum += a[i]*b[i];
    }
    return sum;
}
int bitArrayToInt(bool arr[]) {
    int ret = 0;
    int tmp;
    for (int i = 0; i < nh; i++) {
        tmp = arr[i];
        ret |= tmp << ( nh - i - 1);
    }
    return ret;
}

unordered_map<string, vector<int> > create_hashmap(float data[][dims],float hps[][dims]) {
    unordered_map<string, vector<int> > hm;
    
    for(int i = 0; i < data_size; i++) {
        string hash="";
        for(int j = 0; j < nh; j++) {
            hash += dot_p(data[i],hps[j]) > 0 ? "1" : "0";
        }
        hm[hash].push_back(i);
    }
    return hm;
}

void fill_buckets(float data[][dims], float hps[][nh][dims], vector<unordered_map<string, vector<int> > > &buckets) { 
    for(int i = 0; i < l; i++) {
        buckets.push_back(create_hashmap(data, hps[i]));
    }
}

void find_knn_LSH(float data[][dims], float hps[][nh][dims], vector<unordered_map<string, vector<int> > > &buckets, float q[]) {
    vector<int> candidates;
    for(int i = 0; i < l; i++) {
        string hash = "";
        for(int j = 0; j < nh; j++) {
            hash += dot_p(data[i],hps[j]) > 0 ? "1" : "0";
        }
        
    }

}

void make_query_uniform(float q[]) {
    //random generator from SO
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_real_distribution<float> distr(min_range, max_range); // define the range
    for(int i = 0; i < dims; i++) q[i] = distr(gen);
    return;
}
int main() {
    float (*data)[dims]; 
    data = (float (*)[dims])malloc(sizeof(float[data_size][dims]));
    string line;
    ifstream f;
    f.open ("data_float.txt");
    for (int i = 0 ; i < data_size ; i++)
    {
        for (int j = 0 ; j < dims ; j++)
        {
            getline(f, line,',');
            data[i][j] = stof(line);
        }
    } 

    float query[dims];
    float hps[l][nh][dims];
    for(int i = 0; i < l; i++)
    make_hyperplanes(hps[i]);
    vector<unordered_map<string, vector<int> > > buckets;
    fill_buckets(data, hps, buckets);
    make_query_uniform(query);
    find_knn_LSH(data, hps, buckets, query);
    free(data);
    f.close();
    // auto start = chrono::steady_clock::now();
    // priority_queue<pair<float,float> > res = brute_search(data, query);
    // auto end = chrono::steady_clock::now();
    // auto diff = end - start;
    // cout << "Brute forced " << data_size << " " << dims << "D "<<"vectors " <<"in ";
    // cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    // cout << "result (index, distance^2) :";
    // print_queue(res);
    // free(data);
    // f.close();
}