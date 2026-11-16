// ============================================================
//  Part_Shahad.cpp  -  Shahad's part
//  Linear search over the sorted linked list. Because the list
//  is already sorted by era and poet, the results come out in
//  the same logical order.
// ============================================================
#include "Part_Shahad.h"
#include <iostream>

using namespace std;

// which field a search looks at
enum SearchField { BY_POET, BY_METER, BY_RHYME };

static string fieldValue(const Poem& p, SearchField field)
{
    switch (field)
    {
    case BY_POET:  return p.getPoetName();
    case BY_METER: return p.getMeter();
    default:       return p.getRhyme();
    }
}

// shared search routine: partial = substring match, otherwise exact match
static int searchList(const PoemList& list, const string& key,
                      SearchField field, bool partial)
{
    string target = toLowerCase(key);
    int found = 0;
    for (PoemNode* cur = list.getHead(); cur != nullptr; cur = cur->next)
    {
        string value = toLowerCase(fieldValue(cur->data, field));
        bool match = partial ? (value.find(target) != string::npos)
                             : (value == target);
        if (match)
        {
            found++;
            cout << "\n(" << found << ")\n";
            cur->data.display();
        }
    }
    if (found == 0)
        cout << "\nNo poems matched \"" << key << "\".\n";
    else
        cout << "\n" << found << " poem(s) found.\n";
    return found;
}

int searchByPoet(const PoemList& list, const string& poetName)
{
    cout << "\n--- Poems by poet: " << poetName << " ---\n";
    return searchList(list, poetName, BY_POET, true);
}

int filterByMeter(const PoemList& list, const string& meter)
{
    cout << "\n--- Poems on meter (Bahr): " << meter << " ---\n";
    return searchList(list, meter, BY_METER, false);
}

int filterByRhyme(const PoemList& list, const string& rhyme)
{
    cout << "\n--- Poems with rhyme (Qafiyah): " << rhyme << " ---\n";
    return searchList(list, rhyme, BY_RHYME, false);
}

// prints each distinct value of a field once
static void listDistinct(const PoemList& list, SearchField field)
{
    bool first = true;
    for (PoemNode* cur = list.getHead(); cur != nullptr; cur = cur->next)
    {
        string value = toLowerCase(fieldValue(cur->data, field));
        // skip it if an earlier node already had the same value
        bool seen = false;
        for (PoemNode* before = list.getHead(); before != cur; before = before->next)
        {
            if (toLowerCase(fieldValue(before->data, field)) == value)
            {
                seen = true;
                break;
            }
        }
        if (!seen)
        {
            cout << (first ? "  " : ", ") << fieldValue(cur->data, field);
            first = false;
        }
    }
    cout << (first ? "  (none)\n" : "\n");
}

void listAvailableMeters(const PoemList& list)
{
    cout << "Meters in the Diwan:\n";
    listDistinct(list, BY_METER);
}

void listAvailableRhymes(const PoemList& list)
{
    cout << "Rhymes in the Diwan:\n";
    listDistinct(list, BY_RHYME);
}

void searchMenu(const PoemList& list)
{
    if (list.isEmpty())
    {
        cout << "\nThe Diwan is empty, add a poem first.\n";
        return;
    }
    cout << "\n--- Search for poems ---\n"
         << "  1. By poet\n"
         << "  2. By meter (Bahr)\n"
         << "  3. By rhyme (Qafiyah)\n"
         << "  4. Back\n";
    int choice = readInt("Choose: ", 1, 4);
    switch (choice)
    {
    case 1:
        searchByPoet(list, readLine("Poet name (or part of it): "));
        break;
    case 2:
        listAvailableMeters(list);
        filterByMeter(list, readLine("Meter: "));
        break;
    case 3:
        listAvailableRhymes(list);
        filterByRhyme(list, readLine("Rhyme: "));
        break;
    default:
        break;
    }
}
