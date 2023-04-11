/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:43:19 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/11 19:38:02 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror_exit("fork");
	return (pid);
}

void	ft_pipe(int fd[2])
{
	int	p;

	p = pipe(fd);
	if (p < 0)
		perror_exit("pipe");
}

int	ft_open(char *file, int oflags)
{
	int	fd;

	fd = open(file, oflags, 0644);
	if (fd < 0)
		perror_exit(file);
	return (fd);
}
