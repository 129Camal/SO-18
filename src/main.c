#include "reader.h"

int main(int argc, char** argv){

	D_ARRAY d = readInput("/Users/fredericopinto/Documents/SO-18/src/exemplo.nb");

	free_array(d);


	return 0;
}