/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:21:00 by shiori            #+#    #+#             */
/*   Updated: 2024/08/17 18:27:30 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_expose(t_game *game)
{
	render_map(game);
	return (0);
}

int	close_handler(t_game *game)
{
	ft_exit(game);
	return (0);
}
