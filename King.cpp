class King
{
private:
    int place;
    int owner;
public:
    void move(int newPlace) {place=newPlace;}
    int getPlace() {return place;}
	int getOwner() {return owner;}
};