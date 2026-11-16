// ============================================================
//  Part_Noura.h  -  Noura's part
//  The Poem record: poet info, era, title, meter, rhyme,
//  number of lines, Mu'allaqat flag and memorization status.
//  Also contains safe console input helpers.
// ============================================================
#ifndef PART_NOURA_H
#define PART_NOURA_H

#include <string>

// Historical eras, declared in chronological order so that
// comparing two eras as numbers gives the historical order.
enum Era
{
    PRE_ISLAMIC = 0,
    EARLY_ISLAMIC,
    UMAYYAD,
    ABBASID,
    ANDALUSIAN,
    MODERN,
    ERA_COUNT
};

// Memorization status of a poem
enum Status
{
    UNREAD = 0,
    IN_PROGRESS,
    MEMORIZED,
    STATUS_COUNT
};

std::string eraToString(Era era);
std::string statusToString(Status status);

class Poem
{
private:
    std::string poetName;
    Era era;
    std::string title;      // title or first line (Matla')
    std::string meter;      // Bahr, e.g. Tawil, Kamil
    std::string rhyme;      // Qafiyah, e.g. Lam, Mim
    int numberOfLines;      // number of verses (Bayt)
    bool isMuallaqa;        // one of the Mu'allaqat?
    Status status;

public:
    Poem();
    Poem(const std::string& poetName, Era era, const std::string& title,
         const std::string& meter, const std::string& rhyme,
         int numberOfLines, bool isMuallaqa, Status status = UNREAD);

    // getters
    std::string getPoetName() const;
    Era getEra() const;
    std::string getTitle() const;
    std::string getMeter() const;
    std::string getRhyme() const;
    int getNumberOfLines() const;
    bool getIsMuallaqa() const;
    Status getStatus() const;

    // setters
    void setPoetName(const std::string& name);
    void setEra(Era e);
    void setTitle(const std::string& t);
    void setMeter(const std::string& m);
    void setRhyme(const std::string& r);
    void setNumberOfLines(int n);
    void setIsMuallaqa(bool flag);
    void setStatus(Status s);

    // true if this poem should come before 'other'
    // (ordered by era first, then alphabetically by poet name)
    bool comesBefore(const Poem& other) const;

    void display() const;
};

// ---------- safe input helpers ----------
std::string readLine(const std::string& prompt);              // non-empty line
int  readInt(const std::string& prompt, int minVal, int maxVal);
bool readYesNo(const std::string& prompt);
std::string toLowerCase(const std::string& s);

// Asks the user for all the poem fields and returns the new poem
Poem readPoemFromUser();

#endif
