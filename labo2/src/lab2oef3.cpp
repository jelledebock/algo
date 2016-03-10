#include <iostream>
#include "sortvector.h"
#include "sorteermethode.h"

using namespace std;

int main(int argc, char *argv[])
{
    ShellShellSort <int> sss;
    ShellSort <int>ss;
    STLSort <int>stl;
    
    ofstream uitvoer;
    uitvoer.open("test.csv");
    Sorteermethode<int>::vergelijk(1,100,Stijgend,uitvoer, &sss,&ss,&stl);
    uitvoer.close();
    return 0;
}
