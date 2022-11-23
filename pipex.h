/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:12:11 by ubegona           #+#    #+#             */
/*   Updated: 2022/11/23 14:17:09 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "unistd.h"
#include "stdio.h"
#include "sys/wait.h"
#include "stdlib.h"


// ********************************* estruktura ********************************

typedef struct s_list
{
	char	*file1;
	char	*file2;
	char	***command;
	char	**path;
}					t_list;

// ********************************* pipex_split ***************************
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		contword(char const *s, char c);
int		contletter(char const *s, char c);
char	**ft_split(char const *s, char c);
// ********************************* pipex_main ***************************
void	pipex(t_list input);
int		main(int argc, char **argv, char **envp);
void	child_procces(int fd[2], t_list input);
// ********************************* pipex_libft ***************************
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
#endif
