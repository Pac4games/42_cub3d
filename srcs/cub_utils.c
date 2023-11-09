/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:51:12 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/09 11:53:48 by mnascime         ###   ########.fr       */
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

	if (!line)
		return (0);
	if (ft_strchr(line, '\n'))
		i = ft_strlen(line) - 1;
	else if (ft_strchr(line, '\0'))
	{
		i = 0;
		while (line[i] != '\0')
			i++;
	}
	else
		i = ft_strlen(line);
	while (line[i] && line[i] == ' ')
		i--;
	return (i);
}

char	**solo_matrix(int rows, int cols)
{
	int		i;
	char	**mat;

	mat = malloc((sizeof(*mat) + 1) * rows);
	if (!mat)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		mat[i] = malloc((sizeof(*(mat[i])) + 1) * cols);
		if (!mat[i])
		{
			i = -1;
			while (mat[++i])
				free(mat[i]);
			free(mat);
			return (NULL);
		}
		i++;
	}
	return (mat);
}
