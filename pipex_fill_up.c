/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fill_up.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:46:44 by ubegona           #+#    #+#             */
/*   Updated: 2022/11/29 13:21:35 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		input.path[j++] = command_test;
		command_test = NULL;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	return (free(paths), free(command_test), input);
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
