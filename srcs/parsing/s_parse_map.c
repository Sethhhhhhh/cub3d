/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_parse_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:23:34 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/13 12:23:36 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*s_check(t_g *g, int count, char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (!ft_strchr(" 012NSEW", line[i]))
			s_error(g, "	Parsing: the map is not correctly closed or is\
	not composed only of [012NSEW].\n");
		if (line[i] == ' ')
			line[i] = '1';
	}
	if (count == 0)
	{
		i = -1;
		while (line[++i])
			if (line[i] != '1')
				s_error(g, "	Parsing: the map is not correctly closed or is\
	not composed only of [012NSEW].\n");
	}
	else if (line[0] != '1' || line[(int)ft_strlen(line) - 1] != '1')
		s_error(g, "	Parsing: the map is not correctly closed or is not\
		composed only of [012NSEW].\n");
	return (line);
}

static char	*s_complete(t_g *g, char *line, int count)
{
	char	*new;
	char	add[count];
	int		i;

	i = 0;
	while (i < count)
	{
		add[i] = '1';
		i++;
	}
	add[i] = '\0';
	if (!(new = ft_strcat(line, add)))
		s_error(g, "	Parsing: the malloc failed [new].\n");
	return (new);
}

static void	s_copy_line(t_g *g, char ***tmp, int count, int ml)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	if (count >= 1)
	{
		i = count;
		while (--i >= 0)
		{
			if (!((g->parse.map)[i] = (char *)malloc(sizeof(char) * (ml + 1))))
				s_error(g, "	Parsing: malloc failed [g->parse.map[i]].\n");
			if ((int)ft_strlen((*tmp)[i]) < ml)
			{
				new = s_complete(g, (*tmp)[i], (ml
				- (int)ft_strlen((*tmp)[i])));
				ft_strcpy((g->parse.map)[i], new);
				free(new);
			}
			else
				ft_strcpy((g->parse.map)[i], (*tmp)[i]);
			free((*tmp)[i]);
		}
		free(*tmp);
	}
}

int			s_parse_map(t_g *g, char *line, int *count, int *ml)
{
	char		**tmp;
	char		*new;
	int			length;

	new = NULL;
	if (!(line = s_check(g, (*count), line)))
		s_error(g, "	Parsing: the parsing failed.\n");
	tmp = (*count) >= 1 ? g->parse.map : NULL;
	if (!((g->parse.map) = (char **)malloc(sizeof(char *) * (*count) + 1)))
		s_error(g, "	Parsing: the malloc failed [g->parse.map].\n");
	if ((length = ft_strlen(line)) > (*ml))
		(*ml) = length;
	if (!((g->parse.map)[(*count)] = (char *)malloc(sizeof(char) * (*ml) + 1)))
		s_error(g, "	Parsing: the malloc failed [g->parse.map[*count]].\n");
	if (length == (*ml))
		ft_strcpy((g->parse.map)[(*count)], line);
	else
	{
		new = s_complete(g, line, ((*ml) - length));
		ft_strcpy((g->parse.map)[(*count)], new);
		free(new);
	}
	s_copy_line(g, &tmp, *count, *ml);
	(*count)++;
	return (1);
}
