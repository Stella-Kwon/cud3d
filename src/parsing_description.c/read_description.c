/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_description.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:00:52 by skwon2            #+#    #+#             */
/*   Updated: 2024/10/30 16:25:02 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void print_map(t_caster *c)
{
	for (int y = 0; y < c->map->map_width; y++)
	{
		for (int x = 0; x < c->map->map_width; x++)
		{
			printf("%d", c->map->map_arr[y][x]);
		}
		printf("\n");
	}
}

int	read_description(t_caster *c)
{
	if (file_exits(c, c->map->map_path, ".cub", MAP) == EXIT_FAILURE)
		return ;
	if (check_map(c) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	c->map->scale_x = (double)((WIDTH / 5) / c->map->map_width);
	c->map->scale_y = (double)((HEIGHT / 5) / c->map->map_height);
	print_map(c);
	if (find_player_pos(c) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_wall(c) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_wall(c) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}



