/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:41:44 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/08 19:07:55 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*word_splitter(const char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_add_word(char **w, const char *s, char c, int j)
{
	w[j] = word_splitter(s, c);
	if (!w[j])
	{
		while (j-- > 0)
			free(w[j]);
		free(w);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**w;

	if (!s)
		return (NULL);
	w = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!w)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!ft_add_word(w, &s[i], c, j++))
				return (NULL);
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	w[j] = NULL;
	return (w);
}

/*void	free_split(char **tab)
{
	int i = 0;
	if (!tab)
		return;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	main(void)
{
	char **result;
	char *test = "Hello!zzzzzzzz";
	char testsep = 'z';
	int i = 0;

	result = ft_split(test, testsep);
	if (!result)
		return (1);
	while (i < ft_count_words(test, testsep))
	{
		printf("%s\n", result[i]);
		i++;
	}
	free_split(result);
	return (0);
}*/
