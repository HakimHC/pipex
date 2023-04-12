/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:28:50 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/12 17:31:43 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			return (ft_strdup(ft_strchr(envp[i], '=') + 1));
		i++;
	}
	// perror_exit("PATH");
	return (NULL);
}

char	**split_path(char *path)
{
	char	**arr;
	char	*aux;
	int		i;

	arr = ft_split(path, ':');
	free(path);
	i = 0;
	while (arr[i])
	{
		aux = arr[i];
		arr[i] = ft_strjoin(arr[i], "/");
		free(aux);
		i++;
	}
	return (arr);
}

char	**path_arr(char *envp[])
{
	char	*path;
	char	**arr_path;

	path = get_path(envp);
	if (!path)
		return (NULL);
	arr_path = split_path(path);
	return (arr_path);
}

char	*get_cmd(char *path[], char *cmd)
{
	int		i;
	char	*check;

	i = 0;
	while (path && path[i] && cmd)
	{
		check = ft_strjoin(path[i], cmd);
		if (!access(check, F_OK))
			return (ft_free_strarr(path), check);
		free(check);
		i++;
	}
	if (path)
		ft_free_strarr(path);
	// ft_putstr_fd("command not found: ", 2);
	// if (cmd)
	// 	ft_putendl_fd(cmd, 2);
	// else
	// 	write(2, "\n", 1);
	exit(errno);
	return (0);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	*path;
// 	char	**arr;
//
// 	path = get_path(envp);
// 	arr = split_path(path);
// 	ft_printf("%d\n", access_check(arr, argv[1]));
// }
