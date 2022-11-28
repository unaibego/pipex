/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:34:26 by ubegona           #+#    #+#             */
/*   Updated: 2022/11/28 15:25:52 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_procces_first(int *fd, t_list input, char **envp, int i)
{
	int	temp;

	temp = dup(STDIN_FILENO);
	dup2(input.file_fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(input.file_fd[0]);
	close(fd[0]);
	close(fd[1]);
	if (execve(input.path[i], input.command[i], envp) <= 0)
	{

		dup2(temp, STDOUT_FILENO);
		write(1, "ERROR\n", 6);
	}
}

void	child_procces_last(int *fd, t_list input, char **envp, int i)
{
	int	temp;

	temp = dup(STDIN_FILENO);
	dup2(fd[0], STDIN_FILENO);
	dup2(input.file_fd[1], STDOUT_FILENO);
	close(input.file_fd[1]);
	close(fd[0]);
	close(fd[1]);
	if (execve(input.path[i], input.command[i], envp) <= 0)
	{
		dup2(temp, STDOUT_FILENO);
		write(1, "ERROR\n", 6);
	}
}

char	**find_paths(char **envp)
{
	int		i;
	char	*path_test;
	char	**paths;
	char	**path_okey;

	i = 0;
	path_okey = NULL;
	while (ft_strncmp("PATH", envp[i++], 4))
		path_test = &envp[i][5];
	paths = (ft_split(path_test, ':'));
	path_okey = malloc(sizeof(char *) * ft_strlen(*paths));
	i = 0;
	while (paths[i])
	{
		path_okey[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	path_okey[i] = NULL;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (path_okey);
}

t_list	fill_up_path(int argc, t_list input, char **envp)
{
	int		i;
	int		j;
	char	**paths;
	char	*command_test;

	paths = find_paths(envp);
	input.path = malloc(sizeof(char **) * (argc - 2));
	j = 0;
	while (input.command[j])
	{	
		i = 0;
		command_test = ft_strjoin(paths[i], *input.command[j]);
		while (paths[i] && access(command_test, 0) != 0)
		{
			free(command_test);
			command_test = ft_strjoin(paths[i], *input.command[j]);
			i++;
		}
		input.path[j] = command_test;
		command_test = NULL;
		j++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	return (free(paths), free(command_test), input);
}

t_list	fill_up_input(int argc, char **argv, char **envp)
{
	int		i;
	int		j;
	t_list	input;

	i = 1;
	j = 0;
	input.command = malloc(sizeof(char **) * (argc));
	input.file = malloc(sizeof(char *) * 2);
	input.file[0] = argv[i++];
	while (argv[i + 1])
	{
		input.command[j++] = ft_split(argv[i++], ' ');
	}
	input.command[j] = NULL;
	input.file[1] = argv[i];
	input = fill_up_path(argc, input, envp);
	return (input);
}

void	free_input(t_list input)
{
	int	i;
	int	j;
	int	h;

	i = 0;
	j = 0;
	h = 0;
	free(input.file);
	free(input.path[0]);
	free(input.path[1]);
	free(input.path);
	while (input.command[j])
	{
		while (input.command[j][h])
		{
			free(input.command[j][h]);
			h++;
		}
		h = 0;
		free(input.command[j]);
		j++;
	}
	free(input.command);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	input;

	input = fill_up_input(argc, argv, envp);
	pipex(input, envp);
	free_input(input);
}

int	pipex(t_list input, char **envp)
{
	int		id;
	int		id2;
	int		fd[2];

	pipe(fd);
	id = fork();
	if (id == 0)
	{
		input.file_fd[0] = open(input.file[0], O_RDONLY);
		child_procces_first(fd, input, envp, 0);
	}
	id2 = fork();
	if (id2 == 0)
	{
		input.file_fd[1] = open(input.file[1], O_WRONLY);
		// if (read(0, &id, 1) != 1)
		// 	return (0);
		child_procces_last(fd, input, envp, 1);
	}
	close(fd[1]);
	close(fd[0]);
	waitpid(id, NULL, 0);
	waitpid(id2, NULL, 0);
	return (0);
}
