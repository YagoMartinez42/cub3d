/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarr_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:06:51 by bvelasco          #+#    #+#             */
/*   Updated: 2024/02/26 16:17:01 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	strarr_len(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i])
		i++;
	return (i);
}
