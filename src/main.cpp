#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <fstream>
#include <iomanip>
#define STOC_FIS "stoc.txt"
#define COS_FIS "cos.txt"

using namespace std;

class Produs{
private:
    int id;
    string nume;
    int cantitate;
    double pret;
public:
    Produs(int idVal = 0, string numeVal = "", int cantitateVal = 0, double pretVal = 0.0);
    Produs(int idVal, string numeVal, int cantitateVal);
    int getId();
    string getNume();
    int getCantitate();
    void setCantitate(int _cantitate);
    double getPret();

    friend std::ostream &operator<<(std::ostream &out, const Produs &p);
    friend std::istream &operator>>(std::istream &in, Produs &p);
};

Produs::Produs(int idVal, string numeVal, int cantitateVal, double pretVal)
    : id{idVal}, nume{numeVal}, cantitate{cantitateVal}, pret{pretVal}{
}

Produs::Produs(int idVal, string numeVal, int cantitateVal){
    Produs(idVal, numeVal, cantitateVal, 0);
}

int Produs::getId(){
    return id;
}

string Produs::getNume(){
    return nume;
}

int Produs::getCantitate(){
    return cantitate;
}

void Produs::setCantitate(int _cantitate){
    cantitate = _cantitate;
}

double Produs::getPret(){
    return pret;
}

std::ostream &operator<<(std::ostream &out, const Produs &p){
    out << p.id << "\t\t\t" << p.nume << "\t\t\t" << p.cantitate << "\t\t\t" << p.pret;
    return out;
}

std::istream &operator>>(std::istream &in, Produs &p){
    in >> p.id >> p.nume >> p.cantitate >> p.pret;
    return in;
}

//=====================================================================clasa stoc==========================================================================

class Stoc{
private:
    vector <Produs> vectorProduse;
public:
    int existaProdus(int id);
    void adaugareProdus(Produs& p);
    void scadDinStoc(int id, int cant);
    void afisareProduse();
    friend std::ostream &operator<<(std::ostream &out, const Stoc &s);
    void citireFisier();
    void salvareFisier();
};

int Stoc::existaProdus(int id){
    for(int i = 0; i < vectorProduse.size(); i++){
        if(vectorProduse[i].getId() == id){
            return i;
        }
    }
    return -1;
}

void Stoc::adaugareProdus(Produs &p){
    int i = this->existaProdus(p.getId());
    if(i != -1){
        vectorProduse[i].setCantitate(vectorProduse[i].getCantitate() + p.getCantitate());
    }
    else{
        vectorProduse.push_back(p);
    }
}

void Stoc::scadDinStoc(int id, int cant){
    int i = existaProdus(id);
    if(i != -1){
        if(cant <= vectorProduse[i].getCantitate()){
            vectorProduse[i].setCantitate(vectorProduse[i].getCantitate() - cant);
        }
        else{
            cout << "Cantitate insuficienta!" << endl;
        }
    }
    else{
        cout << "Produsul nu exista in stoc!" << endl;
    }
}

std::ostream &operator<<(std::ostream &out, const Stoc &s){
    for(int i = 0; i < s.vectorProduse.size(); i++){
        out << s.vectorProduse[i] << endl;
    }
    return out;
}

void Stoc::citireFisier(){
    ifstream f(STOC_FIS);
    int n;
    f >> n;
    for(int i = 0; i < n; i++){
        Produs p = Produs();
        f >> p;
        adaugareProdus(p);
    }
    f.close();
}

void Stoc::salvareFisier(){
    ofstream f(STOC_FIS);
    f << this->vectorProduse.size() << endl;
    f << *this;
    f.close();
}

//===================================================================clasa cos=============================================================================

class CosCumparaturi{
private:
    vector <Produs> vectorProduse;
public:
    int existaProdus(int id);
    void adaugareProdus(Produs& p);
    friend std::ostream &operator<<(std::ostream &out, const CosCumparaturi &c);
    void stergereProdus(int id, int cant);
    void citireFisier();
    void salvareFisier();
    double getPretTotal();
};

int CosCumparaturi::existaProdus(int id){
    for(int i = 0; i < vectorProduse.size(); i++){
        if(vectorProduse[i].getId() == id){
            return i;
        }
    }
    return -1;
}

void CosCumparaturi::adaugareProdus(Produs& p){
    int i = this->existaProdus(p.getId());
    if(i != -1){
       vectorProduse[i].setCantitate(vectorProduse[i].getCantitate() + p.getCantitate());
    }
    else{
        vectorProduse.push_back(p);
    }
}

void CosCumparaturi::stergereProdus(int id, int cant){
    int i = existaProdus(id);
    if(i != -1){
        if(cant <= vectorProduse[i].getCantitate()){
            vectorProduse[i].setCantitate(vectorProduse[i].getCantitate() - cant);
        }
    }
}

