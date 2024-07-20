/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_percent_symbol.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:50:36 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/13 19:42:36 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_percent_symbol(va_list args)
{
	char	c;

	(void)args;
	c = '%';
	write(1, &c, 1);
	return (1);
}
