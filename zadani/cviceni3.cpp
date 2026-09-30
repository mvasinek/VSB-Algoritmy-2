```cpp
/*
===============================================================================
ALGORITMY II

Cvičení: Binární vyhledávací strom vs. AVL strom
Strategie: Transformuj a vyřeš
===============================================================================

CÍL
---

Cílem tohoto cvičení NENÍ implementovat binární vyhledávací strom ani
AVL strom. Obě datové struktury jsou již implementovány níže.

Vaším úkolem je tyto datové struktury POUŽÍT a experimentálně porovnat
jejich chování.

Budeme simulovat systém, který ukládá události (například záznamy logu).
Každá událost má unikátní celočíselnou časovou značku (timestamp).

Porovnáme dvě situace:

    1. CHRONOLOGICKÁ DATA
       Události přicházejí seřazené podle času.

    2. NÁHODNÁ DATA
       Stejné události přicházejí v náhodném pořadí.

Pro obě datové sady vložte přesně stejné časové značky do:

    - standardního binárního vyhledávacího stromu (BST),
    - AVL stromu.

Následně analyzujte vzniklé stromy.


===============================================================================
ÚKOLY
===============================================================================

Doplňujte POUZE část označenou:

    ÚKOL PRO STUDENTA

Neměňte implementace BST ani AVL stromu.


Pro každý experiment proveďte následující kroky:


1. VLOŽENÍ DAT
--------------

Vložte všechny vygenerované časové značky do:

    a) BinarySearchTree
    b) AVLTree


2. VÝŠKA STROMU
---------------

Zjistěte výšku obou stromů.

Zjistěte:

    výšku BST,
    výšku AVL stromu.


3. EXPERIMENT S VYHLEDÁVÁNÍM
-----------------------------

Vyhledejte každou hodnotu obsaženou v datové sadě.

Pro každé vyhledávání spočítejte, kolik uzlů stromu bylo navštíveno.

Vypočítejte:

    - celkový počet navštívených uzlů,
    - průměrný počet navštívených uzlů na jedno vyhledávání,
    - maximální počet navštívených uzlů během jednoho vyhledávání.


4. VÝPIS VÝSLEDKŮ
-----------------

Výsledky vypište přesně v následujícím formátu:

--------------------------------------------------
CHRONOLOGICKÁ DATA
--------------------------------------------------
Počet událostí: 10000

BST
Výška: ...
Celkem navštívených uzlů: ...
Průměr navštívených uzlů: ...
Maximum navštívených uzlů: ...

AVL
Výška: ...
Celkem navštívených uzlů: ...
Průměr navštívených uzlů: ...
Maximum navštívených uzlů: ...


--------------------------------------------------
NÁHODNÁ DATA
--------------------------------------------------
Počet událostí: 10000

BST
Výška: ...
Celkem navštívených uzlů: ...
Průměr navštívených uzlů: ...
Maximum navštívených uzlů: ...

AVL
Výška: ...
Celkem navštívených uzlů: ...
Průměr navštívených uzlů: ...
Maximum navštívených uzlů: ...


===============================================================================
OTÁZKY
===============================================================================

Po spuštění programu odpovězte na následující otázky.

Q1:
Porovnejte výšku BST a AVL stromu pro CHRONOLOGICKÁ DATA.
Vysvětlete pozorovaný rozdíl.

Q2:
Porovnejte průměrný počet navštívených uzlů při vyhledávání v BST a AVL
stromu pro CHRONOLOGICKÁ DATA.
Jak tento počet souvisí s výškou stromu?

Q3:
Porovnejte výsledky pro NÁHODNÁ DATA.
Proč si standardní BST vede lépe než v případě CHRONOLOGICKÝCH DAT?

Q4:
Která z datových struktur je citlivější na pořadí, ve kterém data
přicházejí? Svou odpověď podložte naměřenými výsledky.

Q5:
Na základě naměřených výsledků vysvětlete hlavní výhodu a nevýhodu
použití AVL stromu oproti standardnímu BST.

===============================================================================
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using namespace std;


// ============================================================================
// Binární vyhledávací strom
// ============================================================================

class BinarySearchTree {
private:

    struct Node {
        int key;
        Node* left;
        Node* right;

        explicit Node(int value)
            : key(value), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;


    Node* insert(Node* node, int key)
    {
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);

        return node;
    }


    int height(Node* node) const
    {
        if (node == nullptr)
            return 0;

        return 1 + max(
            height(node->left),
            height(node->right)
        );
    }


    void destroy(Node* node)
    {
        if (node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);

        delete node;
    }


public:

    ~BinarySearchTree()
    {
        destroy(root);
    }


    void insert(int key)
    {
        root = insert(root, key);
    }


    int height() const
    {
        return height(root);
    }


    /*
        Vyhledá zadaný klíč.

        Proměnná visitedNodes obsahuje počet uzlů, které bylo nutné
        během vyhledávání navštívit.

        Příklad:

                  20
                 /  \
                10   30
                    /
                   25

        Při hledání hodnoty 25 navštívíme:

            20 -> 30 -> 25

        tedy:

            visitedNodes = 3
    */
    bool search(int key, int& visitedNodes) const
    {
        visitedNodes = 0;

        Node* current = root;

        while (current != nullptr) {

            visitedNodes++;

            if (key == current->key)
                return true;

            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }

        return false;
    }
};


// ============================================================================
// AVL strom
// ============================================================================

class AVLTree {
private:

    struct Node {
        int key;
        int height;

        Node* left;
        Node* right;

        explicit Node(int value)
            : key(value),
              height(1),
              left(nullptr),
              right(nullptr)
        {
        }
    };


    Node* root = nullptr;


    int nodeHeight(Node* node) const
    {
        if (node == nullptr)
            return 0;

        return node->height;
    }


    int balanceFactor(Node* node) const
    {
        if (node == nullptr)
            return 0;

        return nodeHeight(node->left)
             - nodeHeight(node->right);
    }


    void updateHeight(Node* node)
    {
        node->height =
            1 + max(
                nodeHeight(node->left),
                nodeHeight(node->right)
            );
    }


    Node* rotateRight(Node* y)
    {
        Node* x = y->left;
        Node* subtree = x->right;

        x->right = y;
        y->left = subtree;

        updateHeight(y);
        updateHeight(x);

        return x;
    }


    Node* rotateLeft(Node* x)
    {
        Node* y = x->right;
        Node* subtree = y->left;

        y->left = x;
        x->right = subtree;

        updateHeight(x);
        updateHeight(y);

        return y;
    }


    Node* insert(Node* node, int key)
    {
        // Standardní vložení do BST

        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);

        else if (key > node->key)
            node->right = insert(node->right, key);

        else
            return node;


        // Aktualizace výšky

        updateHeight(node);


        // Kontrola vyvážení

        int balance = balanceFactor(node);


        // Levý-levý případ

        if (balance > 1 &&
            key < node->left->key)
        {
            return rotateRight(node);
        }


        // Pravý-pravý případ

        if (balance < -1 &&
            key > node->right->key)
        {
            return rotateLeft(node);
        }


        // Levý-pravý případ

        if (balance > 1 &&
            key > node->left->key)
        {
            node->left =
                rotateLeft(node->left);

            return rotateRight(node);
        }


        // Pravý-levý případ

        if (balance < -1 &&
            key < node->right->key)
        {
            node->right =
                rotateRight(node->right);

            return rotateLeft(node);
        }


        return node;
    }


    void destroy(Node* node)
    {
        if (node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);

        delete node;
    }


public:

    ~AVLTree()
    {
        destroy(root);
    }


    void insert(int key)
    {
        root = insert(root, key);
    }


    int height() const
    {
        if (root == nullptr)
            return 0;

        return root->height;
    }


    bool search(int key, int& visitedNodes) const
    {
        visitedNodes = 0;

        Node* current = root;

        while (current != nullptr) {

            visitedNodes++;

            if (key == current->key)
                return true;

            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }

        return false;
    }
};


// ============================================================================
// Generování datových sad
// ============================================================================

vector<int> generateChronologicalData(int count)
{
    vector<int> data(count);

    /*
        Použijeme časové značky:

            100001
            100002
            100003
            ...

        Jejich konkrétní hodnoty nejsou důležité.
        Důležité je jejich pořadí.
    */

    iota(data.begin(), data.end(), 100001);

    return data;
}


vector<int> generateRandomData(int count)
{
    vector<int> data =
        generateChronologicalData(count);

    /*
        Pevně nastavený seed znamená, že všichni studenti dostanou
        stejnou datovou sadu a experiment je reprodukovatelný.
    */

    mt19937 generator(42);

    shuffle(
        data.begin(),
        data.end(),
        generator
    );

    return data;
}


// ============================================================================
// Výsledky
// ============================================================================

struct SearchStatistics {

    long long totalVisited = 0;

    double averageVisited = 0.0;

    int maximumVisited = 0;
};


struct ExperimentResults {

    int numberOfEvents = 0;

    int bstHeight = 0;
    int avlHeight = 0;

    SearchStatistics bstSearch;
    SearchStatistics avlSearch;
};


// ============================================================================
// ÚKOL PRO STUDENTA
// ============================================================================


/*
    ÚKOL 1

    Implementujte tuto funkci.

    Vyhledejte v "tree" KAŽDOU hodnotu z vektoru "data".

    Pro každé vyhledávání zjistěte počet navštívených uzlů.

    Vypočítejte:

        totalVisited
        averageVisited
        maximumVisited

    Všechny hodnoty z "data" jsou ve stromu zaručeně přítomny.
*/

template<typename Tree>
SearchStatistics analyseSearch(
    const Tree& tree,
    const vector<int>& data)
{
    SearchStatistics statistics;

    // TODO:
    //
    // 1. Vyhledejte každý klíč z data.
    //
    // 2. Pro každé vyhledávání zjistěte visitedNodes.
    //
    // 3. Přičtěte visitedNodes k totalVisited.
    //
    // 4. Aktualizujte maximumVisited.
    //
    // 5. Vypočítejte averageVisited.
    //
    // DŮLEŽITÉ:
    //
    // averageVisited musí obsahovat průměrný počet navštívených
    // uzlů stromu NA JEDNO VYHLEDÁVÁNÍ.


    return statistics;
}


/*
    ÚKOL 2

    Implementujte celý experiment.

    Postup:

        1. Vytvořte BST.
        2. Vytvořte AVL strom.

        3. Vložte VŠECHNY hodnoty z data do BST.
        4. Vložte VŠECHNY hodnoty z data do AVL stromu.

        5. Uložte počet událostí.

        6. Zjistěte výšku BST.
        7. Zjistěte výšku AVL stromu.

        8. Analyzujte vyhledávání v BST pomocí analyseSearch().
        9. Analyzujte vyhledávání v AVL pomocí analyseSearch().

       10. Vraťte všechny výsledky.

    DŮLEŽITÉ:

    Hodnoty vkládejte PŘESNĚ v tom pořadí, v jakém se nacházejí
    ve vektoru "data".
*/

ExperimentResults runExperiment(
    const vector<int>& data)
{
    ExperimentResults results;

    // TODO


    return results;
}


/*
    ÚKOL 3

    Vypište výsledky PŘESNĚ ve formátu uvedeném v zadání.

    Průměr vypište na DVĚ desetinná místa.

    Příklad:

        Průměr navštívených uzlů: 13.45
*/

void printResults(
    const string& name,
    const ExperimentResults& results)
{
    // TODO
}


// ============================================================================
// Hlavní program
// ============================================================================

int main()
{
    const int NUMBER_OF_EVENTS = 10000;


    // ------------------------------------------------------------------------
    // Vygenerování datových sad
    // ------------------------------------------------------------------------

    vector<int> chronological =
        generateChronologicalData(NUMBER_OF_EVENTS);

    vector<int> random =
        generateRandomData(NUMBER_OF_EVENTS);


    // ------------------------------------------------------------------------
    // Provedení experimentů
    // ------------------------------------------------------------------------

    ExperimentResults chronologicalResults =
        runExperiment(chronological);

    ExperimentResults randomResults =
        runExperiment(random);


    // ------------------------------------------------------------------------
    // Výpis výsledků
    // ------------------------------------------------------------------------

    printResults(
        "CHRONOLOGICKÁ DATA",
        chronologicalResults
    );

    printResults(
        "NÁHODNÁ DATA",
        randomResults
    );


    return 0;
}


/*
===============================================================================
CO ODEVZDAT
===============================================================================

Odevzdejte:

1. Doplněný zdrojový kód.

2. Výstup vytvořený programem pro:

       NUMBER_OF_EVENTS = 10000

3. Odpovědi na otázky Q1-Q5 uvedené na začátku souboru.


NEODEVZDÁVEJTE pouze zdrojový kód.

Naměřené výsledky a jejich interpretace jsou podstatnou součástí
tohoto cvičení.
===============================================================================
*/
```