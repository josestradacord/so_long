/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:31:44 by joestrad          #+#    #+#             */
/*   Updated: 2023/03/27 17:29:34 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * @brief 			This function fills the map from the player's position
 * 
 * @param game 		A pointer to the main structure of the program
 * @param p_r 		A pointer to the row where the player is
 * @param p_c 		A pointer to the column where the player is
 */
void	ft_fill(t_game *game, int p_r, int p_c)
{
	if (p_r < 0 || p_r >= game->map_nr || p_c < 0 || p_c >= game->map_nc || \
		game->map_cp[p_r][p_c] == '1' || game->map_cp[p_r][p_c] == 'F')
		return ;
	if (game->map_cp[p_r][p_c] == 'C' || game->map_cp[p_r][p_c] == 'E')
		game->map_cp[p_r][p_c] = '0';
	game->map_cp[p_r][p_c] = 'F';
	ft_fill(game, p_r - 1, p_c);
	ft_fill(game, p_r + 1, p_c);
	ft_fill(game, p_r, p_c - 1);
	ft_fill(game, p_r, p_c + 1);
}

/**
 * @brief 			This function calls the ft_fill function to fill the map
 * 					from the player's position and it is used to check if there
 * 					is a valid path in the map
 * 
 * @param game 		A pointer to the main structure of the program
 * @param p_r 		A pointer to the row where the player is
 * @param p_c 		A pointer to the column where the player is
 */
void	ft_flood_fill(t_game *game, int p_r, int p_c)
{
	ft_fill(game, p_r, p_c);
}

/**
 * @brief 			This function locates the player's position in the map,
 * 					that is the row and the column where the player is
 * 
 * @param game 		A pointer to the main structure of the program
 * @param p_r 		A pointer to the row where the player is
 * @param p_c 		A pointer to the column where the player is
 */
void	ft_locate_player(t_game *game, int *p_r, int *p_c)
{
	while (*p_r < game->map_nr)
	{
		*p_c = 0;
		while (*p_c < game->map_nc)
		{
			if (game->map_cp[*p_r][*p_c] == 'P')
			{
				game->pos_ply_x = *p_r;
				game->pos_ply_y = *p_c;
				break ;
			}
			(*p_c)++;
		}
		if (game->map_cp[*p_r][*p_c] == 'P')
		{
			game->pos_ply_x = *p_r;
			game->pos_ply_y = *p_c;
			break ;
		}
		(*p_r)++;
	}
}

/**
 * @brief 			This function checks if there is a valid path (without
 * 					crossing walls) in the map, so the player can reach all
 * 					the collectable objects and the exit. If there is not that
 * 					path it throws an error's message
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_check_path(t_game *game)
{
	int	p_r;
	int	p_c;
	int	i_r;
	int	i_c;

	p_r = 0;
	p_c = 0;
	ft_locate_player(game, &p_r, &p_c);
	ft_flood_fill(game, p_r, p_c);
	i_r = 0;
	while (i_r < game->map_nr)
	{
		i_c = 0;
		while (i_c < game->map_nc)
		{
			if (game->map_cp[i_r][i_c] == 'C' || game->map_cp[i_r][i_c] == 'E')
				ft_error(PTH_ERROR, game);
			i_c++;
		}
		i_r++;
	}
}
