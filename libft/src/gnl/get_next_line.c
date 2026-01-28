/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:31:45 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/27 04:10:24 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	**gnl_stash_ptr(void)
{
	static char	*stash[MAX_FD] = {NULL};

	return (stash);
}

static char	*extract_line(char *stash)
{
	int		i;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	gnl_memcpy(line, stash, i);
	line[i] = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	new_stash = malloc(gnl_strlen(stash) - i + 1);
	if (!new_stash)
		return (free(stash), NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

static char	*read_and_join(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes;
	char	*tmp;

	if (!stash)
		stash = gnl_strdup("");
	bytes = 1;
	while (!gnl_strchr(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(stash), NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		tmp = gnl_strjoin(stash, buffer);
		free(stash);
		if (!tmp)
			return (NULL);
		stash = tmp;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		**stash;
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	stash = gnl_stash_ptr();
	if (!stash)
		return (NULL);
	stash[fd] = read_and_join(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = clean_stash(stash[fd]);
	if (!line || line[0] == '\0')
		return (free(line), NULL);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	test_errors(void)
{
	int		fd;
	char	*line;

	line = get_next_line(-1);
	if (line == NULL)
		printf("C'est ok pour fd = -1\n");
	else
	{
		printf("Pas ok pour fd = -1 : %s\n", line);
		free(line);
	}
	fd = open("t_many_random_lines.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur");
		return;
	}
	close(fd);
	line = get_next_line(fd);
	if (line == NULL)
		printf("C'est ok pour fd close\n");
	else
	{
		printf("Pas ok pour fd close : %s\n", line);
		free(line);
	}
	fd = open("t_empty.txt", O_RDONLY);
	if (fd < 0)
		perror("Erreur");
	else
	{
		line = get_next_line(fd);
		if (line == NULL)
			printf("C'est ok pour fichier vide\n");
		else
		{
			printf("Pas ok pour fichier vide : %s\n", line);
			free(line);
		}
		close(fd);
	}
}

static void	test_multi_fd(void)
{
	int		fd1, fd2, fd3;
	char	*l1, *l2, *l3;
	int		done = 0;

	fd1 = open("t_multi1_bonus.txt", O_RDONLY);
	fd2 = open("t_multi2_bonus.txt", O_RDONLY);
	fd3 = open("t_multi3_bonus.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		perror("Error");
		return;
	}
	while (!done)
	{
		done = 1;
		l1 = get_next_line(fd1);
		l2 = get_next_line(fd2);
		l3 = get_next_line(fd3);
		if (l1)
		{
			printf("[FD1] %s", l1);
			free(l1);
			done = 0;
		}
		if (l2)
		{
			printf("[FD2] %s", l2);
			free(l2);
			done = 0;
		}
		if (l3)
		{
			printf("[FD3] %s", l3);
			free(l3);
			done = 0;
		}
	}
	close(fd1);
	close(fd2);
	close(fd3);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i = 1;

	if (argc == 2 && strcmp(argv[1], "test-errors") == 0)
		return (test_errors(), 0);
	if (argc == 2 && strcmp(argv[1], "test-multi") == 0)
		return (test_multi_fd(), 0);
	if (argc == 1)
	{
		printf("Entrée standard\n");
		fd = 0;
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Erreur");
			return (1);
		}
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Ligne %d : %s", i, line);
		free(line);
		i++;
	}

	if (argc == 2)
		close(fd);

	return (0);
}
*/
