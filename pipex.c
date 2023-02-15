/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:39:58 by snocita           #+#    #+#             */
/*   Updated: 2023/02/15 18:24:05 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	checkandopen(int argc, char *argv[], t_pipex *pipex)
{
	if (argc != 5)
	{
		ft_putstr_fd(INPUTERR, 1);
		return (1);
	}
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		ft_putstr_fd(INFILEERR, 1);
		return (2);
	}
	pipex->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->outfile < 0)
	{
		ft_putstr_fd(OUTFILEERR, 1);
		return (3);
	}
	if (pipe(pipex->fd) < 0)
	{
		ft_putstr_fd(PIPERR, 1);
		return (4);
	}
	return (0);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (checkandopen(argc, argv, &pipex) == 0)
	{
		pipex.paths = find_path(envp);
		pipex.cmd_paths = ft_split(pipex.paths, ':');
		pipex.pid1 = fork();
		if (pipex.pid1 == 0)
		{
			first_subprocess(pipex, argv, envp);
		}
		pipex.pid2 = fork();
		if (pipex.pid2 == 0)
		{
			second_subprocess(pipex, argv, envp);
		}
		close_pipes(&pipex);
		waitpid(pipex.pid1, NULL, 0);
		waitpid(pipex.pid2, NULL, 0);
		freemainprocess(&pipex);
		return (0);
	}
}
