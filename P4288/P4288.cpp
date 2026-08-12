#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using namespace std;

using Real = long double;

struct Point {
    Real x, y;
};

struct Circle {
    Point center;
    Real radius2;
};

Point operator+(const Point& a, const Point& b) {
    return {a.x + b.x, a.y + b.y};
}

Point operator-(const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
}

Point operator/(const Point& a, Real k) {
    return {a.x / k, a.y / k};
}

Real norm2(const Point& a) {
    return a.x * a.x + a.y * a.y;
}

Real cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

bool contains(const Circle& c, const Point& p) {
    if (c.radius2 < 0) return false;
    constexpr Real EPS = 1e-14L;
    Real distance2 = norm2(p - c.center);
    return distance2 <= c.radius2 + EPS * max(1.0L, c.radius2);
}

Circle diameterCircle(const Point& a, const Point& b) {
    Point center = (a + b) / 2;
    return {center, norm2(a - center)};
}

Circle circleThroughThree(const Point& a, const Point& b, const Point& c) {
    Point u = b - a;
    Point v = c - a;
    Real denominator = 2 * cross(u, v);

    // 理论上随机增量算法不会要求三个共线点确定圆。这里的分支用于
    // 处理完全共线或浮点计算下近乎共线的退化情况。
    Real scale = max({1.0L, norm2(u), norm2(v)});
    if (fabsl(denominator) <= 1e-24L * scale) {
        Circle best{{0, 0}, numeric_limits<Real>::infinity()};
        Circle candidates[] = {
            diameterCircle(a, b),
            diameterCircle(a, c),
            diameterCircle(b, c)
        };
        for (const Circle& candidate : candidates) {
            if (contains(candidate, a) && contains(candidate, b) &&
                contains(candidate, c) && candidate.radius2 < best.radius2) {
                best = candidate;
            }
        }
        return best;
    }

    Point offset{
        (norm2(u) * v.y - norm2(v) * u.y) / denominator,
        (u.x * norm2(v) - v.x * norm2(u)) / denominator
    };
    Point center = a + offset;
    return {center, norm2(a - center)};
}

Circle minimumEnclosingCircle(vector<Point> points) {
    mt19937 rng(static_cast<unsigned>(
        chrono::steady_clock::now().time_since_epoch().count()));
    shuffle(points.begin(), points.end(), rng);

    Circle circle{{0, 0}, -1};
    for (int i = 0; i < static_cast<int>(points.size()); ++i) {
        if (contains(circle, points[i])) continue;

        circle = {points[i], 0};
        for (int j = 0; j < i; ++j) {
            if (contains(circle, points[j])) continue;

            circle = diameterCircle(points[i], points[j]);
            for (int k = 0; k < j; ++k) {
                if (contains(circle, points[k])) continue;
                circle = circleThroughThree(points[i], points[j], points[k]);
            }
        }
    }
    return circle;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> points(n);
    for (Point& point : points) cin >> point.x >> point.y;

    int angleDegree, amplification;
    cin >> angleDegree >> amplification;

    const Real PI = acosl(-1.0L);
    Real angle = angleDegree * PI / 180;
    Real cosine = cosl(angle);
    Real sine = sinl(angle);

    // 先将增幅方向旋转到 x 轴，再把该方向压缩 amplification 倍。
    // 此变换把长短轴比固定的椭圆变成半径等于原半短轴的圆。
    for (Point& point : points) {
        Real x = point.x;
        Real y = point.y;
        point.x = (x * cosine + y * sine) / amplification;
        point.y = -x * sine + y * cosine;
    }

    Circle answer = minimumEnclosingCircle(points);
    cout << fixed << setprecision(3) << sqrtl(max(0.0L, answer.radius2)) << '\n';
    return 0;
}
