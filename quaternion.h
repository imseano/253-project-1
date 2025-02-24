class Quaternion {
	public:
	// w is real part
	// x, y, z are imaginary parts
	double x, y, z, w;
	Quaternion(double x, double y, double z, double w);
	Quaternion();
        Quaternion& operator*(Quaternion& q);
        Quaternion& operator*(double s);
	Quaternion& operator+(Quaternion& q);

	Quaternion inverse();
	void set(double x, double y, double z, double w);
};
