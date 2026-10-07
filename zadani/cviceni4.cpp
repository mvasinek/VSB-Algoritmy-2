#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

// ============================================================
// ALGORITMY II
// Hornerovo schéma + prioritní fronta implementovaná haldou
// ============================================================
//
// CÍL ÚLOHY
//
// 1. Implementovat Hornerovo schéma pro výpočet hodnoty polynomu.
// 2. Doplnit pravidlo pro porovnání priorit dvou procesů.
// 3. Použít dodanou maximovou haldu jako prioritní frontu a doplnit implementace funkci max a extractMax.
// 4. Pomocí prioritní fronty simulovat jednoduchý plánovač procesů.
//
// Každý proces má:
//   - ID,
//   - hodnotu x,
//   - prioritu.
//
// Priorita procesu je určena hodnotou zadaného polynomu P(x).
//
// Scheduler zpracovává tři typy událostí:
//
// ADD id x
//      Přidá nový proces.
//      Priorita procesu se vypočítá jako P(x).
//
// RUN
//      Spustí a odstraní proces s nejvyšší prioritou.
//
// PEEK
//      Zjistí proces s nejvyšší prioritou, ale neodstraní jej.
//
// Pokud mají dva procesy stejnou prioritu,
// přednost má proces s nižším ID.
//
// Pokud je při RUN nebo PEEK fronta prázdná,
// operace se ignoruje.
//
// ============================================================


// ============================================================
// PROCES
// ============================================================

struct Process {
    int id;
    int x;
    int priority;
};


// ============================================================
// MAXIMOVÁ HALDA
//
// Implementaci haldy NEMĚŇTE s výjimkou funkce
// hasHigherPriority(), kterou máte doplnit.
//
// Haldu použijte jako prioritní frontu procesů.
//
// Základní operace:
//
// insert(process)  - vložení procesu
// max()            - získání procesu s nejvyšší prioritou
// extractMax()     - TODO: získání a odstranění procesu
// empty()          - TODO: test prázdné fronty
// size()           - počet procesů
//
// ============================================================

class MaxHeap {
private:

    std::vector<Process> heap;


    // ========================================================
    // ÚLOHA 1
    // POROVNÁNÍ PRIORIT,MAX a EXTRACTMAX
    // ========================================================
    //
    // Porovnání priorit:
    //
    // Funkce vrací true, pokud má proces a vyšší prioritu
    // než proces b.
    //
    // Pravidla:
    //
    // 1. Proces s vyšší hodnotou priority má přednost.
    //
    // 2. Pokud mají oba procesy stejnou hodnotu priority,
    //    má přednost proces s nižším ID.
    //
    // Příklady:
    //
    // a.priority = 20
    // b.priority = 10
    //
    // -> a má vyšší prioritu
    //
    //
    // a.id = 10, a.priority = 20
    // b.id = 30, b.priority = 20
    //
    // -> a má vyšší prioritu
    //
    // ========================================================

    bool hasHigherPriority(
        const Process& a,
        const Process& b
    ) const {

        // TODO:
        // Implementujte porovnání dvou procesů.

        return false;
    }


    void siftUp(int index) {

        while (index > 0) {

            int parent = (index - 1) / 2;

            if (!hasHigherPriority(
                    heap[index],
                    heap[parent])) {
                break;
            }

            std::swap(
                heap[index],
                heap[parent]
            );

            index = parent;
        }
    }


    void siftDown(int index) {

        int n = static_cast<int>(heap.size());

        while (true) {

            int left = 2 * index + 1;
            int right = 2 * index + 2;

            int highest = index;

            if (
                left < n &&
                hasHigherPriority(
                    heap[left],
                    heap[highest])
            ) {
                highest = left;
            }

            if (
                right < n &&
                hasHigherPriority(
                    heap[right],
                    heap[highest])
            ) {
                highest = right;
            }

            if (highest == index) {
                break;
            }

            std::swap(
                heap[index],
                heap[highest]
            );

            index = highest;
        }
    }


public:

    void insert(const Process& process) {

        heap.push_back(process);

        siftUp(
            static_cast<int>(heap.size()) - 1
        );
    }


    Process extractMax() {

        assert(!heap.empty());

        // TODO:
        //
        // 1. Vyberte kořen haldy.
        // 2. Nahraďte kořen posledním prvkem.
        // 3. Odstraňte poslední prvek.
        // 4. Pokud halda není prázdná,
        //    obnovte její vlastnost pomocí siftDown(0).
        // 5. Vraťte původní kořen.
    }


    const Process& max() const {

        assert(!heap.empty());

        // TODO:
        // Implementujte získání procesu s nejvyšší prioritou.

    }


    bool empty() const {

        return heap.empty();
    }


    int size() const {

        return static_cast<int>(heap.size());
    }
};


