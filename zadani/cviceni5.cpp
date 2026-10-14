
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Problem {
    vector<string> objects;
    vector<pair<int, int>> conflicts;
};

using State = int;

// Overi, zda zadna konfliktni dvojice
// nezustala bez operatora na stejnem brehu.
bool isValid(State state, const Problem& p) {    
}

// Vygeneruje vsechny platne stavy,
// kterych lze dosahnout jednim prevozem.
vector<State> generateNeighbors(State state,
                                const Problem& p) {
    vector<State> neighbors;

    return neighbors;
}

// BFS vraci nejkratsi posloupnost stavu.
// Prazdny vektor znamena, ze cesta neexistuje.
vector<State> bfs(const Problem& p,
                  State start,
                  State goal) {
    
}

void printState(State state, const Problem& p) {
    
}

void printSolution(const vector<State>& path,
                   const Problem& p) {    
}

int main() {
    // Klasicky problem: vlk, koza, zeli
    Problem p{
        {"vlk", "koza", "zeli"},
        {{0, 1}, {1, 2}}
    };

    // Zadny konflikt: operator muze prevazet
    // objekty postupne.
    Problem noConflicts{
        {"A", "B"},
        {}
    };    

    // Vsechny dvojice konfliktni:
    // se tremi objekty a kapacitou jeden
    // reseni neexistuje.
    Problem impossible{
        {"A", "B", "C"},
        {{0, 1}, {0, 2}, {1, 2}}
    };    
}
