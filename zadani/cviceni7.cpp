
#include <cassert>
#include <vector>

using namespace std;

/*
 * CVICENI 7 - DYNAMICKE PROGRAMOVANI
 * Optimalizace obsahu cache
 *
 * ZADANI:
 *
 * Aplikace pracuje s objekty ulozenymi na pomalejsim ulozisti.
 * Vybrane objekty lze uchovavat v rychle cache, ktera ma
 * omezenou kapacitu.
 *
 * Kazdy objekt ma dve vlastnosti:
 *   size    - velikost objektu v MB
 *   benefit - prinos ulozeni objektu do cache
 *
 * Ukolem je vybrat objekty tak, aby jejich celkovy prinos
 * byl maximalni a soucet jejich velikosti neprekrocil
 * kapacitu cache.
 *
 * Kazdy objekt lze vybrat nejvyse jednou.
 * Objekty nelze delit na mensi casti.
 *
 * IMPLEMENTACE:
 *
 * 1. Navrhnete algoritmus pro nalezeni maximalniho prinosu.
 * 2. Implementujte funkci maximizeBenefit().
 * 3. Overte spravnost pomoci pripravenych testu.
 * 4. Odpovezte na otazky na konci souboru.
 *
 * Predpokladejte nezaporne hodnoty size, benefit a capacity.
 * Funkce vraci maximalni dosazitelny prinos.
 * Pokud nelze vybrat zadny objekt, vraci 0.
 */

struct Object {
    int size;
    int benefit;
};

// ---------------------------------------------------------
// UKOL: Implementujte nasledujici funkci.
// ---------------------------------------------------------

int maximizeBenefit(const vector<Object>& objects, int capacity) {

}

// ---------------------------------------------------------
// TESTY - neupravujte ocekavane vysledky.
// ---------------------------------------------------------

int main() {

    // Test 1: Zakladni priklad
    {
        vector<Object> objects = {
            {6, 12},
            {4, 9},
            {5, 11},
            {3, 5}
        };

        assert(maximizeBenefit(objects, 10) == 21);
    }

    // Test 2: Hladovy vyber podle pomeru
    // prinos/velikost nemusi byt optimalni.
    {
        vector<Object> objects = {
            {6, 12},
            {5, 9},
            {5, 9}
        };

        assert(maximizeBenefit(objects, 10) == 18);
    }

    // Test 3: Vsechny objekty se vejdou
    {
        vector<Object> objects = {
            {2, 4},
            {3, 5},
            {4, 7}
        };

        assert(maximizeBenefit(objects, 10) == 16);
    }

    // Test 4: Zadny objekt se nevejde
    {
        vector<Object> objects = {
            {6, 10},
            {8, 15}
        };

        assert(maximizeBenefit(objects, 3) == 0);
    }

    // Test 5: Nulova kapacita
    {
        vector<Object> objects = {
            {2, 5},
            {3, 8}
        };

        assert(maximizeBenefit(objects, 0) == 0);
    }

    // Test 6: Prazdny seznam objektu
    {
        vector<Object> objects;

        assert(maximizeBenefit(objects, 10) == 0);
    }

    // Test 7: Kazdy objekt lze vybrat pouze jednou
    {
        vector<Object> objects = {
            {3, 10}
        };

        assert(maximizeBenefit(objects, 9) == 10);
    }

    // Test 8: Vyber vice mensich objektu
    {
        vector<Object> objects = {
            {8, 15},
            {4, 9},
            {3, 8},
            {3, 8}
        };

        assert(maximizeBenefit(objects, 10) == 25);
    }

    // Test 9: Optimalni reseni nemusi
    // vyuzit celou kapacitu cache.
    {
        vector<Object> objects = {
            {6, 15},
            {4, 8},
            {3, 7}
        };

        assert(maximizeBenefit(objects, 8) == 15);
    }

    return 0;
}

/*
 * =========================================================
 * OTAZKY
 * =========================================================
 *
 * Odpovedi zapiste primo pod jednotlive otazky.
 *
 * 1. PRINCIP ALGORITMU
 *
 * Vysvetlete, jak vas algoritmus postupuje.
 * Jake mensi podproblemy resi a jak z jejich vysledku
 * sestavuje optimalni reseni?
 *
 * Odpoved:
 *
 *
 *
 * 2. POMOCNE DATOVE STRUKTURY
 *
 * Jake pomocne datove struktury pouzivate?
 * Vysvetlete, co predstavuji hodnoty, ktere do nich
 * ukladate.
 *
 * Odpoved:
 *
 *
 *
 * 3. CASOVA SLOZITOST
 *
 * Urcete casovou slozitost vaseho algoritmu.
 * Oznacte:
 *   N - pocet objektu
 *   C - kapacita cache
 *
 * Vyjadrete slozitost pomoci O(...) a vysvetlete,
 * z ceho vyplyva.
 *
 * Odpoved:
 *
 *
 *
 * 4. PAMETOVA SLOZITOST
 *
 * Urcete pametovou slozitost vaseho algoritmu
 * vzhledem k N a C.
 *
 * Vysvetlete, na cem zavisi mnozstvi pouzite pameti.
 *
 * Odpoved:
 *
 *
 *
 * 5. HLADOVY ALGORITMUS
 *
 * Predstavte si, ze objekty seradite podle pomeru
 * benefit / size a budete je postupne vybirat,
 * dokud se vejdou do cache.
 *
 * Zaruci tento postup vzdy optimalni reseni?
 * Vysvetlete svou odpoved a uvedte protipriklad.
 *
 * Odpoved:
 *
 *
 *
 */