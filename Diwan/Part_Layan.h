// ============================================================
//  Part_Layan.h  -  Layan's part
//  User memorization tracking and statistics.
//  When a poem's status becomes "Memorized" its lines (Bayt)
//  are automatically added to the user's total memorized lines.
// ============================================================
#ifndef PART_LAYAN_H
#define PART_LAYAN_H

#include "Part_Rafa.h"

class UserStats
{
private:
    int totalMemorizedLines;

public:
    UserStats();

    int getTotalMemorizedLines() const;

    // Must be called whenever a poem is added to the Diwan:
    // if it is already memorized, its lines are counted.
    void onPoemAdded(const Poem& poem);

    // Changes the status of a poem and updates the total automatically:
    //  - becomes Memorized      -> lines are added
    //  - was Memorized, changed -> lines are removed (keeps total correct)
    void changeStatus(Poem& poem, Status newStatus);

    // Prints totals and a per-status / per-era summary
    void display(const PoemList& list) const;
};

// "Update memorization status" sub-menu
void updateStatusMenu(PoemList& list, UserStats& stats);

// Fills the Diwan with some well known classical poems for demo/testing
void loadSampleData(PoemList& list, UserStats& stats);

#endif
