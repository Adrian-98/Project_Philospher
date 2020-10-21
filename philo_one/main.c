/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:26:47 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/10/21 20:32:11 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int			ft_error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}


int			main(int argc, char **agv)
{
	if (argc < 5 || argc > 6)
		return(ft_error("ERROR :Bad arguments \n"));
	
	return (0);
}