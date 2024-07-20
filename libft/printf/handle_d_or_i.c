/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d_or_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:41:52 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/13 19:52:03 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_d_or_i(va_list args)
{
	char	*str;
	int		len;
	int		num;

	num = va_arg(args, int);
	str = ft_itoa(num);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
