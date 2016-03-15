#ifndef __HEAP_H
#define __HEAP_H
#include <vector>
#include <iostream>

using std::ostream;
using std::vector;

//Heap: wortel is grootste element
template<class T>
class Heap{
    public:
        /*    
              De constructor krijgt de tabel mee (die er al is)
              en het aantal effectief ingenomen plaatsen, dat niet groter is dan de grootte van de vector
              Hij vormt de vector ter plaatse om tot een heap.
              De Heap is een maxheap: de grootste waarde zit in de wortel
              Voor heapsort zou het effici"ent zijn een functie verwijderWortelEnVerplaatsHemNaarDeVrijgekomenPlaats()
              te hebben.
              */
        Heap(std::vector<T>& _v,int _aantal);
        //geefwortel laat de wortel zitten!
        const T* geefWortel() const;
        void verwijderWortel();
        void vervangWortel(const T&);
        friend ostream& operator<<(ostream& os, const Heap<T>& s){
            s.schrijf(os);
            return os;
        }
    private:
        //volgende velden dienen om een uniforme naamgeving te krijgen
        std::vector<T>& v;
        int aantal;     //aantal elementen van de heap
        void add_element(T);
        void bubble_up();
        void bubble_down(int);
        void fix_heap();
        int biggest_child(int);
        void remove_max_from_heap();
        void schrijf(ostream& os) const;
};

template<class T>
Heap<T>::Heap(std::vector<T>& _v, int _aantal): v(_v)
{
    aantal = _v.size();
    fix_heap();
    for(int i=0;i<_aantal;i++)
    {
        remove_max_from_heap();
    }
}

template<class T>
const T* Heap<T>::geefWortel() const
{
    return &v[1];
}

template<class T>
void Heap<T>::remove_max_from_heap()
{
    T tmp = std::move(v[1]);
    v[aantal]=std::move(tmp);
    aantal--;
    bubble_down(1);
}

template<class T>
int Heap<T>::biggest_child(int parent_pos)
{
    int child = parent_pos * 2;

    if(v[child]<aantal)
        if(v[child]<v[child+1])
            child++;

    return child;
}

template<class T>
void Heap<T>::bubble_down(int pos)
{
    if(!(2*pos > aantal))
    {
        T tmp = std::move(v[pos]);
        int max_pos = biggest_child(pos);
        
        bool ok = true;

        while(ok && v[max_pos]>tmp)
        {
            v[pos] = std::move(v[max_pos]);
            pos = max_pos;
            if(2*pos <= aantal)
                max_pos = biggest_child(pos);
            else
                ok =false;
        }
        v[pos] = std::move(tmp);
    }
}

template<class T>
void Heap<T>::fix_heap()
{
    for(int i=aantal/2;i>0;i--)
        bubble_down(i);
}
template<class T>
void Heap<T>::add_element(T val)
{
    //Add an extra node
    aantal++;
    v[aantal] = val;
    Heap<T>::bubble_up();
}

template<class T>
void Heap<T>::bubble_up()
{
    int i = aantal;
    T tmp = std::move(v[i]);

    while(v[i]>v[(int)i/2])
    {
        v[i]=std::move(v[(int)i/2]);
        i /= 2;
    }
    v[i] = std::move(tmp);
}

template<class T>
void Heap<T>::schrijf(ostream& os) const
{
    for(int i = aantal+1 ; i<v.size() ; i++)
        os<<v[i]<<"\t"<<std::endl;
}
#endif

