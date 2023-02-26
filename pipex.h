/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:26:25 by snocita           #+#    #+#             */
/*   Updated: 2023/02/26 15:28:16 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* CUSTOM LIBRARIES */
# include "LIBFT/libft.h"

/* BASIC LIBRARIES */
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

/* SYSTEM LIBRARIES: write, read, close, pipe, dup, dup2, execve, fork */
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <sys/wait.h>

/* ERROR HANDLING */
# define INFILEERR "Error happening in Infile"
# define OUTFILEERR "Error happening in Outfile"
# define INPUTERR "Invalid number of arguments"
# define PIPERR "Error in pipe"
# define CMDERR "Command not found\n"

/* STUCTURE FOR PIPEDATA */
typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	int		fd[2];
	char	*cmd;
	char	**cmd_paths;
	char	**cmd_args;
	char	*paths;
}				t_pipex;

int			main(int argc, char *argv[], char *envp[]);
void		ft_putstr_fd(char *s, int fd);
void		first_subprocess(t_pipex pipex, char *argv[], char *envp[]);
void		second_subprocess(t_pipex pipex, char *argv[], char *envp[]);
// static char	*get_cmd(char **paths, char *cmd);
void		freemainprocess(t_pipex *pipex);
void		freesubprocess(t_pipex *pipex);
void		ft_putstr_fd(char *s, int fd);
int			signalerr(char *err);
int			msg(char *err);

#endif