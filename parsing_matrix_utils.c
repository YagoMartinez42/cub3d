/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_matrix_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:25:53 by samartin          #+#    #+#             */
/*   Updated: 2024/11/20 15:32:09 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

/**
 * Frees memory allocated for a NULL-terminated array of strings.
 * 
 * @param array_of_str A pointer to an array of strings (char* pointers).
 * 
 * @return 1 if the pointer was NULL, 0 if any free worked.
 */
__uint8_t	c3d_free2d(char **array_of_str)
{
	int	i;

	i = 0;
	if (!array_of_str)
		return (1);
	while (array_of_str[i])
	{
		free(array_of_str[i]);
		i++;
	}
	free(array_of_str);
	return (0);
}

/**
 * Frees the six header strings used to build the map, returns 255 to be used
 *  as an error code if called after detecting a parsing error.
 * 
 * @param header The header pointer itself should be in the heap and is not to
 * be freed.
 * 
 * @return 255 in any case, it will be ignored if the map parsing was complete.
 */
__uint8_t	c3d_clear_header(char **header)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (header[i])
			free(header[i]);
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
__uint8_t	c3d_matrix_health_3(char **matrix)
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
