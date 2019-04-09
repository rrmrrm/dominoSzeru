#ifndef KING_H
#define KING_H

class King
{
private:
    int place;
    int owner;
public:
    King();
    ~King();
    void move(int newPlace) {place=newPlace;}
    int getPlace() {return place;}
    int getOwner() {return owner;}
};

#endif // KING_H
