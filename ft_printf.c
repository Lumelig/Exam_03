# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

size_t ft_putstr(char *str)
{
    int i = 0;
    if (!str)
    {
        i = write(1, "(null)", 6);
        return (i);
    }
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    return (i);
}

size_t ft_putnumbr(long nbr, int base)
{
    char *set = "0123456789abcdef";
    size_t len = 0;
    if (nbr < 0)
    {
        len += write(1, "-", 1);
        nbr *= -1;
    }
    if (nbr >= base)
        len += ft_putnumbr(nbr / base, base);
    
    len += write(1, &set[nbr % base], 1);
    return (len);

}

int ft_printf(char *f, ...)
{
    size_t len = 0;
    int i = 0;
    va_list ap;

    va_start(ap, f);
    while (f[i])
    {
        if (f[i] == '%' && f[i + 1])
        {
            i++;
            if (f[i] == 's')
            {
                len += ft_putstr(va_arg(ap, char *));
            }
            else if (f[i] == 'd')
            {
                len += ft_putnumbr(va_arg(ap, int), 10);
            }
            else if (f[i] == 'x')
            {
                len += ft_putnumbr(va_arg(ap,unsigned int), 16);
            }
            else if (f[i] == '%')
                len += write(1, "%", 1);
        }
        else
        {
            len += write(1, &f[i], 1);
        }
        i++;
    }
    va_end(ap);
    return (len);
}

