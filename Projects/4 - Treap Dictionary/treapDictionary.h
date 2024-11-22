//
// Created by scsiet on 11/22/24.
//

#ifndef TREAP_DICTIONARY_H
#define TREAP_DICTIONARY_H

#include <cstdint>      // for uint32_t
#include <stdexcept>    // for domain_error
#include <random>       // for random number generation

static const uint32_t
    NULL_INDEX = 0xffffffff,
    DEFAULT_INITIAL_CAPACITY = 16;

template <typename KeyType,typename ValueType>
class TreapDictionary {
public:
    explicit TreapDictionary(uint32_t _cap = DEFAULT_INITIAL_CAPACITY) {
    }

    ~TreapDictionary() {
    }

    void clear() {
    }

    uint32_t size() {
    }

    uint32_t height() {
    }

    bool isEmpty() {
    }

    void remove(const KeyType &k) {
    }

    ValueType &search(const KeyType &k) {
    }

    ValueType &operator[](const KeyType &k) {
    }

private:
    uint32_t prvAllocate() {
    }

    void prvFree(uint32_t n) {
    }

    void prvClear(uint32_t r) {
    }

    void prvAdjust(uint32_t r) {
    }

    uint32_t prvRotateLeft(uint32_t r) {
    }

    uint32_t prvRotateRight(uint32_t r) {
    }

    uint32_t prvInsert(uint32_t r,uint32_t &n,const KeyType &k) {
    }

    uint32_t prvRemove(uint32_t r,uint32_t &ntbd,const KeyType &k) {
    }

    uint32_t
        root;           // tree root
    static uint32_t     // this is the shared data
        *counts,        // counts for each node
        *heights,       // heights for each node
        *left,          // left node indexes
        *right,         // right node indexes
        *heapVals,      // random values for the treap
        nTreaps,        // number of treaps with this key and value type
        capacity,       // size of the arrays
        freeListHead;   // the head of the unused node list (the free list)
    static std::random_device
        *rd;            // source of random noise
    static std::mt19937
        *mt;            // a random number generator
    static KeyType
        *keys;          // pool of keys
    static ValueType
        *values;        // pool of values
};

template <typename KeyType,typename ValueType>
uint32_t *TreapDictionary<KeyType,ValueType>::counts = nullptr;

template <typename KeyType,typename ValueType>
uint32_t *TreapDictionary<KeyType,ValueType>::heights = nullptr;

template <typename KeyType,typename ValueType>
uint32_t *TreapDictionary<KeyType,ValueType>::left = nullptr;

template <typename KeyType,typename ValueType>
uint32_t *TreapDictionary<KeyType,ValueType>::right = nullptr;

template <typename KeyType,typename ValueType>
std::random_device *TreapDictionary<KeyType,ValueType>::rd = nullptr;

template <typename KeyType,typename ValueType>
std::mt19937 *TreapDictionary<KeyType,ValueType>::mt = nullptr;

template <typename KeyType,typename ValueType>
KeyType *TreapDictionary<KeyType,ValueType>::keys = nullptr;

template <typename KeyType,typename ValueType>
ValueType *TreapDictionary<KeyType,ValueType>::values = nullptr;

template <typename KeyType,typename ValueType>
uint32_t *TreapDictionary<KeyType,ValueType>::heapVals = nullptr;

template <typename KeyType,typename ValueType>
uint32_t TreapDictionary<KeyType,ValueType>::nTreaps = 0;

template <typename KeyType,typename ValueType>
uint32_t TreapDictionary<KeyType,ValueType>::freeListHead = 0;

template <typename KeyType,typename ValueType>
uint32_t TreapDictionary<KeyType,ValueType>::capacity = 0;

#endif