/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:47:13 by tkurukul          #+#    #+#             */
/*   Updated: 2025/04/08 15:37:25 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pwd(int	i)
{
	char	*buf; //THE-PATH_MAX-ON-LINUX

	buf = getcwd(NULL, 0); // AUTOMATICALLY ALLOCATES MEMORY NESSCARY FOR  THE PATH
	if (!buf)
	{
		perror("pwd: error while retrieving current directory: getcwd:");
		return (NULL);
	}
	else
	{
		if (i == 1)
			ft_printf("%s\n", buf);
		return (buf);
	}
}

/* int	main()
{
	char	*hh;

	hh = ft_pwd();
	printf("%s\n", hh);
	free(hh);
} */
