/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:08:12 by paugonca          #+#    #+#             */
/*   Updated: 2023/11/06 16:41:47 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_walls_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	printf("map:\n");
	for (int k = 0; map[k]; k++)
		printf("%s\n", map[k]);
	printf("check 1\n");
	while (map[0][++j])
		if (map[0][j] != '1' || map[0][j] != ' ')
			return (0);
	printf("check 2\n");
	while (map[++i])
	{
		j = 0;
		printf("check loop\n");
		while (map[i][++j])
			if (map[i][0] != '1' || map[i][ft_strlen(map[i])] != '1')
				return (0);
	}
	printf("check 3\n");
	j = -1;
	while (map[i][j])
		if (map[i][++j] != '1' || map[0][j] != ' ')
			return (0);
	return (1);
}

int	is_valid_map(char **map)
{
	if (!is_walls_closed(map))
		return (0);
	return (1);
}
