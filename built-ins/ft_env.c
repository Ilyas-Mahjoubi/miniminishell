/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:48:49 by tkurukul          #+#    #+#             */
/*   Updated: 2025/04/08 15:38:10 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// form_env should be in the main with the read line

void	form_env(char **env, t_info	*info)
{
	int		count;

	count = 0;
	while (env[count])
		count++;
	info->env = malloc((count + 1) * sizeof(char *));
	if (!info->env)
	{
		write(2, "ERROR WHILE COPYING ENV\n", 24);
		return ;
	}
	count = 0;
	while(env[count])
	{
		info->env[count] = ft_strdup(env[count]);
		count++;
	}
	info->env[count] = NULL;
}

void	ft_env(t_info *info)
{
	int	i;

	i = 0;
	while (info->env[i])
	{
		ft_printf("%s\n", info->env[i]);
		i++;
	}
}
/* int	main(int ac, char **av, char **env)
{
	int	i;
	t_info	i;

	(void)ac;
	(void)av;

	i = 0;
	i.matrix = ft_env(env);
	while (matrix[i])
	{
		printf("%s\n", i.matrix[i]);
		fflush(stdout);
		free(i.matrix[i]);
		i++;
	}
	free(i.matrix);
} */
