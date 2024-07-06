/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:34 by shiori            #+#    #+#             */
/*   Updated: 2024/07/06 17:36:05 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>
#include "map.h"

int load_map(const char *filename, t_map *map)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);

    char *line = NULL;
}