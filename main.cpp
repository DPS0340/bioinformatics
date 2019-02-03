#include <iostream>
#include <cmath>

using namespace std;

constexpr double PI = 3.141592;
constexpr double G = 9.81;

struct jumper {
	int mass;
	int angle;
	int speed;
	int location;
};

int abs(int a, int b) {
	return a > b ? a - b : b - a;
}

jumper* nextgen(jumper arr[], int len, int location) {
	jumper* result = (jumper*)malloc(sizeof(jumper) * len);
	for(int i=0;i<len;i++) {
		if(arr[i].location < location) {
			result[i].angle = arr[i].angle | arr[rand() % len].angle;
		} else {
			result[i].angle = arr[i].angle & arr[rand() % len].angle;
		}
		if(arr[i].location < location) {
			result[i].mass = arr[i].mass | arr[rand() % len].mass;
		} else {
			result[i].mass = arr[i].mass & arr[rand() % len].mass;
		}
		if(arr[i].location < location) {
			result[i].speed = arr[i].speed | arr[rand() % len].speed;
		} else {
			result[i].speed = arr[i].speed & arr[rand() % len].speed;
		}
		if(result[i].mass == 0) {
			result[i].mass = rand() % 70 + 30;
		}
		if(result[i].speed == 0) {
			result[i].speed = rand() % 1000;
		}
		result[i].location = result[i].speed / result[i].mass / 10.0 * result[i].speed / result[i].mass / 10.0 * sin(2*result[i].angle * PI / 180) / G; 
	}
	return result;
}

int main() {
	constexpr int n = 500;
	srand(time(NULL));
	jumper* jumpers = (jumper*)malloc(sizeof(jumper) * n);
	int location = rand() % 10000 + 100;
	cout << "location is: " << location << endl;
	for(int i=0;i<n;i++) {
		jumpers[i].mass = rand() % 80 + 10;
		jumpers[i].angle = (rand() % 900);
		jumpers[i].speed = (rand() % 1000000) + 1;
		jumpers[i].location = jumpers[i].speed / jumpers[i].mass / 10.0 * jumpers[i].speed / jumpers[i].mass / 10.0 * sin(2*jumpers[i].angle * PI / 180) / G; 
	}
	for(int i=0;i<n;i++) {
		cout << i + 1 << "'th jumper: " << endl;
		if(location < jumpers[i].location) {
			cout << jumpers[i].location - location << "만큼 더 갔습니다! " << endl;
		}
		else if(location > jumpers[i].location) {
			cout << location - jumpers[i].location << "만큼 덜 갔습니다! " << endl;
		} else {
			cout << "정확하게 도착했습니다!" << endl;
		}
	}
	for(int half = n / 2; half != 0; half /= 2) {
		jumper* nextjumpers = (jumper*)malloc(sizeof(jumper) * half);
		for(int i=0;i<half;i++) {
			int j;
			int index;
			for(j=0;j<n;j++) {
				if(jumpers[j].location != -1) {
					index = j;
					break;
				}
			}
			for(;j<n;j++) {
				if(jumpers[j].location != -1) {
					if(abs(jumpers[j].location, location) < abs(jumpers[index].location, location)) {
						index = j;
					}
				}
			}
			nextjumpers[i] = jumpers[index];
			jumpers[index].location = -1;
		}
		jumpers = nextgen(nextjumpers, half, location);
		for(int i=0;i<half;i++) {
			cout << i + 1 << "'th jumper: " << endl;
			if(location < jumpers[i].location) {
				cout << jumpers[i].location - location << "만큼 더 갔습니다! " << endl;
			}
			else if(location > jumpers[i].location) {
				cout << location - jumpers[i].location << "만큼 덜 갔습니다! " << endl;
			} else {
				cout << "정확하게 도착했습니다!" << endl;
			}
		}
	}
	cout << "질량: " << jumpers[0].mass << endl;
	cout << "각도: " << jumpers[0].angle / 10.0 << endl;
	cout << "속도: " << jumpers[0].speed << endl;
	return 0;
}
