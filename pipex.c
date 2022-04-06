/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 22:55:42 by ayakdi            #+#    #+#             */
/*   Updated: 2022/04/06 12:16:01 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char *env[])
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			paths = ft_split(env[i], "=:");
			return (paths);
		}
		i++;
	}
	return (NULL);
}

int	treat_child_one(int fd, int pipe_fd[2], char *cmd, char *env[])
{
	char	**paths;
	char	**cmds;
	char	*pathcmd;
	int		i;

	paths = get_path(env);
	cmds = ft_split(cmd, " ");
	close(pipe_fd[0]);
	if (dup2(fd, 0) == -1 || dup2(pipe_fd[1], 1) == -1)
		return (perror("dup2: "), 0);
	i = 0;
	while (paths[i])
	{
		pathcmd = ft_strjoin(paths[i], "/");
		pathcmd = ft_strjoin(pathcmd, cmds[0]);
		if (execve(cmd, cmds, env) == -1)
			execve(pathcmd, cmds, env);
		free(pathcmd);
		i++;
	}
	perror("execve: ");
	exit(EXIT_FAILURE);
}

int	treat_child_two(int fd, int pipe_fd[2], char *cmd, char *env[])
{
	char	**paths;
	char	**cmds;
	char	*pathcmd;
	int		i;

	i = 0;
	paths = get_path(env);
	cmds = ft_split(cmd, " ");
	close(pipe_fd[1]);
	if (dup2(fd, 1) == -1 || dup2(pipe_fd[0], 0))
		return (perror("dup2: "), 0);
	i = 0;
	while (paths[i])
	{
		pathcmd = ft_strjoin(paths[i], "/");
		pathcmd = ft_strjoin(pathcmd, cmds[0]);
		if (execve(cmd, cmds, env) == -1)
			execve(pathcmd, cmds, env);
		free(pathcmd);
		i++;
	}
	perror("execve: ");
	exit(EXIT_FAILURE);
}

void	pipex(int f1, int f2, char *av[], char *env[])
{
	pid_t	child1;
	pid_t	child2;
	int		status;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("pipe: "));
	child1 = fork();
	if (child1 < 0)
		return (perror("fork: "));
	if (child1 == 0)
	{
		treat_child_one(f1, pipe_fd, av[2], env);
		waitpid(child1, &status, 0);
	}
	child2 = fork();
	if (child2 < 0)
		return (perror("fork: "));
	if (child2 == 0)
		treat_child_two(f2, pipe_fd, av[3], env);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(child2, &status, 0);
}

int	main(int ac, char *av[], char *env[])
{
	int	f1;
	int	f2;

	if (ac != 5)
		return (write(2, "Invalid number of arguments.\n", 29));
	f1 = openfile(av[1], 0);
	f2 = openfile(av[4], 1);
	if (f1 < 0 || f2 < 0)
		exit(EXIT_FAILURE);
	pipex(f1, f2, av, env);
	close (f1);
	close (f2);
	return (0);
}
