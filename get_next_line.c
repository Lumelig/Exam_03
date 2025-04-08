# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char    *ft_strchr(char *src, int c)
{
    int i = 0;
    while (src[i])
    {
        if (src[i] == (char)c)
            return ((char *)&src[i]);
        i++;
    }
    return (NULL);
}

size_t ft_strlen(const char *str)
{
    size_t i = 0;
    while (str[i])
        i++;
    return (i);
}

void *ft_strcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char *ft_strdup(const char *src)
{
    size_t len = ft_strlen(src);
    char *dest = malloc(len + 1);
    if (!dest)
        return (NULL);
    ft_strcpy(dest, src);
    return (dest);

}
char    *ft_strjoin(char *s1,char *s2)
{
    if (!s1 || !s2)
        return (NULL);
    size_t  len1 = ft_strlen(s1);
    size_t  len2 = ft_strlen(s2);
    char    *join = malloc(len1 + len2 + 1);
    if (!join)
        return (NULL);
    ft_strcpy(join, s1);
    ft_strcpy((join + len1), s2);
    free(s1);
    return (join);
}
/**
 * get_next_line - Reads a line from a file descriptor
 * @param fd: The file descriptor to read from
 * @return: The line read (including newline if present), or NULL if EOF/error
 *
 * This function reads a line from a file descriptor and returns it as a dynamically
 * allocated string. It uses a static buffer to store leftovers between calls.
 */
char *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE + 1];  // Static buffer persists between function calls
    char        *line;                 // Will hold the line to return
    char        *newline;              // Pointer to newline character if found
    int         countread;             // Number of bytes read
    int         to_copy;               // Number of bytes to include in final line

    // STEP 1: Initialize our line with any leftover content from previous calls
    line = ft_strdup(buf);  // Create a duplicate of the static buffer
    
    // STEP 2: Keep reading until we either find a newline or reach EOF
    while (!(newline = ft_strchr(line, '\n')) && (countread = read(fd, buf, BUFFER_SIZE)))
    { 
        // Null-terminate what we just read
        buf[countread] = '\0';
        
        // Join the new data to our existing line (with memory management)
        line = ft_strjoin(line, buf);
    }
    
    // STEP 3: Handle empty line case (EOF with nothing to return)
    if (ft_strlen(line) == 0) 
        return (free(line), NULL);  // Free memory and return NULL
    
    // STEP 4: Process the line based on whether a newline was found
    if (newline != NULL)  // Newline found
    {
        // Calculate length including the newline character
        to_copy = newline - line + 1;
        
        // Save everything after the newline for the next call
        ft_strcpy(buf, newline + 1);
    }
    else  // No newline found (end of file)
    {
        // Use the entire string
        to_copy = ft_strlen(line);
        
        // Clear the static buffer
        buf[0] = '\0';
    }
    
    // STEP 5: Finalize the line by adding null terminator at proper position
    line[to_copy] = '\0';
    
    // STEP 6: Return the completed line
    return (line);
}

// char    *get_next_line(int fd)
// {
//     static char buf[BUFFER_SIZE + 1];
//     char        *line;
//     char        *newline;
//     int         countread;
//     int         to_copy;

//     line = ft_strdup(buf);
//     while (!(newline = ft_strchr(line, '\n')) && (countread = read(fd, buf, BUFFER_SIZE)))
//     { 
//         buf[countread] = '\0';
//         line = ft_strjoin(line, buf);
//     }
//     if (ft_strlen(line) == 0) 
//         return (free(line), NULL);
//     if (newline != NULL)
//     {
//         to_copy = newline - line + 1; 
//         ft_strcpy(buf, newline + 1);
//     }
//     else
//     {
//         to_copy = ft_strlen(line);
//         buf[0] = '\0';
//     }
//     line[to_copy] = '\0';
//     return (line);
// }