#include "KPSA.h"

int main(int argc,char** argv){
    int Iteration = atoi(argv[1]);
    int Files = atoi(argv[2]);

    KPSA sa(Iteration,Files);
    sa.SA();
    return 0;
}