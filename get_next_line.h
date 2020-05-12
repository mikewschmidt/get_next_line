
// REMOVE THIS NEXT LINE!!!
#ifndef BUFF_SIZE
# define BUFF_SIZE 32
#endif
typedef struct          s_buff
{
        char    buff[BUFF_SIZE];
        int     idx;
        int     eol;
	int	line_size;
        int     line_idx;
}                       t_buff;

typedef struct          s_list
{
        int             fd;
        t_buff          *tracker;
        struct s_list   *next;
}                       t_list;

t_buff			*get_buff();
t_list			*create_fd_node(int fd);
t_buff			*add_fd_node(t_list **head, int fd);
t_buff			*get_fd_node(t_list **head, int fd);
int			get_next_line(int fd, char **line);
void     		check_line_buff(char **line, t_buff **buff);
