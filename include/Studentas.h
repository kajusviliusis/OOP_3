#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "Vector.h"
#include "Zmogus.h"

#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

class Studentas : public Zmogus{
private:
    int egz_;
    Vector<int> nd_;
    double galVid_;
    double galMed_;

public:
    Studentas() : Zmogus("", ""), egz_(0), nd_{}, galVid_(0.0), galMed_(0.0) {}
    Studentas(const std::string& vardas, const std::string& pavarde, int egz, const Vector<int>& nd)
       : Zmogus(vardas, pavarde), egz_(egz), nd_{nd}, galVid_(0.0), galMed_(0.0) {}

    // copy konstruktorius
    Studentas(const Studentas& s)
        : Zmogus(s.vardas_, s.pavarde_),
    egz_(s.egz_), nd_(s.nd_),
    galVid_(s.galVid_), galMed_(s.galMed_) {}

    // move konstruktorius
    Studentas(Studentas&& s) // && - rvalue nuoroda, std::move pavercia i rvalue
        : Zmogus(std::move(s.vardas_), std::move(s.pavarde_)),
    egz_(s.egz_), nd_(std::move(s.nd_)),
    galVid_(s.galVid_), galMed_(s.galMed_) {
        s.egz_ = 0;
        s.galVid_ = 0.0;
        s.galMed_ = 0.0;
    }

    // destruktorius
    ~Studentas() override {
        vardas_.clear();
        pavarde_.clear();
        nd_.clear();
        egz_ = 0;
        galVid_ = 0.0;
        galMed_ = 0.0;
    }

    // copy assignment operatorius
    Studentas& operator=(const Studentas& s) {
        if (this == &s) return *this;
        vardas_ = s.vardas_;
        pavarde_ = s.pavarde_;
        egz_ = s.egz_;
        nd_ = s.nd_;
        galVid_ = s.galVid_;
        galMed_ = s.galMed_;

        return *this;
    }

    // move assignment operatorius
    Studentas& operator=(Studentas&& s) {
        if (this == &s) return *this;
        vardas_ = std::move(s.vardas_);
        pavarde_ = std::move(s.pavarde_);
        nd_ = std::move(s.nd_);
        egz_ = s.egz_;
        galVid_ = s.galVid_;
        galMed_ = s.galMed_;

        s.egz_ = 0;
        s.galVid_ = 0.0;
        s.galMed_ = 0.0;

        return *this;
    }

    std::string tipas() const override { return "Studentas"; }

    // output operatorius
    friend std::ostream& operator<<(std::ostream& out, const Studentas& s) {
        out << s.vardas_ << ' ' << s.pavarde_;
        for (int nd : s.nd_) out << ' ' << nd;
        out << ' ' << s.egz_;
        return out;
    }

    // input operatorius
    friend std::istream& operator>>(std::istream& in, Studentas& s) {
    std::string eilute;
    std::getline(in, eilute);
    if (!in) return in;

    std::stringstream ss(eilute);

    if (!(ss >> s.vardas_ >> s.pavarde_)) {
        throw std::runtime_error("Blogas studento formatas: truksta vardo/pavardes");
    }

    s.nd_.clear();
    int paz;
    while (ss >> paz) s.nd_.push_back(paz);

    if (s.nd_.empty()) {
        throw std::runtime_error("Blogas studento formatas: truksta pazymiu");
    }

    s.egz_ = s.nd_.back();
    s.nd_.pop_back();

    s.galVid_ = s.skaiciuotiGalutiniSuVid();
    s.galMed_ = s.skaiciuotiGalutiniSuMed();
    return in;
}

    int getEgz() const { return egz_; }
    const Vector<int>& getNd() const { return nd_; }
    double getGalVid() const { return galVid_; }
    double getGalMed() const { return galMed_; }

    void setEgz(int e) { egz_ = e; }
    void setGalVid(double v) { galVid_ = v; }
    void setGalMed(double v) { galMed_ = v; }

    void pridetiNd(int pazymys) { nd_.push_back(pazymys); }
    void isvalytiNd() { nd_.clear(); }
    void pasalintiPaskutiniNd() {
        if (nd_.empty()) throw std::runtime_error("Truksta pazymiu eiluteje");
        nd_.pop_back();
    }


    double skaiciuotiGalutiniSuVid() const;
    double skaiciuotiGalutiniSuMed() const;
};

#endif
