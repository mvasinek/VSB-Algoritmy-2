/* Toto zadaní bylo vytvořeno s pomocí AI. AI bylo použito pro vytvoření ukázkových testů a nápověd k implementaci. */

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

const double EPS = 1e-9;


// ============================================================
// Pomocna funkce
// ============================================================

bool equal(double a, double b)
{
    return abs(a - b) < EPS;
}


// ============================================================
// TASK 1: Transform
// ============================================================
//
// Transformujte rozšířenou matici na schodovitý tvar
// pomocí Gaussovy eliminace.
//
// Příklad:
//
//  2  1 -1 |  8
// -3 -1  2 | -11
// -2  1  2 | -3
//
// by měla byt transformována na matici ve tvaru:
//
//  *  *  * | *
//  0  *  * | *
//  0  0  * | *
//
// Můžete:
//   - přidat násobek jedné řádky k druhé řádce,
//   - prohodit dvě řádky.
//
// Důležité:
// Matice nemusí být čtvercová.
// Poslední sloupec obsahuje pravou stranu.
//
void transform(vector<vector<double>>& matrix)
{    
    // Implementujte Gaussovu eliminaci.
}


// ============================================================
// TASK 2: Solve
// ============================================================
//
// Matice je již ve schodovitém tvaru.
//
// Použijte zpětnou substituci k nalezení hodnot všech proměnných.
//
// Zavolejte tuto funkci pouze pokud má systém právě jedno řešení.
//
// Funkce bude vracet:
//   {x1, x2, x3, ...}
//
vector<double> solve(const vector<vector<double>>& matrix)
{    
    // Implementujte zpětnou substituci.

    return {};
}


// ============================================================
// TASK 3: Detekovat systém bez řešení
// ============================================================
//
// Doplnte chybějící části.
//
// Po Gaussově eliminaci, systém nemá řešení
// pokud řádek reprezentuje:
//
//      0*x1 + 0*x2 + ... + 0*xn = c
//
// kde c != 0.
//
// Příklad:
//
//      1  2  3 | 4
//      0  1  2 | 3
//      0  0  0 | 5
//
// Poslední řádek reprezentuje:
//
//      0 = 5
//
// proto systém nemá řešení.
//
bool hasNoSolution(const vector<vector<double>>& matrix)
{
    int rows = matrix.size();
    int variables = matrix[0].size() - 1;

    for (int row = 0; row < rows; row++)
    {
        bool allZero = true;

        // Doplnte zde kod, ktery overi, zda jsou vsechny koeficienty v radce nulove
        // Použijte EPS při porovnání desetinných čísel.

        // Pokud jsou vsechny koeficienty v radce nulove, ale prava strana neni nula,
        // tak systém nemá řešení.

    }

    return false;
}


// ============================================================
// TASK 4: Detekovat nekonecne mnoho reseni
// ============================================================
//
// Doplnte chybějící části.
//
// Nulový řádek takový jako
//
//      0  0  0 | 0
//
// nám neposkytuje žádnou novou informaci.
//
// Pokud je počet nezávislých rovnic menší než počet proměnných,
// alespoň jedna proměnná je volná
// a systém má nekonecne mnoho reseni.
//
// Důležité:
// Zavolejte hasNoSolution() před touto funkcí.
//
bool hasInfiniteSolutions(const vector<vector<double>>& matrix)
{
    int rows = matrix.size();
    int variables = matrix[0].size() - 1;

    int nonZeroRows = 0;

    for (int row = 0; row < rows; row++)
    {
        bool allZero = true;

        // Doplnte zde kod, ktery overi, zda jsou vsechny koeficienty v radce nulove
        // Použijte EPS při porovnání desetinných čísel.

        if (!allZero)
        {
            nonZeroRows++;
        }
    }

    // Doplnte zde kod, ktery overi, zda je pocet nezavislych rovnic dostatecny pro urceni vsech promennych

    return false;
}


// ============================================================
// Tests
// ============================================================

