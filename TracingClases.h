#include "STLheaders.h"

#define inf 1e10
#define Ch 100
#define Cw 100

class Canvas{
public:
    int _height, _width;
    char symbols[3] = {'.', '|', '&'};

    std::vector<std::vector<char>> _window;

    Canvas(int _h, int _w);
    
    void show();
    void setPoint(int x, int y, int brightnes);
};

class Vector3{
public:
    double _vec[3];
    
    Vector3();
    Vector3(double, double, double);

    Vector3 operator +(Vector3);
    Vector3 operator -(Vector3);
    double operator *(Vector3);

    double length();
};

class Object{
public:
    std::string type = "none";

    Vector3 coords = {1, 1, 1};

    Vector3 color = {255, 255, 255};
    
    Object(std::string type = "none", Vector3 coords = {1, 1, 1}, Vector3 color = {1, 1, 1}) : type(type), coords(coords), color(color) {}
    virtual ~Object() = default;
};

class Sphere: public Object{
public:
    double radius = 1;
    
    Sphere() : Object("sphere"){}
    Sphere(double radius, Vector3 center, Vector3 color) : Object("sphere", center, color), radius(radius) {}
};

class Scene{
public:
    std::vector<Object*> _objects;

    Scene();
    Scene(std::vector<Object*>);
};

class Camera: public Object{
public:
    double d = 1;
    
    double Vw = d, Vh = d;
    
    Vector3 color = {0, 0, 0}, coords = {0, 0, 0};
    
    Camera(): d(1), Vw(1), Vh(1), Object("camera", coords, color){}
    Camera(double d): d(d), Vw(d), Vh(d), Object("camera", coords, color){}
    Vector3 CanvasToViewPort(int x, int y);
    double TraceRay(Vector3 O, Vector3 D, double t_min, double t_max, Scene scene);
    std::vector<double> IntersectSphere(Vector3 O, Vector3 D, Sphere *sphere);
};