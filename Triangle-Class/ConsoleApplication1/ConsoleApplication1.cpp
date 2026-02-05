#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;
struct Point {double x, y;};
class Triangle {
public:
    Triangle() {};
    Triangle(Point a, Point b, Point c) :
        a_(a),
        b_(b),
        c_(c) {
        try
        {
            check_tirangle(a_, b_, c_);
        }
        catch (const std::exception& e)
        {
            cout << e.what() << endl;
            exit(EXIT_FAILURE);
        }
        calc_perimeter();
        calc_ploshad();
    };

    double get_perimeter() { return perimetr; }

    array<double, 3> get_sides() { return sides; }
    
    double get_ploshad() { return ploshad; }

    string move_triangle(double k) { return move_str(k); }
    


private:
    Point a_;
    Point b_;
    Point c_;

    array<double, 3> sides = {0, 0, 0};

    double perimetr = 0;
    double ploshad = 0;

    string move_str(double k){
        ostringstream info_position;
        a_.x += k;
        a_.y += k;
        b_.x += k;
        b_.y += k;
        c_.x += k;
        c_.y += k;
        info_position << "(" << a_.x << "," << a_.y << ") " << "(" << b_.x << "," << b_.y << ") " << "(" << c_.x << "," << c_.y << ")";
        return info_position.str();
    }

    void calc_perimeter() {
        sides[0] = hypot(b_.x - a_.x, b_.y - a_.y);
        sides[1] = hypot(c_.x - b_.x, c_.y - b_.y);
        sides[2] = hypot(a_.x - c_.x, a_.y - c_.y);
        perimetr = accumulate(sides.begin(), sides.end(), 0.0);
        sort(sides.begin(), sides.end());
    }

    void calc_ploshad() {
        double pol_per = perimetr / 2;
        double temp = pol_per * (pol_per - sides[0]) * (pol_per - sides[1]) * (pol_per - sides[2]);
        ploshad = pow(temp, 0.5);
    }

    bool same(Point a, Point b) {
        if (a.x == b.x && a.y == b.y) { return true; }
        return false;
    };

    void check_tirangle(Point a, Point b, Point c, double eps = 1e-9) {
        double cross = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
        if (std::fabs(cross) < eps)
        {
            throw runtime_error("ERROR: it is impossible to construct a triangle from given points");
        }

        if (same(a, b) || same(a, c) || same(b, c))
        {
            throw runtime_error("ERROR: it is impossible to construct a triangle from given points");
        }
    }
};

bool check_eq_triangles(Triangle tr1, Triangle tr2, double eps = 1e-9) {
    auto arr1 = tr1.get_sides();
    auto arr2 = tr2.get_sides();
    bool eq1 = fabs(arr1[0] - arr2[0]) < eps;
    bool eq2 = fabs(arr1[1] - arr2[1]) < eps;
    bool eq3 = fabs(arr1[2] - arr2[2]) < eps;
    return (eq1 and eq2 and eq3);
}
bool check_eq_plosh_triangle(Triangle tr1, Triangle tr2, double eps = 1e-9) {
    return fabs(tr1.get_ploshad() - tr2.get_ploshad()) < eps;
}

int main()
{
    setlocale(LC_ALL, "ru");
    cout << fixed << setprecision(2);
    Point a;
    Point b;
    Point c;
    double k;

    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    Triangle triangleR(a, b, c);
    cout << "perimeterR: " << triangleR.get_perimeter() << endl;

    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    Triangle triangleP(a, b, c);
    cout << "perimeterP: " << triangleP.get_perimeter() << endl;

   
    

    if (check_eq_triangles(triangleR, triangleP)) {
        cout << "The triangles are equal" << endl;
    }
    else {
        cout << "The triangles are not equal" << endl;
    }

    if (check_eq_plosh_triangle(triangleR, triangleP)) {
        cout << "The areas are equal" << endl;
    }
    else {
        cout << "The areas are not equal" << endl;
    }

    cin >> k;

    cout << "TriangleP moved, new vertices=" << triangleP.move_triangle(k) << endl;
    
}