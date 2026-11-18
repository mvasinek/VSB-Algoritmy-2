
/*
 * Algoritmy II
 * Minimalni kostra grafu - vystavba opticke site
 *
 * ZADANI
 * ======
 *
 * Poskytovatel internetoveho pripojeni planuje propojit
 * skupinu budov optickou siti.
 *
 * Mezi nekterymi budovami jiz existuje opticke vedeni,
 * mezi jinymi je mozne nove vedeni vybudovat.
 * Pro kazde mozne spojeni jsou znamy naklady na jeho
 * realizaci.
 *
 * Vasim ukolem je navrhnout vystavbu opticke site tak,
 * aby byly vsechny budovy vzajemne dostupne a celkove
 * naklady na vystavbu nove infrastruktury byly minimalni.
 *
 * Pravidla:
 *
 * 1. Spojeni mezi budovami jsou obousmerna.
 * 2. Budovy nemusi byt propojeny primo, komunikace muze
 *    probihat prostrednictvim dalsich budov.
 * 3. Existujici spojeni zustavaji zachovana a jejich
 *    vyuziti nepredstavuje zadne dodatecne naklady.
 * 4. Existujici infrastruktura muze obsahovat cykly.
 * 5. Neni zadouci budovat nadbytecna nova spojeni.
 * 6. Pokud vsechny budovy nelze propojit, musi program
 *    tuto skutecnost detekovat.
 *
 * IMPLEMENTACE
 * ============
 *
 * Implementujte funkci buildNetwork(), ktera vrati:
 *
 * - informaci, zda lze vsechny budovy propojit,
 * - minimalni celkove naklady na vystavbu,
 * - seznam nove budovanych spojeni.
 *
 * Pouzijte algoritmus pro hledani minimalni kostry grafu.
 * Volba konkretniho algoritmu a pomocnych datovych
 * struktur je na vas.
 *
 * Implementaci zvoleneho algoritmu muzete dohledat,
 * musite ji vsak umet vysvetlit a prizpusobit zadani.
 *
 * Vstupni predpoklady:
 *
 * - Sit obsahuje alespon jednu budovu.
 * - Budovy jsou cislovany od 0 do buildingCount - 1.
 * - Vsechny naklady jsou nezaporne.
 * - Kazde spojeni ma platne indexy budov.
 * - Naklady a jejich soucet se vejdou do typu int.
 *
 * Pokud sit nelze vybudovat, vratte:
 *
 * possible = false
 * totalCost = 0
 * newConnections = prazdny vektor
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;


// ================================================
// DATOVE STRUKTURY
// ================================================

struct Connection {
    int from;
    int to;
    int cost;
    bool existing;
};

struct Network {
    int buildingCount;
    vector<Connection> connections;
};

struct Result {
    bool possible;
    int totalCost;
    vector<Connection> newConnections;
};


// ================================================
// IMPLEMENTACE
// ================================================

Result buildNetwork(const Network& network) {

    // TODO: Doplnte vlastni implementaci.

    Result result;
    result.possible = false;
    result.totalCost = 0;

    return result;
}


// ================================================
// TESTOVACI SADA
// ================================================


// Test 1: Zakladni sit bez existujicich spojeni.
void testBasicNetwork() {

    Network network = {
        4,
        {
            {0, 1, 10, false},
            {0, 2, 20, false},
            {1, 2, 15, false},
            {1, 3, 30, false},
            {2, 3, 18, false}
        }
    };

    Result result = buildNetwork(network);

    assert(result.possible);
    assert(result.totalCost == 50);
    assert(result.newConnections.size() == 3);
}


// Test 2: Vyber nejlevnejsich hran by vytvoril cyklus.
void testCycle() {

    Network network = {
        4,
        {
            {0, 1, 1, false},
            {1, 2, 2, false},
            {0, 2, 3, false},
            {2, 3, 10, false},
            {0, 3, 20, false}
        }
    };

    Result result = buildNetwork(network);

    assert(result.possible);
    assert(result.totalCost == 13);
    assert(result.newConnections.size() == 3);
}


// Test 3: Cast infrastruktury jiz existuje.
// Existujici spojeni muze mit nenulovou historickou
// cenu. Tato cena se nezapocitava do nove vystavby.
void testExistingConnections() {

    Network network = {
        5,
        {
            {0, 1, 100, true},
            {2, 3, 200, true},
            {1, 2, 10, false},
            {3, 4, 20, false},
            {0, 4, 40, false}
        }
    };

    Result result = buildNetwork(network);

    assert(result.possible);
    assert(result.totalCost == 30);
    assert(result.newConnections.size() == 2);
}


// Test 4: Existujici infrastruktura obsahuje cyklus.
void testExistingCycle() {

    Network network = {
        4,
        {
            {0, 1, 100, true},
            {1, 2, 100, true},
            {2, 0, 100, true},
            {2, 3, 15, false},
            {0, 3, 20, false}
        }
    };

    Result result = buildNetwork(network);

    assert(result.possible);
    assert(result.totalCost == 15);
    assert(result.newConnections.size() == 1);
}


// Test 5: Vsechny budovy nelze propojit.
void testDisconnectedNetwork() {

    Network network = {
        5,
        {
            {0, 1, 10, false},
            {1, 2, 20, false},
            {3, 4, 30, false}
        }
    };

    Result result = buildNetwork(network);

    assert(!result.possible);
    assert(result.totalCost == 0);
    assert(result.newConnections.empty());
}


// Test 6: Existuje vice optimalnich reseni.
void testEqualCosts() {

    Network network = {
        4,
        {
            {0, 1, 10, false},
            {1, 2, 10, false},
            {2, 3, 10, false},
            {3, 0, 10, false},
            {0, 2, 10, false}
        }
    };

    Result result = buildNetwork(network);

    assert(result.possible);
    assert(result.totalCost == 30);
    assert(result.newConnections.size() == 3);
}


// Test 7: Vsechny budovy jsou jiz propojeny.
void testCompleteNetwork() {

    Network network = {
        4,
        {
            {0, 1, 100, true},
            {1, 2, 200, true},
            {2, 3, 300, true},
            {0, 3, 10, false}
        }
    };

    Result result = buildNetwork(network);

    assert(result.possible);
    assert(result.totalCost == 0);
    assert(result.newConnections.empty());
}


// Test 8: Sit obsahuje pouze jednu budovu.
void testSingleBuilding() {

    Network network = {1, {}};

    Result result = buildNetwork(network);

    assert(result.possible);
    assert(result.totalCost == 0);
    assert(result.newConnections.empty());
}


// Test 9: Nulova cena noveho spojeni neznamena,
// ze se jedna o existujici spojeni.
void testZeroCost() {

    Network network = {
        3,
        {
            {0, 1, 0, false},
            {1, 2, 10, false},
            {0, 2, 20, false}
        }
    };

    Result result = buildNetwork(network);

    assert(result.possible);
    assert(result.totalCost == 10);
    assert(result.newConnections.size() == 2);
}


// ================================================
// HLAVNI PROGRAM
// ================================================

int main() {

    testBasicNetwork();
    testCycle();
    testExistingConnections();
    testExistingCycle();
    testDisconnectedNetwork();
    testEqualCosts();
    testCompleteNetwork();
    testSingleBuilding();
    testZeroCost();

    cout << "Vsechny testy prosly." << endl;

    return 0;
}


/*
 * OTAZKY
 * ======
 *
 * 1. Proc lze problem vystavby opticke site resit
 *    pomoci minimalni kostry grafu?
 *
 * 2. Popiste princip algoritmu, ktery jste pouzili.
 *    Vysvetlete, proc vede k optimalnimu reseni.
 *
 * 3. Jakym zpusobem vas algoritmus zjistuje,
 *    zda by pridanim noveho spojeni vznikl cyklus?
 *
 * 4. Jak jste upravili algoritmus, aby zohlednoval
 *    jiz existujici infrastrukturu?
 *
 * 5. Kolik novych spojeni je nutne vybudovat,
 *    pokud existujici infrastruktura tvori
 *    k vzajemne nepropojenych komponent?
 *
 * 6. Jak algoritmus zjisti, ze vsechny budovy
 *    nelze propojit?
 *
 * 7. Jaka je casova a pametova slozitost vaseho
 *    reseni? Vyjadrete ji v zavislosti na poctu
 *    budov V a poctu moznych spojeni E.
 *    Zduvodnete slozitost jednotlivych operaci.
 *
 * 8. Muze pro stejna vstupni data existovat vice
 *    ruznych optimalnich reseni? Uvedte priklad.
 *
 * 9. Zarucuje vysledna sit take nejkratsi cestu
 *    mezi libovolnymi dvema budovami?
 *    Vysvetlete proc.
 *
 * 10. Co se stane, pokud dojde k poruse nektereho
 *     nove vybudovaneho spojeni? Bude sit nadale
 *     funkcni? 
 */
