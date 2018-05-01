#include "reader.h"

int main(int argc, char** argv){

	D_ARRAY d = readInput("/home/mont3iro68/Documents/SO/TP/SO-18/src/exemplo.nb");

	free_array(d);


	return 0;
}