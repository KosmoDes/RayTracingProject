#include "Tracing.h"

int main(){
    int h, w, d;
    std::cin >> w >> h >> d;
    Canvas c{h, w};
    Scene scene(std::vector<Object*>{new Sphere(2, Vector3{2.4, 4, 8}, Vector3{255, 223, 253})});
    Vector3 O{0, 0, 0};
    Camera cam(d, O);
    for(auto y : range(0, Ch + 1)){
        for(auto x : range(0, Cw + 1)){
            Vector3 D = cam.CanvasToViewPort(x, y);
            double color = cam.TraceRay(O, D, d, inf, scene);
            c.setPoint(x, y, color);
        }
    }
    c.show();
    c.next_frame();
    scene._objects[0]->coords[1]++;
    for(auto y : range(0, Ch + 1)){
        for(auto x : range(0, Cw + 1)){
            Vector3 D = cam.CanvasToViewPort(x, y);
            double color = cam.TraceRay(O, D, d, inf, scene);
            c.setPoint(x, y, color);
        }
    }
    c.show();
}