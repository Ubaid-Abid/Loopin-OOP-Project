#pragma once

class Date {
private:
	int d, m, y;
public:
	Date(int d = 0, int m = 0, int y = 0) :d(d), m(m), y(y) {}
	void set_Date(int& d, int& m, int& y) {
		this->d = d;
		this->m = m;
		this->y = y;
	}
	Date operator=(const Date& temp) {
		d = temp.d;
		m = temp.m;
		y = temp.y;
		return *this;
	}
	bool operator==(const Date& dat)
	{
		return y == dat.y && m == dat.m && d == dat.d;
	}
	bool operator<(const Date& temp) {
		if (y != temp.y) return y < temp.y;
		else if (m != temp.m) return m < temp.m;
		else                     return d < temp.d;
	}
	int get_d() { return d; }
	int get_m() { return m; }
	int get_y() { return y; }
	~Date() {};
};
