/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexconv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:14:49 by tkurukul          #+#    #+#             */
/*   Updated: 2024/12/03 18:15:40 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexconv(int unsigned nb, const char c)
{
	int		i;
	int		resto;
	char	*upp;
	char	*lower;

	upp = "0123456789ABCDEF";
	lower = "0123456789abcdef";
	i = 0;
	if (nb > 15)
	{
		i += ft_hexconv(nb / 16, c);
	}
	resto = nb % 16;
	if (c == 'x')
		i += write (1, &lower[resto], 1);
	if (c == 'X')
		i += write(1, &upp[resto], 1);
	return (i);
}
/* int	main(void)
{
	ft_hexconv(-42, 'X');
} */
