/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:20:03 by skwon2            #+#    #+#             */
/*   Updated: 2024/10/30 13:39:24 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void set_player_direction(t_caster *c, size_t x, size_t y)
{
    if (c->map->map_arr[y][x] == 'N')
        c->view_angle = -M_PI_2; // 90 degrees
    else if (c->map->map_arr[y][x] == 'S')
        c->view_angle = M_PI_2; // -90 degrees
    else if (c->map->map_arr[y][x] == 'E')
        c->view_angle = 0; // 0 degrees (facing east)
    else if (c->map->map_arr[y][x] == 'W')
        c->view_angle = M_PI; // 180 degrees (facing west)
}

static int check_else_char(t_caster *c, char character)
{
    if (ft_strchr("01 NSWE", character) == NULL)
        return (exit_failure(c, "Invalid characters in the map."));
}

static void store_position_player(t_caster *c, int *found, size_t x, size_t y)
{
    if (found == 0)
    {
        if (c->map->map_arr[y][x] == 'N' || c->map->map_arr[y][x] == 'S' ||
            c->map->map_arr[y][x] == 'W' || c->map->map_arr[y][x] == 'E')
        {
            (*found)++;
            c->px = x + 0.0001;
            c->py = y + 0.0001;
            c->mmap_px = x * c->map->scale_x + 0.0001;
            c->mmap_py = y * c->map->scale_y + 0.0001;
            set_player_direction(c, x, y);
        }
    }
}

int find_player_pos(t_caster *c)
{
    size_t x;
    size_t y;
    int     found;
    
    found = 0;
    y = -1;
    while (++y < (size_t)c->map->map_height)
    {
        x = -1;
        while (++x < ft_strlen(c->map->map_arr[y]))
        {
            if (check_else_char(c, c->map->map_arr[y][x]) == EXIT_FAILURE)
                return (EXIT_FAILURE);
            store_position_player(c, &found, x, y);
        }
        if (found == 0)
            return (exit_failure(c, "Player not found."));
        else if (found > 1)
            return (exit_failure(c, "There is more than one player."));
    }
    return (EXIT_SUCCESS);
}
