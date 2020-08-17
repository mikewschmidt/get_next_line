/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:29:19 by mschmidt          #+#    #+#             */
/*   Updated: 2020/08/15 02:20:34 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE__BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct			s_buff
{
	char			buff[BUFFER_SIZE];
	int				idx;
	int				read_size;
	int				ln_siz;
	int				line_idx;
}						t_buff;

typedef struct			s_list
{
	int				fd;
	t_buff			*tracker;
	struct s_list	*next;
}						t_list;

t_buff					*get_buff();
t_list					*create_fd_node(int fd);
t_buff					*add_fd_node(t_list **head, int fd);
t_buff					*get_fd_node(t_list **head, int fd);
void					remove_fd_node(t_list **head, int fd);
int						get_next_line(int fd, char **line);
#endif
