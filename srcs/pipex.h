/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:43:37 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/11 01:50:38 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/inc/libft.h"
# include <errno.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# define READ_END 0
# define WRITE_END 1

char	**ft_split(char const *s, char c);
char	*get_path(char *envp[]);
char	**split_path(char *path);
int		ft_error_files(char *in, char *out);
char	*get_cmd(char *path[], char *cmd);
char	**path_arr(char *envp[]);
void	perror_exit(char *error);
int		ft_error_infile(char *in);
int		ft_error_outfile(char *out);
pid_t	ft_fork(void);
void	ft_pipe(int fd[2]);
void	ft_heredoc(char *dl, char **envp, char *cmd, int fd[2]);
void	ft_redirect(char *cmd, char **envp, int fd[2]);
void	ft_execute(char *cmd, char **envp);
int ft_abs_path(char *cmd);

#endif
