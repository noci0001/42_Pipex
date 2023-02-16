/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:39:58 by snocita           #+#    #+#             */
/*   Updated: 2023/02/16 14:36:15 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Looks into the ENV file and 
 * compares every indices with the voice "PATH".
 * returns the whole path minus "PATH="
 * @return /usr/local/bin:/usr/bin:
 * /bin:/usr/sbin:/sbin:/usr/local/munki:
 * /opt/X11/bin:/Library/Apple/usr/bin
 */
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

/**
 * @brief Checks that the arguments are 5, 
 * that the in/outfile is correctly connected to argv[1/-1],
 * that the pipe was successfully created.
 * @param pipex Is a struct with all the info regarding the pipe project
 **/
int	checkandopen(int argc, char *argv[], t_pipex *pipex)
{
	if (argc != 5)
	{
		signalerr(INPUTERR);
	}
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		signalerr(INFILEERR);
	}
	pipex->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->outfile < 0)
	{
		signalerr(OUTFILEERR);
	}
	if (pipe(pipex->fd) < 0)
	{
		signalerr(PIPERR);
	}
	return (0);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

/**
 * @brief Simulate a pipe operator
 * @param argc Is the number of arguments passed into the program
 * @param argv Is the argument vector 
 * example -> argv[./pipex, infile.txt, "cat", "grep BROWN", outfile.txt]
 */
int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (checkandopen(argc, argv, &pipex) != 0)
		return (0);
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_subprocess(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_subprocess(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	freemainprocess(&pipex);
	return (0);
}
