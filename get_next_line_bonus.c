/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:55:58 by mschmidt          #+#    #+#             */
/*   Updated: 2020/08/15 02:43:01 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		reached_eof(int fd, char **line, int ret_val, t_list **head)
{
	remove_fd_node(head, fd);
	if (ret_val == -1)
		return (-1);
	if(!*line)
	{
		if (!(*line = (char*)malloc(sizeof(char))))
			return (-1);
		(*line)[0] = '\0';
	}
	return (0);
}

void	increase_line_by(char **line, t_buff **b, int read_size)
{
	int		i;
	char	*temp;

	i = 0;
	if (!(temp = (char *)malloc(((*b)->ln_siz + read_size) * sizeof(char) + 1)))
		return ;
	while (i < (*b)->ln_siz + read_size + 1)
		temp[i++] = '\0';
	i = 0;
	while (i < (*b)->ln_siz)
	{
		temp[i] = (*line)[i];
		i++;
	}
	if ((*b)->ln_siz != 0)
		free(*line);
	*line = temp;
	(*b)->ln_siz += read_size;
}

int		get_next_line(int fd, char **line)
{
	static t_list	*head;
	t_buff			*node;
	int				j;

	j = 0;
	if (BUFFER_SIZE < 1 || !line || !(node = get_fd_node(&head, fd)))
		return (reached_eof(fd, line, -1, &head));
	*line = NULL;
	if (node->idx == 0)
		if ((node->read_size = read(fd, node->buff, BUFFER_SIZE)) < 1)
			return (reached_eof(fd, line, node->read_size, &head));
	increase_line_by(line, &node, node->read_size);
	while (node->buff[node->idx] != '\n' && node->read_size > 0)
	{
		(*line)[j++] = node->buff[node->idx++];
		if (node->idx >= node->read_size)
		{
			node->read_size = read(fd, node->buff, BUFFER_SIZE);
			node->idx = 0;
			increase_line_by(line, &node, node->read_size);
		}
	}
	node->ln_siz = 0;
	node->idx = (node->idx >= node->read_size - 1) ? 0 : node->idx + 1;
	return ((node->read_size <= 0) ? reached_eof(fd, line, 0, &head) : 1);
}
