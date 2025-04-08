#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char *get_next_line(int fd)
{
    char buffer[BUFFER_SIZE + 1];
    static char *remainder = NULL;
    char *line = NULL;
    char *temp;
    char *newline_pos;
    int bytes_read;
    
    if (remainder)
    {
        if ((newline_pos = strchr(remainder, '\n')))
        {
            *newline_pos = '\0';
            line = strdup(remainder);
            temp = strdup(newline_pos + 1);
            free(remainder);
            remainder = temp;
            
            return line;
        }
        line = remainder;
        remainder = NULL;
    }
    else
    {
        line = malloc(1);
        if (!line)
            return NULL;
        line[0] = '\0';
    }
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        if ((newline_pos = strchr(buffer, '\n')))
        {
            *newline_pos = '\0';
            temp = line;
            line = malloc(strlen(temp) + strlen(buffer) + 1);
            if (!line)
            {
                free(temp);
                return NULL;
            }
            strcpy(line, temp);
            strcat(line, buffer);
            free(temp);
            remainder = strdup(newline_pos + 1);
            return line;
        }
        temp = line;
        line = malloc(strlen(temp) + bytes_read + 1);
        if (!line)
        {
            free(temp);
            return NULL;
        }
        strcpy(line, temp);
        strcat(line, buffer);
        free(temp);
    }
    if (line && *line)
        return line;
    free(line);
    return NULL;
}