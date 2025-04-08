/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:46:45 by tkurukul          #+#    #+#             */
/*   Updated: 2025/04/08 15:37:59 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*home_path(t_info *info)
{
	int	i;
	char	*str;

	i = 0;
	while(info->env[i])
	{
		if (ft_strncmp(info->env[i], "HOME=", 5) == 0)
			str = (info->env[i] + 5);
		i++;
	}
	return (str);
}

void	update_oldpwd(t_info *info)
{
	int	i;
	char	*oldpwd;
	char	*pwd;

	i = 0;
	while(info->env[i])
	{
		if (ft_strncmp(info->env[i], "PWD=", 4) == 0)
			pwd = (info->env[i]+ 4);
		i++;
	}
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	i = 0;
	while(info->env[i])
	{
		if (ft_strncmp(info->env[i], "OLDPWD=", 7) == 0)
		{
			free(info->env[i]);
			info->env[i] = oldpwd;
		}
		i++;
	}
}

void	update_pwd(t_info *info)
{
	int	i;
	char	*newpwd;
	char	*join;

	i = 0;
	newpwd = ft_pwd(0);
	join = ft_strjoin("PWD=", newpwd);
	while(info->env[i])
	{
		if (ft_strncmp(info->env[i], "PWD=", 4) == 0)
		{
			free(info->env[i]);
			info->env[i] = join;
		}
		i++;
	}
}

int	ft_cd(char **args, t_info *info)
{	//ilyas will add args for the list
	char	*home;

	home = home_path(info);
	if (args[1])
		return (write(2, "MINISHELL: cd: too many arguments\n", 35), -1);
	if (args[0] == NULL)
	{
		update_oldpwd(info);
		chdir((const char*)home);
		update_pwd(info);
		return (0);
	}
	else if(args[0])
	{
		if (chdir(args[0]) != 0)
			return (ft_printf("%s\n",strerror(errno)), -1);
		else
		{
			update_oldpwd(info);
			update_pwd(info);
			return (0);
		}
	}
	return (-1);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_info	info;
// 	char	*args[2];
// 	int	i;

// 	i = 0;
// 	(void)ac;
// 	(void)av;
// 	args[0] = NULL;
// 	args[1] = NULL;
// 	info.env = NULL;
// 	ft_env(env, &info);
// 	// while (info.env[i])
// 	// {
// 	// 	printf("%s\n", info.env[i]);
// 	// 	i++;
// 	// }
// 	// printf("\nBEFORE\n\n\nAFTER\n");
// 	ft_cd(args, &info);
// 	i = 0;
// 	while (info.env[i])
// 	{
// 		printf("%s\n", info.env[i]);
// 		fflush(stdout);
// 		i++;
// 	}
// }

