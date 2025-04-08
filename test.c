#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

/*
 * ft_strlen - Calculate the length of a string
 * @str: The string to measure
 *
 * Returns the number of characters in the string.
 * Handles NULL input by returning 0.
 */
int ft_strlen(char *str)
{
    int i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

/*
 * ft_strchr - Find the first occurrence of a character in a string
 * @src: The string to search
 * @c: The character to find
 *
 * Returns a pointer to the first occurrence of c in src,
 * or NULL if the character is not found.
 * Handles NULL input by returning NULL.
 */
char *ft_strchr(char *src, int c)
{
    int i = 0;
    if (!src)
        return (NULL);
    while (src[i])
    {
        if (src[i] == (char)c)
            return ((char *)&src[i]);
        i++;
    }
    return (NULL);
}

/*
 * ft_strdup - Duplicate a string
 * @src: The string to duplicate
 *
 * Returns a newly allocated string containing a copy of src.
 * If src is NULL, returns an empty string.
 * Caller is responsible for freeing the returned memory.
 */
char *ft_strdup(char *src)
{
    char *dest;
    int i = 0;
    
    if (!src)
        return (ft_strdup(""));
    dest = malloc(ft_strlen(src) + 1);
    if (!dest)
        return (NULL);
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

/*
 * ft_strcpy - Copy a string
 * @dest: The destination buffer
 * @src: The source string
 *
 * Copies the string src to dest, including the terminating null byte.
 * Assumes dest has enough space to hold the copy.
 * Does nothing if src is NULL.
 */
void ft_strcpy(char *dest, char *src)
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

/*
 * ft_strjoin - Join two strings
 * @s1: The first string
 * @s2: The second string
 *
 * Returns a newly allocated string containing s1 followed by s2.
 * Handles NULL inputs by treating them as empty strings.
 * Frees the original s1 after joining.
 * Caller is responsible for freeing the returned memory.
 */
char *ft_strjoin(char *s1, char *s2)
{
    int i = 0;
    int j = 0;
    char *res;
    
    if (!s1)
        s1 = ft_strdup("");
    if (!s2)
        s2 = ft_strdup("");
    res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!res)
        return (NULL);
    while (s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        res[i] = s2[j];
        j++;
        i++;
    }
    res[i] = '\0';
    free(s1); // Free the original s1 after joining to prevent memory leaks
    return (res);
}

/*
 * get_next_line - Read a line from a file descriptor
 * @fd: The file descriptor to read from
 *
 * Returns a newly allocated string containing the next line from the file,
 * or NULL if there are no more lines or an error occurs.
 * A line is defined as a sequence of characters ending with '\n' or EOF.
 * Caller is responsible for freeing the returned memory.
 *
 * This function uses a static buffer to efficiently read from the file.
 * Subsequent calls to the function will continue from where the previous call left off.
 */
char *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE + 1]; // Static buffer to store data between function calls
    char *line;                       // The line we're building to return
    char *newline;                    // Pointer to newline character if found
    int bytes_read;                   // Number of bytes read in each read() call
    char *temp;                       // Temporary string for buffer management

    // Check for invalid file descriptor or buffer size
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    
    // Initialize line with content from the static buffer
    line = ft_strdup(buf);
    if (!line)
        return (NULL);
    
    // Keep reading until we find a newline or reach EOF
    while (!(newline = ft_strchr(line, '\n')) && 
           (bytes_read = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[bytes_read] = '\0';             // Null-terminate the buffer
        line = ft_strjoin(line, buf);       // Append buffer to line
        if (!line)
            return (NULL);
    }
    
    // Handle read error
    if (bytes_read < 0)
    {
        free(line);
        return (NULL);
    }
    
    // If line is empty, we've reached EOF
    if (ft_strlen(line) == 0)
    {
        free(line);
        return (NULL);
    }
    
    // Handle newline if found
    newline = ft_strchr(line, '\n');
    if (newline)
    {
        temp = ft_strdup(newline + 1);      // Save content after newline
        *(newline + 1) = '\0';              // Terminate line at newline + 1
        ft_strcpy(buf, temp);               // Store remaining content in static buffer
        free(temp);                         // Free temporary string
    }
    else
        buf[0] = '\0';                      // Empty the buffer if no newline found
        
    return (line);
}