int main()
{
    // --------------------------------------------------------
    // TEST 1
    // Standardni system s jednym resenim.
    //
    //  2x +  y - z =  8
    // -3x -  y + 2z = -11
    // -2x +  y + 2z = -3
    //
    // Očekávané:
    // x = 2
    // y = 3
    // z = -1
    // --------------------------------------------------------

    vector<vector<double>> m1 = {
        { 2,  1, -1,   8},
        {-3, -1,  2, -11},
        {-2,  1,  2,  -3}
    };

    transform(m1);

    assert(!hasNoSolution(m1));
    assert(!hasInfiniteSolutions(m1));

    vector<double> s1 = solve(m1);

    assert(s1.size() == 3);
    assert(equal(s1[0],  2));
    assert(equal(s1[1],  3));
    assert(equal(s1[2], -1));

    cout << "Test 1 passed." << endl;


    // --------------------------------------------------------
    // TEST 2
    // Bez reseni.
    //
    //  x + y = 2
    // 2x +2y = 5
    //
    // Eliminace by mela vytvorit radku reprezentujici:
    //
    // 0 = c, kde c != 0
    // --------------------------------------------------------

    vector<vector<double>> m2 = {
        {1, 1, 2},
        {2, 2, 5}
    };

    transform(m2);

    assert(hasNoSolution(m2));

    cout << "Test 2 passed." << endl;


    // --------------------------------------------------------
    // TEST 3
    // Nekonecne mnoho reseni.
    //
    //  x + y = 2
    // 2x +2y = 4
    //
    // Druha rovnice je nasobkem prvni rovnice.
    // --------------------------------------------------------

    vector<vector<double>> m3 = {
        {1, 1, 2},
        {2, 2, 4}
    };

    transform(m3);

    assert(!hasNoSolution(m3));
    assert(hasInfiniteSolutions(m3));

    cout << "Test 3 passed." << endl;

    // --------------------------------------------------------
    // TEST 4
    // Vice promennych nez nezavislych rovnic.
    //
    // x + y + z = 3
    // x - y + z = 1
    //
    // Dve nezavisle rovnice nemuze urcit jednoznacne
    // tri promenne.
    // --------------------------------------------------------

    vector<vector<double>> m4 = {
        {1,  1, 1, 3},
        {1, -1, 1, 1}
    };

    transform(m4);

    assert(!hasNoSolution(m4));
    assert(hasInfiniteSolutions(m4));

    cout << "Test 4 passed." << endl;

    // --------------------------------------------------------
    // TEST 5
    // Zavisle radky v vetsim systemu.
    //
    // Druha rovnice je dvakrat prvni rovnice.
    // --------------------------------------------------------

    vector<vector<double>> m5 = {
        {1, 1, 1,  6},
        {2, 2, 2, 12},
        {1, 2, 3, 14}
    };

    transform(m5);

    assert(!hasNoSolution(m5));
    assert(hasInfiniteSolutions(m5));

    cout << "Test 5 passed." << endl;

    // --------------------------------------------------------
    // TEST 6
    // Prvni pivot je nula.
    //
    //       y = 2
    // x +   y = 3
    //
    // Je zapotřebí prohodit radky.
    //
    // Očekávané:
    // x = 1
    // y = 2
    // --------------------------------------------------------

    vector<vector<double>> m6 = {
        {0, 1, 2},
        {1, 1, 3}
    };

    transform(m6);

    assert(!hasNoSolution(m6));
    assert(!hasInfiniteSolutions(m6));

    vector<double> s6 = solve(m6);

    assert(s6.size() == 2);
    assert(equal(s6[0], 1));
    assert(equal(s6[1], 2));

    cout << "Test 6 passed." << endl;

    // --------------------------------------------------------
    // TEST 7
    // Nulový řádek před užitečným řádkem.
    //
    // Správná transformace musí stále rozpoznat
    // dvě nezavisle rovnice.
    // --------------------------------------------------------

    vector<vector<double>> m7 = {
        {1, 1, 2},
        {0, 0, 0},
        {1, 2, 3}
    };

    transform(m7);

    assert(!hasNoSolution(m7));
    assert(!hasInfiniteSolutions(m7));

    vector<double> s7 = solve(m7);

    assert(s7.size() == 2);
    assert(equal(s7[0], 1));
    assert(equal(s7[1], 1));

    cout << "Test 7 passed." << endl;

    // --------------------------------------------------------
    // TEST 8
    // Desetinna cisla.
    //
    // Tento test overi, ze implementace nezavisi na presnem aritmetice.
    //
    // 0.5x +  y = 2
    //   x  -  y = 1
    //
    // Očekávané:
    // x = 2
    // y = 1
    // --------------------------------------------------------

    vector<vector<double>> m8 = {
        {0.5,  1, 2},
        {1.0, -1, 1}
    };

    transform(m8);

    assert(!hasNoSolution(m8));
    assert(!hasInfiniteSolutions(m8));

    vector<double> s8 = solve(m8);

    assert(s8.size() == 2);
    assert(equal(s8[0], 2));
    assert(equal(s8[1], 1));

    cout << "Test 8 passed." << endl;
    cout << "All tests passed." << endl;

    return 0;
}