/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:43:37 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/13 21:23:01 by hakahmed         ###   ########.fr       */
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
# include <sys/wait.h>
# define READ_END 0
# define WRITE_END 1
# ifndef BONUS
#  define BONUS 0
# endif

char	*get_path(char *envp[]);
char	**split_path(char *path);
int		ft_error_files(char *in, char *out);
char	*get_cmd(char *path[], char *cmd, int b);
char	**path_arr(char *envp[]);
void	perror_exit(char *error);
int		ft_error_infile(char *in);
int		ft_error_outfile(char *out);
pid_t	ft_fork(void);
void	ft_pipe(int fd[2]);
void	ft_heredoc(char *dl, char **envp, char *cmd, int fd[2]);
void	ft_redirect_pipe(char *cmd, char **envp, int fd[2], int u);
void	ft_execute(char *cmd, char **envp);
int		ft_abs_path(char *cmd);
int		no_bonus(int argc, char **argv, char **envp);
int		bonus_no_heredoc(int argc, char **argv, char **envp);
int		bonus_heredoc(int argc, char **argv, char **envp);
int		ft_open(char *file, int oflags);
void	ft_redirect_in(char *cmd, char **envp, int fd[2], char *file);
void	ft_redirect_out(char *file, int oflags, char **envp, char *cmd);
void	exec_unlink(char *cmd, char **envp, int u);
void	print_127(char *cmd);
int		is_in_path(char *cmd, char **envp);
int		cmds_exists(int argc, char **argv, char **envp);

#endif
