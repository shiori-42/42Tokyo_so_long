/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:11:50 by shiori            #+#    #+#             */
/*   Updated: 2024/07/16 16:51:29 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void free_double_pointer(char **ptr,int height)
{
    int y;

    y=0;
    while(y<height)
    {
        free(ptr[y]);
        y++;
    }
    free(ptr);
}