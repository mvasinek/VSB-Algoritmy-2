#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

// ALGORITMY II - Hashovaci tabulka a LRU cache
//
// Ukol:
// 1. Implementujte hashovaci funkci hash().
// 2. Zvolte oddelene retezeni NEBO otevrene adresovani (linearni sondovani).
// 3. Implementujte insert(), find() a erase().
//
// Nepouzivejte std::hash, std::map ani std::unordered_map.
// Vsechny velikosti a indexy reprezentujte typem int.

class HashTable {
public:
    // Hodnotou v tabulce je pozice stranky v seznamu LRU cache.
    typedef list<string>::iterator Position;

    HashTable(int size) {
        tableSize = size;
        // TODO: Inicializujte vlastni datovou strukturu pro tabulku.
    }

    // Vrati index v rozsahu 0 az tableSize - 1.
    int hash(string url) {
        // TODO: Implementujte vlastni hashovaci funkci.
        return 0;
    }

    // Vlozi dvojici (URL, pozice v seznamu).
    // Vrati true pri uspechu, false pokud URL jiz existuje.
    bool insert(string url, Position position) {
        // TODO: Implementujte vlozeni vcetne reseni kolizi.
        return false;
    }

    // Vrati ukazatel na ulozenou pozici, pokud URL existuje.
    // Jinak vrati nullptr.
    Position* find(string url) {
        // TODO: Implementujte vyhledavani.
        return nullptr;
    }

    // Odstrani URL z tabulky. Vrati true, pokud existovala.
    bool erase(string url) {
        // TODO: Implementujte odstraneni.
        return false;
    }

private:
    int tableSize;

    // TODO: Zvolte a deklarujte vlastni uloziste zaznamu.
    // Jeden zaznam obsahuje klic (string URL) a hodnotu (Position).
    //
    // Retezeni: na kazdem indexu muze byt vice zaznamu.
    // Otevrene adresovani: zaznamy jsou primo v poli; pri kolizi
    // hledejte dalsi pozici. Pri mazani osetrete smazana mista.
};

// HOTOVA CAST - tuto tridu nemente.
// Stranky jsou v seznamu od nejdele nepouzite po nejnovejsi.
class LRUCache {
public:
    LRUCache(int capacity, int tableSize) : index(tableSize) {
        this->capacity = capacity;
    }

    // true = stranka byla v cache (HIT), false = nebyla (MISS).
    bool visit(string url) {
        HashTable::Position* found = index.find(url);

        if (found != nullptr) {
            // Presun existujici stranky na konec seznamu.
            pages.splice(pages.end(), pages, *found);
            return true;
        }

        // Je-li cache plna, odstranime nejdele nepouzitou stranku.
        if ((int)pages.size() == capacity) {
            string oldest = pages.front();
            bool removed = index.erase(oldest);
            assert(removed);
            pages.pop_front();
        }

        // Nova stranka se vlozi na konec seznamu.
        pages.push_back(url);
        HashTable::Position position = pages.end();
        --position;
        bool inserted = index.insert(url, position);
        assert(inserted);
        return false;
    }

    // Vrati aktualni poradi stranek pro testovani.
    vector<string> snapshot() {
        vector<string> result;
        for (string url : pages) {
            result.push_back(url);
        }
        return result;
    }

    void print() {
        cout << "LRU [";
        bool first = true;
        for (string url : pages) {
            if (!first) cout << ", ";
            cout << url;
            first = false;
        }
        cout << "] MRU" << endl;
    }

private:
    int capacity;
    list<string> pages;
    HashTable index;
};

int main() {
    LRUCache cache(3, 7);  // kapacita cache = 3, velikost tabulky = 7

    assert(cache.visit("a.cz") == false);
    assert(cache.visit("b.cz") == false);
    assert(cache.visit("c.cz") == false);
    assert(cache.visit("a.cz") == true);
    assert(cache.visit("d.cz") == false);
    assert(cache.visit("b.cz") == false);

    vector<string> expected = {"a.cz", "d.cz", "b.cz"};
    assert(cache.snapshot() == expected);
    cache.print();

    return 0;
}

/*
OTAZKY K ZADANI

Odpovezte strucne a sve odpovedi oduvodnete.

1. Jak vase hashovaci funkce prevadi webovou adresu na index tabulky?
   Proc musi byt vysledny index v rozsahu 0 az tableSize - 1?

2. Co je kolize v hashovaci tabulce?

3. Jak vase implementace resi kolize? Popiste postup pri vkladani
   a vyhledavani, pokud na danem indexu uz existuje jiny zaznam.

4. Co se stane, kdyz odstranite zaznam, se kterym kolidoval
   jiny zaznam? Jak zajistite, ze druhy zaznam zustane vyhledatelny?

5. Jaka je ocekavana casova slozitost operaci insert(), find()
   a erase()? Jaka muze byt jejich slozitost v nejhorsim pripade?

6. Jak ovlivnuje velikost hashovaci tabulky pocet kolizi?
   Co se muze stat, kdyz je tabulka prilis mala?
*/
