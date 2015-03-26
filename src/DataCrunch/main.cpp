#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QHash>
#include <QDir>

#include "inscription.h"

int main( int argc, char *argv[])
{
    QString dir = QString::fromLatin1( argv[1]);

    qDebug() << dir;

    QFile file1( dir + QDir::separator() + "input.txt");

    QTextStream in( &file1);

    QHash< QString, Inscription > entries;

    while( !in.atEnd())
    {
        QString line = in.readLine();
        QStringList inputs = line.split( " ");

        Inscription entry( inputs.at( 0), inputs.at( 1).toInt(), inputs.at( 2).toInt());

        entries.insert( inputs.at( 0), entry);

        entry.display();
    }

    for( int i = 0; i < 17; ++i)
    {
        QFile file( dir + QDir::separator() + "graph" + QString::number( i) + ".txt");

        QTextStream input( &file);

        while( !input.atEnd())
        {
            QString line = input.readLine();
            QStringList trait = line.split( ",");

            QHash< QString, Inscription >::iterator it;

            for( int j = 0; j < trait.size(); ++j)
            {
                it = entries.find( trait.at( j));

                if( it != entries.end())
                {
                    it.value().addTrait( QString::number( j));
                }
            }
        }
    }

    return 0;
}
