#include "get_next_line.h"

void	free_mem(char *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

int newline_checker(char *str) // check newline
{
	int a = 0;

	while(str[a] != 0)
	{	
		if (str[a] == '\n')
		{
			return (a + 1);
		}
		a++;
	}
	return (0);
}
char *line_read(int fd)
{
	size_t size;
	int chkr;
	char *buf;
	char *retline;

	size = 1;
	chkr = 0;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	retline = NULL;
	while(size > 0 && chkr == 0)
	{
		size = read(fd,buf,BUFFER_SIZE);
		chkr = newline_checker(buf);
		buf[size] = '\0';
		if (retline == 0)
			retline = ft_strdup(buf);
		else	
			retline = ft_strjoin(retline, buf);
	}
	if (size == 0)
		return NULL;
	free_mem(buf);
	return retline;
}
char *stash2(char *s, int size) // returning string until newline
{
	int a = 0;
	int s_size = ft_strlen(s);
	char *str = malloc(s_size * sizeof(char));
	if(size == 0)
		return s;
	while(a < size)
	{
		str[a] = s[a];
		a++;	
	}
	str[s_size + 1] = '\0';
	return str;
}

char *get_next_line(int fd)
{
	static char *stash;
    int chkr;
	char *last;

	chkr = 0;
	last = NULL;
	if (!last)
		return (NULL);
	while(fd > 0 || last != NULL)
	{
		if(stash == 0 || *stash == '\0')
		{
			last = line_read(fd);
			if (!last)
				return NULL;
		}
		else
		{
			chkr = newline_checker(stash);
			if (chkr > 0)
			{
				last = stash2(stash, chkr);
				stash = ft_strdup(stash + chkr);
				return last;
			}
			else
			{
				last = ft_strjoin(stash,line_read(fd));
				free_mem(stash);
			}
		}
		chkr = newline_checker(last);
		if (chkr > 0)
			stash = ft_strdup(last + chkr);
		return last = stash2(last,chkr);
	}
return NULL;	
}