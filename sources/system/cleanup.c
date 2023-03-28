/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:06:25 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/16 18:07:11 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	cleanup(t_sockets sockets, struct addrinfo *address)
{
	if (sockets.recv != -1)
		close(sockets.recv);
	if (sockets.send != -1)
		close(sockets.send);
	if (address != NULL)
		freeaddrinfo(address);
}
