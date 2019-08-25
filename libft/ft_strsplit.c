/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:35:19 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/26 17:35:20 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	**ft_init(char const *s, char c)
{
	char	**array;
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c)
		{
			k = k + 1;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	if (!(array = (char **)malloc(sizeof(char *) * (k + 1))))
		return (NULL);
	return (array);
}

static char	**ft_init_words(char **array, char const *s, char c)
{
	int i;
	int chars;
	int word;

	i = 0;
	chars = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i++])
				chars++;
			if (!(array[word] = ft_strnew(chars)))
				return (NULL);
			chars = 0;
			word++;
		}
		else
			i++;
	}
	if (!(array[word] = ft_strnew(1)))
		return (NULL);
	return (array);
}

static void	ft_fill_array(char **array, char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
			{
				array[j][k] = s[i];
				i++;
				k++;
			}
			array[j][k] = '\0';
			k = 0;
			j++;
		}
		else
			i++;
	}
	array[j] = NULL;
}

char		**ft_strsplit(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = ft_init(s, c);
	if (!array)
		return (NULL);
	array = ft_init_words(array, s, c);
	if (!array)
		return (NULL);
	ft_fill_array(array, s, c);
	return (array);
}
