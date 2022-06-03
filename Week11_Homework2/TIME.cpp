#include <cstdio>
#include <iostream>
using namespace std;

class TimeHMS {
public:
	int hour, min, sec;
	TimeHMS(int h = 0, int m = 0, int s = 0) : hour(h), min(m), sec(s) { }
	void print(const char* msg) {
		printf("%s %d :  %d :  %d \n", msg, hour, min, sec);
	}
	TimeHMS operator+(TimeHMS t) {
		return TimeHMS(hour + t.hour + (min + t.min + (sec + t.sec) / 60) / 60,
			(min + t.min + (sec + t.sec) / 60) - 60 * ((min + t.min + (sec + t.sec) / 60) / 60),
			(sec + t.sec) - 60 * ((sec + t.sec) / 60));
	}
	TimeHMS operator-(TimeHMS t) {
		return TimeHMS(hour - t.hour - (min - t.min - (sec - t.sec) / 60) / 60,
			(min - t.min - (sec - t.sec) / 60) - 60 * ((min - t.min - (sec - t.sec) / 60) / 60),
			(sec - t.sec) - 60 * ((sec - t.sec) / 60));
	}
	bool operator==(TimeHMS t) {
		return hour == t.hour && min == t.min && sec == t.sec;
	}
	bool operator!=(TimeHMS t) {
		return hour != t.hour || min != t.min || sec != t.sec;
	}
	TimeHMS& operator++()
	{
		hour += 1;
		return *this;
	}
	TimeHMS& operator--()
	{
		hour -= 1;
		return *this;
	}
	const TimeHMS operator++(int)
	{
		const TimeHMS h(hour);
		hour += 1;
		return h;
	}
	const TimeHMS operator--(int)
	{
		const TimeHMS h(hour);
		hour -= 1;
		return h;
	}
	int& operator[](int id) {
		if (id == 0) return hour;
		else if (id == 1) return min;
		else return sec;
	}
	operator int() {
		return (int)hour * 3600 + min * 60 + sec;
	}
	operator double() {
		return (double)(hour * 3600 + min * 60 + sec) / 3600;
	}
	friend TimeHMS operator*(int n, TimeHMS t) {
		return TimeHMS(n * t.hour + (n * t.min + n * t.sec / 60) / 60,
			(n * t.min + n * t.sec / 60) - 60 * ((n * t.min + n * t.sec / 60) / 60),
			n * t.sec - 60 * (n * t.sec / 60));
	}
	friend istream& operator>>(istream& is, TimeHMS& t);
	friend ostream& operator<<(ostream& os, const TimeHMS& t);
};
istream& operator>>(istream& is, TimeHMS& t) {
	is >> t.hour;
	is >> t.min;
	is >> t.sec;
	return is;
}
ostream& operator<<(ostream& os, const TimeHMS& t) {
	os << "t : " << t.hour << ":" << t.min << ": " << t.sec << "" << endl;
	return os;
}
void main() {
	TimeHMS t;
	TimeHMS t1(1, 20, 30), t2(4, 35, 46), t3;
	t1.print("t1 :");
	t2.print("t2 :");
	t3 = t1 + t2;
	t3.print("t3 = t1 + t2 :");
	t3 = t1 - t2;
	t3.print("t3 = t1 - t2 :");
	if (t1 == t2) {
		printf("t1 == t2");
	}
	else if (t1 != t2) {
		printf("t1 != t2\n");
	}
	++t1;
	t1.print("++t1 :");
	--t1;
	t1.print("--t1 :");
	t1++;
	t1.print("t1++ :");
	t1--;
	t1.print("t1-- :");
	printf("t1[0] : %d:\n", t1[0]);
	printf("t1[1] : %d:\n", t1[1]);
	printf("t1[2] : %d:\n", t1[2]);
	printf("(int)t1 : %d:\n", (int)t1);
	printf("(double)t1 : %f:\n", (double)t1);
	t1 = 2 * t1;
	t1.print("2*t1 :");
	cout << "\n" << "시간 분 초 입력하세요 :\n";
	cin >> t;
	cout << t;
}