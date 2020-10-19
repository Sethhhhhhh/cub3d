/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:17:27 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/13 12:17:29 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	s_set_resolution(t_g *g, char *line, t_size *size, int index)
{
	int		check;

	check = 0;
	if (!index)
		line++;
	while (*line && !ft_isdigit(*line))
		if (!ft_isspace(*line++))
			s_error(g, "	Parsing: invalid input.\n");
	if ((!index && size->w != -1) || size->h != -1)
		s_error(g, "	Parsing: 2 resolutions in map file.\n");
	if (!index)
		size->w = 0;
	else
		size->h = 0;
	while (*line && ft_isdigit(*line))
		if (!index)
			size->w = size->w * 10 + (*line++ - 48);
		else
			size->h = size->h * 10 + (*line++ - 48);
	while (index >= 1 && *line)
		if (ft_isalnum((*line)++))
			check = 1;
	if (index < 1 || check)
		s_set_resolution(g, line, size, index + 1);
	return (1);
}

static int	s_set_textures(t_g *g, char *line, char **texture, int id)
{
	int		i;

	if (*texture != NULL)
		s_error(g, "	Parsing: 2 same textures in map file.\n");
	if (id == 4)
		line += 1;
	else
		line += 2;
	while (*line && ft_isspace(*line))
		line++;
	if (!(*texture = (char *)malloc(sizeof(char) * ft_strlen(line) + 1)))
		s_error(g, "	Parsing: the malloc failed [*texture]");
	i = 0;
	while (*line && !ft_isspace(*line))
		(*texture)[i++] = *line++;
	(*texture)[i] = '\0';
	return (1);
}

static int	s_set_colors(t_g *g, char *line, int *color, int index)
{
	int color_base;
	int	check;

	check = 0;
	if (!index && line++)
		if (*color != -1 && !(*color = 0))
			s_error(g, "	Parsing: 2 colors in map file.\n");
	while (*line && (ft_isspace(*line) || *line == ','))
		line++;
	color_base = 0;
	while (*line && ft_isdigit(*line) && (check = 1))
		color_base = color_base * 10 + (*(line++) - 48);
	if (color_base > 255 || color_base < 0 || !check)
		s_error(g, "	Parsing: the color is not correct.\n	[Usage]:\
		r[0-255], g[0-255], b[0-255]\n");
	if (!index)
		*color += color_base * 65536;
	else
		*color += index == 1 ? color_base * 256 : color_base;
	if (index <= 1)
		s_set_colors(g, line, color, index + 1);
	else if (ft_strlen(line) > 1)
		s_error(g, "	Parsing: bad input.\n");
	return (1);
}

static int	s_check(char *line, t_g *g)
{
	while (*line && ft_isspace(*line))
		line++;
	if (!ft_strncmp(line, "R", 1))
		return (s_set_resolution(g, line, &(g->parse.size), 0));
	else if (!ft_strncmp(line, "NO", 2))
		return (s_set_textures(g, line, &(g->parse.north), 0));
	else if (!ft_strncmp(line, "SO", 2))
		return (s_set_textures(g, line, &(g->parse.south), 1));
	else if (!ft_strncmp(line, "WE", 2))
		return (s_set_textures(g, line, &(g->parse.west), 2));
	else if (!ft_strncmp(line, "EA", 2))
		return (s_set_textures(g, line, &(g->parse.east), 3));
	else if (!ft_strncmp(line, "S", 1))
		return (s_set_textures(g, line, &(g->parse.sprite), 4));
	else if (!ft_strncmp(line, "F", 1))
		return (s_set_colors(g, line, &(g->parse.floor), 0));
	else if (!ft_strncmp(line, "C", 1))
		return (s_set_colors(g, line, &(g->parse.ceiling), 0));
	return (-1);
}

void		s_parse(t_g *g, int fd)
{
	char	*line;
	int		ret;
	int		ml;
	int		lb;

	ml = 0;
	lb = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line && *line != '\0')
			if ((ret = s_check(line, g)) == -1 && ft_strchr(" 102NSEW", *line))
			{
				if (s_is_map_parsing(g))
					if (s_parse_map(g, line, &g->parse.size_grid_y, &ml)
					&& lb == 2)
						s_error(g, "	Parsing: the wap is wrong.");
				lb = 1;
			}
			else if (ret == -1)
				s_error(g, "	Parsing: bad id.\n");
		lb = (lb && *line == '\0') ? 2 : lb;
		free(line);
	}
	free(line);
}
