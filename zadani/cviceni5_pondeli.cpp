/*
 * ALGORITMY II – CVICENI 5 (varianta: Tri nadoby)
 * Tema: Prevod problemu na graf stavu a BFS 
 *
 * ZADANI
 * Mate tri nadoby s kapacitami 8, 5 a 3 litry. Na zacatku je
 * prvni nadoba plna, zbyvajici jsou prazdne: (8, 0, 0).
 * Cilem je dosahnout stavu (4, 4, 0) s nejmensim poctem preliti.
 *
 * Pravidla:
 *  - Vodu lze prelevat mezi libovolnymi dvema ruznymi nadobami.
 *  - Nelze vodu doplnovat ani vylevat mimo nadoby.
 *  - Pri preliti se prevede maximalni mozne mnozstvi: az do
 *    vyprazdneni zdroje nebo naplneni cile.
 *  - Kazde preliti ma cenu 1. 
 *
 * UKOLY: .
 *  1. Doplnte isValid a generateNeighbors.
 *  2. Doplnte BFS vcetne evidence visited a rekonstrukce cesty.
 *  3. Doplnte printState a printSolution.
 *  4. Overte testy.
 *
 * OCEKAVANE CHOVANI:
 *  - bfs vrati posloupnost stavu vcetne pocatecniho a ciloveho.
 *  - Pokud cesta neexistuje, vrati prazdny vektor.
 *  - Pokud start == goal, vrati vektor s jedinym stavem.
 *  - Nemenit stav predany do generateNeighbors.
 */

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct Problem {
    array<int, 3> capacity;
    int totalWater;
};

using State = array<int, 3>;

// UKOL 1: Vratte true, pokud kazdy objem lezi v rozsahu
// 0..capacity[i] a soucet objemu odpovida totalWater.
bool isValid(State& state, Problem& p) {
    // TODO
    return false;
}

// UKOL 2: Vratte vsechny ruzne stavy dosazitelne JEDNIM
// platnym prelitim. Uvazujte vsech 6 usporadanych dvojic nadob.
// Preskocite preliti, pri nemz se neprevede zadna voda.
vector<State> generateNeighbors(State& state,Problem& p) {
    // TODO    
    return {};
}

// UKOL 3: BFS nad implicitnim grafem.
// Pouzijte queue, visited a parent (nebo jinou rekonstrukci cesty).
// Pozor: start i goal musi byt platne stavy.
vector<State> bfs(Problem& p, State& start, State& goal) {
    // TODO    
    return {};
}

// UKOL 4a: Vypiste stav ve formatu (A, B, C).
void printState(State& state) {
    // TODO    
}

// UKOL 4b: Vypiste stavy cesty a pocet preliti.
// Pro prazdnou cestu vypiste informaci, ze reseni neexistuje.
void printSolution(vector<State>& path) {
    // TODO    
}

int main() {
    // Hlavni problem
    const Problem p{{8, 5, 3}, 8};
    const State start{8, 0, 0};
    const State goal{4, 4, 0};

    const auto path = bfs(p, start, goal);
    printSolution(path);

    const Problem impossible{{6, 4, 2}, 6};
    const auto impossiblePath = bfs(impossible, State{6, 0, 0}, State{3, 3, 0});
    printSolution(impossiblePath);

    return 0;
}