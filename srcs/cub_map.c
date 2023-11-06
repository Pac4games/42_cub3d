/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:08:12 by paugonca          #+#    #+#             */
/*   Updated: 2023/11/06 18:10:00 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		*i += 1;
}

static int	is_walls_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("map:\n");
	for (int k = 0; map[k]; k++)
		printf("%s\n", map[k]);
	skip_spaces(map[0], &j);
	while (map[0][++j])
		if (map[0][j] != '1' && map[0][j] != ' ')
			return (0);
	while (map[++i])
		if (map[i][j] != '1' || map[i][ft_strlen(map[i])] != '1')
				return (0);
	j = -1;
	while (map[i][j])
		if (map[i][++j] != '1' && map[0][j] != ' ')
			return (0);
	return (1);
}

int	is_valid_map(char **map)
{
	if (!is_walls_closed(map))
		return (0);
	return (1);
}
