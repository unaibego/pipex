/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:34:26 by ubegona           #+#    #+#             */
/*   Updated: 2022/11/21 14:01:12 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // fork
#include <stdio.h> //printf
#include <sys/wait.h> //wait
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	id;
	int	fd[2];
	char	*test;

	if (pipe(fd) == -1)
		return (1);
	id = fork();
	test = malloc(sizeof(char) * 9);
	if (id == 0)
	{
		test[0] = 'b';
		test[1] = 'a';
		close(fd[0]);
		// dup2(fd[1], 1);
		// printf("kaixo mundua");
		// if (execl("/sbisdfn/ping", "ping", "-c", "3", "google.com", NULL) <= 0)
		// 	printf("mierda");
		if (write(fd[1], &test, 2) <= 0)
			printf("mecadafuen\n");
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		// dup2(1, fd[0]);
		if (read(fd[0], &test, 2) == 0)
			printf("mecauen\n");
		close(fd[0]);
		test[2] = '\0';
		printf("%s\n", test);
	}
	return (0);
}
