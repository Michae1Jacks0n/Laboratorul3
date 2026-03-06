#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Bilet {
protected:
    string numar;
    string oraStart;
    string oraSfarsit;

public:
    Bilet(string numar, string oraStart, string oraSfarsit) {
        this->numar = numar;
        this->oraStart = oraStart;
        this->oraSfarsit = oraSfarsit;
    }

    int calculeazaDurata() {
        int hStart, mStart, hSfarsit, mSfarsit;
        char sep;

        stringstream ss1(oraStart);
        ss1 >> hStart >> sep >> mStart;

        stringstream ss2(oraSfarsit);
        ss2 >> hSfarsit >> sep >> mSfarsit;

        int startTotal = hStart * 60 + mStart;
        int sfarsitTotal = hSfarsit * 60 + mSfarsit;

        return sfarsitTotal - startTotal;
    }

    virtual double calculeazaCost() = 0;

    virtual string getTip() = 0;

    string getNumar() {
        return numar;
    }

    virtual ~Bilet() {}
};

class BiletStandard : public Bilet {
private:
    double costPeOra = 2.0;

public:
    BiletStandard(string numar, string oraStart, string oraSfarsit) : Bilet(numar, oraStart, oraSfarsit) {}

    double calculeazaCost() {
        double durataPeOre = calculeazaDurata() / 60.0;
        return durataPeOre * costPeOra;
    }

    string getTip() {
        return "Bilet Standard";
    }
};

class Abonament : public Bilet {
private:
    double costAbonament = 50.0;

public:
    Abonament(string numar, string oraStart, string oraSfarsit) : Bilet(numar, oraStart, oraSfarsit) {}

    double calculeazaCost() {
        return costAbonament;
    }

    string getTip() {
        return "Abonament";
    }
};

class BiletReducere : public Bilet {
private:
    double costPeOra = 1.0;

public:
    BiletReducere(string numar, string oraStart, string oraSfarsit) : Bilet(numar, oraStart, oraSfarsit) {}

    double calculeazaCost() {
        double durataPeOre = calculeazaDurata() / 60.0;
        return durataPeOre * costPeOra;
    }

    string getTip() {
        return "Bilet Reducere";
    }
};

class BiletTuristic : public Bilet {
private:
    double costPeZi = 10.0;

public:
    BiletTuristic(string numar, string oraStart, string oraSfarsit) : Bilet(numar, oraStart, oraSfarsit) {}

    double calculeazaCost() {
        return costPeZi;
    }

    string getTip() {
        return "Bilet Turistic";
    }
};

int main() {
    vector<Bilet*> bilete;
    string tip, numar, oraStart, oraSfarsit;
    
    ifstream fisier("bilete.txt");
    if (!fisier.is_open()) {
        cout <<"Eroare: nu s-a putut deschide fisierul bilete.txt";
        return 0;
    }
    
    while (fisier >> tip >> numar >> oraStart >> oraSfarsit) {
        if (tip == "BiletStandard") {
            bilete.push_back(new BiletStandard(numar, oraStart, oraSfarsit));
        } else if (tip == "Abonament") {
            bilete.push_back(new Abonament(numar, oraStart, oraSfarsit));
        } else if (tip == "BiletReducere") {
            bilete.push_back(new BiletReducere(numar, oraStart, oraSfarsit));
        } else if (tip == "BiletTuristic") {
            bilete.push_back(new BiletTuristic(numar, oraStart, oraSfarsit));
        }
    }

    fisier.close();

    for (int i = 0; i < bilete.size(); i++) {
        cout <<"Tip: "<< bilete[i]->getTip() <<endl;
        cout <<"Numar: "<< bilete[i]->getNumar() <<endl;
        cout <<"Durata: "<< bilete[i]->calculeazaDurata() <<" minute "<<endl;
        cout <<"Cost: "<< bilete[i]->calculeazaCost() <<" lei "<<endl;
        cout << endl;
    }

    for (int i = 0; i < bilete.size(); i++) {
        delete bilete[i];
    }

    return 0;
}
