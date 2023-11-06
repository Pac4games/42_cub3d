/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:18:44 by paugonca          #+#    #+#             */
/*   Updated: 2023/11/06 14:19:00 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t	p;

	p = 0;
	if (dst == src || len == 0)
		return (dst);
	while (p < len)
	{
		((char *)dst)[p] = ((const char *)src)[p];
		p++;
	}
	return (dst);
}
