# get_next_line
Function to read from a file descriptor one line at a time, every time it is called.



DESCRIPTION:
Call the get_next_line fuction to read a line of text from the specified file descriptor (fd), without the newline, into a variable (line).
Calling the function get_next_line in a loop will then allow you to read the text available on a file descriptor one line at a time until the EOF.
Must use a macro definition variable named BUFFER_SIZE and define a size, to specify how many bytes are being read from the read call. 
Example when compiling: 
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32
get_next_line.c get_next_line_utils.c

PROTOTYPE
int get_next_line(int fd, char **line)

INPUT
fd: file descriptor to receive input data
line: string pointer variable that stores the line read

OUTPUT
1: A line has been read
0: EOF (End-Of-File) has been reached
-1: An error occured


INTERNAL EXPLAINATION OF FUNCTIONS
Variables:
static t_list *head: 
A static linked list that points to the head of the linked list. It is static so it will remain persistent across function calls



