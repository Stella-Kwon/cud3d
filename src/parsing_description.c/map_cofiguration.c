/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cofiguration.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:24:03 by skwon2            #+#    #+#             */
/*   Updated: 2024/10/29 17:55:16 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	parse_texture_color(t_caster *c, char *line, char *order, T_Dir i)
{
	if (!ft_strncmp(line, order, ft_strlen(order)))
	{
		if (i == F || i == C)
			parse_plain_colors(c, line);
		else
		{
			if (line[4] == '.' && line[5] == '/')
				c->map->texture_path = ft_substr(line, 4, ft_strlen(line) - 4);
			if (file_exits(c, c->map->texture_path, ".png", TEXTURE) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (i == NT)
				c->textures->north_texture = mlx_load_png(c->map->texture_path);
			if (i == ST)
				c->textures->south_texture = mlx_load_png(c->map->texture_path);
			if (i == WT)
				c->textures->west_texture = mlx_load_png(c->map->texture_path);
			if (i == ET)
				c->textures->east_texture = mlx_load_png(c->map->texture_path);
		}
	}
	return (EXIT_SUCCESS);
}

void	init_var(int *width, T_Dir *i, const char **order, char **line)
{
	order[0] = "NO ";
	order[1] = "SO ";
	order[2] = "WE ";
	order[3] = "EA ";
	order[4] = "F ";
	order[5] = "C ";
	*width = 0;
	*line = getnextline(c->map->map_fd);
	*i = NT;
}

int whole_space_line(char *str)
{
	while (*str)
	{
		if (*str != ' ' && !(*str >= 9 && *str <= 13))
			return (0);
		str++;
	}
	return (1);
}

void	process_line(t_caster *c, char *line, int width, T_Dir *i, const char **order)
{
	if (width > c->map->map_width)
		c->map->map_width = width - 1;
	
	if (*i < end)
	{
		parse_texture_color(c, line, order[*i]);
		(*i)++;
	}
	else
	{
		append_array(line, &c->map->map_arr, &c->map->map_height);
	}
}

void	check_map(t_caster *c)
{
	int		width;
	char 	*line;
	T_Dir	 i;
	const char	*order[6];

	init_var(&width, &i, order, &line);
	while (line)
	{
		if (line[0] == '\n' || !whole_space_line(line))
		{
			free(line);
			line = NULL;
			line = getnextline(c->map->map_fd);
			continue;
		}
		process_line(c, line, width, &i, order);
		free(line);
		line = NULL;
		line = getnextline(c->map->map_fd);
	}
}


// void	check_map(t_caster *c)
// {
// 	int		width;
// 	char 	*line;
// 	T_Dir	 i;
// 	const char	*order[6];

// 	init_var(&width, &i, order, &line);
// 	while(line)
// 	{
// 		if (line[0] == '\n' || !whole_space_line(line))
// 		{
// 			free(line);
// 			line = getnextline(c->map->map_fd);
// 			continue;
// 		}
// 		if (width > c->map->map_width)
// 			c->map->map_width = width - 1;
// 		if (i < end)
// 		{
// 			parse_texture_color(c, line, order[i]);
// 			i++;
// 		}
// 		else
// 			append_array(line, &c->map->map_arr, &c->map->map_height);
// 		free(line);
// 		line = getnextline(c->map->map_fd);
// 	}
// }