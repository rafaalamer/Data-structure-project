// ============================================================
//  Part_Layan.cpp  -  Layan's part
//  Implementation of user statistics and status updates.
// ============================================================
#include "Part_Layan.h"
#include <iostream>
#include <iomanip>

using namespace std;

UserStats::UserStats() : totalMemorizedLines(0)
{
}

int UserStats::getTotalMemorizedLines() const
{
    return totalMemorizedLines;
}

void UserStats::onPoemAdded(const Poem& poem)
{
    if (poem.getStatus() == MEMORIZED)
        totalMemorizedLines += poem.getNumberOfLines();
}

void UserStats::changeStatus(Poem& poem, Status newStatus)
{
    Status oldStatus = poem.getStatus();
    if (oldStatus == newStatus)
        return;

    if (newStatus == MEMORIZED)
        totalMemorizedLines += poem.getNumberOfLines();   // auto add the Bayt
    else if (oldStatus == MEMORIZED)
        totalMemorizedLines -= poem.getNumberOfLines();   // no longer memorized

    poem.setStatus(newStatus);
}

void UserStats::display(const PoemList& list) const
{
    int statusCount[STATUS_COUNT] = { 0 };
    int eraCount[ERA_COUNT] = { 0 };
    int totalLines = 0;

    for (PoemNode* cur = list.getHead(); cur != nullptr; cur = cur->next)
    {
        statusCount[cur->data.getStatus()]++;
        eraCount[cur->data.getEra()]++;
        totalLines += cur->data.getNumberOfLines();
    }

    cout << "\n===== User statistics =====\n";
    cout << "  Total memorized lines (Bayt) : " << totalMemorizedLines << "\n";
    cout << "  Total lines in the Diwan     : " << totalLines << "\n";
    if (totalLines > 0)
    {
        double percent = 100.0 * totalMemorizedLines / totalLines;
        cout << "  Memorization progress        : " << fixed << setprecision(1)
             << percent << "%\n";
        cout.unsetf(ios::fixed);
    }

    cout << "\n  Poems by status:\n";
    for (int i = 0; i < STATUS_COUNT; i++)
        cout << "    " << left << setw(13) << statusToString((Status)i)
             << ": " << statusCount[i] << "\n";

    cout << "\n  Poems by era:\n";
    for (int i = 0; i < ERA_COUNT; i++)
        cout << "    " << left << setw(13) << eraToString((Era)i)
             << ": " << eraCount[i] << "\n";
    cout << right;
    cout << "\n  Total poems: " << list.size() << "\n";
}

void updateStatusMenu(PoemList& list, UserStats& stats)
{
    if (list.isEmpty())
    {
        cout << "\nThe Diwan is empty, add a poem first.\n";
        return;
    }
    cout << "\n--- Update memorization status ---\n";
    list.displayTitles();
    int position = readInt("Choose a poem number: ", 1, list.size());
    PoemNode* node = list.getAt(position);

    cout << "New status:\n";
    for (int i = 0; i < STATUS_COUNT; i++)
        cout << "  " << (i + 1) << ". " << statusToString((Status)i) << "\n";
    Status newStatus = (Status)(readInt("Choose status: ", 1, STATUS_COUNT) - 1);

    Status oldStatus = node->data.getStatus();
    stats.changeStatus(node->data, newStatus);

    cout << "\nStatus of \"" << node->data.getTitle() << "\" changed from "
         << statusToString(oldStatus) << " to " << statusToString(newStatus) << ".\n";
    if (newStatus == MEMORIZED && oldStatus != MEMORIZED)
        cout << "Well done! " << node->data.getNumberOfLines()
             << " lines were added to your memorized total.\n";
    cout << "Total memorized lines: " << stats.getTotalMemorizedLines() << "\n";
}

void loadSampleData(PoemList& list, UserStats& stats)
{
    Poem samples[] = {
        Poem("Imru' al-Qais", PRE_ISLAMIC, "Qifa nabki min dhikra habibin wa manzili",
             "Tawil", "Lam", 82, true, MEMORIZED),
        Poem("Tarafa ibn al-Abd", PRE_ISLAMIC, "Li-Khawlata atlalun bi-burqati Thahmadi",
             "Tawil", "Dal", 104, true, IN_PROGRESS),
        Poem("Zuhayr ibn Abi Sulma", PRE_ISLAMIC, "A-min Ummi Awfa dimnatun lam takallami",
             "Tawil", "Mim", 59, true),
        Poem("Antarah ibn Shaddad", PRE_ISLAMIC, "Hal ghadara al-shu'ara'u min mutaraddami",
             "Kamil", "Mim", 75, true),
        Poem("Labid ibn Rabi'a", PRE_ISLAMIC, "Afati al-diyaru mahalluha fa-muqamuha",
             "Kamil", "Mim", 88, true),
        Poem("Ka'b ibn Zuhayr", EARLY_ISLAMIC, "Banat Su'ad fa-qalbi al-yawma matbulu",
             "Basit", "Lam", 58, false),
        Poem("Jarir", UMAYYAD, "Inna al-'uyuna allati fi tarfiha hawarun",
             "Basit", "Nun", 30, false),
        Poem("Al-Farazdaq", UMAYYAD, "Hadha alladhi ta'rifu al-bat-ha'u wat'atahu",
             "Basit", "Mim", 27, false),
        Poem("Al-Mutanabbi", ABBASID, "Ala qadri ahli al-'azmi ta'ti al-'aza'imu",
             "Tawil", "Mim", 46, false, MEMORIZED),
        Poem("Abu Tammam", ABBASID, "Al-sayfu asdaqu inba'an mina al-kutubi",
             "Basit", "Ba", 71, false),
        Poem("Ibn Zaydun", ANDALUSIAN, "Adha al-tana'i badilan min tadanina",
             "Basit", "Nun", 51, false),
        Poem("Ahmad Shawqi", MODERN, "Salu qalbi ghadata sala wa taba",
             "Wafir", "Ba", 71, false)
    };

    int n = sizeof(samples) / sizeof(samples[0]);
    for (int i = 0; i < n; i++)
    {
        list.insertSorted(samples[i]);
        stats.onPoemAdded(samples[i]);
    }
}
