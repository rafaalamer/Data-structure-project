# Diwan Arabic Poetry Organizer (CSC214 Final Project)

A C++ console program to manage, categorize and track classical Arabic poems.

## How to run (Visual Studio)
1. Open `Diwan.sln` in Visual Studio 2022 (workload: *Desktop development with C++*).
2. Press **Ctrl + F5** (Start Without Debugging).
3. Answer `y` to load 12 sample poems, or `n` to start with an empty Diwan.

> If Visual Studio asks to retarget the project (older SDK / toolset), click **OK**.

## Data structure
A **sorted doubly linked list** (`PoemList`). Every new poem is inserted directly in its
correct place, ordered by **historical era** (Pre-Islamic → Modern) and then **alphabetically by poet
name**, so the records are always logically ordered with no extra sort step. Poems can be added at any
time without a fixed size, and the list is traversed to filter by meter, rhyme, poet or the Mu'allaqat flag.

## Team split | تقسيم العمل

| Member | Files | Responsibility |
|---|---|---|
| Noura · نوره | `Part_Noura.h / .cpp` | `Poem` class (poet, era, title/Matla', meter, rhyme, lines, Mu'allaqa flag, status), `Era`/`Status` enums, safe input helpers, reading a new poem from the user |
| Rafa · رفا | `Part_Rafa.h / .cpp` | `PoemList` sorted doubly linked list: sorted insert (era then poet), remove, get by position, display all, display all Mu'allaqat |
| Shahad · شهد | `Part_Shahad.h / .cpp` | Search by poet (partial match), filter by meter (Bahr) and rhyme (Qafiyah), list available meters/rhymes, search sub-menu |
| Layan · ليان | `Part_Layan.h / .cpp` | `UserStats`: memorization status changes that automatically add the poem's lines to the total when it becomes *Memorized*, statistics screen, sample data |
| Main | `main.cpp` | The Diwan menu loop that connects all parts |

## Menu
1. Add a new poem entry
2. Search for poems (by poet, meter, or rhyme)
3. Display all Mu'allaqat
4. Display user statistics (total memorized lines)
5. Update a poem's memorization status
6. Display all poems (sorted by era, then poet)
7. Exit

## GUI design (bonus)
Figma design of the interface (6 screens: Dashboard, Add poem, Search, Mu'allaqat, Statistics, Update status):
https://www.figma.com/design/XOoUDe1prxdpHfcNS3IpYG
