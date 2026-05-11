//palygint pacios programos veikima su skirtingais vector (refactorint v3.0 kad naudotu Vector ir lygint su v1.5 saka)
//tada pridet doxygen dokumentacija, readme.md, tada setup faila

## Programos aprašymas

Programa skirta apdoroti studentų duomenis ir analizuoti jų akademinius rezultatus. Ji leidžia:

- Įvesti studentų duomenis rankiniu būdu
- Įvesti vardus ir pavardes, o pažymius sugeneruoti atsitiktinai
- Atsitiktinai generuoti studentų vardus, pavardes ir pažymius
- Nuskaityti studentų duomenis iš failo
- Sugeneruoti failą su atsitiktiniais studentų duomenimis

Programoje taip pat įgyvendintos trys strategijos, skirtos palyginti programos veikimo laiką naudojant skirtingus konteinerius (vector, list, deque) skirstant studentus į pažangius ir nepažangius.

## Naudojimosi instrukcijos

Instaliuokite CMake, C++ kompiliatorių.

1. Klonuoti projektą:

```
git clone https://github.com/kajusviliusis/OOP_3.git
cd OOP_3
```
2. Sukurti build directory ir kompiliuoti su CMake:
```
mkdir build
cd build
cmake ..
cmake --build .
```

3. Paleisti programą:
```
./OOP_3
```
4. Paleisti testus:
```
./testai
```

## v2.0

Šioje versijoje projektas papildytas automatizuotais unit testais ir Doxygen dokumentacija. Unit testai realizuoti naudojant GoogleTest karkasą, o testų tikslas - patikrinti svarbiausią `Studentas` klasės elgseną: konstruktorių, kopijavimą, perkėlimą, priskyrimo operatorių, įvesties/išvesties operatorių ir galutinio balo skaičiavimą.
<img width="695" height="63" alt="image" src="https://github.com/user-attachments/assets/db87ca6b-99d9-4689-a9bf-f10f5e8850e3" />


## v1.5

Šioje versijoje pridėta bazinė (abstrakti) klasė `Zmogus` ir iš jos išvestinė (derived) klasė `Studentas`.
Programa naudoja tą pačią v1.2 logiką, tik `Studentas` dabar paveldi bendrą informaciją apie žmogų (vardą ir pavardę).

### Klasių struktūra

| Klasė | Tipas | Paskirtis | Pastabos |
|------|------|----------|---------|
| `Zmogus` | Abstrakti bazinė | Saugo bendrą informaciją apie žmogų (`vardas_`, `pavarde_`) | Negalima sukurti `Zmogus` objektų, nes turi `virtual std::string tipas() const = 0;` |
| `Studentas` | Išvestinė iš `Zmogus` | Saugo studento pažymius ir skaičiavimus | Įgyvendina `tipas()` ir palaiko v1.2 rule of five |

Bandant sukurti žmogaus objektą:
<img width="1583" height="303" alt="image" src="https://github.com/user-attachments/assets/4056d6af-b2b6-4256-b4e5-825ba84253fe" />

## v1.2

Šioje versijoje klasė `Studentas` papildyta pilnai realizuotais rule of five metodais ir perdengtais įvesties/išvesties operatoriais.

### Realizuoti metodai ir operatoriai

| Funkcionalumas              | Realizacija | Kada naudojama                                                              |
|-----------------------------|---|-----------------------------------------------------------------------------|
| Copy konstruktorius         | `Studentas(const Studentas& s)` | Kai sukuriama objekto kopija (pvz. kopijuojant į konteinerius)              |
| Copy assignment operatorius | `Studentas& operator=(const Studentas& s)` | Kai vykdomas priskyrimas `a = b`                                            |
| Move konstruktorius         | `Studentas(Studentas&& s)` | Kai objektas perkeliamas iš laikino (pvz. su `std::move`)                   |
| Move assignment operatorius | `Studentas& operator=(Studentas&& s)` | Kai vykdomas `a = std::move(b)`                                             |
| Destruktorius               | `~Studentas()` | Automatiškai kviečiamas išeinant iš scope                                   |
| Įvesties operatorius        | `operator>>(std::istream&, Studentas&)` | Skaito eilutę formatu `Vardas Pavarde ND... Egz` (tinka failams ir testams) |
| Išvesties operatorius       | `operator<<(std::ostream&, const Studentas&)` | Išveda `Vardas Pavarde ND... Egz` (patogu spausdinimui ir testams)          |

Visi metodai ir operatoriai atlikus testavimą veikia teisingai:

<img width="565" height="252" alt="image" src="https://github.com/user-attachments/assets/61c50a74-307b-4a2e-a51f-06d304c95645" />


## v1.1

v1.1 šaka sukurta siekiant palyginti class ir struct naudojimą studentų duomenų saugojimui. Žemiau pateikiami atlikto tyrimo rezultatai. Versijoje v1.1 įgyvendinta class struktūra lyginama su v1.0, kurioje naudotas struct.
Tyrimas atliktas pasitelkiant 3 strategiją ir naudojant vektoriaus konteinerį.

| Programos veikimo laikas su CLASS | Programos veikimo laikas su STRUCT | Studentų kiekis | Optimizavimo vėliava | Vykdomojo failo dydis su CLASS (KB) | Vykdomojo failo dydis su STRUCT (KB) |
| ------ | ----- | --------------- | ------------------------ | ---- | ---- |
| 0.2189s | 0.2070s | 100 000 | -O1 | 149 | 149 |
| 0.2282s | 0.2137s | 100 000 | -O2 | 146 | 153 |
| 0.2261s | 0.2019s | 100 000 | -O3 | 148 | 152 |
| 0.4896s | 0.4138s | 100 000 | - | 234 | 229 |
|  |  |  |  |  |  |
| 1.7954s | 1.9903s | 1 000 000 | -O1 | 149 | 149 |
| 1.7116s | 2.1445s | 1 000 000 | -O2 | 146 | 153 |
| 1.7465s | 2.0847s | 1 000 000 | -O3 | 148 | 152 |
| 4.4061s | 4.4432s | 1 000 000 | - | 234 | 229 |
