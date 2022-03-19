//#include "gnl.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
# define FD_MAX 256
#include <string.h>
#define buf_size 42


void	ft_bzero(void *s, size_t n)
{
	unsigned char	*a;
	size_t			b;

	b = 0;
	a = s;
	while (b < n)
	{
		a[b] = 0;
		b++;
	}
}
int	ft_strlen(const char *s)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
	{
		a++;
	}
	return (a);
}
void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = (void *)malloc(count * size);
	if (str == 0)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest2;
	char	*src2;
	size_t	a;

	a = 0;
	dest2 = (char *)dest;
	src2 = (char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (a < n)
	{
		dest2[a] = src2[a];
		a++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	int		slen;
	char	*str;

	slen = ft_strlen(s);
	str = (char *)ft_calloc(slen + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s, slen);
	return (str);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	a;
	size_t	b;
	char	*str;

	a = 0;
	b = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[b] != '\0')
	{
		str[b] = s1[b];
		b++;
	}
	while (s2[a] != '\0')
	{
		str[b + a] = s2[a];
		a++;
	}
	str[b + a] = '\0';
	return (str);
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

char *ret(int fd)
{
	size_t size;
	int chkr = 0;
	char *retline;
	char *buf = malloc((buf_size + 1) * sizeof(char));

	while(size > 0 && chkr == 0)
	{
		size = read(fd,buf,buf_size);
		chkr = newline_checker(buf);
		retline = ft_strjoin(retline, buf);
	}
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
    char *buf = malloc((buf_size + 1) * sizeof(char));
	static char *stash;
    int chkr = 0;
	char *line;
	char *stash3;

	if(stash == 0 || *stash == '\0')
	{
		line = ret(fd);
    }
    else
	{
		chkr = newline_checker(stash);
		stash3 = stash2(stash, chkr);
		if (chkr > 0)
			free(stash);
		else
			stash = ft_strdup(stash + chkr);
	}
	chkr = newline_checker(line);
	stash = ft_strdup(line + chkr);
	line = stash2(line,chkr);
    return line;
}
/*
int main (int arc, char *argv[])
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	printf("%s",get_next_line(fd));
	return 0;
}
*/


int main(int argc, char *argv[])
{
        int fd;
        char *line;
		int a = 0;
		int size;

        line = malloc(1 *sizeof(char));

        if (argc == 2)
        {
                fd = open(argv[1], O_RDONLY);
                while (line != NULL)
                {
                        free(line);
                        line = get_next_line(fd);
						//size = ft_strlen(line);
                        if (line == NULL)
                                exit(1);
				size = ft_strlen(line);				
				printf("line size = %d, line number = %d %s",size,a,line);
				a++;
                }
        }
	if (argc < 2)
	{
		while ((line = get_next_line(0)) != NULL)
		{
      			printf("Next line -> %s", line);
		}
	}
        return 0;
}
