#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QHash>
#include <QDir>
#include <QMap>

#include <vector>
#include <iostream>

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
    QMap< Inscription, QString > sortedEntries;

    while( !in.atEnd())
    {
        QString line = in.readLine();
        QStringList inputs = line.split( " ");

        Inscription entry( inputs.at( 0), inputs.at( 1).toInt(), inputs.at( 2).toInt());

        entries.insert( entry.getName(), entry);
        sortedEntries.insert( entry, entry.getName());
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

    for( int i = 1; i <= 17; ++i)
    {

        std::cout << "#trait " << QString::number( i).toStdString() << std::endl;

        int ctr = 1;

        std::vector< QString > x;
        std::vector< QString > y;

        for( QMap< Inscription, QString >::iterator it = sortedEntries.begin(); it != sortedEntries.end(); ++it)
        {
            if( entries.find( it.value()).value().isTraitActive( QString::number( i)))
            {
                x.push_back( "x" + QString::number( i) + "_" + entries.find( it.value()).value().getName());
                y.push_back( "y" + QString::number( i) + "_" + entries.find( it.value()).value().getName());

                std::cout << "x" + QString::number( i).toStdString() + "_" + entries.find( it.value()).value().getName().toStdString() + " = [" << QString::number( entries.find( it.value()).value().getStart()).toStdString() << "," << QString::number( entries.find( it.value()).value().getEnd()).toStdString() << "]\n";
                std::cout << "y" + QString::number( i).toStdString() + "_" + entries.find( it.value()).value().getName().toStdString() + " = [" << QString::number( ctr).toStdString() << "," << QString::number( ctr).toStdString() << "]\n";
            }

            ++ctr;
        }

        std::cout << "plot(";

        for( unsigned int i = 0; i < x.size(); ++i)
        {
            std::cout << x[i].toStdString() << "," << y[i].toStdString();

            if( i == x.size() - 1)
            {
                std::cout << ")\n";
            }
            else
            {
                std::cout << ",";
            }
        }
    }

    return 0;
}
