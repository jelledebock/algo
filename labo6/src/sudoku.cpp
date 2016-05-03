#include "backtrackflex.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Sudoku : public vector<vector<int>>{
    public:
        Sudoku(string);
        friend ostream& operator<<(ostream &, Sudoku&);
        void geefLeegVakje(int &, int &);
};

Sudoku::Sudoku(string bestand_naam){
    string line;
    ifstream sudoku_bestand(bestand_naam);
    int i=0,j=0;
    string number;

    this->resize(9);
    for(i=0;i<9;i++)
    {
        this->operator[](i).resize(9);
    }

    if(sudoku_bestand.is_open()){
        i=0;
        while(getline(sudoku_bestand, line) && line.size()>1){
            istringstream ss(line);
            //cout<<"LINE DEBUG:"<<line.size()<<endl;
            j=0;
            while(std::getline(ss,number,'\t') && !number.empty()){
                //cout<<"CELL DEBUG:"<<number<<endl;
                this->operator[](i).operator[](j) = atoi(number.c_str());
                j++;
            }
            i++;
        }
    }
}

void Sudoku::geefLeegVakje(int & rij, int & kolom){
   bool stop=false;
   while(rij<9 && !stop){
        while(kolom<9 && !stop){
            if(this->operator[](rij).operator[](kolom)==0){
                stop = true;
            }
            else{
                kolom++;
            }
        }
        kolom = 0;
        rij++;
   }
   rij--;
   if(!stop){
        rij = -1;
        kolom = -1;
   }
}

ostream& operator<<(ostream& out, Sudoku& sudoku){
    out<<"  0\t1\t2\t\t3\t4\t5\t\t6\t7\t8"<<endl;
    out<<" ========================================================================================="<<endl;
    for(int i=0; i<sudoku.size(); i++){
        if(i!=0 && i%3==0)
            out<<"-----------------------------------------------------------------------------------------"<<endl;
        out<<i<<"|";
        for(int j=0; j<sudoku[i].size();j++){
            if(j!=0 && j%3==0)
                out<<"|\t";
            out<<sudoku[i][j]<<"\t";
        }
        out<<"|";
        out<<endl<<endl;
    }
    out<<" ========================================================================================="<<endl;
    return out;
}

int main(int argc, char ** argv){
    Sudoku sudoko("sudoku.txt");
    int rij=4,kolom=5;
    sudoko.geefLeegVakje(rij,kolom);
    cout<<sudoko;
    cout<<"Eerste leeg vakje op: ["<<rij<<","<<kolom<<"]."<<endl;
}
