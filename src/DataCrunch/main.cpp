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

    QFile file1( dir + QDir::separator() + "inscriptions.txt");

    if( !file1.open( QIODevice::ReadOnly))
    {
        qDebug() << "Could not open file(" << file1.fileName() << ")";
    }

    QTextStream in( &file1);

    QHash< QString, Inscription > entries;

    while( !in.atEnd())
    {
        QString line = in.readLine();
        QStringList inputs = line.split( " ");

        Inscription entry( inputs.at( 0), inputs.at( 1).toInt(), inputs.at( 2).toInt());

        entries.insert( inputs.at( 0), entry);
    }

    for( int i = 1; i <= 17; ++i)
    {
        QFile file( dir + QDir::separator() + "graph" + QString::number( i) + ".txt");

        if( !file.open( QIODevice::ReadOnly))
        {
            qDebug() << "Could not open file(" << file.fileName() << ")";
        }

        QTextStream input( &file);

        while( !input.atEnd())
        {
            QString line = input.readLine();
            line.remove( ' ');
            QStringList incriptionWithCurrentTrait = line.split( ",");

            QHash< QString, Inscription >::iterator it;

            for( int j = 0; j < incriptionWithCurrentTrait.size(); ++j)
            {
                it = entries.find( incriptionWithCurrentTrait.at( j));

                if( it != entries.end())
                {
                    it.value().addTrait( QString::number( i));
                }
            }
        }
    }

    for( QHash< QString, Inscription >::iterator it = entries.begin(); it != entries.end(); ++it)
    {
        it.value().display();
    }

    return 0;
}
