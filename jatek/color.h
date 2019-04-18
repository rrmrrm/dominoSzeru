#ifndef COLOR_H
#define COLOR_H


#include <assert.h>
#include <map>
#include <QPixmap>
#include <QImage>
#include "common.h"
#define ColorSize common::_lastVal

using namespace std;
class ColorConverter{
    map<common::COLOR, QImage> images;
    map<common::COLOR, QPixmap> pixmaps;

    map<common::PLAYERCOLOR, QPixmap> crownPixmaps;
public:
    ColorConverter();

    const QPixmap colorToPixmap(common::COLOR c);
    const QImage colorToImage(common::COLOR c);

    const QPixmap playerColorToPixmap(common::PLAYERCOLOR pc);
};
#endif // COLOR_H
