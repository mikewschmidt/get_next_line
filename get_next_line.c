#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>

int	get_next_line(int fd, char **line)
{
	static t_list	*head;
	t_buff		*temp;
	int		j;

	j = 0;
	if(!(temp = get_fd_node(&head, fd)))
		return (-1);
	if(temp->idx == 0)
		if((temp->eol = read(fd, temp->buff, BUFF_SIZE)) == 0)
			return (0);
	check_line_buff(line, &temp);
	while (temp->buff[temp->idx] != '\n' && temp->eol > 0)
	{
		check_line_buff(line, &temp);
		(*line)[j++] = temp->buff[temp->idx++];
		if (temp->idx >= temp->eol)
		{
			temp->eol = read(fd, temp->buff, BUFF_SIZE);
			temp->idx = 0;
		}
	}
	(*line)[j] = '\0';
	temp->line_size = 0;
	(temp->idx >= temp->eol - 1) ? (temp->idx = 0) : (temp->idx++);
	return (1);
}
