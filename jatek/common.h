#ifndef COMMON_H
#define COMMON_H

namespace common{

enum DIR {UP, DOWN, LEFT, RIGHT};
enum PLAYERCOLOR{ RED, GREEN, BLUE, YELLOW};

///\value  _lastVal :
/// ha _lastVal-tól balra vannak az értékek (SWAMP...CASTLE), akkor
/// _lastVal egyenlő a COLOR értékeinek a számával, és ez nekem jól jön.
enum COLOR{ SWAMP, MOUNTAIN, WHEATFIELD, FOREST, LAKE, PASTURE, EMPTY, CASTLE, _lastVal};

}

#endif //COMMON_H;
