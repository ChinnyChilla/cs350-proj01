#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(int argc, char * argv[])
{    
    if(argc != 2){
        printf(1, "Please provide your age\n");
		exit();
    };
	// check if argv1 is not a number
	if (atoi(argv[1]) == 0) {
		printf(1, "Please provide a valid number\n");
		exit();
	};
	if (age(atoi(argv[1])) < 0)
		{
			printf(1, "Some error happened\n");
		};
    exit(); //return 0;
}