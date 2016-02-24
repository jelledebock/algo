#include <iostream>
#include "sortvector.h"
#include "sorteermethode.h"
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(0));
    Sortvector<int> vec1(10);
    vec1.vul_range();
    cout<<"Gevuld met een range: \t"<<vec1;    
    cout<<"Gesorteerd (Y/N)? \t"<<(vec1.is_gesorteerd()?"Y":"N")<<endl;
    cout<<"Range (Y/N)? \t"<<(vec1.is_range()?"Y":"N")<<endl;
    vec1.shuffle();
    cout<<"Geshuffelde vector 1: \t"<<vec1;    
    cout<<"Gesorteerd (Y/N)? \t"<<(vec1.is_gesorteerd()?"Y":"N")<<endl;
    cout<<"Range (Y/N)? \t"<<(vec1.is_range()?"Y":"N")<<endl;

    Sortvector<int> vec2(20);
    vec2.vul_random();
    cout<<"Gevuld met random: \t"<<vec2;    
    cout<<"Gesorteerd (Y/N)? \t"<<(vec2.is_gesorteerd()?"Y":"N")<<endl;
    cout<<"Range (Y/N)? \t"<<(vec2.is_range()?"Y":"N")<<endl;

    Sortvector<int> vec3(15);
    vec3.vul_random_zonder_dubbels();
    cout<<"Gevuld met random zonder dubbels: \t"<<vec3;
    cout<<"Gesorteerd (Y/N)? \t"<<(vec3.is_gesorteerd()?"Y":"N")<<endl;
    cout<<"Range (Y/N)? \t"<<(vec3.is_range()?"Y":"N")<<endl;

    Sortvector<int> vec4(15);
    vec4.vul_omgekeerd();
    cout<<"Gevuld in omgekeerde volgorde: \t"<<vec4;
    cout<<"Gesorteerd (Y/N)? \t"<<(vec4.is_gesorteerd()?"Y":"N")<<endl;
    cout<<"Range (Y/N)? \t"<<(vec4.is_range()?"Y":"N")<<endl;
   
    return 0;
}

