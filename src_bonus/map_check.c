/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:37:52 by joestrad          #+#    #+#             */
/*   Updated: 2023/03/27 16:58:44 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

/**
 * @brief 			This function checks the rows in the map and counts them
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_check_rows(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[index])
		index++;
	if (index == 0)
		ft_error(ROW_ERROR, game);
	game->map_nr = index;
	game->map_h = game->map_nr * game->sprite_h;
}

/**
 * @brief 			This function checks the length of the columns in the map
 * 					and verifies that all of them have the same length 
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_check_cols(t_game *game)
{
	int	index;
	int	len;

	index = 0;
	while (index < game->map_nr)
	{
		len = ft_strlen(game->map[index]);
		if (game->map_nc == 0)
			game->map_nc = len;
		else if (game->map_nc != len)
			ft_error(COL_ERROR, game);
		else
			game->map_nc = len;
		index++;
	}
	if (index == 0)
		ft_error(COL_ERROR, game);
	game->map_w = game->map_nc * game->sprite_w;
}

/**
 * @brief 			This function checks if the map has a valid border
 * 
 * @param game 		A pointer to the main structure of the program
 * @return int 		The return value: 1 if the map has a valid border,
 * 					0 otherwise
 */
int	ft_check_border(t_game *game)
{
	int	i_r;
	int	i_c;

	i_r = 0;
	while (i_r < game->map_nr)
	{
		i_c = 0;
		if (i_r == 0 || i_r == (game->map_nr - 1))
		{
			while (i_c < game->map_nc)
			{
				if (game->map[i_r][i_c] != '1')
					return (0);
				i_c++;
			}
		}
		else
			if (game->map[i_r][0] != '1' || \
				game->map[i_r][game->map_nc - 1] != '1')
				return (0);
		i_r++;
	}
	return (1);
}

/**
 * @brief 			This function checks if the map has the correct number of
 * 					valid characters or not. It must have one and only one 
 * 					player and exit and at least one collectable object. If
 * 					not, it throws an error
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_check_chars(t_game *game)
{
	if (game->n_p != 1)
		ft_error(PLY_ERROR, game);
	else if (game->n_c < 1)
		ft_error(CLL_ERROR, game);
	else if (game->n_e != 1)
		ft_error(EXT_ERROR, game);
}

/**
 * @brief 			This function checks the character of one given map's
 * 					position
 * 
 * @param game 		A pointer to the main structure of the program
 * @param row 		The row of the map
 * @param col 		The column of the map
 * @param inv 		A pointer to an integer that indicates if there is a not
 * 					valid character in the map (or if there is an invalid
 * 					character in the map), its value is 1 if there is an
 * 					invalid character and 0 otherwise
 */
void	ft_check_map_chars(t_game *game, int row, int col, int *inv)
{
	if (game->map[row][col] == 'P')
		game->n_p++;
	else if (game->map[row][col] == 'C')
		game->n_c++;
	else if (game->map[row][col] == 'E')
		game->n_e++;
	else if (game->map[row][col] == 'B')
		game->n_en++;
	else if (game->map[row][col] != '0' && game->map[row][col] != '1')
		*inv = 1;
}
