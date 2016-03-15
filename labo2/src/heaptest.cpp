#include <iostream>
#include "heap.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> v = {0,1,5,7,89,4,589,75,7,8,578,57,58,65,45};
    Heap<int> heap(v,v.size()-1);
    cout<<heap;
    return 0;
}
