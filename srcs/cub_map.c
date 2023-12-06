/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:57:39 by paugonca          #+#    #+#             */
/*   Updated: 2023/12/06 09:52:14 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_obj(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != ZERO && map[i][j] != SPACE \
			&& map[i][j] != WALL && map[i][j] != NORTH \
			&& map[i][j] != SOUTH && map[i][j] != EAST \
			&& map[i][j] != WEST && map[i][j] != DOOR)
				return (0);
		}
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
			if (map[i][j] == NORTH || map[i][j] == SOUTH \
			|| map[i][j] == EAST || map[i][j] == WEST)
				num++;
	}
	if (num != 1)
		return (0);
	return (1);
}

int	check_line(char **map, int i)
{
	int	j;

	j = -1;
	while (map[i][++j])
	{
		if (map[i][j] == ZERO || map[i][j] == NORTH || map[i][j] == SOUTH ||
			map[i][j] == EAST || map[i][j] == WEST)
		{
			if (j == 0 || j == ft_strlen(map[i]) - 1)
				return (1);
			if (check_line_lim(map, i, j) || check_line_mid(map, i, j))
				return (1);
		}
		if (map[i][j] == DOOR)
		{
			if (j == 0 || j == ft_strlen(map[i]) - 1)
				return (1);
			if (check_door(map, i, j))
				return (1);
		}
	}
	return (0);
}

static int	check_closed(char **map)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (map[++i])
	{
		if (i == 0 || i == mtx_len(map) - 1)
			res += check_border(map, i);
		else
			res += check_line(map, i);
		if (res != 0)
			break ;
	}
	return (res);
}

int	check_map(char **map)
{
	if (!check_obj(map))
		return (print_err_ret("one or more invalid objects in map"));
	else if (!check_player(map))
		return (print_err_ret("invalid player in map"));
	else if (check_closed(map))
		return (print_err_ret("map isn't closed"));
	return (1);
}
