/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 13:58:56 by mnascime          #+#    #+#             */
/*   Updated: 2023/12/10 11:48:05 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

void	ft_free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

char	*strs(const char *s, int i, int f)
{
	char	*str;
	int		j;

	j = 0;
	str = malloc(sizeof(char *) * (f - i));
	if (!str)
		return (NULL);
	while (s[i] && i < f)
	{
		str[j] = s[i++];
		j++;
	}
	str[j] = '\0';
	return (str);
}
