/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:27:11 by shiori            #+#    #+#             */
/*   Updated: 2024/07/15 19:16:37 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
	{
		len++;
	}
	return (len);
}

t_map	read_map(const char *filename)
{
	char *line;
	int fd = open(filename, O_RDONLY);
	t_map map = {NULL, 0, 0};

	if (fd == -1)
	{
		perror("Error opening file");
		return (map);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] != '\n')
			map.y++;
		if (map.y == 1)
			map.x = ft_strlen(line) - 1;
		free(line);
	}
	close(fd);

	map.data = malloc(map.y * sizeof(char *));
	if (!map.data)
		return (map);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (map);

	int i = 0;
	while ((line = get_next_line(fd)) != NULL)
		map.data[i++] = line;
	close(fd);

	return (map);
}

int	validate_map(t_map *map)
{
	int	player_cnt;
	int	exit_cnt;
	int	collected;
	int	x;
	int	y;

	player_cnt = 0;
	exit_cnt = 0;
	collected = 0;
	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (map->data[y][x] == '\n')
				break ;
			if (map->data[y][x] == 'P')
				player_cnt++;
			else if (map->data[y][x] == 'E')
				exit_cnt++;
			else if (map->data[y][x] == 'C')
				collected++;
			else if (map->data[y][x] != '0' && map->data[y][x] != '1')
			{
				return (1);
			}
			x++;
		}
		y++;
	}
	if (player_cnt != 1)
		return (1);
	if (exit_cnt != 1)
		return (1);
	if (collected < 1)
		return (1);
	return (0);
}
