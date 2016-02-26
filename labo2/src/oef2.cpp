#include <iostream>
#include "sortvector.h"
#include "sorteermethode.h"
#include "chrono.h"
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(0));
    Sortvector<int> temp(10);
    temp.shuffle();
    
    //Start het hele sorteer-circus
    Chrono chr;

    cout<<"Insertion sort"<<endl;
    vector<int> vec1 = temp;
    InsertionSort<int> ins_sort;
    chr.start();
    ins_sort(vec1);
    chr.stop();
    cout<<"Insertion sort duurde "<<chr.tijd()<<"."<<endl;
    
    cout<<"STL sort"<<endl;
    vec1 = temp;
    STLSort<int> stl_sort;
    chr.start();
    stl_sort(vec1);
    chr.stop();
    cout<<"Insertion sort duurde "<<chr.tijd()<<"."<<endl;

    return 0;
}

