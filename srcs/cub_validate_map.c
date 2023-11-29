/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validate_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:14:06 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/26 20:25:11 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_line_is_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != ZERO && line[i] != WALL && line[i] != SPACE \
		&& line[i] != NORTH && line[i] != SOUTH && line[i] != EAST \
		&& line[i] != WEST && line[i] != DOOR_UP \
		&& line[i] != DOOR_DOWN)
			return (0);
		i++;
	}
	return (1);
}

static int	has_seq(char *line, char *seq)
{
	if (ft_strnstr(line, seq, ft_strlen(seq)) \
	&& line[ft_strlen(seq)] == ' ')
		return (1);
	return (0);
}

int	is_valid_elem(char *line)
{
	if (has_seq(line, PRT_NORTH))
		return (NO);
	else if (has_seq(line, PRT_SOUTH))
		return (SO);
	else if (has_seq(line, PRT_EAST))
		return (EA);
	else if (has_seq(line, PRT_WEST))
		return (WE);
	else if (has_seq(line, PRT_UP))
		return (UP);
	else if (has_seq(line, PRT_LOW))
		return (DO);
	else if (has_seq(line, PRT_FLOOR))
		return (F);
	else if (has_seq(line, PRT_CEIL))
		return (C);
	else if (line[0] == '1')
		return (TOT);
	return (-1);
}
