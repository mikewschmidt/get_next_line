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
	temp->endfile = 1;
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

	curr = *head;
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

void	set_tracking_vars(int fd, t_buff *tracker)
{
	if (tracker->eol < BUFFER_SIZE && tracker->idx == tracker->eol - 1)
	{
		tracker->endfile = 0;
	}
	else if (tracker->idx == BUFFER_SIZE - 1)
	{
		tracker->idx = 0;
		tracker->eol = read(fd, tracker->buff, BUFFER_SIZE);
		if (tracker->eol == 0)
			tracker->endfile = 0;
	}
	else if (tracker->eol < tracker->idx)
	{
		tracker->endfile = 0;
	}
	else if (tracker->endfile == 1)
	{
		tracker->idx++;
		tracker->eol = 1;
	}
}
