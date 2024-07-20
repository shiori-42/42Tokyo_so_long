/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:07:11 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/15 20:52:52 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// static int	ft_putunbr_fd(unsigned int n, int fd)
// {
// 	int	len;

// 	len = 1;
// 	if (n >= 10)
// 	{
// 		ft_putunbr_fd(n / 10, fd);
// 		len++;
// 	}
// 	ft_putchar_fd((n % 10) + '0', fd);
// 	return (len);
// }

// int	handle_u(va_list args)
// {
// 	unsigned int	n;
// 	int				len;

// 	n = va_arg(args, unsigned int);
// 	len = ft_putunbr_fd(n, 1);
// 	return (len);
// }

int	handle_u(va_list args)
{
	int			udexed_nbr;
	int			len;
	char		*base;
	char		*str;

	udexed_nbr = va_arg(args, unsigned int);
	base = "0123456789";
	str = ft_itoa_base(udexed_nbr, base);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
