/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:15:56 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/11 23:09:17 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

void	perror_exit(char *error)
{
	perror(error);
	exit(errno);
}

int	ft_error_infile(char *in)
{
	if (access(in, F_OK))
		return (1);
	if (access(in, R_OK))
		return (1);
	return (0);
}

int	ft_error_outfile(char *out)
{
	if (!access(out, F_OK) && access(out, W_OK))
		return (1);
	return (0);
}
//
// int	main(void)
// {
// 	ft_printf("%d\n", ft_error_files("in", "outt"));
// }
