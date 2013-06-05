#include <iostream>
#include "common.h"

using namespace std;

int main() {
	cout << "Test program started." << endl;
	color c(0.5, 0.3, 0.1);
	cout << c << endl;
	c *= 2;
	cout << c << endl;
	c = 2 * c;
	cout << c << endl;
	return 0;
}
