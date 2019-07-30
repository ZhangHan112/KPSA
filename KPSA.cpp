#include "KPSA.h"

KPSA::KPSA(int Iteration,int Files){
    iter = Iteration;
    files = Files;

    srand(time(NULL));   
}

void KPSA::SA(){
    string str = "output0.dat";

    for(f=8;f<=files;f++){
        for(int j=0;j<30;j++){
        ReadFile(f);
        Initialize();        

        str.replace(6,1,to_string(f));
        // ofstream file(str);
        
        for(int i=0;i<iter;i++){
            if(i%500==0) // 500次iterations後，再次升溫
                restartT();
            neighbor = Transition(alternation);
            Fitness(alternation,neighbor);
            Determination();
            updateT(f);
            // file << i+1 << " " << Best << endl;
            //cout << "turnaround: " << turnaround << endl;
        }

        //file.close();
        cout << "p0" << f <<" Best: " << Best << endl;
    }
    }
}

void KPSA::Initialize(){
    alternation = vector<int> (size,0);
    neighbor = vector<int> (size,0);
    Best = 0;
}

void KPSA::restartT(){
    if(f==8)
        T = 1000000;
    else if(f>4)
        T = 1000000;
    else 
        T = 100000;
}

vector<int> KPSA::Transition(vector<int> arr){
    int pos = rand()%size;
    if(arr[pos]==0) 
        arr[pos] = 1;
    else
        arr[pos] = 0;
    
    // for(int i = 0;i<arr.size();i++)
    //     cout << arr[i] << " ";
    // cout << endl;
    return arr;
}

void KPSA::Fitness(vector<int> arr1,vector<int> arr2){
    v1=0;v2=0;w1=0;w2=0;
    for(int i=0;i<size;i++){
        if(arr1[i]==1){
            v1 += value[i];
            w1 += weight[i];
        }
        if(arr2[i]==1){
            v2 += value[i];
            w2 += weight[i];
        }
    }
        
}

void KPSA::Determination(){
    double random = (double)(rand()%100+1)/100;

    if( w1<W && w2<W ){
        if( v1<v2 ){
            if(Best<v2)
                Best = v2;
            alternation = neighbor;
            
        }
        else{
            turnaround = (double) exp( (double)(v2-v1)/T ); 
            if(random<turnaround)
                alternation = neighbor; 
        }
    }
    
}

void KPSA::updateT(int f){
    if(f==8)
        T *= 0.99999;
    else 
        T *= 0.999;

}

void KPSA::ReadFile(int num){
    string s = "p00_p.txt";
    int temp;
    
    
    value.clear();
    weight.clear();
    W = 0;


    s.replace(2,1,to_string(num)); // Read value[i]
    ifstream inputFile(s);
    while(inputFile>>temp){
        value.push_back(temp);
    }
    inputFile.close();

    s.replace(4,1,"w"); //Read weight[i]
    inputFile.open(s);
    while(inputFile>>temp){
        weight.push_back(temp);
    }
    inputFile.close();
    
    s.replace(4,1,"c"); //Read W
    inputFile.open(s);
    inputFile>>temp;
    W = temp;
    inputFile.close();

    size = value.size();
}