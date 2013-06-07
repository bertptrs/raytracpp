#include "OutputBitmap.h"

ostream& operator << (ostream& output, OutputBitmap* bitmap) {
	bitmap->write(output);
	return output;
}
