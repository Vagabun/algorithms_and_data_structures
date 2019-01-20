#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::endl;

typedef long long int long_t;

long_t upgraded_gcd(const long_t &a, const long_t &b, long_t &x, long_t &y) {
    long_t new_x, new_y, g;
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    else {
        g = upgraded_gcd(b % a, a, new_x, new_y);
        x = new_y - (b / a) * new_x;
        y = new_x;
    }
    return g;
}

bool find_solution(const long_t &a, const long_t &b, const long_t &c, long_t &x, long_t &y) {
    long_t g;
    g = upgraded_gcd(a, b, x, y);
    if (c % g != 0)
        return false;
    else {
        x *= (c / g);
        y *= (c / g);
    }
    return true;
}

int main() {

    ifstream input("input.txt");
    ofstream output("output.txt");

    long_t a, b, c, x, y;

    input >> a >> b >> c;
    if (find_solution(a, b, c, x, y))
        output << x << " " << y << endl;
    else
        output << -1 << endl;

    input.close();
    output.close();

    return 0;
}