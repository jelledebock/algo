#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int maxgrootte = 20;
    int even_getal=1;
    int even_i_2=1;
    int even_i=1;
    int oneven_ip1_2=1;
    int oneven = 1;
    int i = 0;
    cout<<"1"<<",";
    while(i<maxgrootte)
    {
        even_i_2*=2;
        if(i%2)
        {
            even_i*=2;
            cout<<1+(9*even_i_2-9*even_i)<<",";
        }
        else
        {
            oneven_ip1_2*=2;
            cout<<1+8*even_i_2-6*oneven_ip1_2<<",";
        }
        i++;
    }
    cout<<endl;
    return 0;
}
