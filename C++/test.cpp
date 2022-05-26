#include<iostream>

using std::cout;
using std::endl;

class Point2d {
public:
    float x, y;
    //virtual function
    virtual func() {}
};
class Point3d : public Point2d{
public:
    float z;
};
class Vertex {
public:
    Vertex *next;
    virtual func() {}
};
class Vertex3D: public Point2d, public Vertex {
public:
    float mumble;
};



int main() {

}