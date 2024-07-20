/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:33:50 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/13 20:44:41 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

static int	dispatch_handler(char specifier, va_list args)
{
	if (specifier == 'c')
		return (handle_c(args));
	else if (specifier == 's')
		return (handle_s(args));
	else if (specifier == 'p')
		return (handle_p(args));
	else if (specifier == 'd' || specifier == 'i')
		return (handle_d_or_i(args));
	else if (specifier == 'u')
		return (handle_u(args));
	else if (specifier == 'x')
		return (handle_lowhex(args));
	else if (specifier == 'X')
		return (handle_upperhex(args));
	else if (specifier == '%')
		return (handle_percent_symbol(args));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed_chars;
	int		i;

	printed_chars = 0;
	va_start(args, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			printed_chars += dispatch_handler(format[++i], args);
		}
		else
		{
			printed_chars += 1;
			write(1, &format[i], 1);
		}
		i++;
	}
	va_end(args);
	return (printed_chars);
}

// int main()
// {
// 	ft_printf("%d\n", -1);
// 	ft_printf("%d\n", 10);
// }