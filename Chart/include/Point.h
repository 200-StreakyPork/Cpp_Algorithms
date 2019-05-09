//
//@Author StreakyPork
//@create 2019/5/8.
//

#ifndef ALGORITHMS_POINT_H
#define ALGORITHMS_POINT_H

class Point{
private:
    int id;
    string color;
    Point* parent;
    int discover_time;
    int finish_time;
    int back;
public:
    Point(const int id);
    Point(const int id, const int discover_time);
    int getID() const;
    string getColor() const;
    void setColor(const string color);
    int getDiscoverTime() const;
    void setDiscoverTime(const int discoverTime);
    int getFinishTime() const;
    void setFinishTime(const int finishTime);
    int getBack() const;
    void setBack(const int back);
    Point* getParent() const;
    void setParent(Point* parent);
};

#endif //ALGORITHMS_POINT_H
