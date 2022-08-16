#include "defns.h"
// assert(data_size >= k);
template<typename T>
void print_queue(T q) { // NB: pass by value so the print uses a copy
    while(!q.empty()) {
        cout << q.top().second << ',' << q.top().first << ' ';
        q.pop();
    }
    cout << '\n';
}

int euc_distance(int d[], int q[]) {
    int sum = 0;
    for(int i = 0; i < dims; i++) {
        sum += (d[i] - q[i])*(d[i] - q[i]);
    }
    // return sqrt(sum);
    return sum; //doesnt make a difference
}

priority_queue< pair<int,int> > brute_search(int data[][dims], int q[]) {
    priority_queue<pair<int,int> > pq;
    int d;
    // cout << "\ndistances are :";
    for(int i = 0; i < k; i++) {
        d = euc_distance(data[i], q);
        // cout << d << " ";
        pq.push(make_pair(d,i));
    }
    
    for(int i = k; i < data_size; i++) {
        d = euc_distance(data[i], q);
        // cout << d << " ";
        pq.push(make_pair(d,i));
        pq.pop(); //removes the top element, using std::less<T> causes the largest element(distance) to appear as the top().
    }
    return pq;
}

void make_query_uniform(int q[]) {
    //random generator from SO
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(min_range, max_range); // define the range
    for(int i = 0; i < dims; i++) q[i] = distr(gen);
    return;
}

int main() {
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

    int query[dims];
    make_query_uniform(query);
    
    auto start = chrono::steady_clock::now();
    priority_queue<pair<int,int> > res = brute_search(data, query);
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "Brute forced " << data_size << " " << dims << "D "<<"vectors " <<"in ";
    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    cout << "result (index, distance^2) :";
    print_queue(res);
    free(data);
    f.close();
}