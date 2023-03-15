/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute_queries.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:48:26 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/14 20:00:00 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

t_querie	traceroute_queries(int socket, Packet *packet, struct addrinfo *address)
{
	t_querie		querie;
	struct timeval	start, end;

	if (gettimeofday(&start, NULL) < 0)
		return ((t_querie){.error = ERR_UNDEFINED});
	if (send_packet(socket, packet, address) == -1)
		return ((t_querie){.error = ERR_SEND});
	querie = recv_packet(socket, address->ai_family);
	if (gettimeofday(&end, NULL) < 0)
		return ((t_querie){.error = ERR_UNDEFINED});
	querie.time = get_elapsed_time(start, end);
	return (querie);
}
