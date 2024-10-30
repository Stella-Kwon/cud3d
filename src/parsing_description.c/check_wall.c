/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:02:09 by skwon2            #+#    #+#             */
/*   Updated: 2024/10/30 16:23:38 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int check_dfs(t_caster *c, int y, int x, int visited[c->map->map_hieght][c->map->map_width])
{
    int up;
    int down;
    int left;
    int right;

    if (y <= 0 || y >= c->map->map_height || x <= 0 || x >= c->map->map_width)
        return (false);
    if (visited[y][x] || c->map->map_arr[y][x] == '1')
        return (true);
    visited[y][x] = true;
    up = check_dfs(c, y - 1, x, visit);
    down = check_dfs(c, y + 1, x, visit);
    left = check_dfs(c, y, x - 1, visit);
    right = check_dfs(c, y, x + 1, visit);
    return (up && down && left && right);
}

int check_wall(t_caster *c)
{
    int visited[c->map->map_height][c->map->map_width];
    int i;
    int j;

    i = 0;
    while (i < c->map->map_height)
    {
        j = 0;
        while (j < c->map->map_width)
        {
            visited[i][j] = false;
            j++;
        }
        i++;
    }
    if (!check_dfs(c, c->py, c->px, visited))
        return (exit_failure(c, "Map does not covered by walls."));

    return (EXIT_SUCCESS);
}