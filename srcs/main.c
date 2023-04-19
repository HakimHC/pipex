/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:42:22 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/19 12:10:08 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	if (BONUS == 0)
		return (no_bonus(argc, argv, envp));
	else if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 9))
		return (bonus_heredoc(argc, argv, envp));
	else if (argc >= 5)
		return (bonus_no_heredoc(argc, argv, envp));
	return (EXIT_FAILURE);
}
