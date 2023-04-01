/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 00:09:19 by lucocozz          #+#    #+#             */
/*   Updated: 2023/04/01 19:11:18 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	send_packet(int socket, Packet *packet, struct addrinfo *address)
{
	struct sockaddr_in	dest = {0};
	struct sockaddr_in	*sockaddr = (struct sockaddr_in *)address->ai_addr;
	int					bytes_sent;

	dest.sin_family = address->ai_family;
	dest.sin_addr = sockaddr->sin_addr;
	dest.sin_port = get_port(packet);
	bytes_sent = sendto(socket, packet->raw, packet->size.total, MSG_NOSIGNAL, (struct sockaddr *)&dest, sizeof(dest));
	return (bytes_sent);
}
