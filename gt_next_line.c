#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 42

char    *ft_strchr(char *s, int c) //learn and write
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    return (NULL);
}

size_t  ft_strlen(const char *s)
{
    size_t  i = 0;

    while (s[i])
        i++;
    return (i);
}

void    ft_strcpy(char *dst, const char *src)
{
    while (*src)
        *dst++ = *src++;
    *dst = '\0';
}

char    *ft_strdup(const char *src)
{
    size_t  len = ft_strlen(src) + 1;
    char    *dst = malloc(len);

    if (dst == NULL)
        return (NULL);
    ft_strcpy(dst, src);
    return (dst);
}
// Beispiel: Wenn du ein sehr großes Array hast, könnte die Länge in int negativ werden,
// was zu unerwartetem Verhalten führt. Mit size_t passiert das nicht
char    *ft_strjoin(char *s1, char const *s2) //learn and write
{
    size_t  s1_len = ft_strlen(s1);
    size_t  s2_len = ft_strlen(s2);
    char    *join = malloc((s1_len + s2_len + 1));

    if (!s1 || !s2)
        return (NULL);
    if (!join)
        return (NULL);
    ft_strcpy(join, s1);
    ft_strcpy((join + s1_len), s2);
    free(s1);
    return (join);
}

char    *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE + 1];
    char        *line;
    char        *newline;
    int         countread;
    int         to_copy;

    line = ft_strdup(buf);
    while (!(newline = ft_strchr(line, '\n')) && (countread = read(fd, buf, BUFFER_SIZE)))// check for if eof and read works
    { // if line != \n it return null so first part of while run until we find a \n or read is eof
        // and newline as well safe the point where /n appears
        buf[countread] = '\0';// set null char and end of read
        line = ft_strjoin(line, buf); // join read and old input
    }
    // do it until read is zero or \n
    if (ft_strlen(line) == 0) //could the be also contread? nope not working
        return (free(line), NULL);
    if (newline != NULL)// if newline is not empty also to add meaning of before while check only null when a \n is found
    {
        to_copy = newline - line + 1; //to copy is the pos where to set the \0 and at is at newline whats the lenth of the string until \n - and i is pos of start string so 1 + 1 bc we wanna also have in our substring the \n
        ft_strcpy(buf, newline + 1);//copy newline + 1 into buf
    }
    else // when new line is null or when eof
    {
        to_copy = ft_strlen(line);// else copy is lenth of line
        buf[0] = '\0'; //and buff pos 0 to null char wtf?
    }
    line[to_copy] = '\0';// this i understand
    return (line);
}


int main(void)
{
    int fd = open("testfile.txt", O_RDONLY);
    char *line;

    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}