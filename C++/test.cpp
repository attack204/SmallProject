#include<iostream>
using namespace std;

class Point3d {
    xxx
public:
    Point3d normalize() const {
        register float msg = magnitude();
        Point3d normal;
        normal._x = _x / msg;
        normal._y = _y / msg;
        normla._z = _z / msg;
        return normal;
    }
};


void normalize_point3d7v(const Point3d * const this, Point3d &result) {
    register float msg = magnitude();
    result.Point3d::Point3d(); //constructor
    result._x = this->_x / msg;
    result._y = this->_y / msg;
    result._z = this->_z / msg;
    return
}


int main() {
    Point3d obj;
    Point3d *ptr = &obj;
    obj.normalize();
    ptr->normalize();


    Point3d result
    normalize_point3d7v(&obj, result)
    normalize_point3d7v(&ptr, result)

}

