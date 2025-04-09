#include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return(i);
}
void    ft_strcpy(char *dest, char *src)
{
    int i = 0;
    if (!src)
        return;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
char    *ft_strjoin(char *s1, char *s2)
{
    int i = 0;
    int j = 0;
    char *str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!str)
        return(NULL);
    while (s1[i])
    {
        str[i] = s1[i]; 
        i++;
    }
    while (s2[j])
    {
        str[i] = s2[j];
        i++;
        j++;
    }
    str[i] = '\0';
    free(s1);
    return(str);
}
char *ft_strchr(char *str, int c)
{
    int i = 0;
    while (str[i])
    {
        if(str[i] == (char) c)
            return((char *)&str[i]);
        i++;
    }
    return(NULL);
}
char    *ft_strdup(char *src)
{
    int i = 0;
    char *dest = malloc(ft_strlen(src) + 1);
    if(!dest)
        return (NULL);
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE + 1];
    char    *line = NULL;
    char    *newline;
    char    *temp;
    int     read_fd;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    
    line = ft_strdup("");
    if (!line)
        return (NULL);

    // First, check if there's already a newline in the buffer
    if (buf[0] != '\0')
        line = ft_strjoin(line, buf);

    newline = ft_strchr(line, '\n');
    // Read until we find a newline or reach EOF
    while (!newline && (read_fd = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[read_fd] = '\0';
        line = ft_strjoin(line, buf);
        if (!line)
            return (NULL);
        
        newline = ft_strchr(line, '\n');
    }

    // Handle read error
    if (read_fd < 0)
    {
        free(line);
        return (NULL);
    }

    // Handle empty line (EOF)
    if (ft_strlen(line) == 0)
    {
        free(line);
        return (NULL);
    }

    // Handle the buffer for the next call
    if (newline)
    {
        temp = ft_strdup(newline + 1);
        *(newline + 1) = '\0';
        ft_strcpy(buf, temp);
        free(temp);
    }
    else
        buf[0] = '\0';

    return (line);
}