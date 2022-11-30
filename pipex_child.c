/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:44:12 by ubegona           #+#    #+#             */
/*   Updated: 2022/11/30 10:12:51 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_procces_first(int *fd, t_list input, char **envp, int i)
{
	int	temp;

	temp = dup(STDOUT_FILENO);
	dup2(input.file_fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(input.file_fd[0]);
	close(fd[0]);
	close(fd[1]);
	if (execve(input.path[i], input.command[i], envp) <= 0)
	{
		dup2(temp, STDOUT_FILENO);
		write(1, "ERROR: Primer proceso\n", 22);
		return (1);
	}
	return (0);
}

int	child_procces_last(int *fd, t_list input, char **envp, int i)
{
	int	temp;

	temp = dup(STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	dup2(input.file_fd[1], STDOUT_FILENO);
	close(input.file_fd[1]);
	close(fd[0]);
	close(fd[1]);
	if (execve(input.path[i], input.command[i], envp) <= 0)
	{
		dup2(temp, STDOUT_FILENO);
		write(1, "ERROR: Segundo proceso\n", 23);
		return (1);
	}
	return (0);
}
