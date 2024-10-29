/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_description.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:00:52 by skwon2            #+#    #+#             */
/*   Updated: 2024/10/29 16:21:29 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void read_description(t_caster *c)
{
	if (file_exits(c, c->map->map_path, ".cub", MAP) == EXIT_FAILURE)
		return ;
	
	
}