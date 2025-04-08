/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:02:26 by tkurukul          #+#    #+#             */
/*   Updated: 2024/12/03 18:22:01 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <ctype.h>
# include <stdarg.h>

int	ft_hexconv(int unsigned nb, const char c);
int	ft_punt(void *ptr);
int	ft_putcharr(char c);
int	ft_putnbr(int nb);
int	ft_putstr(char *str);
int	ft_unputnbr(unsigned int nb);
int	ft_printf(const char *convs, ...);

#endif
