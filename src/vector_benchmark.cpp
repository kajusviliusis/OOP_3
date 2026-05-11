#include "Vector.h"

#include <chrono>
#include <iostream>
#include <vector>

template <typename Konteineris>
double matuotiPushBack(int kiekis)
{
    Konteineris v;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < kiekis; i++) {
        v.push_back(i);
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> trukme = end - start;
    return trukme.count();
}

template <typename Konteineris>
int skaiciuotiPerskirstymus(int kiekis)
{
    Konteineris v;
    int perskirstymai = 0;

    for (int i = 0; i < kiekis; i++) {
        if (v.size() == v.capacity()) {
            perskirstymai++;
        }

        v.push_back(i);
    }

    return perskirstymai;
}

int main()
{
    int kiekiai[] = {10000, 100000, 1000000, 10000000, 100000000};

    std::cout << "----------------------------------------------------------\n";

    for (int kiekis : kiekiai) {
        double stdVectorLaikas = matuotiPushBack<std::vector<int>>(kiekis);
        double vectorLaikas = matuotiPushBack<Vector<int>>(kiekis);

        std::cout << "Elementu kiekis: " << kiekis << "\n";
        std::cout << "std::vector: " << stdVectorLaikas << " s\n";
        std::cout << "Vector:      " << vectorLaikas << " s\n\n";
    }

    std::cout << "----------------------------------------------------------\n";

    int perskirstymoKiekis = 100000000;

    std::cout << "Perskirstymu skaicius su "
              << perskirstymoKiekis
              << " elementu:\n";

    std::cout << "std::vector: "
              << skaiciuotiPerskirstymus<std::vector<int>>(perskirstymoKiekis)
              << "\n";

    std::cout << "Vector:      "
              << skaiciuotiPerskirstymus<Vector<int>>(perskirstymoKiekis)
              << "\n";
}