std::ostream &operator<<(std::ostream &out, const CosCumparaturi &c){
    for(int i = 0; i < c.vectorProduse.size(); i++){
        out << c.vectorProduse[i] << endl;
    }
    out << endl;
    return out;
}

void CosCumparaturi::citireFisier(){
    ifstream f(COS_FIS);
    int n;
    f >> n;
    vectorProduse.clear();
    for(int i = 0; i < n; i++){
        Produs p = Produs();
        f >> p;
        adaugareProdus(p);
    }
    f.close();
}

void CosCumparaturi::salvareFisier(){
    ofstream f(COS_FIS);
    f << this->vectorProduse.size() << endl;
    f << *this;
    f.close();
}

double CosCumparaturi::getPretTotal(){
    double pretTotal = 0;
    for(int i = 0; i < vectorProduse.size(); i++) {
        pretTotal += vectorProduse[i].getPret() * vectorProduse[i].getCantitate();
    }
    return pretTotal;
}

//=========================================================================================================================================================

void setConsoleTextColor(int color){
    HANDLE stdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    if(stdOutput != INVALID_HANDLE_VALUE)
        SetConsoleTextAttribute(stdOutput, color);
}

void meniu(){
    setConsoleTextColor(13);
    cout << setw(65) << "Bun venit!" << endl << endl;
    setConsoleTextColor(7);
    cout << setw(70) << "Alegeti o optiune!" << endl;
    cout << setw(64) << "1. Admin" << endl;
    cout << setw(65) << "2. Client" << endl;
    cout << setw(65) << "3. Iesire" << endl;
    cout << setw(70) << "Optiunea aleasa: ";
}

void meniuAdmin(){
    setConsoleTextColor(13);
    cout << setw(60) << "ADMIN" << endl << endl;
    setConsoleTextColor(7);
    cout << setw(65) << "Alegeti o optiune:" << endl;
    cout << setw(81) << "1. Vizualizare produse in stoc" << endl;
    cout << setw(78) << "2. Adaugare produse in stoc" << endl;
    cout << setw(79) << "3. Stergere produse din stoc" << endl;
    cout << setw(60) << "4. Iesire" << endl;
    cout << setw(65) << "Optiunea aleasa: ";
}

void meniuClient(){
    setConsoleTextColor(13);
    cout << setw(60) << "CLIENT" << endl << endl;
    setConsoleTextColor(7);
    cout << setw(65) << "Alegeti o optiune:" << endl;
    cout << setw(81) << "1. Vizualizare produse in stoc" << endl;
    cout << setw(81) << "2. Vizualizare cos cumparaturi" << endl;
    cout << setw(75) << "3. Adauga produse in cos" << endl;
    cout << setw(76) << "4. Sterge produse din cos" << endl;
    cout << setw(60) << "5. Iesire" << endl;
    cout << setw(65) << "Optiunea aleasa: ";
}

void exitProgram(Stoc s, CosCumparaturi c){
    s.salvareFisier();
    c.salvareFisier();
    exit(0);
}

//============================================================================main=========================================================================

