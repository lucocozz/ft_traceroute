/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_datagram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 00:09:19 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/07 20:32:38 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	send_datagram(int socket, t_datagram datagram, struct addrinfo *address)
{
	struct sockaddr_in	dest;
	struct sockaddr_in	*sockaddr = (struct sockaddr_in *)address->ai_addr;
	int					bytes_sent;

	dest.sin_family = address->ai_family;
	dest.sin_addr = sockaddr->sin_addr;
	bytes_sent = sendto(socket, datagram.raw, datagram.total, 0, (struct sockaddr *)&dest, sizeof(dest));
	return (bytes_sent);
}
