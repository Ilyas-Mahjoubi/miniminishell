/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:47:10 by tkurukul          #+#    #+#             */
/*   Updated: 2025/04/08 15:38:15 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify(char	*str)
{
	int	i;

	i = 0;
	if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
		return (-1);
	else
		i++;
	while(str[i] && str[i] != '=')
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || ((str[i] >= 'A' && str[i] <= 'Z')) || str[i] == '_'
		|| (str[i] >= '0' && str[i] <= '9') ||  str[i] == 61 || str[i] == '"' || str[i] == 39)
			i++;
		else
			return (-1);
	}
	return (0);
}

int	verify_equal(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 61)
			count = 1;
		i++;
	}
	if (count != 1)
		return (-1);
	return (0);
}

int	exisit(char **matrix, char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], arg, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*form_str(char *str)
{
	int	i;
	int	j;
	int	count;
	int	tot;
	char	*changed;

	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		if(str[i] == 34 || str[i] == 39)
			count++;
		i++;
	}
	if (count == 0)
		return (ft_strdup(str));
	tot = ft_strlen(str) - count;
	changed = malloc((tot + 1) * sizeof(char));
	i = 0;
	while (str[i])
	{
		if(str[i] != 34 && str[i] != 39)
		{
			changed[j] = str[i];
			j++;
		}
		i++;
	}
	changed[j] = '\0';
	return (changed);
}

void	free_mat(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
	{
		// printf("%s\n", matrix[i]);
		// printf("%d\n", i);
		// fflush(stdout);
		i++;
	}
	i--;
	while (i >= 0 && matrix[i])
	{
		free(matrix[i]);
		i--;
	}
	free(matrix);
	matrix = NULL;
	return ;
}

void	matrix_tmp(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->env[i])
		i++;
	info->size = i;
	info->tmp = malloc((i + 1) * sizeof(char *));
	while (info->env[j])
	{
		info->tmp[j] = ft_strdup(info->env[j]);
		j++;
	}
	info->tmp[j] = NULL;
	return ;
}

int	append(char **matrix, char *args)
{
	int	pos;
	int	flag;

	flag = 0;
	pos = exisit(matrix, args);
	if (pos != -1)
	{
		free(matrix[pos]);
		matrix[pos] = ft_strdup(args);
		flag = 1;
	}
	return (flag);
}

char	**matrix_join(t_info *info, char **args, int size)
{
	int		i;
	int		x;
	int		j;
	char	**new;

	i = 0;
	x = 0;
	new = malloc((size + 1) * sizeof(char *));
	while (x <= size)
	{
		new[x] = NULL;
		x++;
	}
	j = 0;
	while(info->tmp[j])
	{
		new[i] = ft_strdup(info->tmp[j]);
		i++;
		j++;
	}
	j = 0;
	while(args[j])
	{
		if (append(new, args[j]) != 1)
			new[i] = ft_strdup(args[j]);
		i++;
		j++;
	}
	free_mat(info->tmp);
	new[size] = NULL;
	return (new);
}

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	sorting(t_info *info)
{
	int	i;
	int	flag;

	matrix_tmp(info);
	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (info->tmp[i + 1])
		{
			if (ft_strcmp(info->tmp[i], info->tmp[i + 1]) > 0)
			{
				swap(&info->tmp[i], &info->tmp[i + 1]);
				flag = 1;
			}
			i++;
		}
	}
}

void	print_export(t_info *info)
{
	int	i;

	i = 0;
	sorting(info);
	while(info->tmp[i])
	{
		ft_printf("declare -x %s\n", info->tmp[i]);
		i++;
	}
	free_mat(info->tmp);
}


void	ft_export(t_info *info, char **args)
{
	int	i;
	int	x;
	int	j;
	int	count;
	char	**tmp;

	i = 0;
	x = 0;
	count = 0;
	if (!args[i])
	{
		print_export(info);
		return ;
	}
	while (args[i])
	{
		if((verify(args[i]) != 0) || (verify_equal(args[i]) != 0))
			ft_printf("bash: export: '%s' : not a valid identifier\n", args[i]);
		else
			count++;
		i++;
	}
	tmp = malloc((count + 1) * sizeof(char *));
	while (x <= count)
	{
		tmp[x] = NULL;
		x++;
	}
	i = 0;
	j = 0;
	while (args[i])
	{
		if((verify(args[i]) == 0) && (verify_equal(args[i]) == 0))
		{
			tmp[j] = form_str((args[i]));
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	matrix_tmp(info);
	free_mat(info->env);
	info->size += count;
	info->env = matrix_join(info, tmp, info->size);
	free_mat(tmp);
}


/* int	main(int ac, char **av, char **env)
{
	t_info	info;
	char	*args[4];
	int	i;

	i = 0;
	(void)ac;
	(void)av;
	args[0] = "FACT= ";
	args[1] = "1fa== 2";
	args[2] = "fic=1";
	args[3] = NULL;
	info.env = NULL;
	form_env(env, &info);
	ft_export(&info, args);
	while (info.env[i])
	{
		printf("%s\n", info.env[i]);
		i++;
	}
	free_mat(info.env);
	// printf("\nBEFORE\n\n\nAFTER\n");
	// i = 0;
	// while (info.env[i])
	// {
	// 	printf("%s\n", info.env[i]);
	// 	fflush(stdout);
	// 	i++;
	// }
} */
//first character has to be a-z
// later it can be a combo of characters numerals and under4score
// "" and '' allowed any where
// try to save env in a ***matrix
// variables that are correct will work
