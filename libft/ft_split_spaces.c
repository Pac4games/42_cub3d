/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:38:50 by mnascime          #+#    #+#             */
/*   Updated: 2023/12/10 11:48:36 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	beg_trim(const char *s, int i)
{
	while (s[i] != '\0' && !ft_isspace(s[i]))
		i++;
	return (i);
}

static int	count_c(const char *s)
{
	size_t	f;

	f = 0;
	while (*s)
	{
		while (*s && !ft_isspace(*s))
			s++;
		if (*s && ft_isspace(*s))
			f++;
		while (*s && ft_isspace(*s))
			s++;
	}
	return (f);
}

static int	pre_check(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (!s[i])
		return (0);
	return (1);
}

char	**ft_split_spaces(char const *s)
{
	size_t	i;
	size_t	j;
	char	**ptrs;

	i = 0;
	j = 0;
	if (!s || !pre_check(s))
		return (NULL);
	ptrs = malloc(sizeof(char *) * (ft_strlen(s) + count_c(s) + 1));
	if (!ptrs)
		return (NULL);
	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (s[i] == '\0')
			break ;
		ptrs[j++] = strs(s, i, beg_trim(s, i));
		if (!ptrs[j - 1])
		{
			ft_free_split(ptrs);
			return (NULL);
		}
		i = beg_trim(s, i);
	}
	ptrs[j] = NULL;
	return (ptrs);
}
