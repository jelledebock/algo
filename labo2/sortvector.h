#ifndef __SORTVECTOR
#define __SORTVECTOR

//sortvector is een klasse van sorteerbare vectoren
//Bovenop de vectoreigenschappen zijn er hulpfuncties om sorteervergelijkingen
//te vergemakkelijken.
#include <iostream>
using std::istream;
using std::ostream;
#include <iomanip>   // voor setw
#include <cstdlib>   // voor rand - opletten!! 
#include <vector>
#include <set>
using std::vector;

template<class T>
class Sortvector:public vector<T>{
    public:

        // Constructor: het argument geeft de grootte aan
        // bij constructie zal de tabel opgevuld worden met 
        // n verschillende getallen in random volgorde
        // (zie hulplidfuncties)
        Sortvector(int);

        Sortvector(const Sortvector<T>& v) = delete;
        Sortvector<T>& operator=(const Sortvector<T>& v) = delete;
        Sortvector<T>& operator=(Sortvector<T>&& v) = delete;
        Sortvector(Sortvector<T>&& v) = delete;

        ///vul vector met de waarden T(0)...T(size()-1) in volgorde
        void vul_range();
        void draai_om();
        void vul_omgekeerd();
        void shuffle();
        void vul_random_zonder_dubbels();
        void vul_random(); // nog niet implementeren

        bool is_gesorteerd() const;
        bool is_range() const;

        friend ostream& operator<<(ostream& os, const Sortvector<T>& s){
            s.schrijf(os);
            return os;
        }

    private: 
        void schrijf(ostream & os)const;

};

template<class T>
Sortvector<T>::Sortvector(int size)
{
    vector<T>::resize(size);
}
    template <class T>
void Sortvector<T>::vul_range()
{
    //std::cout<<"[DEBUG] Vector size "<<vector<T>::size()<<std::endl;
    for(int i=0;i<vector<T>::size();i++)
    {
        //std::cout<<"[DEBUG] Trying to fill with "<<T(i)<<std::endl;
        vector<T>::operator[](i)=T(i);
    }
}

    template <class T>
void Sortvector<T>::draai_om()
{
    int s = vector<T>::size();
    int l=0;
    int r=vector<T>::size()-1;
    T temp;
    while(l<=r)
    {
        temp = vector<T>::operator[](l);
        vector<T>::operator[](l) = vector<T>::operator[](r);
        vector<T>::operator[](r) = temp;
        l++;
        r--;
    }
}

    template <class T>
void Sortvector<T>::vul_omgekeerd()
{
    for(int i=vector<T>::size()-1;i>=0;i--)
    {
        vector<T>::operator[]((vector<T>::size()-1)-i)=T(i);
    }
}

    template <class T>
void Sortvector<T>::shuffle()
{
    auto currentIndexCounter = vector<T>::size();

    for (auto iter = vector<T>::rbegin(); iter != vector<T>::rend();
            iter++, --currentIndexCounter)
    {
        int randomIndex = std::rand() % currentIndexCounter;

        if (*iter != vector<T>::at(randomIndex))
        {
            std::swap(vector<T>::at(randomIndex), *iter);
        }
    }

}

    template <class T>
void Sortvector<T>::vul_random_zonder_dubbels()
{
    std::set<T> dubbels;
    for(int i=0;i<vector<T>::size();i++)
    {
        T random = T(std::rand()%vector<T>::size());
        while(dubbels.count(random)>0)
        {
            random = T(std::rand()%vector<T>::size());
            //std::cout<<"[DEBUG] Er werd een duplicaat random gegenereerd!"<<std::endl;
        }
        dubbels.insert(random);
        vector<T>::operator[](i)=random;
    }
}


    template <class T>
void Sortvector<T>::vul_random()
{
    for(int i=0;i<vector<T>::size();i++)
    {
        vector<T>::operator[](i)=std::rand()%vector<T>::size();
    }
}

template <class T>
bool Sortvector<T>::is_gesorteerd() const
{
    int i=1;
    while(vector<T>::operator[](i-1)<=vector<T>::operator[](i) && i<vector<T>::size())
    {
        i++;
    }
    if(vector<T>::operator[](i-1)>vector<T>::operator[](i))
        return false;
    return true;

}

template <class T>
bool Sortvector<T>::is_range() const
{
    int i=1;
    while(i<vector<T>::size() && std::abs(vector<T>::operator[](i) - vector<T>::operator[](i-1))==T(1))
    {
        i++;
    }
    //Je springt "buiten" de vector wanneer je eigenlijk tot het einde gaat want dan voldoet i niet meer aan de conditie in de while voorwaarde
    //std::cout<<"[DEBUG] i="<<i<<"[i-1]+1 = "<<vector<T>::operator[](i-1)+1<<"[i]= "<<vector<T>::operator[](i)<<std::endl;
    if( std::abs(vector<T>::operator[](i-1) - vector<T>::operator[](i-2))==T(1)&& i == vector<T>::size())
        return true;
    return false;
}

template <class T>
void Sortvector<T>::schrijf(ostream & os)const{
    for(auto&& t : *this){
        os<<t<<" ";
    }
    os<<"\n";
}



#endif
