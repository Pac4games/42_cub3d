/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:51:12 by mnascime          #+#    #+#             */
/*   Updated: 2023/12/06 09:56:07 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_isspace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	is_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_str_end_trim(char *line)
{
	int		i;

	i = 0;
	if (!line)
		return (0);
	if (ft_strchr(line, '\n'))
		i = ft_strlen(line) - 1;
	else if (!ft_strchr(line, '\n'))
	{
		while (line[i] != '\0')
			i++;
	}
	while (line[i] && line[i] == ' ')
		i--;
	return (i);
}

char	*conv_to_txtr_text(char c)
{
	if (c == NO)
		return (PRT_NORTH);
	else if (c == SO)
		return (PRT_SOUTH);
	else if (c == EA)
		return (PRT_EAST);
	else if (c == WE)
		return (PRT_WEST);
	else if (c == F)
		return (PRT_FLOOR);
	else if (c == C)
		return (PRT_CEIL);
	else if (c == DO)
		return (PRT_DOOR);
	else if (c == SP)
		return (PRT_SPR);
	else
		return (NULL);
}
