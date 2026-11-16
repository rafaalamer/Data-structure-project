// ============================================================
//  Part_Rafa.cpp  -  Rafa's part
//  Implementation of the sorted doubly linked list.
// ============================================================
#include "Part_Rafa.h"
#include <iostream>

using namespace std;

PoemList::PoemList() : head(nullptr), tail(nullptr), count(0)
{
}

PoemList::~PoemList()
{
    clear();
}

void PoemList::clear()
{
    PoemNode* current = head;
    while (current != nullptr)
    {
        PoemNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = tail = nullptr;
    count = 0;
}

void PoemList::insertSorted(const Poem& poem)
{
    PoemNode* newNode = new PoemNode(poem);

    // case 1: empty list
    if (head == nullptr)
    {
        head = tail = newNode;
        count++;
        return;
    }

    // case 2: new poem goes before the head
    if (poem.comesBefore(head->data))
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        count++;
        return;
    }

    // case 3: find the first node that should come after the new poem
    PoemNode* current = head;
    while (current->next != nullptr && !poem.comesBefore(current->next->data))
        current = current->next;

    // insert after 'current'
    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != nullptr)
        current->next->prev = newNode;
    else
        tail = newNode;           // inserted at the end
    current->next = newNode;
    count++;
}

PoemNode* PoemList::getAt(int position) const
{
    if (position < 1 || position > count)
        return nullptr;
    PoemNode* current = head;
    for (int i = 1; i < position; i++)
        current = current->next;
    return current;
}

bool PoemList::removeAt(int position)
{
    PoemNode* target = getAt(position);
    if (target == nullptr)
        return false;

    if (target->prev != nullptr) target->prev->next = target->next;
    else                         head = target->next;

    if (target->next != nullptr) target->next->prev = target->prev;
    else                         tail = target->prev;

    delete target;
    count--;
    return true;
}

PoemNode* PoemList::getHead() const { return head; }
int  PoemList::size() const         { return count; }
bool PoemList::isEmpty() const      { return count == 0; }

void PoemList::displayAll() const
{
    if (isEmpty())
    {
        cout << "\nThe Diwan is empty.\n";
        return;
    }
    cout << "\n===== All poems (sorted by era, then poet) =====\n";
    int index = 1;
    Era lastEra = ERA_COUNT;
    for (PoemNode* cur = head; cur != nullptr; cur = cur->next, index++)
    {
        if (cur->data.getEra() != lastEra)
        {
            lastEra = cur->data.getEra();
            cout << "\n### " << eraToString(lastEra) << " era ###\n";
        }
        cout << "\n[" << index << "]\n";
        cur->data.display();
    }
    cout << "\nTotal poems: " << count << "\n";
}

void PoemList::displayTitles() const
{
    int index = 1;
    for (PoemNode* cur = head; cur != nullptr; cur = cur->next, index++)
    {
        cout << "  " << index << ". " << cur->data.getTitle()
             << "  -  " << cur->data.getPoetName()
             << "  (" << statusToString(cur->data.getStatus()) << ")\n";
    }
}

void PoemList::displayMuallaqat() const
{
    cout << "\n===== The Mu'allaqat =====\n";
    int found = 0;
    for (PoemNode* cur = head; cur != nullptr; cur = cur->next)
    {
        if (cur->data.getIsMuallaqa())
        {
            found++;
            cout << "\n(" << found << ")\n";
            cur->data.display();
        }
    }
    if (found == 0)
        cout << "No Mu'allaqat in the Diwan yet.\n";
    else
        cout << "\nTotal Mu'allaqat: " << found << "\n";
}
