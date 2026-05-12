#include "my_lib.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <sstream>
#include <fstream>

double Studentas::skaiciuotiGalutiniSuVid() const
{
    if (getNd().empty()) {
        throw std::invalid_argument("Negalima skaiciuoti vidurkio, truksta namu darbu ivertinimu");
    }
    double pazSuma = 0;
    for (int paz : getNd()) pazSuma += paz;
    double vid = pazSuma / double(getNd().size());

    return 0.4 * vid + 0.6 * getEgz();
}

double Studentas::skaiciuotiGalutiniSuMed() const
{
    if (getNd().empty()) {
        throw std::invalid_argument("Negalima skaiciuoti medianos, truksta namu darbu ivertinimu");
    }

    Vector<int> kopija = getNd();
    std::sort(kopija.begin(), kopija.end());

    int n = kopija.size();
    double med;
    if (n % 2 == 0) med = (kopija[n / 2 - 1] + kopija[n / 2]) / 2.0;
    else med = kopija[n / 2];

    return 0.4 * med + 0.6 * getEgz();
}

void rodytiRezultatus(const Vector<Studentas>& studentai)
{
    char skaiciavimas;

    while (true) {
        std::cout << "Ar skaičiuoti pagal vidurkį ar medianą? (v arba m)\n";
        std::cin >> skaiciavimas;

        skaiciavimas = std::tolower(skaiciavimas);
        if (skaiciavimas == 'v' || skaiciavimas == 'm') break;
        std::cout << "Neteisingas pasirinkimas. Bandykite dar karta\n";
        std::cin.clear();
        std::cin.ignore(10000,'\n');
    }
    std::cout << std::left << std::setw(10) << "Vardas"
              << std::setw(15) << "Pavardė"
              << "Galutinis ("
              << (skaiciavimas == 'm' ? "Med.)" : "Vid.)")
              << "\n";

    std::cout << "--------------------------------------------\n";

    for (const Studentas& s : studentai)
    {
        double galutinisBalas;

        if (skaiciavimas == 'v')
            galutinisBalas = s.skaiciuotiGalutiniSuVid();
        else
            galutinisBalas = s.skaiciuotiGalutiniSuMed();

        std::cout << std::setw(10) << s.getVardas()
                  << std::setw(15) << s.getPavarde()
                  << std::fixed << std::setprecision(2)
                  << galutinisBalas << "\n";
    }
}

void generuotiPazymius(Studentas& s)
{
    int kiekis = 5;

    s.isvalytiNd();

    for (int i = 0; i < kiekis; i++)
        s.pridetiNd(rand() % 10 + 1);

    s.setEgz(rand() % 10 + 1);
}

void generuotiStudentus(Vector<Studentas>& studentai)
{
    Vector<std::string> vardai = {"Jonas","Petras","Antanas","Marius","Lukas","Mantas","Darius","Andrius","Tomas","Linas"};
    Vector<std::string> pavardes = {"Kazlauskas","Jankauskas","Petrauskas","Paukštis","Stankevičius","Vasiliauskas","Žukauskas","Butkus","Paura","Kairys"};

    int studentuKiekis = rand() % 7 + 1;

    for (int i = 0; i < studentuKiekis; i++)
    {
        Studentas s;
        s.setVardas(vardai[rand() % vardai.size()]);
        s.setPavarde(pavardes[rand() % pavardes.size()]);
        generuotiPazymius(s);
        studentai.push_back(s);
    }
}

void rodytiRez(const Vector<Studentas>& studentai)
{
    std::stringstream buffer;
    buffer << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavardė" << std::setw(20)
        << "Galutinis (Vid.)" << std::setw(20) << "Galutinis (Med.)" << std::endl;

    for (const Studentas& s : studentai) {
        buffer << std::left << std::setw(20) << s.getVardas() << std::setw(20) << s.getPavarde() << std::setw(20)
               << std::fixed << std::setprecision(2) << s.skaiciuotiGalutiniSuVid()
               << std::setw(20) << std::fixed << std::setprecision(2) << s.skaiciuotiGalutiniSuMed()
               << std::endl;
    }

    int pasirinkimas;
    while (true) {
        std::cout << "Kur norite matyti rezultatus? ekrane(1), faile(2)" << std::endl;
        if (std::cin >> pasirinkimas && (pasirinkimas == 1 || pasirinkimas == 2) ) break;

        std::cout << "Klaida, iveskite 1 arba 2.\n";
        std::cin.clear();
        std::cin.ignore(10000,'\n');
    }
    if(pasirinkimas == 1) {
        std::cout << buffer.str();
    }
    else if(pasirinkimas == 2) {
        std::ofstream failas("Rezultatai.txt");
        if (!failas) throw std::runtime_error("Nepavyko sukurti failo");
        failas << buffer.str();
        failas.close();
    }
}

