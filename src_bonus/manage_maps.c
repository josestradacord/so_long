/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_maps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:37:27 by joestrad          #+#    #+#             */
/*   Updated: 2023/03/27 16:57:30 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

/**
 * @brief 			This function joins the line to the old_map, return a
 * 					new map (with the line added) and before frees the
 * 					old_map map
 * 
 * @param old_map 	The map read until now
 * @param line 		The new line to be added to th map
 * @return char* 	The new map with the line added
 */
char	*ft_join_map(char *old_map, char *line)
{
	char	*map;

	map = ft_strjoin(old_map, line);
	free(old_map);
	return (map);
}

/**
 * @brief 			This function reads the map from the file asociated to
 * 					the given fd and copies it in the structure pointed by
 * 					game
 * 
 * @param game 		A pointer to the main structure of the program
 * @param fd 		An integer asociated to the file which holds the map
 */
void	ft_read_map(t_game *game, int fd)
{
	char	*line;
	char	*map;

	line = get_next_line(fd);
	map = NULL;
	while (line)
	{
		map = ft_join_map(map, line);
		free(line);
		line = get_next_line(fd);
	}
	if (ft_strlen(map) == 0)
		ft_error(BOR_ERROR, game);
	game->map = ft_split(map, '\n');
	game->map_cp = ft_split(map, '\n');
	free(line);
	free(map);
}

/**
 * @brief 			This function checks if the characters in the map are the
 * 					valid ones or not. In the map only must be the following
 * 					characters: '0', '1', 'P', 'E', 'B' and 'C'. If there is a
 * 					not valid character, it throws an error
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_check_elems(t_game *game)
{
	int	i_r;
	int	i_c;
	int	invalid_car;

	i_r = 0;
	invalid_car = 0;
	while (i_r < game->map_nr)
	{
		i_c = 0;
		while (i_c < game->map_nc)
		{
			ft_check_map_chars(game, i_r, i_c, &invalid_car);
			i_c++;
		}
		i_r++;
	}
	ft_check_chars(game);
	if (invalid_car == 1)
		ft_error(INV_ERROR, game);
}

/**
 * @brief 			This function checks if the map (stored in the game
 * 					structure) complains the requisites to be a valid map
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_check_map(t_game *game)
{
	ft_check_rows(game);
	ft_check_cols(game);
	if (!ft_check_border(game))
		ft_error(BOR_ERROR, game);
	ft_check_elems(game);
	ft_check_path(game);
}

/**
 * @brief 			This function does the validation of the map. It reads it
 * 					and checks it
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_map_valid(t_game *game)
{
	int		fd;

	fd = open(game->map_name, O_RDONLY);
	if (fd < 0)
		ft_error(FILE_ERROR, game);
	ft_read_map(game, fd);
	close(fd);
	ft_check_map(game);
}
