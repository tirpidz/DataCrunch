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

void Inscription::display() const
{
    qDebug() << "Inscription:" << name_ << QString::number( yearStart_) << QString::number( yearEnd_);
    qDebug() << "Traits:";

    for( QSet< QString >::const_iterator it = activeTraits_.begin(); it != activeTraits_.end(); ++it)
    {
        qDebug() << *it;
    }
}

bool Inscription::operator<( const Inscription& other) const
{
    if( (yearStart_ + ((yearStart_ + yearEnd_) / 2)) < (other.yearStart_ + ((other.yearStart_ + other.yearEnd_) / 2)))
    {
        return true;
    }
    else
    {
        if( (yearStart_ + ((yearStart_ + yearEnd_) / 2)) == (other.yearStart_ + ((other.yearStart_ + other.yearEnd_) / 2)))
        {
            if( yearEnd_ < other.yearEnd_)
            {
                return true;
            }
            else
            {
                if( name_.compare( other.name_) < 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
    }
}

