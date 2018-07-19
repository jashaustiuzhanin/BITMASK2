#ifndef MASKDATA_H
#define MASKDATA_H

#include <QtCore>

typedef struct TMaskDataOfOneBit
{
    QColor BackColorState0;
    QColor BackColorState1;
    QColor TextColorState0;
    QColor TextColorState1;

    QString Text;
}
TMaskDataOfOneBit;



#endif // MASKDATA_H
