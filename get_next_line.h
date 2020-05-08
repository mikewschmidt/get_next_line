
typedef struct          s_buff
{
        char    buff[BUFFER_SIZE];
        int     idx;
        int     eol;
        int     endfile;
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
void			set_tracking_vars(int fd, t_buff *tracker);
int			get_next_line(int fd, char **line);
