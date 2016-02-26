#include <iostream>
#include <vector>
#include "sortvector.h"
#include "sorteermethode.h"
#include "chrono.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Insertion sort"<<endl<<"---------------------"<<endl;
    InsertionSort<int> sm;
    sm.meet(10,10000000,cout);

    cout<<"STL sort"<<endl<<"---------------------"<<endl;
    STLSort<int> stl;
    stl.meet(10,10000000,cout);
    return 0;
}
