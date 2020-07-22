/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:42:26 by mschmidt          #+#    #+#             */
/*   Updated: 2020/07/22 01:03:38 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

t_buff	*get_buff(void)
{
	t_buff	*temp;

	temp = (t_buff*)malloc(sizeof(t_buff));
	if (!temp)
		return (NULL);
	temp->idx = 0;
	temp->eol = 0;
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
	int		i;
	char	*temp;

	i = 0;
	if ((*b)->line_idx >= (*b)->ln_siz - 1)
	{
		(*b)->ln_siz = ((*b)->ln_siz == 0) ? 2 : (*b)->ln_siz;
		if (!(temp = (char*)malloc((*b)->ln_siz * (*b)->ln_siz * sizeof(char))))
			return ;
		if ((*b)->ln_siz > 2)
		{
			while (i < (*b)->ln_siz)
			{
				temp[i] = (*line)[i];
				i++;
			}
			free(*line);
		}
		*line = temp;
		(*b)->line_idx = i;
		(*b)->ln_siz *= (*b)->ln_siz;
	}
	else
		(*b)->line_idx++;
}
