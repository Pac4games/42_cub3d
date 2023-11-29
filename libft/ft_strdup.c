/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:17:28 by paugonca          #+#    #+#             */
/*   Updated: 2023/11/06 14:18:34 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dst;

	dst = (char *)malloc((sizeof(char)) * (ft_strlen(str) + 1));
	if (!dst)
		return (0);
	ft_memcpy(dst, str, ft_strlen(str) + 1);
	return (dst);
}
