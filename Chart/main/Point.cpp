//
//@Author StreakyPork
//@create 2019/5/8.
//
#include "..\include\Point.h"

    Point::Point(const int id){
        Point::id = id;
        color = "white";
        discover_time = 0;
        finish_time = 0;
        back = 0;
        parent = NULL;
    }

    Point::Point(const int id, const int discover_time){
        Point::id = id;
        Point::discover_time = discover_time;
        finish_time = 0;
        back = 0;
        color = "white";
        parent = NULL;
    }

    int Point::getID() const {
        return id;
    }
    string Point::getColor() const {
        return color;
    }
    void Point::setColor(const string color){
        Point::color = color;
    }
    int Point::getDiscoverTime() const {
        return discover_time;
    }
    void Point::setDiscoverTime(const int discoverTime) {
        discover_time = discoverTime;
    }
    int Point::getFinishTime() const {
        return finish_time;
    }
    void Point::setFinishTime(const int finishTime) {
        finish_time = finishTime;
    }
    int Point::getBack() const {
        return back;
    }
    void Point::setBack(const int back) {
        Point::back = back;
    }
    Point* Point::getParent() const{
        return parent;
    }
    void Point::setParent(Point* parent){
        Point::parent = parent;
    }
};

