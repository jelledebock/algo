#ifndef __SORTEERMETHODE
#define __SORTEERMETHODE
#include <iostream>
    using std::endl;
    using std::cout;
    using std::move;
    using std::vector;
#include <algorithm>   // voor sort()-methode uit STL
#include "chrono.h"
#include "sortvector.h"
#include <iomanip>

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



};

template <typename T>
void meet(int kortste, int langste, Sorteermethode<T>& sm, ostream& os)
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
        sm(sv);
        cr.stop();
        t_gesorteerd = cr.tijd();
        //Omgekeerde volgorde
        sv.draai_om();
        //cout<<"[DEBUG] Reversed "<<sv;
        cr.start();
        sm(sv);
        cr.stop();
        t_omgekeerd = cr.tijd();
        //Random volgorde
        sv.shuffle();
        //cout<<"[DEBUG] Shuffled "<<sv;
        cr.start();
        sm(sv);
        cr.stop();
        t_random = cr.tijd();
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
class ShellSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;
};

template <typename T>
void ShellSort<T>::operator()(vector<T> & v) const
{
    vector<int> breedtes({9427969,4188161,2354689,1045505,587521,260609,64769,146305,36289,16001,8929,3905,2161,929,505,209,109,41,19,5,1});
    for(int breedte : breedtes)
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
void Sorteermethode<T>::meet(int kortste, int langste, ostream& os)
{
    ::meet(kortste,langste,*this,os);    
}

template <typename T>
void STLSort<T>::meet(int kortste, int langste, ostream& os)
{
    ::meet(kortste,langste,*this,os);    
}
#endif 
