#include<iostream>
#include<vector>
#include<cstdio>
#include<ctime>
#include<cmath>
#include<fstream>
using namespace std;

class KPSA{
public:
    int iter;
    int files;
    int size;

    int w1;
    int w2;
    int W;
    int v1;
    int v2;
    int Best;
    int f;
    double T;
    double turnaround;

    vector<int> value;
    vector<int> weight;
    vector<int> alternation;
    vector<int> neighbor;

    KPSA(int Iteration,int Run);
    void SA();
    void ReadFile(int num);
    void Initialize();
    void restartT();
    vector<int> Transition(vector<int> arr);
    void Fitness(vector<int> arr1,vector<int> arr2);
    void Determination();
    void updateT(int f);


};