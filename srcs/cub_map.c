/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:57:39 by paugonca          #+#    #+#             */
/*   Updated: 2023/11/09 16:21:57 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int check_obj(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] != ZERO && map[i][j] != SPACE && \
				map[i][j] != WALL && map[i][j] != NORTH && \
				map[i][j] != SOUTH && map[i][j] != EAST && \
				map[i][j] != WEST)
					return (0);
	}
	return (1);
}

static int	check_player(char **map)
{
	int	i;
	int	j;
	int	num;

	i = -1;
	num = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == NORTH || map[i][j] == SOUTH || \
				map[i][j] == EAST || map[i][j] == WEST)
					num++;
	}
	if (num != 1)
		return (0);
	return (1);
}

int	is_valid_map(char **map)
{
	if (!check_obj(map))
		return (0);
	else if (!check_player(map))
		return (0);
	return (1);
}
