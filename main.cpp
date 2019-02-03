#include <iostream>

using namespace std;

struct jumper {
	int mass;
	double angle;
	double speed;
	double location;
};

int main() {
	srand(time(NULL));
	jumper jumpers[100000];
	int location = rand() % 300 + 200;
	cout << "location is: " << location << endl;
	for(int i=0;i<100000;i++) {
		jumpers[i].mass = rand() % 50 + 50;
		jumpers[i].angle = (rand() % 36000) / 100.0;
		jumpers[i].speed = (rand() % 10000) / 100.0;
	}
	for(int i=0;i<100;i++) {
		cout << i + 1 << "'th jumper: " << endl;
		cout << "mass : " << jumpers[i].mass << endl;
		cout << "angle : " << jumpers[i].angle;
		cout << endl;
		cout << "speed : " << jumpers[i].speed;
		cout << endl;
		
	}
	return 0;
}
