#ifndef __SORTEERMETHODE
#define __SORTEERMETHODE
#include <iostream>
using std::endl;
using std::cout;
using std::move;
using std::vector;
using std::ofstream;
using std::string;
#include <algorithm>   // voor sort()-methode uit STL
#include "chrono.h"
#include "sortvector.h"
#include <iomanip>
#include <fstream>

enum Ordening {Random,Stijgend,Dalend};
template <typename T>
class Sorteermethode{
    public:
        virtual void operator()(vector<T> & v) const = 0;

        // Deze externe procedure schrijft naar os een overzicht (met de nodige ornamenten) 
        // met de snelheid van de opgegeven sorteermethode *this. Er wordt 1 lijn uitgedrukt voor elke mogelijke
        // grootte. Deze groottes zijn kleinste, 10*kleinste, 100*kleinste,
        // enzovoorts, tot aan grootste.
        // Op een lijn staat de snelheid van de methode toegepast op
        // (1) een random tabel
        // (2) een al gesorteerde tabel.
        // (3) een omgekeerd gesorteerde tabel.

        // Deze functie werkt alleen als T een toekenning van een int toelaat,
        // zodat bv.
        //    T a=5;
        // geldig is.
        void meet(int kortste, int langste, ostream& os);
        static void vergelijk(int, int, Ordening,ostream&);
        template<class S, class... _args>
        static void vergelijk(int, int, Ordening, ostream&, S , _args ...);


};

    template <typename T>
void Sorteermethode<T>::vergelijk(int min, int max, Ordening sorteer_volgorde, ostream& out)
{

}
    template <typename T> template<class S, class... _args> 
void Sorteermethode<T>::vergelijk(int min, int max, Ordening sorteer_volgorde, ostream& out, S eerste, _args ... andere)
{
    out<<typeid(*eerste).name()<<",";
    for(int i = min; i<=max; i+=10)
    {
        Sortvector<T> sv(i);
        switch(sorteer_volgorde)
        {
            case Random:
                sv.vul_random();
                break;
            case Stijgend:
                sv.vul_range();
                break;
            case Dalend:
                sv.vul_omgekeerd();
                break;
        }
        Chrono cr;
        cr.start();
        eerste->operator()(sv);
        cr.stop();
        out<<cr.tijd()<<",";
    }
    out<<endl;
    Sorteermethode<T>::vergelijk(min,max,sorteer_volgorde,out,andere...);
}

    template <typename T>
void meet(int kortste, int langste, Sorteermethode<T> *sm, ostream& os)
{
    int size=kortste;
    double t_gesorteerd;
    double t_omgekeerd;
    double t_random;
    Sortvector<T> sv(0);
    os<<std::setw(12)<<"lengte"<<std::setw(12)<<"random"<<std::setw(12)<<"gesorteerd"<<std::setw(12)<<"omgekeerd"<<std::endl;
    while(size<langste)
    {
        sv.resize(size);
        //Gesorteerde volgorde
        sv.vul_range();
        //cout<<"[DEBUG] Range "<<sv;
        Chrono cr;
        cr.start();
        sm->operator()(sv);
        cr.stop();
        //cout<<"[DEBUG] Range sorted"<<sv;
        t_gesorteerd = cr.tijd();
        //Omgekeerde volgorde
        sv.draai_om();
        //cout<<"[DEBUG] Reversed "<<sv;
        cr.start();
        sm->operator()(sv);
        cr.stop();
        t_omgekeerd = cr.tijd();
        //cout<<"[DEBUG] Reversed sorted"<<sv;
        //Random volgorde
        sv.shuffle();
        //cout<<"[DEBUG] Shuffled "<<sv;
        cr.start();
        sm->operator()(sv);
        cr.stop();
        t_random = cr.tijd();
        //cout<<"[DEBUG] Shuffled Sorted"<<sv;
        size*=10;
        os<<std::setw(12)<<size<<std::setw(12)<<t_random<<std::setw(12)<<t_gesorteerd<<std::setw(12)<<t_omgekeerd<<std::endl;
    }
}
/*
 *   STANDARD TEMPLATE LIBRARY SORT
 */
template <typename T>
class STLSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;
        void meet(int,int,ostream&);
};

template <typename T>
void STLSort<T>::operator()(vector<T> & v) const{
    sort(v.begin(),v.end());
}

/*
 *   INSERTION SORT
 */
template <typename T>
class InsertionSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;   
        //void meet(int,int,ostream&);
};

template <typename T>
void InsertionSort<T>::operator()(vector<T> & v) const{
    for(int i=1; i<v.size(); i++){
        T h;
        h=move(v[i]);
        int j=i-1;
        while(j>=0 && h<v[j]){
            v[j+1] = move(v[j]);
            j--;
        }
        v[j+1] = move(h);
    }
}

/*
 *   SHELLSORT
 */

template <typename T>
class ShellBase : public Sorteermethode<T>{
    public:
        mutable vector<int> breedtes;
        void operator()(vector<T> & v) const;
        void meet(int,int,ostream&);
        void set_breedtes(vector<int> &v) const
        {
            breedtes = std::move(v);
        }
        void print_breedtes() const
        {
            cout<<"Breedtes : ";
            for(int breedte : breedtes)
                cout<<breedte<<"\t";
            cout<<endl;
        }
};

template <typename T>
void ShellBase<T>::operator()(vector<T> & v) const
{
    for(int breedte : this->breedtes)
    {
        for(int i = breedte; i<v.size();i++)
        {
            T tmp = move(v[i]);
            int j = i-breedte;
            while(j>=0 && tmp< v[j])
            {
                v[j+breedte]=move(v[j]);
                j-=breedte;
            }
            v[j+breedte]=tmp; 
        }
    }

}

template <typename T>
class ShellSort : public ShellBase<T>
{
    public:
        ShellSort()
        {
            vector<int> tmp = {9427969,4188161,2354689,1045505,587521,260609,64769,146305,36289,16001,8929,3905,2161,929,505,209,109,41,19,5,1};
            ShellBase<T>::set_breedtes(tmp);
        }
};

template <typename T>
class ShellShellSort : public ShellBase<T>
{
    public:
        ShellShellSort()
        {
            ShellBase<T>::breedtes = {};
        }
        void operator()(vector<T> & v) const;
        void bereken_reeks(vector<T> &v) const;
};

template <typename T>
void ShellShellSort<T>::operator()(vector<T> & v) const 
{
    bereken_reeks(v);
    ShellBase<T>::operator()(v);
}

template <typename T>
void ShellShellSort<T>::bereken_reeks(vector<T> &v) const
{
    vector<int> tmp = {};
    int i=v.size()/2;

    while(i!=0)
    {
        tmp.push_back(i);
        i/=2;
    }
    ShellBase<T>::set_breedtes(tmp);
}

    template <typename T>
void ShellBase<T>::meet(int kortste, int langste, ostream& os)
{
    ::meet(kortste,langste,this,os);
}

    template <typename T>
void Sorteermethode<T>::meet(int kortste, int langste, ostream& os)
{
    ::meet(kortste,langste,this,os);    
}

    template <typename T>
void STLSort<T>::meet(int kortste, int langste, ostream& os)
{
    ::meet(kortste,langste,this,os);    
}
#endif 
