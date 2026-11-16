// ============================================================
//  Part_Rafa.h  -  Rafa's part
//  PoemList: a sorted doubly linked list that stores all poems.
//  Every insert keeps the list ordered by historical era and
//  then alphabetically by poet name, so the records are always
//  logically ordered without a separate sort step.
// ============================================================
#ifndef PART_RAFA_H
#define PART_RAFA_H

#include "Part_Noura.h"

struct PoemNode
{
    Poem data;
    PoemNode* next;
    PoemNode* prev;

    PoemNode(const Poem& p) : data(p), next(nullptr), prev(nullptr) {}
};

class PoemList
{
private:
    PoemNode* head;
    PoemNode* tail;
    int count;

public:
    PoemList();
    ~PoemList();

    // inserts the poem in its sorted position (era, then poet name)
    void insertSorted(const Poem& poem);

    // removes the poem at 1-based position, returns false if invalid
    bool removeAt(int position);

    // returns the node at a 1-based position (nullptr if invalid)
    PoemNode* getAt(int position) const;

    PoemNode* getHead() const;
    int size() const;
    bool isEmpty() const;

    // prints every poem in order with its position number
    void displayAll() const;

    // prints a short numbered list (title - poet) used for choosing a poem
    void displayTitles() const;

    // prints only the poems whose Mu'allaqa flag is true
    void displayMuallaqat() const;

    void clear();

private:
    // copying is disabled (the list owns its nodes)
    PoemList(const PoemList&);
    PoemList& operator=(const PoemList&);
};

#endif
