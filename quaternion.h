#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Quaternion {
	public:
	// w is real part
	// x, y, z are imaginary parts
	double x, y, z, w;
	Quaternion(double x, double y, double z, double w);
	Quaternion();
        Quaternion operator*(const Quaternion& q);
        Quaternion operator*(const double s);
	Quaternion operator+(const Quaternion& q);

	Quaternion inverse();
	void set(double x, double y, double z, double w);

    // Overload stream extraction operator for input
    friend istream& operator>>(istream& is, Quaternion& q) {
        is >> q.x >> q.y >> q.z >> q.w;
        return is;
    }

    // Overload stream insertion operator for output
    friend ostream& operator<<(ostream& os, const Quaternion& q) {
        os << q.x << " " << q.y << " " << q.z << " " << q.w;
        return os;
    }
};
