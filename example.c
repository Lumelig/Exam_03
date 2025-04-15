#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif 

#include <unistd.h>
#include <stdlib.h>

char *ft_strdup(char *str)
{
    char *dup;
    char *start;
    int len = 0;

    while(str[len] != '\0')
        len++;
    dup = (char *)malloc(sizeof(char) * (len + 1));
    if(!dup)
        return(NULL);
    start = dup;
    while(*str)
        *dup++ = *str++;
    *dup = '\0';
    return(start);
}
char *get_next_line(int fd)
{
    static int pos;
    static int rd;
    static char buf[BUFFER_SIZE];
    int i = 0;
    char line[70000];

    if(fd<0||BUFFER_SIZE <= 0)
        return(NULL);
        
    while(1)
    {
        if(pos >= rd)
        {
            rd= read(fd, buf, BUFFER_SIZE);
            pos= 0;
            if(rd <= 0)
                break;
        }
        line[i] = buf[pos++];
        if(line[i]== '\n')
        {
            i++;
            break;
        }
        i++;
    }
    if(i == 0)
        return(NULL);
    line[i] = '\0';
    return(ft_strdup(line));
}

char *get_next_line(int fd)
{
    // 🟡 Static Variablen behalten ihren Wert zwischen Funktionsaufrufen
    static int pos;                 // aktuelle Position im Buffer
    static int rd;                  // wie viele Bytes zuletzt gelesen wurden
    static char buf[BUFFER_SIZE];   // fester Lese-Buffer mit BUFFER_SIZE

    int i = 0;                      // Index fürs line-Array
    char line[70000];              // Zeile, die wir zusammensetzen (Achtung: groß!)

    // 🔴 Fehlerfall: ungültiger File Descriptor oder ungültige Buffer-Größe
    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    // 🔁 Hauptschleife: wir lesen so lange, bis wir eine Zeile fertig haben oder nichts mehr da ist
    while (1)
    {
        // 🟡 Wenn der Buffer aufgebraucht ist, neu lesen
        if (pos >= rd)
        {
            rd = read(fd, buf, BUFFER_SIZE); // versuch, neue Daten zu lesen
            pos = 0;                         // Position im Buffer zurücksetzen

            if (rd <= 0)                     // 🔴 Nichts mehr zu lesen (EOF oder Fehler)
                break;
        }

        // 🟢 Zeichen aus dem Buffer in die Zeile kopieren
        line[i] = buf[pos++];

        // ⏎ Wenn ein Newline kommt: Zeile ist vollständig
        if (line[i] == '\n')
        {
            i++;       // `\n` mitnehmen
            break;     // Zeile fertig
        }

        i++; // weiter zum nächsten Zeichen
    }

    // 🟡 Wenn gar nichts gelesen wurde (z. B. EOF direkt beim Aufruf): gib NULL zurück
    if (i == 0)
        return NULL;

    // 🟢 String terminieren (wichtig für ft_strdup)
    line[i] = '\0';

    // 🟢 Gib eine Kopie der fertigen Zeile zurück
    return ft_strdup(line); // Achtung: strdup allokiert Speicher → später free() nicht vergessen
}
