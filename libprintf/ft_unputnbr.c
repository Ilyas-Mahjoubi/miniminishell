/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unputnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:57:08 by tkurukul          #+#    #+#             */
/*   Updated: 2024/12/03 18:22:54 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	motor(char *str, unsigned int f, unsigned int nb)
{
	int					i;
	unsigned int		count;

	i = f;
	count = 0;
	while (nb > 9)
	{
		str[i] = (nb % 10) + 48;
		nb = nb / 10;
		i++;
		count++;
	}
	str[i] = (nb + 48);
	str[i + 1] = '\0';
	while (i >= 0)
	{
		write(1, &str[i], 1);
		i--;
	}
	return (count + 1);
}

int	ft_unputnbr(unsigned int nb)
{
	unsigned int	i;
	char			str[24];

	i = 0;
	i = motor(str, i, nb);
	return (i);
}
/* int main() {
  printf("\n%d\n", ft_unputnbr(-21474836));
  return 0;
} */
