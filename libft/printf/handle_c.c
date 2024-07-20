/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:39:40 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/30 19:34:11 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_c(va_list args)
{
	unsigned char	c;

	c = (unsigned char)va_arg(args, int);
	write(1, &c, 1);
	return (1);
}
