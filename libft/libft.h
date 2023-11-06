/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:13:08 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/06 14:20:17 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(const char *s1, char const *set);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_strjoin_gnl(char *s1, char const *s2);
int		clean_buf(char *buffer);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
int		ft_printf(const char *s, ...);
int		ft_putchar(char c);
int		ft_putnbr_base(int str, char vari);
int		ft_putnbr_p(unsigned long long nb);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	**ft_split_spaces(char const *s);
void	*ft_memset(void *s, int c, size_t n);
int		ft_isdigit(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	*ft_memcpy(void *dst, const void *src, size_t len);
char	*ft_strdup(const char *str);

#endif