// ============================================================
// ÚLOHA 2
// HORNEROVO SCHÉMA
// ============================================================
//
// Implementujte výpočet hodnoty polynomu pomocí
// Hornerova schématu.
//
// Koeficienty jsou zadány od nejvyšší mocniny.
//
// Například:
//
// P(x) = -x^3 + 9x^2 - 15x + 20
//
// je reprezentován vektorem:
//
// {-1, 9, -15, 20}
//
// Hornerovo schéma odpovídá zápisu:
//
// ((-1 * x + 9) * x - 15) * x + 20
//
// Nepoužívejte:
//   - pow()
//   - explicitní výpočet jednotlivých mocnin x
//
// ============================================================

int horner(
    const std::vector<int>& coefficients,
    int x
) {

    // TODO:
    // Implementujte Hornerovo schéma.

    return 0;
}


// ============================================================
// UDÁLOSTI SCHEDULERU
// ============================================================

enum class EventType {
    ADD,
    RUN,
    PEEK
};


struct Event {

    EventType type;

    // Používá se pouze u ADD.
    int id = 0;
    int x = 0;

    Event(EventType type, int id = 0, int x = 0)
        : type(type), id(id), x(x) {
    }
};


// ============================================================
// VÝSLEDEK SIMULACE
// ============================================================

struct SchedulerResult {

    // ID procesů v pořadí, v jakém byly spuštěny.
    std::vector<int> executedProcesses;

    // ID procesů, které byly vráceny operací PEEK.
    std::vector<int> peekedProcesses;

    // Celkový počet přidaných procesů.
    int addedProcesses = 0;

    // Celkový počet skutečně spuštěných procesů.
    int executedProcessesCount = 0;

    // Největší počet procesů, který byl současně ve frontě.
    int maximumQueueSize = 0;

    // Počet procesů, které zůstaly po skončení simulace.
    int remainingProcesses = 0;
};


// ============================================================
// ÚLOHA 3
// SCHEDULER
// ============================================================
//
// Implementujte zpracování událostí.
//
// ------------------------------------------------------------
// ADD
// ------------------------------------------------------------
//
// 1. Pomocí funkce horner() vypočítejte prioritu procesu.
// 2. Vytvořte Process.
// 3. Vložte proces do priorityQueue.
// 4. Zvyšte addedProcesses.
// 5. Aktualizujte maximumQueueSize.
//
// ------------------------------------------------------------
// RUN
// ------------------------------------------------------------
//
// Pokud fronta není prázdná:
//
// 1. Odeberte proces s nejvyšší prioritou.
// 2. Jeho ID vložte do executedProcesses.
// 3. Zvyšte executedProcessesCount.
//
// ------------------------------------------------------------
// PEEK
// ------------------------------------------------------------
//
// Pokud fronta není prázdná:
//
// 1. Zjistěte proces s nejvyšší prioritou.
// 2. Proces NEODSTRAŇUJTE.
// 3. Jeho ID vložte do peekedProcesses.
//
// ------------------------------------------------------------
//
// Na konci nastavte remainingProcesses.
//
// Použijte výhradně dodanou implementaci MaxHeap.
// Nepoužívejte std::priority_queue.
//
// ============================================================

SchedulerResult processEvents(
    const std::vector<Event>& events,
    const std::vector<int>& coefficients
) {

    MaxHeap priorityQueue;

    SchedulerResult result;

    // TODO:
    // Implementujte zpracování událostí.


    // TODO:
    // Uložte počet procesů, které zůstaly ve frontě.


    return result;
}


// ============================================================
// TEST 1
// HORNEROVO SCHÉMA
// ============================================================

void testHorner() {

    // P(x) = -x^3 + 9x^2 - 15x + 20

    std::vector<int> coefficients = {
        -1, 9, -15, 20
    };


    assert(horner(coefficients, 0) == 20);
    assert(horner(coefficients, 1) == 13);
    assert(horner(coefficients, 2) == 18);
    assert(horner(coefficients, 3) == 29);
    assert(horner(coefficients, 4) == 40);
    assert(horner(coefficients, 5) == 45);


    std::cout
        << "Horner tests passed."
        << std::endl;
}


// ============================================================
// TEST 2
// POROVNÁNÍ PRIORIT
// ============================================================

void testPriorityComparison() {

    {
        MaxHeap heap;

        // Proces 20 má prioritu 10.
        heap.insert({20, 0, 10});

        // Proces 30 má prioritu 20.
        heap.insert({30, 0, 20});

        // Vyšší priorita má přednost.
        assert(heap.extractMax().id == 30);
        assert(heap.extractMax().id == 20);
    }


    {
        MaxHeap heap;

        // Oba procesy mají stejnou prioritu.
        heap.insert({20, 0, 10});
        heap.insert({10, 0, 10});

        // Při stejné prioritě má přednost nižší ID.
        assert(heap.extractMax().id == 10);
        assert(heap.extractMax().id == 20);
    }


    std::cout
        << "Priority comparison tests passed."
        << std::endl;
}


