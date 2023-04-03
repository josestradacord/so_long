/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:38:14 by joestrad          #+#    #+#             */
/*   Updated: 2023/03/28 12:09:03 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

/**
 * @brief 			This function displays the different errors' messages that
 * 					can be produced during the program's execution
 * 
 * @param error 	The error code to show (associated to a message)
 */
void	ft_error(int error, t_game *game)
{
	if (error == FILE_ERROR)
		ft_putendl_fd("ERROR\nFile can not be opened", 2);
	else if (error == BOR_ERROR)
		ft_putendl_fd("ERROR\nMap is not bordered", 2);
	else if (error == ROW_ERROR)
		ft_putendl_fd("ERROR\nMap has different number of rows", 2);
	else if (error == COL_ERROR)
		ft_putendl_fd("ERROR\nMap has different number of columns", 2);
	else if (error == PLY_ERROR)
		ft_putendl_fd("ERROR\nThere is not only one player in the map", 2);
	else if (error == CLL_ERROR)
		ft_putendl_fd("ERROR\nThere is not any collectable object", 2);
	else if (error == EXT_ERROR)
		ft_putendl_fd("ERROR\nThere is not only one exit in the map", 2);
	else if (error == INV_ERROR)
		ft_putendl_fd("ERROR\nThere is a not valid char in the map", 2);
	else if (error == PTH_ERROR)
		ft_putendl_fd("ERROR\nThere is a not a valid path in the map", 2);
	ft_free(game);
	exit(1);
}

/**
 * @brief 			This function frees the main structure of the program
 * 					just before the program's end
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_free(t_game *game)
{
	int	index;

	free(game->map_name);
	index = 0;
	while (index < game->map_nr)
	{
		free(game->map[index]);
		free(game->map_cp[index]);
		index++;
	}
	if (game->map)
	{
		free(game->map);
		free(game->map_cp);
	}
	free(game);
}
