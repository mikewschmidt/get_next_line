#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static t_list	*head;
	t_buff		*temp;
	int		j;

	j = 0;
	temp = get_fd_node(&head, fd);
	if (!temp)
		return (-1);
	if (temp->eol == 0)
		temp->eol = read(fd, temp->buff, BUFFER_SIZE);
	while (temp->buff[temp->idx] != '\n' && temp->eol > 0)
	{
		(*line)[j] = temp->buff[temp->idx];
		j++;
		temp->idx++;
		if (temp->buff[temp->idx] == '\0')
		{
			temp->eol = read(fd, temp->buff, BUFFER_SIZE);
			temp->idx = 0;
		}
	}
	(*line)[j] = '\0';
	set_tracking_vars(fd, temp);
	return (temp->endfile);
}
