#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QString>
#include <QSet>
#include <QDebug>

class Inscription
{
public:
    Inscription( QString name, int yearStart, int yearEnd);
    ~Inscription();

    QString getName() const { return name_;}
    int getStart() const { return yearStart_;}
    int getEnd() const { return yearEnd_;}

    void addTrait( QString trait);

    bool isTraitActive( QString trait);

    void display() const;

    bool operator<( const Inscription& other) const;

protected:
    double getInscriptionCenter() const;

    QString name_;
    int yearStart_;
    int yearEnd_;

    QSet< QString > activeTraits_;
};

#endif // INSCRIPTION_H
