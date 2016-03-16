#include <iostream>
#include "heap.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> v = {1,5,7,89,4,589,75,8,578,7,4,57,58,65,45};
    Heap<int> heap(v,v.size());
    cout<<heap;
    return 0;
}
