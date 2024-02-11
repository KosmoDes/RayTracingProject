#include "Tracing.h"

int main(){
    int h, w;
    std::cin >> h >> w;
    Canvas c = {h, w};
    Camera cam;
    Scene scene(std::vector<Object*>{new Sphere(2, Vector3{2, 2, 1}, Vector3{255, 255, 255})});
    Vector3 O{0, 0, 0};
}