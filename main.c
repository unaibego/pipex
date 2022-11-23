/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:34:26 by ubegona           #+#    #+#             */
/*   Updated: 2022/11/23 14:46:28 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_procces(int fd[2], t_list input)
{

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execlp("/sbin/ping", input.command[0][0], input.command[0][1],input.command[0][2], input.command[0][3], NULL) <= 0)
		printf("mierda");
}

t_list	find_path(int argc, t_list input, char **envp)
{
	int		i;
	int		j;
	char	*path_test;
	char	**paths;
	char	*command_test;

	i = 0;
	while (ft_strncmp("PATH", envp[i++], 4))
		path_test = &envp[i][5];
	paths = ft_split (path_test, ':');
	j = 0;
	input.path = malloc(sizeof(char **) * 10);
	while (input.command[j])
	{	
		i = 0;
		
		while (access(command_test, 0) != 0)
		{
			paths[i] = ft_strjoin(paths[i], "/");
			command_test = ft_strjoin(paths[i], *input.command[j]);
			printf("q hostias %s\n", command_test);
			i++;
		}
		free(command_test);
		input.path[j] = command_test;
		j++;
	}
	printf("hau 0 %s eta hau 1 %s\n", input.path[0], input.path[1]);
	return (input);
}

t_list	fill_up_input(int argc, char **argv, char **envp)
{
	int		i;
	int		j;
	t_list	input;

	i = 1;
	j = 0;
	input.file1 = argv[i++];
	input.command = malloc(sizeof(char **) * 10);
	while (argv[i])
	{
		input.command[j++] = ft_split(argv[i++], ' ');
	}
	input.command[j] = NULL;
	input.file2 = argv[i];
	find_path(argc, input, envp);
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	input;

	input = fill_up_input(argc, argv, envp);
	pipex(input);
}

void	pipex(t_list input)
{
	int		id;
	int		id2;
	int		fd[2];

	pipe(fd);
	id = fork();
	if (id == 0)
	{
		child_procces(fd, input);
	}
	else
	{
		id2 = fork();
		if (id2 == 0)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			execlp("/usr/bin/wc", input.command[1][0], input.command[1][1], NULL);
		}
		else
		{
			close(fd[1]);
			close(fd[0]);
			waitpid(id, NULL, 0);
			waitpid(id2, NULL, 0);
		}
	}
}
