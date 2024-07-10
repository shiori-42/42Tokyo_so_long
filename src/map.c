/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:27:11 by shiori            #+#    #+#             */
/*   Updated: 2024/07/10 22:33:07 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // デバッグ用
#include "get_next_line.h"
#include "map.h"

int 	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
	{
		len++;
	}
	return (len);
}

int load_map(const char *filename, t_map *map)
{
    char *line;
    int fd;
    int i;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
    map->x = 0;
    map->y = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (map->y == 0)
            map->x = ft_strlen(line) - 1;
        map->y++;
        free(line);
    }
    close(fd);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (1);
    map->data = malloc(sizeof(char *) * map->y);
    if (!map->data)
    {
        close(fd);
        return (1);
    }
    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        map->data[i] = line;
        i++;
    }
    close(fd);
    return (0);
}

int validate_map(t_map *map)
{
    int player_cnt;
    int exit_cnt;
    int collect_item_cnt;
    int x;
    int y;

    player_cnt = 0;
    exit_cnt = 0;
    collect_item_cnt = 0;
    y = 0;
    while (y < map->y)
    {
        x = 0;
        while (x < map->x)
        {
            if (map->data[y][x] == '\n')
                break;

            if (map->data[y][x] == 'P')
                player_cnt++;
            else if (map->data[y][x] == 'E')
                exit_cnt++;
            else if (map->data[y][x] == 'C')
                collect_item_cnt++;
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
    if (collect_item_cnt < 1)
        return (1);

    return (0);
}
