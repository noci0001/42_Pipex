/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprocesses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:53:39 by snocita           #+#    #+#             */
/*   Updated: 2023/02/22 16:03:45 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

/**
 * @brief Connects infile (fd[1]) to stdin(1), closes fd[0]
 * 
**/
void	first_subprocess(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.fd[0]);
	dup2(pipex.infile, STDIN_FILENO);
	dup2(pipex.fd[1], STDOUT_FILENO);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		freesubprocess(&pipex);
		msg(CMDERR);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	second_subprocess(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.fd[1]);
	dup2(pipex.fd[0], STDIN_FILENO);
	dup2(pipex.outfile, STDOUT_FILENO);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		freesubprocess(&pipex);
		msg(CMDERR);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}
