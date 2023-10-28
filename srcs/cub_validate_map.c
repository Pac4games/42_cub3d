/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validate_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:14:06 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/26 16:14:35 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_line_is_valid(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != ZERO && line[i] != WALL && line[i] != SPACE &&
		line[i] != NORTH && line[i] != SOUTH && line[i] != EAST &&
		line[i] != WEST && line[i] != UP_DOOR_AT_UP && line[i] != UP_DOOR_AT_DOWN \
		&& line[i] != UP_DOOR_AT_LEFT && line[i] != UP_DOOR_AT_RIGHT \
		&& line[i] != DOWN_DOOR_AT_UP && line[i] != DOWN_DOOR_AT_DOWN \
		&& line[i] != DOWN_DOOR_AT_LEFT && line[i] != DOWN_DOOR_AT_RIGHT )
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_elem(char *line)
{
	if (ft_strnstr(line, PRT_NORTH, ft_strlen(PRT_NORTH)) \
	&& line[ft_strlen(PRT_NORTH)] == ' ')
		return (NO);
	else if (ft_strnstr(line, PRT_SOUTH, ft_strlen(PRT_SOUTH)) \
	&& line[ft_strlen(PRT_SOUTH)] == ' ')
		return (SO);
	else if (ft_strnstr(line, PRT_EAST, ft_strlen(PRT_EAST)) \
	&& line[ft_strlen(PRT_EAST)] == ' ')
		return (EA);
	else if (ft_strnstr(line, PRT_WEST, ft_strlen(PRT_WEST)) \
	&& line[ft_strlen(PRT_WEST)] == ' ')
		return (WE);
	else if (ft_strnstr(line, PRT_UP, ft_strlen(PRT_UP)) \
	&& line[ft_strlen(PRT_UP)] == ' ')
		return (UP);
	else if (ft_strnstr(line, PRT_LOW, ft_strlen(PRT_LOW)) \
	&& line[ft_strlen(PRT_LOW)] == ' ')
		return (DOWN);
	else if (ft_strnstr(line, PRT_FLOOR, ft_strlen(PRT_FLOOR)) \
	&& line[ft_strlen(PRT_FLOOR)] == ' ')
		return (F);
	else if (ft_strnstr(line, PRT_CEIL, ft_strlen(PRT_CEIL)) \
	&& line[ft_strlen(PRT_CEIL)] == ' ')
		return (C);
	else if (line[0] == '1')
		return (TOT);
	return (0);
}
