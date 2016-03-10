#include <iostream>
#include <vector>
#include "sorteermethode.h"
#include "sortvector.h"
#include "chrono.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Shellsort"<<endl<<"---------------------"<<endl;
    ShellSort<int> ss;
    ss.meet(10,100000,cout);
    
    cout<<"ShellShellSort sort"<<endl<<"---------------------"<<endl;
    ShellShellSort<int> sss;
    sss.meet(10,100000,cout);
    return 0;
}
