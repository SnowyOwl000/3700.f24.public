#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include "treapDictionary.h"

using namespace std;

#define REPI(ctr,start,limit) for (uint32_t ctr=(start);(ctr)<(limit);(ctr)++)
#define OPF(b) ((b)?"pass":"fail")

const uint32_t
    DEFAULT_NUM_DICTIONARIES = 4,
    DEFAULT_NUM_ENTRIES = 4096,
    STRING_LENGTH = 8,
    TEST_NAME_WIDTH = 16;

uint32_t
    nDictionaries = DEFAULT_NUM_DICTIONARIES,
    nEntries = DEFAULT_NUM_ENTRIES;

int main(int argc,char *argv[]) {
    random_device
        rd;
    mt19937
        mt(rd());
    uniform_int_distribution<>
        dis(0,25);
    TreapDictionary<uint32_t,string>
        *dictionaries;
    vector<pair<uint32_t,string>>
        *rawData,*sortedData;
    pair<uint32_t,string>
        entry;
    bool
        okay;

    // process command-line arguments
    REPI(i,1,argc) {
        // argument must start with -
        if (argv[i][0] != '-')
            continue;

        // d = number of dictionaries to create
        if (argv[i][1] == 'd')
            nDictionaries = strtol(argv[i]+2, nullptr,10);

        // e = number of entries to create per dictionary
        if (argv[i][1] == 'e')
            nEntries = strtol(argv[i]+2, nullptr,10);
    }

    cout << "Dictionaries: " << nDictionaries << endl;
    cout << "Entries per dictionary: " << nEntries << endl;

    // create dictionaries
    dictionaries = new TreapDictionary<uint32_t,string>[nDictionaries];

    cout << "Please stand by" << endl;

    // create random keys and values, use pairs
    rawData = new vector<pair<uint32_t,string>>[nDictionaries];
    sortedData = new vector<pair<uint32_t,string>>[nDictionaries];
    REPI(i,0,nDictionaries) {
        REPI(j,0,nEntries) {
            entry.first = mt();
            entry.second.clear();
            REPI(k,0,STRING_LENGTH)
                entry.second += "abcdefghijklmnopqrstuvwxyz"[dis(mt)];
            rawData[i].push_back(entry);
            sortedData[i].push_back(entry);
        }
    }

    // create lists sorted by key
    REPI(i,0,nDictionaries)
        sort(sortedData[i].begin(),sortedData[i].end());

    // verify empty and size
    okay = true;
    REPI(i,0,nDictionaries)
        if (!dictionaries[i].isEmpty())
            okay = false;
    cout << setw(TEST_NAME_WIDTH) << "Initial empty: " << OPF(okay) << endl;

    okay = true;
    REPI(i,0,nDictionaries)
        if (dictionaries[i].size() != 0)
            okay = false;
    cout << setw(TEST_NAME_WIDTH) << "Initial size: " << OPF(okay) << endl;

    okay = true;
    REPI(i,0,nDictionaries)
        if (dictionaries[i].height() != -1)
            okay = false;
    cout << setw(TEST_NAME_WIDTH) << "Initial height: " << OPF(okay) << endl;

    // insert keys and values
    REPI(i,0,nDictionaries)
        REPI(j,0,nEntries)
            dictionaries[i][rawData[i][j].first] = rawData[i][j].second;

    // verify size
    okay = true;
    REPI(i,0,nDictionaries)
        if (dictionaries[i].size() != nEntries)
            okay = false;
    cout << setw(TEST_NAME_WIDTH) << "Insert: " << OPF(okay) << endl;

    // verify sorted order
    // is this even possible?

    // determine height
    REPI(i,0,nDictionaries)
        cout << setw(TEST_NAME_WIDTH) << "Height " + to_string(i) + ": " << to_string(dictionaries[i].height()) << endl;

    // test searching
    okay = true;
    REPI(i,0,nDictionaries)
        REPI(j,0,nEntries)
            if (dictionaries[i].search(rawData[i][j].first) != rawData[i][j].second)
                okay = false;
    cout << setw(TEST_NAME_WIDTH) << "Search: " << OPF(okay) << endl;

    // remove half of the items
    REPI(i,0,nDictionaries)
        REPI(j,0,nEntries/2)
            dictionaries[i].remove(rawData[i][2*j].first);

    // verify size
    okay = true;
    REPI(i,0,nDictionaries)
        if (dictionaries[i].size() != nEntries / 2)
            okay = false;
    cout << setw(TEST_NAME_WIDTH) << "Size: " << OPF(okay) << endl;

    // verify sorted order

    // determine height
    REPI(i,0,nDictionaries)
        cout << setw(TEST_NAME_WIDTH) << "Height " + to_string(i) + ": " << to_string(dictionaries[i].height()) << endl;

    // test searching
    okay = true;
    REPI(i,0,nDictionaries) {
        REPI(j,0,nEntries / 2)
            try {
                if (dictionaries[i].search(rawData[i][2*j+1].first) != rawData[i][2*j+1].second)
                    okay = false;
            } catch (const domain_error &e) {
                cout << "Cannot find existing key" << endl;
                okay = false;
            }
        REPI(j,0,nEntries / 2)
            try {
                dictionaries[i].search(rawData[i][2*j].first);
                okay = false;
            } catch (const domain_error &e) {
            }
    }
    cout << setw(TEST_NAME_WIDTH) << "Remove: " << OPF(okay) << endl;

    // clear one treap
    dictionaries[0].clear();

    // insert keys in sorted order
    REPI(i,0,nEntries)
        dictionaries[0][sortedData[0][i].first] = sortedData[0][i].second;

    // verify size
    okay = dictionaries[0].size() == nEntries;
    cout << setw(TEST_NAME_WIDTH) << "Sorted size: " << OPF(okay) << endl;

    // verify height
    cout << setw(TEST_NAME_WIDTH) << "Sorted height: " << dictionaries[0].height() << endl;

    // sorted search
    okay = true;
    REPI(i,0,nEntries)
        try {
            if (dictionaries[0].search(rawData[0][i].first) != rawData[0][i].second)
                okay = false;
        } catch (const domain_error &e) {
            cout << "bad search" << endl;
            okay = false;
        }
    cout << setw(TEST_NAME_WIDTH) << "Sorted search: " << OPF(okay) << endl;

    // deallocate space
    delete[] dictionaries;

    return 0;
}
