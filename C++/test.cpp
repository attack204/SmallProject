#include<iostream>

using std::cout;
using std::endl;

class Point2d {
public:
    float x, y;
};
class Point3d : public Point2d{
public:
    float z;
};
class Vertex {
public:
    float num;
};
class Vertex3D: public Point2d, public Vertex {
public:
    float mumble;
};



int main() {

}