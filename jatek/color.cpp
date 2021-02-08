#include "color.h"
#include "common.h"

using namespace common;
using namespace std;

ColorConverter::ColorConverter(): images(), pixmaps() {
    ///ellenorzom, hogy megvaltozott-e a COLOR ertekek darabszama, mert
    /// ha igen, akkor at kell irni az osztalyt
    assert(8 == ColorSize);

    QString resourcePrefix = ":/";
    images.insert(  pair<COLOR,QImage>( SWAMP,  QImage(resourcePrefix+"swamp.png"   ) )  );
    images.insert(  pair<COLOR,QImage>( MOUNTAIN,QImage(resourcePrefix+"mountain.png") )  );
    images.insert(  pair<COLOR,QImage>( WHEATFIELD,QImage(resourcePrefix+"wheatField.png") )  );
    images.insert(  pair<COLOR,QImage>( FOREST, QImage(resourcePrefix+"forest.png"  ) )  );
    images.insert(  pair<COLOR,QImage>( LAKE,   QImage(resourcePrefix+"lake.png"    ) )  );
    images.insert(  pair<COLOR,QImage>( PASTURE,QImage(resourcePrefix+"pasture.png" ) )  );
    images.insert(  pair<COLOR,QImage>( EMPTY,  QImage(resourcePrefix+"empty.png"   ) )  );
    images.insert(  pair<COLOR,QImage>( CASTLE, QImage(resourcePrefix+"castle.png"  ) )  );

    pixmaps.insert(  pair<COLOR,QPixmap>( SWAMP,    QPixmap(resourcePrefix+"swamp.png"  ) )  );
    pixmaps.insert(  pair<COLOR,QPixmap>( MOUNTAIN, QPixmap(resourcePrefix+"mountain.png") )  );
    pixmaps.insert(  pair<COLOR,QPixmap>( WHEATFIELD,QPixmap(resourcePrefix+"wheatField.png") )  );
    pixmaps.insert(  pair<COLOR,QPixmap>( FOREST,   QPixmap(resourcePrefix+"forest.png" ) )  );
    pixmaps.insert(  pair<COLOR,QPixmap>( LAKE,     QPixmap(resourcePrefix+"lake.png"   ) )  );
    pixmaps.insert(  pair<COLOR,QPixmap>( PASTURE,  QPixmap(resourcePrefix+"pasture.png") )  );
    pixmaps.insert(  pair<COLOR,QPixmap>( EMPTY,    QPixmap(resourcePrefix+"empty.png"  ) )  );
    pixmaps.insert(  pair<COLOR,QPixmap>( CASTLE,   QPixmap(resourcePrefix+"castle.png" ) )  );

    crownPixmaps.insert(pair<PLAYERCOLOR,QPixmap>(RED, QPixmap(resourcePrefix+"redCrown.png")));
    crownPixmaps.insert(pair<PLAYERCOLOR,QPixmap>(GREEN, QPixmap(resourcePrefix+"greenCrown.png")));
    crownPixmaps.insert(pair<PLAYERCOLOR,QPixmap>(BLUE, QPixmap(resourcePrefix+"blueCrown.png")));
    crownPixmaps.insert(pair<PLAYERCOLOR,QPixmap>(YELLOW, QPixmap(resourcePrefix+"yellowCrown.png")));


}

const QPixmap& ColorConverter::colorToPixmap(COLOR c){
    return pixmaps.at(c);
}

const QImage& ColorConverter::colorToImage(COLOR c){
    return images.at(c);
}
const QPixmap& ColorConverter::playerColorToPixmap(common::PLAYERCOLOR pc){
    QString resourcePrefix = ":/";
    return crownPixmaps.at(pc);
}
