#include <iostream>
#include <string>
using namespace std;


class Banca;

class Manager {
private:
    string nume;
    string departament;
    double salariu;

public:
    Manager(const string nume, const string departament, const double salariu) {
        this->nume = nume;
        this->departament = departament;
        this->salariu = salariu;
    }

    void prezintaBanca(const Banca& b) const;

    friend ostream& operator<<(ostream& os, const Manager& m);
};

ostream& operator<<(ostream& os, const Manager& m) {
    os << "Manager: " << m.nume << "\n";
    os << "Departament: " << m.departament << "\n";
    os << "Salariu: " << m.salariu << " RON\n";
    return os;
}


class Banca {
private:
    string nume;
    string locatie;
    int sumabanca;



    Manager manager;

public:

    Banca(const string nume, const string locatie,
          const string numeManager, const string depManager, double salariuManager)
        : nume(nume),
          locatie(locatie),
          sumabanca(0),
          manager(numeManager, depManager, salariuManager)
    {

    }


    string getNume() const {
        return nume;
    }

    void SetAdaugaSuma(int valoare) {
        this->sumabanca += valoare;
    }
    int getSumaBanca() const {
        return sumabanca;
    }


    const Manager& getManager() const {
        return manager;
    }


    void prezintaManagerulBanca() const {
        manager.prezintaBanca(*this);
    }

    friend ostream& operator<<(ostream& os, const Banca& b);
};




void Manager::prezintaBanca(const Banca& b) const {

    cout << this->nume << " (" << this->departament << ") va prezinta banca " << b.getNume() << ".\n";
}


ostream& operator<<(ostream& os, const Banca& b) {
    os << "Banca: " << b.nume << "\n";
    os << "Locatia: " << b.locatie << "\n";
    os << "Suma in banca: " << b.sumabanca << "\n";
    os << "--- Managerul Bancii ---\n" << b.getManager();
    return os;
}


class Client {
private:
    string nume;
    int suma;
    bool Verificare(int valoare) const {
        if (valoare>=0)
            return 1;
        else
            return 0;
    }
public:
    Client(): nume("Nume lipsa"), suma(0)
    {cout<< "Datele acestui client nu au fost introduse!\n";
    }
    Client(const string nume, const int suma) {
        this->nume = nume;
        this->suma = suma;
    }
Client& operator=(const Client& other) {
        this->nume = other.nume;
        this->suma = other.suma;
        return *this;
    }
    void transfer(Client& dest, int valoare) {
        if (!Verificare(valoare)) return;

        if (suma >= valoare) {
            suma -= valoare;
            dest.suma += valoare;
        } else {
            cout << "Fonduri insuficiente pentru transfer!\n";
        }
    }


    void depozit(Banca& b, int valoare) {
        if (!Verificare(valoare)) return;

        if (suma >= valoare) {
            suma -= valoare;
            b.SetAdaugaSuma(valoare);
        } else {
            cout << "Fonduri insuficiente pentru depozit!\n";
        }
    }

    void credit(Banca& b, int valoare) {

        if (!Verificare(valoare)) return;


        if (b.getSumaBanca() >= valoare) {

            suma += valoare;
            b.SetAdaugaSuma(-valoare);
        }
        else
        {
            cout << "Banca nu are fondurile suficiente pentru un credit!\n";
        }
    }


~Client() {
        cout<<"\n Clientul a fost sters: "<<this->nume<<"\n";
    }

    friend ostream& operator<<(ostream& os, const Client& c);
};

ostream& operator<<(ostream& os, const Client& c) {
    os << "Nume: " << c.nume << "\n";
    os << "Suma: " << c.suma << "\n";
    return os;
}


int main() {
    Client c1("Andrei", 300);
    Client c2("Maria", 300);
    Client c4=c1;
    Client c5;

    Banca b("SmartBank", "Bucuresti", "Popescu Ion", "Sucursala", 5500.00);

    Client c3("Alex",200);


    // --- Transfer ---
    c1.transfer(c2, 100);
    cout << "\n--- Dupa Transfer ---\n";
    cout << "C1: \n" << c1;
    cout << "C2: \n" << c2;

    // --- Depozit ---
    c2.depozit(b, 50);
    cout << "\n--- Dupa Depozit ---\n";
    cout << "C2: \n" << c2;
    cout << "Banca: \n" << b;

    //--- Credit ---
    c3.credit(b, 30);
    cout << "\n--- Dupa Credit ---\n";
    cout << "C3: \n" << c3;
    cout << "Banca: \n" << b;

    // --- Copiere ---
    cout<<"\n--- Comparam la final constructorul de copiere---\n";
    cout << "C1: \n" << c1;
    cout << "C4: \n" << c4;

    // --- Constructor fara parametru ---
    cout<<"\n--- Verificam constructorul fara parametru---\n";
    cout << "C5: \n" << c5;

    cout << "\n--- Prezentare Manager (prin Banca) ---\n";
    b.prezintaManagerulBanca();

    return 0;
}