/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:12:11 by ubegona           #+#    #+#             */
/*   Updated: 2022/11/30 09:11:30 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "unistd.h"
# include "fcntl.h"
# include "stdio.h"
# include "sys/wait.h"
# include "stdlib.h"
# include "string.h"

// ********************************* estruktura ********************************

typedef struct s_list
{
	char	**file;
	int		file_fd[2];
	char	***command;
	char	**path;
}					t_list;

// ********************************* pipex_split ***************************
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		contword(char const *s, char c);
int		contletter(char const *s, char c);
char	**ft_split(char const *s, char c);
// ********************************* pipex_main ***************************
int		pipex(t_list input, char **envp);
int		main(int argc, char **argv, char **envp);
// ********************************* pipex_child ***************************
int		child_procces_first(int *fd, t_list input, char **envp, int i);
int		child_procces_last(int *fd, t_list input, char **envp, int i);
// ********************************* pipex_fill_up ***************************
char	**find_paths(char **envp);
t_list	fill_up_path(int argc, t_list input, char **envp);
t_list	fill_up_input(int argc, char **argv, char **envp);
// ********************************* pipex_libft ***************************
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(char *s1, char *s2, unsigned int n);

#endif
