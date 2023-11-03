/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:48:41 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/03 15:58:44 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_txt	*load_txt(char *name)
{
	t_txt	*tmp;
	
	tmp = ft_calloc(1, sizeof(t_txt));
	if (!tmp)
		;
	return tmp;
}