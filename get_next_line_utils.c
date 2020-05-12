#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

t_buff	*get_buff()
{
	t_buff	*temp;

	temp = (t_buff*)malloc(sizeof(t_buff));
	if (!temp)
		return (NULL);
	temp->idx = 0;
	temp->eol = 0;
	temp->line_size = 0;
	temp->line_idx = 0;
	return (temp);
}

t_list	*create_fd_node(int fd)
{
	t_list	*temp;

	temp = (t_list*)malloc(sizeof(t_list));
	temp->fd = fd;
	temp->tracker = get_buff();
	temp->next = NULL;
	return (temp);
}

t_buff	*add_fd_node(t_list **head, int fd)
{
	t_list	*curr;
	t_list	*temp;

	curr = *head;
	temp = create_fd_node(fd);
	if (!curr)
	{
		*head = temp;
		return (temp->tracker);
	}
	temp->next = curr->next;
	curr->next = temp;
	return (temp->tracker);
}

t_buff	*get_fd_node(t_list **head, int fd)
{
	t_list	*curr;
	char	test[1];

	curr = *head;
	if (fd < 0 || (read(fd, test, 0) == -1))
		return (NULL);
	if (!curr)
		return(add_fd_node(head, fd));
	while (curr->fd != fd && curr->next != NULL)
	{
		curr = curr->next;
	}
	if (curr->fd == fd) 
		return (curr->tracker);
	else
		return (add_fd_node(head, fd));
}

void	check_line_buff(char **line, t_buff **b)
{
	int	i;
	char	*temp;

	i = 0;
	if ((*b)->line_idx >= (*b)->line_size - 1)
	{
		(*b)->line_size = ((*b)->line_size == 0) ? 2 : (*b)->line_size;
		if(!(temp = (char*)malloc((*b)->line_size * (*b)->line_size * sizeof(char))))
			return ;
		if ((*b)->line_size > 2)
		{
			while (i < (*b)->line_size)
			{
				temp[i] = (*line)[i];
				i++;	
			}
			free(*line);
		}
		*line = temp;
		(*b)->line_idx = i;
		(*b)->line_size *= (*b)->line_size;
	}
	else
		(*b)->line_idx++;
}
