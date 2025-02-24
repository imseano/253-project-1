#include "quaternion.h"

Quaternion::Quaternion(double x, double y, double z, double w) {
        this->x = x;
	this->y = y;
        this->z = z;
        this->w = w;
}

Quaternion::Quaternion() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->w = 0;
}

Quaternion& Quaternion::operator*(Quaternion& q) {
        Quaternion& r = *this;
	Quaternion temp;
	temp.x = r.x * q.w + r.y * q.z - r.z * q.y + r.w * q.x;
	temp.y = -r.x * q.z + r.y * q.w + r.z * q.x + r.w * q.y;
	temp.z = r.x * q.y - r.y * q.x + r.z * q.w + r.w * q.z;
	temp.w = -r.x * q.x - r.y * q.y - r.z * q.z + r.w * q.w;

	r = temp;
        return *this;
}

Quaternion& Quaternion::operator*(double s) {
        Quaternion& r = *this;
        r.x = r.x * s;
        r.y = r.y * s;
        r.z = r.z * s;
        r.w = r.w * s;
        return *this;
}

Quaternion& Quaternion::operator+(Quaternion& q) {
        Quaternion& r = *this;
	r.x = r.x + q.x;
	r.y = r.y + q.y;
	r.z = r.z + q.z;
	r.w = r.w + q.w;
        return *this;
}

Quaternion Quaternion::inverse() {
        Quaternion r = *this;
	return Quaternion(-r.x, -r.y, -r.z, r.w);
}

void Quaternion::set(double x, double y, double z, double w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
}



