#include <osbind.h>
#include "input.h"
#include "types.h"

bool has_input() {
	return Cconis();
}

char get_input() {
	return Cconin();
}