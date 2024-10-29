/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:55:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/10/29 17:07:27 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init(t_caster *c, char **av)
{
	c->window_title = av[0];
	c->img = malloc(sizeof(t_img));
	if (!c->img)
		exit_failure(c, "img malloc failed");
	c->img->handle = NULL;
	c->img->view = NULL;
	c->img->minimap = NULL;
	c->img->player = NULL;
	c->map = malloc(sizeof(t_map));
	c->map_fd = -2;
	c->texture_fd = -2;
	c->map->map_path = av[1];
	c->map->texture_path = NULL;
	printf("the map_name = \"%s\"\n", c->map->map_path);
	if (!c->map)
		exit_failure(c, "map malloc failed");
	c->map->map_arr = NULL;
	c->map->map_width = 0;
	c->map->map_height = 0;
	c->textures = malloc(sizeof(t_textures));
	if (!c->textures)
		exit_failure(c, "textures malloc failed");
	c->textures->north_texture = NULL;
	c->textures->south_texture = NULL;
	c->textures->east_texture = NULL;
	c->textures->west_texture = NULL;
	c->textures->floor_color = 0;
	c->textures->ceiling_color = 0;
	c->speed_multiplier = 0.02;
	c->px = 0;
	c->py = 0;
	c->mmap_px = 0;
	c->mmap_py = 0;
	c->view_angle = 0;
	c->plane_x = 0.66;
	//c->plane_y = -0.66;
	c->camera = 0;
	c->ray_dir_x = 0;
	c->ray_dir_y = 0;
	c->map_x = 0;
	c->map_y = 0;
	c->delta_dist_x = 0;
	c->delta_dist_y = 0;
	c->step_x = 0;
	c->step_y = 0;
	c->side_dist_x = 0;
	c->side_dist_y = 0;
	c->wall_hit_side = 0;
	c->wall_dist = 0;
	c->wall_height = 0;
	c->draw_start = 0;
	c->draw_end = 0;
	c->wall_texture = NULL;
	c->tex_x = 0;
	c->tex_y = 0;
	c->pixel_color = 0;

}

void	reset_images(t_caster *c)
{
	if (c->img->view)
		mlx_delete_image(c->img->handle, c->img->view);
	if (c->img->minimap)
		mlx_delete_image(c->img->handle, c->img->minimap);
	if (c->img->player)
		mlx_delete_image(c->img->handle, c->img->player);
	c->img->view = mlx_new_image(c->img->handle, WIDTH, HEIGHT);
	c->img->minimap = mlx_new_image(c->img->handle, WIDTH, HEIGHT);
	c->img->player = mlx_new_image(c->img->handle, WIDTH, HEIGHT);
	mlx_image_to_window(c->img->handle, c->img->view, 0, 0);
	mlx_image_to_window(c->img->handle, c->img->minimap, 20, 20);
	mlx_image_to_window(c->img->handle, c->img->player, 20, 20);
	c->img->view->instances[0].z = 0;
	c->img->minimap->instances[0].z = 1;
	c->img->player->instances[0].z = 2;
}

void	render_engine(t_caster *c)
{
	printf("FPS: %f\n", 1 / c->img->handle->delta_time);
	//reset_images(c);
	raycaster(c);
	parse_minimap(c);
	if (c->img->player)
		mlx_delete_image(c->img->handle, c->img->player);
	c->img->player = mlx_new_image(c->img->handle, WIDTH, HEIGHT);
	mlx_image_to_window(c->img->handle, c->img->player, 20, 20);
	draw_player_to_minimap(c);
}

void	game_loop(void *param)
{
	t_caster	*c;
	int 		redraw;

	c = (t_caster *)param;
	redraw = 0;

	c->speed_multiplier = c->img->handle->delta_time * 2.2;
	redraw |= movement_up_down(c);
	redraw |= movement_left_right(c);
	redraw |= turn_left_right(c);
	if (redraw)
		render_engine(c);
}

int	main(int ac, char **av)
{
	t_caster c;

	if (ac != 2)
	{
		printf("Error, invalid number of arguments.\n");
		return (0);
	}
	init(&c, av);
	read_map(&c, av);
	int i = -1;
	while (c.map->map_arr[++i])
		printf("%s", c.map->map_arr[i]);
	window_init(&c);
//	i = -1;
//	while (++i < 4096)
//		printf("Pixel data: %d\n", c.textures->wall_texture->pixels[i]);
	render_engine(&c);
	mlx_loop_hook(c.img->handle, &game_loop, &c);
	mlx_key_hook(c.img->handle, &keyboard_listener, &c);
	mlx_loop(c.img->handle);
	exit_mlx(&c);
	return (0);
}
