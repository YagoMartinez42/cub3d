/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_matrix_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:25:53 by samartin          #+#    #+#             */
/*   Updated: 2025/03/24 13:40:48 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

/**
 * Frees the six header strings used to build the map, returns 255 to be used
 *  as an error code if called after detecting a parsing error.
 * 
 * @param header The header pointer itself should be in the heap and is not to
 * be freed.
 * 
 * @return 255 in any case, it will be ignored if the map parsing was complete.
 */
uint8_t	c3d_clear_header(char **header)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (header[i])
		{
			free(header[i]);
			header[i] = NULL;
		}
		i++;
	}
	return (255);
}

/**
 * Frees memory allocated for any 2D array of strings.
 * 
 * @param matrix A double pointer to char, a 2D array of characters. Each
 *  element of the first dimension is a dynamically allocated string.
 * @param size The vertical number of elements in the matrix.
 *  
 * @return an unsigned 8-bit integer value of 0.
 */
uint8_t	c3d_free2d_size(char **matrix, int size)
{
	int	i;

	if (!matrix)
		return (1);
	i = 0;
	while (i < size)
	{
		if (matrix[i])
			free(matrix[i]);
		i++;
	}
	free (matrix);
	return (1);
}

/**
 * Checks if a 2D matrix exists and has exactly 3 rows with non-null values.
 * 
 * @param matrix A null-terminated array of strings.
 * 
 * @return If index 3 and no other is NULL, returns 1 for true, if any element
 *  before index 3 is NULL, or index 3 is not, returns 0 for false.
 */
uint8_t	c3d_matrix_health_3(char **matrix)
{
	int		i;

	if (!matrix)
		return (0);
	i = 0;
	while (i <= 3)
	{
		if (!matrix[i])
		{
			if (i == 3)
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

/**
 * Copies the content of a string from the map and fills with whitespace all
 *  the remaining size until reaching the actual width of the map's matrix.
 * 
 * @param dest The destination string where to copy the map line to.
 * @param src The original map line that can be shorter than the map width.
 * @param full_l The actual full length of a map line.
 * 
 */
void	c3d_cpynfill(char *dest, char *src, size_t full_l)
{
	size_t	pos;

	if (!dest || !src)
		return ;
	pos = 0;
	while (src[pos] != 0 && pos < full_l)
	{
		dest[pos] = src[pos];
		pos++;
	}
	while (pos < full_l)
	{
		dest[pos] = ' ';
		pos++;
	}
	dest[pos] = '\0';
}
