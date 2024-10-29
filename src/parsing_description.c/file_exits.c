/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_exits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:31:29 by skwon2            #+#    #+#             */
/*   Updated: 2024/10/29 16:33:21 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int file_exits(t_caster *c, char *file, char *extension, int i)
{
	int	len;

	len = ft_strlen(file);
	if (i == MAP)
		c->map->map_fd = open(file, O_RDONLY);
	else if (i == TEXTURE)
		c->map->texture_fd = open(file, O_RDONLY);
	if (c->map->map_fd == -1 || c->map->texture_fd == -1) 
		retrun (exit_failure(c, "Error opening file : check if it is the right path"));
	if (file[len - 4] != extension[0] || file[len - 3] != extension[1] \
	|| file[len - 2] != extension[2] || file[len - 1] != extension[3] \
	|| file[len] != extension[4])
		return (exit_failure(c, "Does not match with extension format"));
	return (EXIT_SUCCESS);
}
