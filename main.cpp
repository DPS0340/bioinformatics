#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

constexpr double PI = 3.141592;
constexpr double G = 9.81;

struct jumper {
	int mass;
	int angle;
	int speed;
	int location;
};

double abs(double a, double b) {
	return a > b ? a - b : b - a;
}

jumper* nextgen(jumper arr[], int len, int location) {
	jumper* result = new jumper[len];
	for (int i = 0; i < len; i++) {
		int j;
		int index;
		for (j = 0; j < len * 2; j++) {
			if (arr[j].location != -1) {
				index = j;
				break;
			}
		}
		for (; j < len * 2; j++) {
			if (arr[j].location != -1) {
				if (abs(arr[j].location, location) < abs(arr[index].location, location)) {
					index = j;
				}
			}
		}
		result[i] = arr[index];
		arr[index].location = -1;
	}
	for (int i = 0; i < len; i++) {
		if (result[i].location < location) {
			result[i].angle = result[i].angle | result[rand() % len].angle;
		}
		else {
			result[i].angle = result[i].angle & result[rand() % len].angle;
		}
		if (result[i].location < location) {
			result[i].mass = result[i].mass & result[rand() % len].mass;
		}
		else {
			result[i].mass = result[i].mass | result[rand() % len].mass;
		}
		if (result[i].location < location) {
			result[i].speed = result[i].speed | result[rand() % len].speed;
		}
		else {
			result[i].speed = result[i].speed & result[rand() % len].speed;
		}
		if (result[i].mass == 0) {
			result[i].mass = rand() % 90 + 10;
		}
		if (result[i].speed == 0) {
			result[i].speed = (rand() % 100000) + 100;
		}
		if (result[i].angle == 0) {
			result[i].angle = (rand() % 45) + 1;
		}
		result[i].location = result[i].speed / result[i].mass * result[i].speed / result[i].mass  * sin(2 * result[i].angle * PI / 180) / G;
	}
	return result;
}

int main() {
	int n = 2048;
	srand(time(NULL));
	jumper* jumpers = new jumper[n];
	int location = rand() % 10000 + 100;
	cout << "목적지: " << location << "m" << endl;
	for (int i = 0; i < n; i++) {
		jumpers[i].mass = rand() % 90 + 10;
		jumpers[i].angle = (rand() % 45) + 1;
		jumpers[i].speed = (rand() % 100000) + 100;
		jumpers[i].location = jumpers[i].speed / jumpers[i].mass * jumpers[i].speed / jumpers[i].mass * sin(2 * jumpers[i].angle * PI / 180) / G;
	}
	for (int half = n / 2; half != 0; half /= 2) {
		jumpers = nextgen(jumpers, half, location);
		double x, y;
		x = y = 0.0;
		/*
		for (int i = 0; i < half; i++) {
			cout << i + 1 << "'th" << endl;
			if (jumpers[i].mass == 0) {
				continue;
			}
			double maxt = 2 * sin(jumpers[i].angle * PI / 180) / G * jumpers[i].speed / jumpers[i].mass;
			for (int t = 0; t <= maxt; t++) {
				x = t * cos(jumpers[i].angle * PI / 180) * jumpers[i].speed / jumpers[i].mass;
				y = t * sin(jumpers[i].angle * PI / 180) * jumpers[i].speed / jumpers[i].mass - G * t * t / 2;
				cout << "x: " << x << ", y: " << y << '\r';
			}
			cout << endl;
		}
		*/
	}
	cout << "목적지: " << location << "m" << endl;
	if (location < jumpers[0].location) {
		cout << jumpers[0].location - location << "만큼 더 갔습니다! " << endl;
	}
	else if (location > jumpers[0].location) {
		cout << location - jumpers[0].location << "만큼 덜 갔습니다! " << endl;
	}
	else {
		cout << "정확하게 도착했습니다!" << endl;
	}
	cout << "질량: " << jumpers[0].mass << "kg" << endl;
	cout << "각도: " << jumpers[0].angle << "도" << endl;
	cout << "속도: " << jumpers[0].speed / jumpers[0].mass << "m/s" << endl;
	delete[] jumpers;
	return 0;
}
