/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:57:39 by paugonca          #+#    #+#             */
/*   Updated: 2023/11/10 17:32:06 by paugonca         ###   ########.fr       */
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
			if (map[i][j] != ZERO && map[i][j] != SPACE &&
				map[i][j] != WALL && map[i][j] != NORTH &&
				map[i][j] != SOUTH && map[i][j] != EAST &&
				map[i][j] != WEST && map[i][j] != DOOR1_UP &&
				map[i][j] != DOOR1_DOWN && map[i][j] != DOOR1_LEFT &&
				map[i][j] != DOOR1_RIGHT && map[i][j] != DOOR2_UP &&
				map[i][j] != DOOR2_DOWN && map[i][j] != DOOR2_LEFT &&
				map[i][j] != DOOR2_RIGHT)
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

void	check_map(t_cub3d *cub)
{
	if (!check_obj(cub->map->map))
		print_err_cub("one or more invalid objects in map", cub);
	else if (!check_player(cub->map->map))
		print_err_cub("invalid player in map", cub);
}
