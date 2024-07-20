/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_upperhex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:44:31 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/13 19:45:48 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_upperhex(va_list args)
{
	int		hexed_nbr;
	int		len;
	char	*base;
	char	*str;

	hexed_nbr = va_arg(args, unsigned int);
	base = "0123456789ABCDEF";
	str = ft_itoa_base((uintptr_t)hexed_nbr, base);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
