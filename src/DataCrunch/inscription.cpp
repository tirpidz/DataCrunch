#include "inscription.h"

Inscription::Inscription(QString name, int yearStart, int yearEnd)
{
    name_ = name;
    yearStart_ = yearStart;
    yearEnd_ = yearEnd;
}

Inscription::~Inscription()
{

}

void Inscription::addTrait( QString trait)
{
    if( !activeTraits_.contains( trait))
    {
        activeTraits_.insert( trait);
    }
    else
    {
        qDebug() << "Trait(" << trait << ") already present in activeTrait_";
    }
}

bool Inscription::isTraitActive(QString trait)
{
    if( activeTraits_.contains( trait))
    {
        return true;
    }

    return false;
}

void Inscription::display()
{
    qDebug() << "Inscription:" << name_ << QString::number( yearStart_) << QString::number( yearEnd_);
    qDebug() << "Traits:";

    for( QSet< QString >::iterator it = activeTraits_.begin(); it != activeTraits_.end(); ++it)
    {
        qDebug() << *it;
    }
}