// ============================================================
// TEST 3
// SCHEDULER
// ============================================================

void testScheduler() {

    // P(x) = -x^3 + 9x^2 - 15x + 20

    std::vector<int> coefficients = {
        -1, 9, -15, 20
    };


    std::vector<Event> events = {

        // P(1) = 13
        {EventType::ADD, 101, 1},

        // P(3) = 29
        {EventType::ADD, 102, 3},

        // Nejvyšší priorita: 102
        {EventType::PEEK},

        // Spustí se 102.
        {EventType::RUN},

        // P(5) = 45
        {EventType::ADD, 103, 5},

        // P(2) = 18
        {EventType::ADD, 104, 2},

        // Nejvyšší priorita: 103
        {EventType::PEEK},

        // P(4) = 40
        {EventType::ADD, 105, 4},

        // Spustí se 103.
        {EventType::RUN},

        // Nejvyšší priorita: 105
        {EventType::PEEK},

        // Spustí se 105.
        {EventType::RUN},

        // Spustí se 104.
        {EventType::RUN},

        // Spustí se 101.
        {EventType::RUN}
    };


    SchedulerResult result =
        processEvents(
            events,
            coefficients
        );


    std::vector<int> expectedExecuted = {
        102,
        103,
        105,
        104,
        101
    };

    assert(
        result.executedProcesses ==
        expectedExecuted
    );


    std::vector<int> expectedPeeked = {
        102,
        103,
        105
    };

    assert(
        result.peekedProcesses ==
        expectedPeeked
    );


    assert(result.addedProcesses == 5);
    assert(result.executedProcessesCount == 5);
    assert(result.maximumQueueSize == 4);
    assert(result.remainingProcesses == 0);


    std::cout
        << "Scheduler tests passed."
        << std::endl;
}


// ============================================================
// TEST 4
// PRÁZDNÁ PRIORITNÍ FRONTA
// ============================================================

void testEmptyQueue() {

    // P(x) = x

    std::vector<int> coefficients = {
        1, 0
    };


    std::vector<Event> events = {

        // Fronta je prázdná.
        {EventType::RUN},

        {EventType::PEEK},

        // priorita = 10
        {EventType::ADD, 100, 10},

        {EventType::RUN},

        // Fronta je opět prázdná.
        {EventType::RUN}
    };


    SchedulerResult result =
        processEvents(
            events,
            coefficients
        );


    assert(
        result.executedProcesses ==
        std::vector<int>{100}
    );

    assert(result.peekedProcesses.empty());

    assert(result.addedProcesses == 1);
    assert(result.executedProcessesCount == 1);
    assert(result.maximumQueueSize == 1);
    assert(result.remainingProcesses == 0);


    std::cout
        << "Empty queue tests passed."
        << std::endl;
}


// ============================================================
// TEST 5
// STEJNÁ PRIORITA
// ============================================================

void testSamePriority() {

    // P(x) = x

    std::vector<int> coefficients = {
        1, 0
    };


    std::vector<Event> events = {

        // Oba procesy mají prioritu 5.

        {EventType::ADD, 20, 5},
        {EventType::ADD, 10, 5},

        {EventType::RUN},
        {EventType::RUN}
    };


    SchedulerResult result =
        processEvents(
            events,
            coefficients
        );


    std::vector<int> expected = {
        10,
        20
    };


    assert(
        result.executedProcesses ==
        expected
    );


    std::cout
        << "Same priority tests passed."
        << std::endl;
}


// ============================================================
// MAIN
// ============================================================

int main() {

    testHorner();

    testPriorityComparison();

    testScheduler();

    testEmptyQueue();

    testSamePriority();


    std::cout
        << "All tests passed."
        << std::endl;


    return 0;
}


/*

============================================================
OTÁZKY
============================================================

------------------------------------------------------------
1. PEEK
------------------------------------------------------------

Jaká je časová složitost operace PEEK u maximové haldy?

Vysvětlete proč.

------------------------------------------------------------
2. RUN
------------------------------------------------------------

Jaká je časová složitost operace RUN?

Vysvětlete, co se při odstranění kořene maximové haldy
musí stát.

------------------------------------------------------------
3. VLASTNOST HALDY
------------------------------------------------------------

Musí být všechny prvky maximové haldy seřazeny
od největšího po nejmenší?

Popište přesně podmínku, která musí v maximové haldě platit.

------------------------------------------------------------
4. HALDA VS. SEŘAZENÉ POLE
------------------------------------------------------------

Scheduler bychom mohli implementovat také pomocí
seřazeného pole.

Porovnejte maximovou haldu a seřazené pole z hlediska:

    a) vložení nového procesu,
    b) získání procesu s nejvyšší prioritou,
    c) odstranění procesu s nejvyšší prioritou.

*/