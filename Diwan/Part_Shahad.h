// ============================================================
//  Part_Shahad.h  -  Shahad's part
//  Searching and filtering poems by poet, meter (Bahr)
//  or rhyme (Qafiyah). Searches are case-insensitive; poet
//  search also matches part of the name.
// ============================================================
#ifndef PART_SHAHAD_H
#define PART_SHAHAD_H

#include "Part_Rafa.h"
#include <string>

// each function prints the matching poems and returns how many matched
int searchByPoet(const PoemList& list, const std::string& poetName);
int filterByMeter(const PoemList& list, const std::string& meter);
int filterByRhyme(const PoemList& list, const std::string& rhyme);

// prints every distinct meter / rhyme in the Diwan (helps the user choose)
void listAvailableMeters(const PoemList& list);
void listAvailableRhymes(const PoemList& list);

// the "Search for poems" sub-menu
void searchMenu(const PoemList& list);

#endif
