#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <cstdlib>
using std::cout;
using std::endl;
using std::vector;
using std::string;
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.cpp"
#include "tinyxml/tinyxml.cpp"
#include "tinyxml/tinyxmlparser.cpp"
#include "tinyxml/tinyxmlerror.cpp"

struct Bakker{
    string adres;
    string naam;
    string dorp;
};

void schrijf(vector<struct Bakker> bakkers){
    for(struct Bakker bakker:bakkers){
        cout<<bakker.naam<<" in "<<bakker.adres<<" in de gemeente/stad "<<bakker.dorp<<"\n";
    }
}

void leesXML(const char * bestand){
    TiXmlDocument doc(bestand);
    vector<struct Bakker> bakkers;

    bool ok = doc.LoadFile();
    if(ok){
        TiXmlElement *root, *dorp, *straat, *winkel;

        root = doc.FirstChildElement("dorpdata");
        //Dorpen
        dorp = root->FirstChildElement("dorp");
        while(dorp){
            string dorpnaam = dorp->FirstChildElement("naam")->GetText();
                //cout<<"dorp " <<dorpnaam<<endl;
            //Straten
            straat = dorp->FirstChildElement("straat");
            while(straat){
                string straatnaam = straat->FirstChildElement("naam")->GetText();
                    //cout<<"straat " <<straatnaam<<endl;
                //Winkels
                winkel = straat->FirstChildElement("winkel");
                while(winkel){
                    string winkelnaam = winkel->FirstChildElement("naam")->GetText();
                    string soort = winkel->FirstChildElement("soort")->GetText();
                    //Check dat het een bakker is
                        //cout<<"winkel (" <<winkelnaam<<","<<soort<<")"<<endl;
                    if(soort=="bakker"){
                        struct Bakker bakker = { straatnaam, winkelnaam, dorpnaam};
                        bakkers.push_back(bakker);
                    }
                    winkel = winkel->NextSiblingElement("winkel");
                }
                straat =straat->NextSiblingElement("straat");
            }
            dorp = dorp->NextSiblingElement("dorp");
        }
        schrijf(bakkers);
    }
    else{
        throw "Fout bij het openen van het bestand";
    }
}

int main(int argc, char *argv[])
{
    leesXML("dorp.xml");
    return 0;
}
