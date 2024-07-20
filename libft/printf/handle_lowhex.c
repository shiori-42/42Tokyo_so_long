/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lowhex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:23:33 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/13 19:29:52 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_lowhex(va_list args)
{
	int		hexed_nbr;
	int		len;
	char	*base;
	char	*str;

	hexed_nbr = va_arg(args, unsigned int);
	base = "0123456789abcdef";
	str = ft_itoa_base((uintptr_t)hexed_nbr, base);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
