#include "inc/pipex.h"
#include <stdio.h>

int main (void)
{
	char *line = get_next_line(1);
	printf("%s", line);
	free(line);
	return (0);
}
