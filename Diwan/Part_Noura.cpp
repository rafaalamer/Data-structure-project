// ============================================================
//  Part_Noura.cpp  -  Noura's part
//  Implementation of the Poem class and input helpers.
// ============================================================
#include "Part_Noura.h"
#include <iostream>
#include <cctype>

using namespace std;

string eraToString(Era era)
{
    switch (era)
    {
    case PRE_ISLAMIC:   return "Pre-Islamic";
    case EARLY_ISLAMIC: return "Early Islamic";
    case UMAYYAD:       return "Umayyad";
    case ABBASID:       return "Abbasid";
    case ANDALUSIAN:    return "Andalusian";
    case MODERN:        return "Modern";
    default:            return "Unknown";
    }
}

string statusToString(Status status)
{
    switch (status)
    {
    case UNREAD:      return "Unread";
    case IN_PROGRESS: return "In-progress";
    case MEMORIZED:   return "Memorized";
    default:          return "Unknown";
    }
}

// ---------------- Poem ----------------
Poem::Poem()
    : poetName(""), era(PRE_ISLAMIC), title(""), meter(""), rhyme(""),
      numberOfLines(0), isMuallaqa(false), status(UNREAD)
{
}

Poem::Poem(const string& poetName, Era era, const string& title,
           const string& meter, const string& rhyme,
           int numberOfLines, bool isMuallaqa, Status status)
    : poetName(poetName), era(era), title(title), meter(meter), rhyme(rhyme),
      numberOfLines(numberOfLines), isMuallaqa(isMuallaqa), status(status)
{
}

string Poem::getPoetName() const    { return poetName; }
Era    Poem::getEra() const         { return era; }
string Poem::getTitle() const       { return title; }
string Poem::getMeter() const       { return meter; }
string Poem::getRhyme() const       { return rhyme; }
int    Poem::getNumberOfLines() const { return numberOfLines; }
bool   Poem::getIsMuallaqa() const  { return isMuallaqa; }
Status Poem::getStatus() const      { return status; }

void Poem::setPoetName(const string& name) { poetName = name; }
void Poem::setEra(Era e)                   { era = e; }
void Poem::setTitle(const string& t)       { title = t; }
void Poem::setMeter(const string& m)       { meter = m; }
void Poem::setRhyme(const string& r)       { rhyme = r; }
void Poem::setNumberOfLines(int n)         { numberOfLines = (n < 0) ? 0 : n; }
void Poem::setIsMuallaqa(bool flag)        { isMuallaqa = flag; }
void Poem::setStatus(Status s)             { status = s; }

bool Poem::comesBefore(const Poem& other) const
{
    if (era != other.era)
        return era < other.era;
    // same era -> alphabetical by poet name (case-insensitive)
    return toLowerCase(poetName) < toLowerCase(other.poetName);
}

void Poem::display() const
{
    cout << "  Title/Matla' : " << title << "\n"
         << "  Poet         : " << poetName << "\n"
         << "  Era          : " << eraToString(era) << "\n"
         << "  Meter (Bahr) : " << meter << "\n"
         << "  Rhyme        : " << rhyme << "\n"
         << "  Lines (Bayt) : " << numberOfLines << "\n"
         << "  Mu'allaqa    : " << (isMuallaqa ? "True" : "False") << "\n"
         << "  Status       : " << statusToString(status) << "\n";
}

// ---------------- input helpers ----------------
string toLowerCase(const string& s)
{
    string result = s;
    for (size_t i = 0; i < result.size(); i++)
        result[i] = (char)tolower((unsigned char)result[i]);
    return result;
}

string readLine(const string& prompt)
{
    string line;
    while (true)
    {
        cout << prompt;
        if (!getline(cin, line))
        {
            cin.clear();
            continue;
        }
        // trim spaces at both ends
        size_t start = line.find_first_not_of(" \t\r");
        size_t end = line.find_last_not_of(" \t\r");
        if (start != string::npos)
            return line.substr(start, end - start + 1);
        cout << "  Input cannot be empty, try again.\n";
    }
}

int readInt(const string& prompt, int minVal, int maxVal)
{
    while (true)
    {
        string line = readLine(prompt);
        bool valid = true;
        for (size_t i = 0; i < line.size(); i++)
        {
            if (!isdigit((unsigned char)line[i]) && !(i == 0 && line[i] == '-'))
                valid = false;
        }
        if (valid && line.size() < 10 && line != "-")
        {
            int value = stoi(line);
            if (value >= minVal && value <= maxVal)
                return value;
        }
        cout << "  Please enter a number between " << minVal << " and " << maxVal << ".\n";
    }
}

bool readYesNo(const string& prompt)
{
    while (true)
    {
        string answer = toLowerCase(readLine(prompt));
        if (answer == "y" || answer == "yes" || answer == "true")  return true;
        if (answer == "n" || answer == "no"  || answer == "false") return false;
        cout << "  Please answer y or n.\n";
    }
}

Poem readPoemFromUser()
{
    cout << "\n--- Add a new poem entry ---\n";
    string poet = readLine("Poet name: ");

    cout << "Historical era:\n";
    for (int i = 0; i < ERA_COUNT; i++)
        cout << "  " << (i + 1) << ". " << eraToString((Era)i) << "\n";
    Era era = (Era)(readInt("Choose era: ", 1, ERA_COUNT) - 1);

    string title = readLine("Poem title (or first line / Matla'): ");
    string meter = readLine("Meter (Bahr), e.g. Tawil, Kamil, Basit, Wafir: ");
    string rhyme = readLine("Rhyme (Qafiyah), e.g. Lam, Mim, Ra, Dal: ");
    int lines = readInt("Number of lines (Bayt): ", 1, 100000);
    bool muallaqa = readYesNo("Is it one of the Mu'allaqat? (y/n): ");

    cout << "Memorization status:\n";
    for (int i = 0; i < STATUS_COUNT; i++)
        cout << "  " << (i + 1) << ". " << statusToString((Status)i) << "\n";
    Status status = (Status)(readInt("Choose status: ", 1, STATUS_COUNT) - 1);

    return Poem(poet, era, title, meter, rhyme, lines, muallaqa, status);
}
