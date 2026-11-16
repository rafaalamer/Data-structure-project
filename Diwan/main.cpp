// ============================================================
//  main.cpp
//  Diwan Arabic Poetry Organizer - main menu.
//  Connects the four parts:
//    Noura  -> Poem record + input       (Part_Noura)
//    Rafa   -> sorted linked list        (Part_Rafa)
//    Shahad -> search and filters        (Part_Shahad)
//    Layan  -> statuses and statistics   (Part_Layan)
// ============================================================
#include <iostream>
#include "Part_Noura.h"
#include "Part_Rafa.h"
#include "Part_Shahad.h"
#include "Part_Layan.h"

using namespace std;

static void showMenu()
{
    cout << "\n==================================================\n"
         << " Welcome to the Diwan Arabic Poetry Organizer...\n"
         << "==================================================\n"
         << "Please choose from the following options:\n"
         << "  1. Add a new poem entry.\n"
         << "  2. Search for poems (by poet, meter, or rhyme).\n"
         << "  3. Display all Mu'allaqat.\n"
         << "  4. Display user statistics (total memorized lines).\n"
         << "  5. Update a poem's memorization status.\n"
         << "  6. Display all poems (sorted by era, then poet).\n"
         << "  7. Exit.\n";
}

int main()
{
    PoemList diwan;
    UserStats stats;

    if (readYesNo("Load sample classical poems? (y/n): "))
    {
        loadSampleData(diwan, stats);
        cout << diwan.size() << " sample poems loaded.\n";
    }

    int choice = 0;
    do
    {
        showMenu();
        choice = readInt("Your choice: ", 1, 7);

        switch (choice)
        {
        case 1:
        {
            Poem poem = readPoemFromUser();
            diwan.insertSorted(poem);
            stats.onPoemAdded(poem);
            cout << "\nPoem \"" << poem.getTitle() << "\" added successfully.\n";
            break;
        }
        case 2:
            searchMenu(diwan);
            break;
        case 3:
            diwan.displayMuallaqat();
            break;
        case 4:
            stats.display(diwan);
            break;
        case 5:
            updateStatusMenu(diwan, stats);
            break;
        case 6:
            diwan.displayAll();
            break;
        case 7:
            cout << "\nThank you for using the Diwan. Goodbye!\n";
            break;
        }
    } while (choice != 7);

    return 0;
}
