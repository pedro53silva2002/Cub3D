/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan < vafernan@student.42porto.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-03 16:20:21 by vafernan          #+#    #+#             */
/*   Updated: 2025-03-03 16:20:21 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

char	**special_split(char *str)
{
	char	*dummy;
	char	**result;
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	dummy = ft_strsdup(ft_strdupn(&str[i]));
	result = ft_split(dummy, ' ');
	return (free(dummy), result);
}
