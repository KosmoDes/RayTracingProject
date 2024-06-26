#include "Tracing.h"
#include "FastPrinting.h"

//Canvas
Canvas::Canvas(int _h, int _w): _height(_h), _width(_w){
    this->_window.resize(_h);
    this->_height = _h;
    this->_width = _w;
    for(auto &x : this->_window){
        x.resize(_w);
    }
    for(auto &x : this->_window){
        for(auto &y : x){
            y = '.';
        }
    }
}

bool Canvas::show(){
    for(auto x : this->_window){
        for(auto y : x){
            writeChar(y);
        }
        writeChar('\n');
    }
    return 1;
}

void Canvas::next_frame(){
    for(auto x : this->_window){
        for(auto y : x){
            writeChar('.');
        }
        writeChar('\n');
    }
}

void Canvas::setPoint(int x, int y, int brightnes=1){
    if (x < 0 || x >= this->_window.size() || y < 0 || y >= this->_window[0].size()) {
        return;
    }
    this->_window[x][y] = this->symbols[brightnes%3];
}

//Vector3
Vector3::Vector3(){
    this->_vec[0] = 0;
    this->_vec[1] = 0;
    this->_vec[2] = 0;
}

Vector3::Vector3(double x, double y, double z){
    this->_vec[0] = x;
    this->_vec[1] = y;
    this->_vec[2] = z;
}

Vector3 Vector3::operator +(Vector3 vec){
    Vector3 res;
    res._vec[0] = this->_vec[0] + vec._vec[0];
    res._vec[1] = this->_vec[1] + vec._vec[1];
    res._vec[2] = this->_vec[2] + vec._vec[2];
    return res;
}

Vector3 Vector3::operator -(Vector3 vec){
    Vector3 res;
    res._vec[0] = this->_vec[0] - vec._vec[0];
    res._vec[1] = this->_vec[1] - vec._vec[1];
    res._vec[2] = this->_vec[2] - vec._vec[2];
    return res;
}

double Vector3::operator *(Vector3 vec){
    double res = 0;
    for(int i = 0; i < 3; ++i){
        res += this->_vec[i]*vec._vec[i];

    }
    return res;
}

double Vector3::length(){
    return sqrt(this->_vec[0]*this->_vec[0] + this->_vec[1]*this->_vec[1] + this->_vec[2]*this->_vec[2]);
}

double& Vector3::operator[](int i){
    return this->_vec[i];
}

std::ostream& operator <<(std::ostream& os, Vector3& vec){
    for(auto x : vec._vec){
        os << x << ' ';
    }
    os << ' ';
    return os;
}

//Scene
Scene::Scene(){
    this->_objects = {new Object()};
}
Scene::Scene(std::vector<Object*> obj){
    for(auto x : obj) {
        this->_objects.push_back(x);
    }
}

//Camera
Vector3 Camera::CanvasToViewPort(int x, int y){
    Vector3 res = {x*this->Vw/Ch, y*this->Vh/Cw, this->d};
    return res;
}

std::vector<double> Camera::IntersectSphere(Vector3 O, Vector3 D, Sphere *sphere){
    Vector3 C = sphere->coords;
    double r = sphere->radius;
    Vector3 oc = O - C;
    
    double k1 = D*D;
    double k2 = 2*(oc*D);
    double k3 = (oc*oc) - r*r;
    
    double discriminant = k2*k2 - 4 * k1*k3;
    if(discriminant < 0){
        return std::vector<double>{inf, inf};
    }
    
    double t1 = (-k2 + sqrt(discriminant)) / (2*k1);
    double t2 = (-k2 - sqrt(discriminant)) / (2*k1);

    return std::vector<double>{t1, t2};
}

double Camera::TraceRay(Vector3 O, Vector3 D, double t_min, double t_max, Scene scene){
    double closest_t = inf;
    Object* closest_sphere = new Object();
    for(auto sphere : scene._objects){
        std::vector<double> t1t2 = IntersectSphere(O, D, dynamic_cast<Sphere*>(sphere));
        if (t_min <= t1t2[0] && t1t2[0] <= t_max && t1t2[0] < closest_t){
            closest_t = t1t2[0];
            closest_sphere = sphere;
        }
        if (t_min <= t1t2[1] && t1t2[1] <= t_max && t1t2[1] < closest_t){
            closest_t = t1t2[0];
            closest_sphere = sphere;
        }
    }
    if(closest_sphere->type != "sphere"){
        return 0;
    }
    return closest_sphere->color.length();
}

//functions
std::vector<int> range(int first, int last, int step){
    std::vector<int> res;
    int el = first;
    while(el != last){
        res.push_back(el);
        el += step;
    }
    return res;
}