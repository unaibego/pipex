/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:34:26 by ubegona           #+#    #+#             */
/*   Updated: 2022/11/30 10:09:47 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_input(t_list input)
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

	if (argc != 5)
		return (write(1, "ERROR: Cantidad de argumetos\n", 28), 0);
	input = fill_up_input(argc, argv, envp);
	input.file_fd[0] = open(input.file[0], O_RDONLY);
	input.file_fd[1] = open(input.file[1], O_WRONLY | O_TRUNC | O_CREAT);
	if (input.file_fd[0] == -1 || input.file_fd[1] == -1
		|| access(input.file[0], R_OK) || access(input.file[1], W_OK))
	{
		write(1, "ERROR: Gestion de archivos\n", 27);
		return (free_input(input), 0);
	}
	pipex(input, envp);
	free_input(input);
}

int	pipex(t_list input, char **envp)
{
	int		id;
	int		id2;
	int		fd[2];
	int		status;

	pipe(fd);
	id = fork();
	if (id == 0)
		return (child_procces_first(fd, input, envp, 0));
	id2 = fork();
	if (id2 == 0)
		return (child_procces_last(fd, input, envp, 1));
	close(fd[1]);
	close(fd[0]);
	waitpid(id, &status, 0);
	if (status != 0)
		return (0);
	waitpid(id2, NULL, 0);
	return (0);
}
