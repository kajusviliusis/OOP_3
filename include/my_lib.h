#ifndef MYLIB_H
#define MYLIB_H

#include "Studentas.h"
#include "Vector.h"

#include <string>
#include <deque>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <type_traits>

void rodytiRezultatus(const Vector<Studentas>& studentai);
void generuotiPazymius(Studentas& s);
void generuotiStudentus(Vector<Studentas>& studentai);
void rodytiRez(const Vector<Studentas>& studentai);
bool rikiuotiVarda(const Studentas& A, const Studentas& B);
bool rikiuotiPavarde(const Studentas& A, const Studentas& B);
bool rikiuotiPagalGalutiniVid(const Studentas& A, const Studentas& B);
bool rikiuotiPagalGalutiniMed(const Studentas& A, const Studentas& B);
void nuskaitytiFailaTestavimui(Vector<Studentas>& studentai, int kartai);
void generuotiFaila(int studentuSk);
void isvestiDuFailus(const Vector<Studentas>& vargsai, const Vector<Studentas>& kieti);
void atliktiPirmaTyrima();
void atliktiAntraTyrima();

// templates

template <typename Konteineris>
void nuskaitytiFaila(Konteineris& studentai, const std::string& failoVardas)
{
    std::ifstream failas(failoVardas);
    if (!failas) {
        throw std::runtime_error("Nepavyko atidaryti failo " + failoVardas);
    }

    std::stringstream buffer;
    buffer << failas.rdbuf();

    std::string eilute;
    std::getline(buffer, eilute);

    while (std::getline(buffer, eilute)) {
        std::stringstream ss(eilute);

        Studentas s;
        std::string vardas, pavarde;
        if (!(ss >> vardas >> pavarde)) {
            throw std::runtime_error("Blogas formatas eiluteje " + eilute);
        }
        s.setVardas(vardas);
        s.setPavarde(pavarde);

        int pazymys;
        while (ss >> pazymys) {
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
}

template <typename Konteineris>
void rikiuotiStudentus(Konteineris& studentai, int pasirinkimas)
{
    if (pasirinkimas < 1 || pasirinkimas > 4) {
        throw std::out_of_range("Pasirinkimas turi buti 1-4");
    }

    if (pasirinkimas == 1) {
        // perziuri kompiliavimo metu, kad butu kompiliuojamas tik reikalingas rikiavimas, ziuredamas i template type
        if constexpr (std::is_same<Konteineris, std::list<Studentas> >::value) studentai.sort(rikiuotiVarda);
        else std::sort(studentai.begin(), studentai.end(), rikiuotiVarda);
    } else if (pasirinkimas == 2) {
        if constexpr (std::is_same<Konteineris, std::list<Studentas> >::value) studentai.sort(rikiuotiPavarde);
        else std::sort(studentai.begin(), studentai.end(), rikiuotiPavarde);
    } else if (pasirinkimas == 3) {
        if constexpr (std::is_same<Konteineris, std::list<Studentas> >::value) studentai.sort(rikiuotiPagalGalutiniVid);
        else std::sort(studentai.begin(), studentai.end(), rikiuotiPagalGalutiniVid);
    } else {
        if constexpr (std::is_same<Konteineris, std::list<Studentas> >::value) studentai.sort(rikiuotiPagalGalutiniMed);
        else std::sort(studentai.begin(), studentai.end(), rikiuotiPagalGalutiniMed);
    }
}

// strategija 1
template <typename Konteineris>
void paskirstytiStudentus(const Konteineris& studentai, Konteineris& vargsai,
            Konteineris& kieti) {

    for (const auto& s : studentai) {
        if (s.getGalVid() >= 5.0) {
            kieti.push_back(s);
        } else {
            vargsai.push_back(s);
        }
    }
}

// strategija 2
template <typename Konteineris>
void paskirstytiStudentusS2(Konteineris& studentai, Konteineris& vargsai)
{
    vargsai.clear();

    // rikiuoti mazejimo tvarka kad vargsai butu gale
    if constexpr (std::is_same_v<Konteineris, std::list<Studentas>>)
    {
        studentai.sort([](const Studentas& a, const Studentas& b) {
            return a.getGalVid() > b.getGalVid();
        });
    }
    else
    {
        std::sort(studentai.begin(), studentai.end(),
                  [](const Studentas& a, const Studentas& b) {
                      return a.getGalVid() > b.getGalVid();
                  });
    }

    while (!studentai.empty() && studentai.back().getGalVid() < 5.0)
    {
        vargsai.push_back(studentai.back());
        studentai.pop_back();
    }


}

// strategija 3
template <typename Konteineris>
void paskirstytiStudentusS3(Konteineris& studentai, Konteineris& vargsai)
{
    vargsai.clear();

    // std::partition pertvarko konteineri taip kad visi elementai kurie tenkina salyga butu pradzioje, o kiti gale.
    // Grazina iterator i pirmo elemento po true grupes pradzia
    auto mid = std::partition(studentai.begin(), studentai.end(),
                              [](const Studentas& s) { return s.getGalVid()< 5.0; });

    for (auto it = studentai.begin(); it != mid; ++it) {
        vargsai.push_back(*it);
    }

    studentai.erase(studentai.begin(), mid);
}


template <typename Konteineris>
void atliktiAntraTyrima(int strategija) {
    using namespace std::chrono;
    Vector<int> kiekiai = {1000, 10000, 100000, 1000000, 10000000};
    int rikiavimas = 3;

    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(10) << "Irasai"
              << std::setw(12) << "Skaitymas"
              << std::setw(12) << "Rikiavimas"
              << std::setw(12) << "Skirstymas"
              << "Viso\n";
    std::cout << "-----------------------------------------------------------------------------\n";

    for (int n : kiekiai) {
        Konteineris studentai;
        Konteineris vargsai;
        Konteineris kieti;
        std::string failoVardas = "generuotiStud" + std::to_string(n) + ".txt";

        auto visoPradzia = high_resolution_clock::now();

        // 1 skaitymas
        auto s1 = high_resolution_clock::now();
        try {
            nuskaitytiFaila(studentai, failoVardas);
        } catch (const std::exception& e) {
            std::cerr << "Klaida: Nepavyko rasti " << failoVardas << "\n";
            continue;
        }
        auto e1 = high_resolution_clock::now();

        // 2 rikiavimas didejimo tvarka
        auto s2 = high_resolution_clock::now();
        rikiuotiStudentus(studentai, rikiavimas);
        auto e2 = high_resolution_clock::now();

        // 3 skirstymas
        auto s3 = high_resolution_clock::now();
        if (strategija==1) paskirstytiStudentus(studentai,vargsai,kieti);
        else if (strategija==2) paskirstytiStudentusS2(studentai,vargsai);
        else if (strategija==3) paskirstytiStudentusS3(studentai,vargsai);
        auto e3 = high_resolution_clock::now();

        auto visoPabaiga = high_resolution_clock::now();

        double trukme1 = duration<double>(e1 - s1).count();
        double trukme2 = duration<double>(e2 - s2).count();
        double trukme3 = duration<double>(e3 - s3).count();
        double trukmeViso = duration<double>(visoPabaiga - visoPradzia).count();

        std::cout << std::left << std::setw(10) << n
                  << std::fixed << std::setprecision(4)
                  << std::setw(12) << trukme1
                  << std::setw(12) << trukme2
                  << std::setw(12) << trukme3
                  << trukmeViso << " s\n";

        studentai.clear();
        vargsai.clear();
        kieti.clear();
    }
    std::cout << "-----------------------------------------------------------------------------\n";
}


#endif