int main(){
    Stoc stoc = Stoc();
    CosCumparaturi cos = CosCumparaturi();

    stoc.citireFisier();
    cos.citireFisier();

    int optiune;
    meniu();
    cin >> optiune;

    while(1){
        switch(optiune){
        case 1:
            system("cls");
            int optiuneA1;
            meniuAdmin();
            cin >> optiuneA1;

            if(optiuneA1 == 1){
                system("cls");
                int optiuneA11;

                cout << "ID:\t\t\tNume:\t\t\tCantitate:\t\tPret:" << endl;
                cout << stoc << endl;
                cout << "Pentru a reveni la meniul principal apasati '1': ";
                cin >> optiuneA11;

                if(optiuneA11 == 1){
                    system("cls");
                    meniuAdmin();
                }
                else{
                    cout << "Se revine la meniul principal" << endl;
                    Sleep(3000);
                    system("cls");
                    meniuAdmin();
                }
            }
            else if(optiuneA1 == 2){
                system("cls");

                cout << "Lista produse:" << endl;
                cout << "ID:\t\t\tNume:\t\t\tCantitate:\t\tPret:" << endl;
                cout << stoc;

                int optiuneA21;
                cout << "\nCate produse doriti sa adaugati? ";
                cin >> optiuneA21;

                cout << "Produse adaugate:" << endl;
                for(int i = 0; i < optiuneA21; i++){
                    Produs p = Produs();
                    cin >> p;
                    stoc.adaugareProdus(p);
                }

                cout << "\nSe revine la meniul principal" << endl;
                Sleep(3000);
                system("cls");
                meniuAdmin();
            }
            else if(optiuneA1 == 3){
                system("cls");
                int optiuneA31;

                cout << "Produse in stoc:" << endl;
                cout << "ID:\t\t\tNume:\t\t\tCantitate:\t\tPret:" << endl;
                cout << stoc << endl;
                cout << "\nCate produse doriti sa stergeti? ";
                cin >> optiuneA31;

                cout << "Produse sterse:" << endl;
                for(int i = 0; i < optiuneA31; i++){
                    Produs p = Produs();
                    cin >> p;
                    stoc.scadDinStoc(p.getId(), p.getCantitate());
                }

                cout << setw(75) << "\nSe revine la meniul principal" << endl;
                Sleep(3000);
                system("cls");
                meniuAdmin();
            }
            else if(optiuneA1 == 4){
                exitProgram(stoc, cos);
            }
            else{
                cout << setw(75) << "Optiune invalida, incercati din nou!" << endl;
                Sleep(3000);
                system("cls");
                meniuAdmin();
            }
            break;

        case 2:
            system("cls");
            int optiuneC1;
            meniuClient();
            cin >> optiuneC1;

            if(optiuneC1 == 1){
                system("cls");
                int optiuneC11;

                cout << "Lista produse:" << endl;
                cout << "ID:\t\t\tNume:\t\t\tCantitate:\t\tPret:" << endl;
                cout << stoc;

                cout << "\nPentru a reveni la meniul principal apasati '1': ";
                cin >> optiuneC11;

                if(optiuneC11 == 1){
                    system("cls");
                    meniuClient();
                }
                else{
                    cout << "Se revine la meniul principal" << endl;
                    Sleep(3000);
                    system("cls");
                    meniuClient();
                }
            }
            else if(optiuneC1 == 2){
                system("cls");
                int optiuneC12;
                cout << "Continut cos:" << endl;
                cout << "ID:\t\t\tNume:\t\t\tCantitate:\t\tPret:" << endl;
                cout << cos;

                double pretTotal = cos.getPretTotal();
                cout << "Pret total: " << pretTotal << " lei\n";

                cout << "\nPentru a reveni la meniul principal apasati '1': ";
                cin >> optiuneC12;

                if(optiuneC12 == 1){
                    system("cls");
                    meniuClient();
                }
                else{
                    cout << "Se revine la meniul principal" << endl;
                    Sleep(3000);
                    system("cls");
                    meniuClient();
                }
            }
            else if(optiuneC1 == 3){
                system("cls");
                int optiuneC13;
                int optiuneC133;

                cout << "Lista produse:" << endl;
                cout << "ID:\t\t\tNume:\t\t\tCantitate:\t\tPret:" << endl;
                cout << stoc;

                cout << "\nCate produse doriti sa adaugati? ";
                cin >> optiuneC13;

                cout << "Produse adaugate:" << endl;
                for(int i = 0; i < optiuneC13; i++){
                    Produs p = Produs();
                    cin >> p;
                    cos.adaugareProdus(p);
                    stoc.scadDinStoc(p.getId(), p.getCantitate());
                }

                cout << "\nPentru a reveni la meniul principal apasati '1': ";
                cin >> optiuneC133;

                if(optiuneC133 == 1){
                    system("cls");
                    meniuClient();
                }
                else{
                    cout << "Se revine la meniul principal" << endl;
                    Sleep(3000);
                    system("cls");
                    meniuClient();
                }
            }
            else if(optiuneC1 == 4){
                system("cls");
                int optiuneC14;

                cout << "Produse in cos:" << endl;
                cout << "ID:\t\t\tNume:\t\t\tCantitate:\t\tPret:" << endl;
                cout << cos;
                cout << "Cate produse doriti sa stergeti? ";
                cin >> optiuneC14;

                cout << "Produse sterse:" << endl;
                for(int i = 0; i < optiuneC14; i++){
                    Produs p = Produs();
                    cin >> p;
                    cos.stergereProdus(p.getId(), p.getCantitate());
                    stoc.adaugareProdus(p);
                }

                cout << "Se revine la meniul principal" << endl;
                Sleep(3000);
                system("cls");
                meniuClient();
            }
            else if(optiuneC1 == 5){
                exitProgram(stoc, cos);
            }
            else{
                cout << "Optiune invalida, incercati din nou!";
                Sleep(1000);
                system("cls");
                meniuClient();
            }
            break;

        case 3:
            exitProgram(stoc, cos);

        default:
            cout << endl;
            cout << setw(80) << "Optiune invalida, incercati din nou!";
            Sleep(2000);
            system("cls");
            meniu();
            cin >> optiune;
            break;
        }
    }
    cos.salvareFisier();
    stoc.salvareFisier();

    return 0;
}
