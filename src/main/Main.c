// C standard includes
#include <stdio.h>
#include "platform.h"


int main()
{

	char pl_message[40];	// Since char * or char [] are both variable are already reference address. we don't need to use ampersand.
	print_platform(pl_message);
	printf("%s", pl_message);
    return 0;
}
