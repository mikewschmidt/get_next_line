/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:29:49 by mschmidt          #+#    #+#             */
/*   Updated: 2020/08/15 02:16:49 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_buff	*get_buff(void)
{
	t_buff	*temp;

	temp = (t_buff*)malloc(sizeof(t_buff));
	if (!temp)
		return (NULL);
	temp->idx = 0;
	temp->read_size = 0;
	temp->ln_siz = 0;
	temp->line_idx = 0;
	return (temp);
}

t_list	*create_fd_node(int fd)
{
	t_list	*temp;

	temp = (t_list*)malloc(sizeof(t_list));
	temp->fd = fd;
	if (!(temp->tracker = get_buff()))
		return (NULL);
	temp->next = NULL;
	return (temp);
}

t_buff	*add_fd_node(t_list **head, int fd)
{
	t_list	*curr;
	t_list	*temp;

	curr = *head;
	if (!(temp = create_fd_node(fd)))
		return (NULL);
	if (!curr)
	{
		*head = temp;
		return (temp->tracker);
	}
	temp->next = curr->next;
	curr->next = temp;
	return (temp->tracker);
}

void	remove_fd_node(t_list **head, int fd)
{
	t_list	*curr;
	t_list	*prev;

	if (!head || !*head || fd < 0)
		return ;
	curr = *head;
	prev = curr;
	if ((*head)->fd == fd)
	{
		*head = curr->next;
		free(curr->tracker);
		free(curr);
		curr = NULL;
	}
	while (curr != NULL)
	{
		if (curr->fd == fd)
		{
			if ((*head)->fd == fd)
                                *head = curr->next;
                        else
                                prev->next = curr->next;
			free(curr->tracker);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

t_buff	*get_fd_node(t_list **head, int fd)
{
	t_list	*curr;
	char	test[1];

	curr = *head;
	if (fd < 0 || (read(fd, test, 0) == -1))
		return (NULL);
	if (!curr)
		return (add_fd_node(head, fd));
	while (curr->fd != fd && curr->next != NULL)
		curr = curr->next;
	if (curr->fd == fd)
		return (curr->tracker);
	else
		return (add_fd_node(head, fd));
}
