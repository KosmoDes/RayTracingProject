#include "Tracing.h"
#include "conio.h"

int main(){
    using std::operator""s;
    int h, w, d;
    Canvas c{Ch, Cw};
    Scene scene(std::vector<Object*>{new Sphere(25, Vector3{30, 25, 100}, Vector3{255, 223, 253})});
    Vector3 O{0, 0, 0};
    Camera cam(1, O);
    for(auto x : range(0, Cw + 1)){
        for(auto y : range(0, Ch + 1)){
            Vector3 D = cam.CanvasToViewPort(x, y);
            double color = cam.TraceRay(O, D, 1, inf, scene);
            c.setPoint(x, y, color);
        }
    }
    c.show();
}