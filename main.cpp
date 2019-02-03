#include <iostream>
#include <cmath>

using namespace std;

struct jumper {
	int mass;
	double angle;
	double speed;
	double location;
};

int main() {
	constexpr double PI = 3.141592;
	constexpr double G = 9.81;
	srand(time(NULL));
	jumper jumpers[100000];
	int location = rand() % 10000 + 100;
	cout << "location is: " << location << endl;
	for(int i=0;i<100000;i++) {
		jumpers[i].mass = rand() % 70 + 30;
		jumpers[i].angle = (rand() % 9000) / 100.0 * PI / 180;
		jumpers[i].speed = (rand() % 100000 + 100) / jumpers[i].mass;
		jumpers[i].location = jumpers[i].speed * jumpers[i].speed * sin(2*jumpers[i].angle) / G; 
	}
	for(int i=0;i<100;i++) {
		cout << i + 1 << "'th jumper: " << endl;
		cout << "X location : " << jumpers[i].location;
		cout << endl;
		
	}
	return 0;
}
