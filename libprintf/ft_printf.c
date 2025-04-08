/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:07:57 by tkurukul          #+#    #+#             */
/*   Updated: 2024/12/03 18:16:16 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check(const char c, va_list args)
{
	int	count;

	count = 0;
	if (c == '%')
		count += ft_putcharr('%');
	else if (c == 'c')
		count += ft_putcharr(va_arg(args, int));
	else if (c == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		count += ft_punt(va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		count += ft_unputnbr(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		count += ft_hexconv(va_arg(args, unsigned int), c);
	return (count);
}

int	ft_printf(const char *convs, ...)
{
	va_list		args;
	int			i;
	int			count;

	count = 0;
	i = 0;
	va_start(args, convs);
	while (convs[i] != '\0')
	{
		if (convs[i] == '%')
		{
			i++;
			if (convs[i] == 32)
				return (0);
			count += ft_check(convs[i], args);
		}
		else
			count += ft_putcharr(convs[i]);
		i++;
	}
	va_end(args);
	return (count);
}

/* int	main(void)
{
	char *b = "weq";
	char *f = b;
	int i = 123;
	ft_printf("%s Is it? %p", "Is this working? ", f);
} */
