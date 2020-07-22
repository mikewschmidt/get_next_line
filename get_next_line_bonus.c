/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:55:58 by mschmidt          #+#    #+#             */
/*   Updated: 2020/07/22 01:04:06 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	reached_eof(char **line, int rturn)
{
	if (rturn == -1)
		return (-1);
	if (!(*line = (char*)malloc(sizeof(char))))
		return (-1);
	(*line)[0] = '\0';
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static t_list	*head;
	t_buff			*temp;
	int				j;

	j = 0;
	if (BUFFER_SIZE < 1 || !line || !(temp = get_fd_node(&head, fd)))
		return (-1);
	if (temp->idx == 0)
		if ((temp->eol = read(fd, temp->buff, BUFFER_SIZE)) < 1)
			return (reached_eof(line, temp->eol));
	check_line_buff(line, &temp);
	while (temp->buff[temp->idx] != '\n' && temp->eol > 0)
	{
		check_line_buff(line, &temp);
		(*line)[j++] = temp->buff[temp->idx++];
		if (temp->idx >= temp->eol)
		{
			temp->eol = read(fd, temp->buff, BUFFER_SIZE);
			temp->idx = 0;
		}
	}
	(*line)[j] = '\0';
	temp->ln_siz = 0;
	(temp->idx >= temp->eol - 1) ? (temp->idx = 0) : (temp->idx++);
	return ((temp->eol == 0) ? 0 : 1);
}
