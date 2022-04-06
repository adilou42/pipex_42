/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 22:56:02 by ayakdi            #+#    #+#             */
/*   Updated: 2022/04/02 13:19:10 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char *sep);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		openfile(char *filename, int mode);
int		treat_child_one(int fd, int pipe_fd[2], char *cmd, char *env[]);
int		treat_child_two(int fd, int pipe_fd[2], char *cmd, char *env[]);
void	pipex(int f1, int f2, char *av[], char *env[]);

#endif