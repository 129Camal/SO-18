#include "reader.h"
#include "pipe.h"
#include "execute.h"

int main(int argc, char** argv){
	COMMAND* lc;
	int i;
	D_ARRAY d = readInput("/home/mont3iro68/Documents/SO/TP/SO-18/src/exemplo.nb");
	if (d){
		int count = getPos(d);
		lc = getArray(d);
		if(lc){
			for (i = 0;i < count ;i++){
				COMMAND c = lc[i];
				if (c){
					execute_no_pipe(c);
				}
				
			}
		}
	}

	free_array(d);


	return 0;
}