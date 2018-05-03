#include "reader.h"

int main(int argc, char** argv){
	COMMAND* lc;
	int i;
	D_ARRAY d = readInput("/home/mont3iro68/Documents/SO/TP/SO-18/src/exemplo.nb");
	if (d){
		int count = getPos(d);
		lc = getArray(d);
		if(lc){
			for (i = 0;i < count ;++i){
				COMMAND c = lc[i];
				if (c)
				printf("Descrição|%s| \nInput|%s| \n",getDescription(c),getInput(c));
			}
		}
	}

	free_array(d);


	return 0;
}