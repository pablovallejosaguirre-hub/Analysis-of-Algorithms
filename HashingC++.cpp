#include <iostream>

// Structure to hold individual entries and track their occupation status
struct HashEntry
{
    int key;
    bool isOccupied;

    HashEntry() {
        key = 0;
        isOccupied = false;
    }
};

class HashTable
{
private:
    HashEntry* table;
    int capacity;
    int currentSize;

    // Primary hash function using the division method
    int hashFunction(int key)
    {
        // Ensures positive index even if key is negative
        int index = key % capacity;
        return (index < 0) ? (index + capacity) : index;
    }

public:
    HashTable(int cap)
    {
        capacity = cap;
        currentSize = 0;
        table = new HashEntry[capacity]; // Custom memory allocation
    }

    ~HashTable()
    {
        delete[] table;
    }

    bool insert(int key)
    {
        if (currentSize == capacity)
        {
            std::cout << "Table is at maximum capacity. Cannot insert " << key << ".\n";
            return false;
        }

        int index = hashFunction(key);

        // Linear probing to resolve collisions in closed hashing
        while (table[index].isOccupied)
        {
            if (table[index].key == key)
            {
                std::cout << "Duplicate key " << key << " rejected.\n";
                return false;
            }
            // Move to the next slot, wrapping around to the beginning if necessary
            index = (index + 1) % capacity;
        }

        table[index].key = key;
        table[index].isOccupied = true;
        currentSize++;
        return true;
    }

    bool search(int key)
    {
        int index = hashFunction(key);
        int startIndex = index;

        while (table[index].isOccupied)
        {
            if (table[index].key == key)
            {
                return true; // Key found
            }
            index = (index + 1) % capacity;

            // If we loop back to the initial index, the key does not exist
            if (index == startIndex) break;
        }
        return false;
    }

    void show() {
        for (int i = 0; i < capacity; i++)
        {
            if (table[i].isOccupied) std::cout << "Slot " << i << ": " << table[i].key << "\n";
            else std::cout << "Slot " << i << ": [Empty]\n";
        }
    }
};

int main() {
    // Initialize hash table with a prime number
    HashTable ht(7);

    // 10 % 7 = 3
    ht.insert(10);
    // 24 % 7 = 3 (Collision triggers, moves to slot 4)
    ht.insert(24);
    // 17 % 7 = 3 (Collision, slot 3 and 4 full, moves to slot 5)
    ht.insert(17);
    // 30 % 7 = 2
    ht.insert(30);

    ht.show();

    std::cout << "\nSearch for 24: " << (ht.search(24) ? "Found" : "Not Found") << "\n";
    std::cout << "Search for 99: " << (ht.search(99) ? "Found" : "Not Found") << "\n";

    return 0;
}
