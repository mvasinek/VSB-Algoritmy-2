/*
 * ALGORITMY II – CVICENI 8
 * Optimalizace smeny kryptomen (Floyd-Warshalluv algoritmus)
 *
 * ZADANI
 * Smenarna nabizi orientovane smeny mezi menami. Kurz r znamena,
 * ze za 1 jednotku vychozi meny ziskame r jednotek cilove meny.
 * Ne vsechny smeny jsou dostupne a opacny smer muze mit jiny kurz.
 *
 * Ukoly:
 * 1. Prevedte problem na ohodnoceny orientovany graf. Doplnte
 *    buildGraph(): sestavte matici vah a matici nasledniku.
 * 2. Implementujte floydWarshall() pro nejvyhodnejsi smeny
 *    mezi vsemi dvojicemi men.
 * 3. Implementujte findBestExchange(): vratte optimalni kurz
 *    a posloupnost men (pokud existuje konecne optimum).
 * 4. Implementujte hasArbitrage(): zjistete, zda existuje
 *    vyhodny uzavreny sled smen.
 *
 * NAPOVEDA
 * Floyd-Warshall minimalizuje SOUCET vah hran, zatimco pri
 * postupne smene se kurzy NASOBI. Hledejte matematickou
 * transformaci, ktera prevede nasobeni na scitani a maximalizaci
 * soucinu na minimalizaci souctu.
 *
 * Predpoklady: kurzy jsou kladne, poplatky jsou jiz zahrnuty
 * v kurzech. Pouzivejte double; pro porovnani realnych cisel
 * malou toleranci EPS. Pokud je graf arbitrazni, nerekonstruujte
 * optimalni cestu (nemusi existovat konecne optimum).
 *
 * OTÁZKY K OBHAJOBE
 * 1. Co predstavuji vrcholy, orientovane hrany a jejich vahy?
 * 2. Proc nelze primo minimalizovat soucet smennych kurzu?
 * 3. Jak funguje vase transformace a jeji zpetny prevod?
 * 4. Proc je vnejsi smycka algoritmu vedena pres vrchol k?
 * 5. Jakou casovou a pametovou slozitost maji vase funkce?
 * 6. Jak rekonstruujete posloupnost smen?
 * 7. Jak poznate arbitraz a co znamena pro optimalni cestu?
 * 8. Jak byste zapocitali procentualni poplatek za kazdou smenu?
 */

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const double INF = 1e100;
const double EPS = 1e-9;

struct Exchange {
    int from;
    int to;
    double rate;
};

struct Graph {
    vector<vector<double>> dist;
    vector<vector<int>> next;
};

struct Result {
    bool reachable;
    double rate;
    vector<int> path;
};

// Sestavte graf. dist[i][j] je transformovana vaha,
// next[i][j] je nasledujici vrchol na ceste z i do j.
Graph buildGraph(int n, const vector<Exchange>& exchanges) {
    Graph g;
    // TODO
    return g;
}

// Aktualizujte dist i next pri nalezeni lepsi cesty.
void floydWarshall(Graph& g) {
    // TODO
}

// Volat pouze pro graf BEZ arbitraze.
// Pro nedostupnou cestu vratte Result.reachable=false.
Result findBestExchange(const Graph& g, int from, int to) {
    Result result = {false, 0.0, {}};
    // TODO
    return result;
}

// Detekce zaporneho cyklu z matice po Floyd-Warshallovi.
bool hasArbitrage(const Graph& g) {
    // TODO
    return false;
}

bool nearlyEqual(double a, double b) {
    return fabs(a - b) <= EPS * (1.0 + fabs(b));
}

void testDirectAndIndirect() {
    // Zadna arbitraz: kurzy odpovidaji konzistentnim relativnim cenam.
    vector<Exchange> rates = {
        {0, 1, 0.00012},  // CZK -> LTC
        {1, 2, 0.0027},   // LTC -> BTC
        {0, 2, 0.00030}  // CZK -> BTC (mene vyhodne)
    };
    Graph g = buildGraph(3, rates);
    floydWarshall(g);
    assert(!hasArbitrage(g));
    Result r = findBestExchange(g, 0, 2);
    assert(r.reachable);
    assert(nearlyEqual(r.rate, 0.00012 * 0.0027));
    assert((r.path == vector<int>{0, 1, 2}));
    assert(!findBestExchange(g, 2, 0).reachable);
}

void testSelfAndDisconnected() {
    vector<Exchange> rates = {{0, 1, 2.0}};
    Graph g = buildGraph(3, rates);
    floydWarshall(g);
    assert(!hasArbitrage(g));
    Result same = findBestExchange(g, 1, 1);
    assert(same.reachable);
    assert(nearlyEqual(same.rate, 1.0));
    assert((same.path == vector<int>{1}));
    assert(!findBestExchange(g, 0, 2).reachable);
}

void testArbitrage() {
    vector<Exchange> rates = {
        {0, 1, 2.0},
        {1, 2, 3.0},
        {2, 0, 0.2} // soucin = 1.2 > 1
    };
    Graph g = buildGraph(3, rates);
    floydWarshall(g);
    assert(hasArbitrage(g));
    // Pri arbitrazi se optimalni cesty v tomto testu nevyhledavaji.
}

int main() {
    testDirectAndIndirect();
    testSelfAndDisconnected();
    testArbitrage();
    cout << "Vsechny testy prosly.\n";
    return 0;
}
