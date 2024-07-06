/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:21:11 by shiori            #+#    #+#             */
/*   Updated: 2024/07/06 21:21:12 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
#define MAP_H

typedef struct s_map {
    int x;
    int y;
    char **data;
} t_map;

int load_map(const char *filename, t_map *map);
int validate_map(t_map *map);

#endif
