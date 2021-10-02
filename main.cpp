#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;

class ElfVillage {
public:
    ElfVillage() {
        for (int numTree = 0; numTree < 5; ++numTree) {
            int quantityBigBranch = 3 + rand() % 3;
            for (int numBigBranch = 0; numBigBranch < quantityBigBranch; ++numBigBranch) {
                int quantityMediumBranch = 2 + rand() % 2;
                houses.push_back({numTree, numBigBranch});
                for (int numMediumBranch = 0; numMediumBranch < quantityMediumBranch; ++numMediumBranch) {
                    houses.push_back({numTree, numBigBranch, numMediumBranch});
                }
            }
        }
    }

    void EnterResidents() {
        CountNeighbors.clear();
        string in_str;
        for (int i = 0; i < houses.size(); ++i) {
            cout << "Enter of resident: ";
            cin >> in_str;
            if (in_str == "None")continue;
            houses[i].resident = in_str;
            //Предполагается что каждое имя уникально
            CountNeighbors[{houses[i].numTree, houses[i].numBigBranch}]++;
            residents.insert({in_str, Branch{houses[i].numTree, houses[i].numBigBranch}});
        }
    }

    int RequestQuantityNeighbors(const string& name) {
        auto it = residents.find(name);
        if (it == residents.end())return 0;
        return CountNeighbors[it->second];
    }

private:
    class Branch {
    public:
        int numTree;
        int numBigBranch;

        bool operator<(const Branch& other) const {
            if (this->numTree != other.numTree)return this->numTree < other.numTree;
            return this->numBigBranch < other.numBigBranch;
        }

        bool operator==(const Branch& other) const {
            return this->numTree == other.numTree && this->numBigBranch == other.numBigBranch;
        }
    };

    struct House {
        int numTree;
        int numBigBranch;
        int numMediumBranch = -1;
        string resident;
    };

    vector<House> houses;
    map<Branch, int> CountNeighbors;
    map<string, Branch> residents;

};

int main() {
    ElfVillage elfVillage;
    elfVillage.EnterResidents();
    string name;
    cout << "Enter name of elf for search: ";
    cin >> name;
    cout << "Quantity of elves living with " << name << " on one big branch: "
         << elfVillage.RequestQuantityNeighbors(name);
    return 0;
}
