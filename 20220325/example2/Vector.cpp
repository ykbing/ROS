#include <iostream>
#include <vector>

using namespace std;

struct Vector
{
	float x;
	float y;
	float z;
};

Vector Outer_V(Vector a, Vector b) // 외적
{
	Vector vt;

	vt.x = a.y * b.z - a.z * b.y;
	vt.y = a.z * b.x - a.x * b.z;
	vt.z = a.x * b.y - a.y * b.x;

	return vt;
}

float Inner_V(Vector a, Vector b) // 내적
{
	return a.x * b.x + a.y + b.y + a.z * b.z;
}


int main() {

	Vector v1, v2, v3;

	v1.x = 4, v1.y = 2, v1.z = 3;
	v2.x = 1, v2.y = 2, v2.z = 4;

	v3 = Outer_V(v1, v2);

	cout << "x = " << v3.x << endl << "y = " << v3.y << endl << "z = " << v3.z << endl;
	cout << "Inner = " << Inner_V(v1, v2) << endl;

	return 0;

}