bool rikiuotiVarda(const Studentas& A, const Studentas& B) {
    return A.getVardas() < B.getVardas();
}
bool rikiuotiPavarde(const Studentas& A, const Studentas& B) {
    return A.getPavarde() < B.getPavarde();
}
bool rikiuotiPagalGalutiniVid(const Studentas& A, const Studentas& B) {
    return A.getGalVid() < B.getGalVid();
}
bool rikiuotiPagalGalutiniMed(const Studentas& A, const Studentas& B) {
    return A.getGalMed() < B.getGalMed();
}

void nuskaitytiFailaTestavimui(Vector<Studentas>& studentai, int kartai)
{
    if (kartai <= 0) {
        throw std::invalid_argument("Kartai turi buti > 0");
    }
    std::string failoVardas;
    std::cout << "Koki faila naudoti testavimui?" << std::endl;
    std::cin >> failoVardas;

    using namespace std::chrono;
    double totalSec = 0.0;

    for (int i=0; i<kartai; i++) {
        std::ifstream failas(failoVardas);
        if(!failas)
        {
            throw std::runtime_error("Nepavyko atidaryti failo " + failoVardas);
        }

        studentai.clear();

        auto start = high_resolution_clock::now();

        std::stringstream buffer;
        buffer << failas.rdbuf();

        std::string eilute;
        std::getline(buffer, eilute);

        while (std::getline(buffer,eilute))
        {
            try {
                std::stringstream ss(eilute);

                Studentas s;
                std::string vardas, pavarde;
                if (!(ss >> vardas >> pavarde)) {
                    throw std::runtime_error("Blogas formatas eiluteje " + eilute);
                }
                s.setVardas(vardas);
                s.setPavarde(pavarde);

                int pazymys;
                while(ss >> pazymys)
                {
                    s.pridetiNd(pazymys);
                }

                if (s.getNd().empty()) {
                    throw std::runtime_error("Truksta pazymiu eiluteje " + eilute);
                }

                s.setEgz(s.getNd().back());
                s.pasalintiPaskutiniNd();

                s.setGalVid(s.skaiciuotiGalutiniSuVid());
                s.setGalMed(s.skaiciuotiGalutiniSuMed());

                studentai.push_back(s);
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
        auto end = high_resolution_clock::now();
        duration<double> durationSec = end - start;
        totalSec += durationSec.count();
        failas.close();
    }

    double average = totalSec / kartai;
    std::cout << "Vidutinis failo nuskaitymo laikas po " << kartai << " testu: " << average << " s" << std::endl;
}

void generuotiFaila(int studentuSk) {
    int pazymiuKiekis = 15;
    std::string failoVardas = "generuotiStud" + std::to_string(studentuSk) + ".txt";
    std::ofstream failas(failoVardas);

    failas << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavardė";
    for (int i=1; i<=pazymiuKiekis; i++) {
        failas << std::setw(20) << "ND" + std::to_string(i);
    }
    failas << std::setw(20) << "Egz" << '\n';

    for (int i=1; i<=studentuSk; i++) {
       failas << std::left << std::setw(20) << ("Vardas" + std::to_string(i)) << std::setw(20) << ("Pavarde" + std::to_string(i));

       for (int j = 0; j < pazymiuKiekis; j++) {
            failas << std::setw(20) << (rand() % 10 + 1);
        }
        failas << std::setw(20) << (rand() % 10 + 1) << '\n';
    }
    failas.close();
}

void isvestiDuFailus(const Vector<Studentas>& vargsai, const Vector<Studentas>& kieti) {

    std::ofstream failasVargsai("vargsai.txt");
    std::ofstream failasKieti("kieti.txt");

    failasVargsai << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavardė" << std::setw(20) << "Galutinis (Vid.)" << std::setw(20) << "Galutinis (Med.)" << '\n';
    for (const Studentas& s : vargsai) {
        failasVargsai << std::left << std::setw(20) << s.getVardas() << std::setw(20) << s.getPavarde() << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalVid() << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalMed() << '\n';
    }

    failasKieti << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavardė" << std::setw(20) << "Galutinis (Vid.)" << std::setw(20) << "Galutinis (Med.)" << '\n';
    for (const Studentas& s : kieti) {
        failasKieti << std::left << std::setw(20) << s.getVardas() << std::setw(20) << s.getPavarde() << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalVid() << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalMed() << '\n';
    }

    failasVargsai.close();
    failasKieti.close();
}

void atliktiPirmaTyrima() {
    using namespace std::chrono;
    Vector<int> kiekiai = {1000, 10000, 100000, 1000000, 10000000};

    std::cout << "----------------------------------------------------------\n";
    std::cout << std::left << std::setw(20) << "Irasu kiekis" << "Kurimo trukme (s)\n";
    std::cout << "----------------------------------------------------------\n";

    for (int n : kiekiai) {
        auto start = high_resolution_clock::now();

        generuotiFaila(n);

        auto end = high_resolution_clock::now();
        duration<double> trukme = end - start;

        std::cout << std::left << std::setw(20) << n << std::fixed << std::setprecision(5) << trukme.count() << " s\n";
    }
    std::cout << "----------------------------------------------------------\n";
}