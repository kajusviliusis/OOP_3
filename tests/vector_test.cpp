#include "Vector.h"
#include "Studentas.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <string>
#include <utility>

TEST(VectorTest, DefaultConstructorSukuriaTusciaVektoriu)
{
    Vector<int> v;

    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
    EXPECT_EQ(v.data(), nullptr);
}

TEST(VectorTest, SizeKonstruktoriusSukuriaNumatytasReiksmes)
{
    Vector<int> v(3);

    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v.capacity(), 3u);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 0);
    EXPECT_EQ(v[2], 0);
}

TEST(VectorTest, InicializavimoSarasoKonstruktoriusIssaugoReiksmes)
{
    Vector<int> v{4, 2, 7};

    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 4);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 7);
}

TEST(VectorTest, CopyKonstruktoriusSukuriaNepriklausomaKopija)
{
    Vector<int> original{1, 2, 3};
    Vector<int> copy(original);

    copy[0] = 9;

    EXPECT_EQ(original[0], 1);
    EXPECT_EQ(copy[0], 9);
    EXPECT_EQ(copy.size(), original.size());
}

TEST(VectorTest, CopyAssignmentSukuriaNepriklausomaKopija)
{
    Vector<int> original{1, 2, 3};
    Vector<int> copy;

    copy = original;
    copy[1] = 8;

    EXPECT_EQ(original[1], 2);
    EXPECT_EQ(copy[1], 8);
    EXPECT_EQ(copy.size(), original.size());
}

TEST(VectorTest, MoveKonstruktoriusPerkeliaDuomenis)
{
    Vector<int> original{1, 2, 3};

    Vector<int> moved(std::move(original));

    EXPECT_EQ(moved.size(), 3u);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[2], 3);
    EXPECT_TRUE(original.empty());
}

TEST(VectorTest, MoveAssignmentPerkeliaDuomenis)
{
    Vector<int> original{1, 2, 3};
    Vector<int> moved;

    moved = std::move(original);

    EXPECT_EQ(moved.size(), 3u);
    EXPECT_EQ(moved[1], 2);
    EXPECT_TRUE(original.empty());
}

TEST(VectorTest, IndeksoOperatoriusSkaitoIrKeiciaReiksmes)
{
    Vector<int> v{1, 2, 3};

    v[1] = 9;

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 9);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, AtTikrinaIndeksoRibas)
{
    Vector<int> v{5, 6};

    EXPECT_EQ(v.at(0), 5);
    EXPECT_EQ(v.at(1), 6);
    EXPECT_THROW(v.at(2), std::out_of_range);
}

TEST(VectorTest, FrontBackIrDataGrazinaTeisingasReiksmes)
{
    Vector<int> v{8, 9, 10};

    EXPECT_EQ(v.front(), 8);
    EXPECT_EQ(v.back(), 10);
    ASSERT_NE(v.data(), nullptr);
    EXPECT_EQ(v.data()[1], 9);
}

TEST(VectorTest, IteratoriaiVeikiaSuRangeForIrSort)
{
    Vector<int> v{3, 1, 2};

    std::sort(v.begin(), v.end());
    int sum = 0;
    for (int value : v) {
        sum += value;
    }

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(sum, 6);
}

TEST(VectorTest, ReservePadidinaTalpaNekeiciantDydzio)
{
    Vector<int> v{1, 2};

    v.reserve(10);

    EXPECT_EQ(v.size(), 2u);
    EXPECT_GE(v.capacity(), 10u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, ShrinkToFitSumazinaTalpaIkiDydzio)
{
    Vector<int> v{1, 2, 3};
    v.reserve(20);

    v.shrink_to_fit();

    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v.capacity(), 3u);
}

TEST(VectorTest, PushBackDidinaDydiIrIssaugoReiksmes)
{
    Vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(v.size(), 3u);
    EXPECT_GE(v.capacity(), v.size());
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PopBackSumazinaDydi)
{
    Vector<int> v{1, 2, 3};

    v.pop_back();

    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v.back(), 2);
}

TEST(VectorTest, ClearNustatoDydiINuliIrPaliekaTalpa)
{
    Vector<int> v{1, 2, 3};
    const auto oldCapacity = v.capacity();

    v.clear();

    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), oldCapacity);
}

TEST(VectorTest, ResizePadidinaIrSumazinaVektoriu)
{
    Vector<int> v{1, 2};

    v.resize(4);
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 0);
    EXPECT_EQ(v[3], 0);

    v.resize(1);
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, ResizeSuReiksmeUzpildoNaujusElementus)
{
    Vector<std::string> v{"a"};

    v.resize(3, std::string("x"));

    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], "a");
    EXPECT_EQ(v[1], "x");
    EXPECT_EQ(v[2], "x");
}

TEST(VectorTest, EraseVienasElementasPasalinaReiksme)
{
    Vector<int> v{1, 2, 3, 4};

    auto it = v.erase(v.begin() + 1);

    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(v, (Vector<int>{1, 3, 4}));
}

TEST(VectorTest, EraseIntervalasPasalinaReiksmes)
{
    Vector<int> v{1, 2, 3, 4, 5};

    auto it = v.erase(v.begin() + 1, v.begin() + 4);

    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(*it, 5);
    EXPECT_EQ(v, (Vector<int>{1, 5}));
}

TEST(VectorTest, PalyginimoOperatoriaiLyginaReiksmes)
{
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2, 3};
    Vector<int> c{1, 2, 4};

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
}

TEST(VectorTest, SaugoKopijuojaIrPerkeliaStudentoObjektus)
{
    Studentas jonas("Jonas", "Jonaitis", 10, {8, 9});
    Studentas ona("Ona", "Onaite", 7, {6, 8});

    Vector<Studentas> studentai;
    studentai.push_back(jonas);
    studentai.push_back(std::move(ona));

    Vector<Studentas> copy(studentai);
    Vector<Studentas> moved(std::move(copy));

    ASSERT_EQ(moved.size(), 2u);
    EXPECT_EQ(moved[0].getVardas(), "Jonas");
    EXPECT_EQ(moved[0].getPavarde(), "Jonaitis");
    EXPECT_EQ(moved[0].getEgz(), 10);
    EXPECT_EQ(moved[0].getNd(), (std::vector<int>{8, 9}));

    EXPECT_EQ(moved[1].getVardas(), "Ona");
    EXPECT_EQ(moved[1].getPavarde(), "Onaite");
    EXPECT_EQ(moved[1].getEgz(), 7);
    EXPECT_EQ(moved[1].getNd(), (std::vector<int>{6, 8}));

    EXPECT_TRUE(copy.empty());
    EXPECT_EQ(copy.size(), 0u);
    EXPECT_EQ(copy.capacity(), 0u);
    EXPECT_EQ(copy.data(), nullptr);
}
