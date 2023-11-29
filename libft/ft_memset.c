/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:37:32 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/02 08:42:39 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	int		i;

	ptr = (char *)s;
	i = 0;
	while (n > 0)
	{
		ptr[i++] = (unsigned char)c;
		n--;
	}
	return (s);
}
