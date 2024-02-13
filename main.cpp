#include "Tracing.h"

int main(){
    int h, w;
    std::cin >> w >> h;
    Canvas c{h, w};
    Camera cam;
    Scene scene(std::vector<Object*>{new Sphere(10, Vector3{1, 1, 1}, Vector3{255, 223, 253})});
    Vector3 O{1, 1, 1};
    for(auto y : range(0, Ch + 1)){
        for(auto x : range(0, Cw + 1)){
            Vector3 D = cam.CanvasToViewPort(x, y);
            double color = cam.TraceRay(O, D, 1, inf, scene);
            c.setPoint(x, y, color);
        }
    }
    c.show();
    std::cout << 'yes';
    system("pause");
}