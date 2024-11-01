/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:40:58 by jmakkone          #+#    #+#             */
/*   Updated: 2024/10/02 09:34:32 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	append_array(char *content, char ***new_arr, int *new_arr_size)
{
	*new_arr = ft_realloc(*new_arr, \
					sizeof(char *) * *new_arr_size, \
					sizeof(char *) * (*new_arr_size + 2));
	if (!*new_arr)
	{
		write(2, "realloc failed!", 16);
		return ;
	}
	if (content)
	{
		(*new_arr)[*new_arr_size] = ft_strdup(content);
		*new_arr_size += 1;
	}
	(*new_arr)[*new_arr_size] = NULL;
}
