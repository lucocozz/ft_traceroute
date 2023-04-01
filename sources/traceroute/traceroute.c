/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:03:23 by lucocozz          #+#    #+#             */
/*   Updated: 2023/04/01 15:36:33 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	traceroute(t_cli cli, struct addrinfo *address, t_sockets sockets)
{
	char		*ip;
	t_querie	querie = {0};
	Packet		*packet;

	packet = packet_create(cli.protocol, cli.packetlen);
	if (packet == NULL)
		return (ERR_UNDEFINED);
	set_packet_header(packet, cli);
	packet_checksum(packet);
	ip = get_ip_address(address);
	if (ip == NULL)
		return (ERR_UNDEFINED);

	print_header(cli, ip, packet);
	for (short hop = 1; ft_strcmp(querie.address, ip) != 0 && hop <= cli.max_ttl; ++hop)
	{
		update_packet_header(packet, cli, sockets.send, hop);
		printf("%d:", hop);
		for (short i = 0; i < cli.queries; ++i)
		{
			querie = traceroute_queries(sockets, packet, address);
			if (querie.error == ERR_UNDEFINED)
				break ;
			print_querie(querie, cli);
		}
		printf("\n");
	}

	free(ip);
	packet_destroy(packet);
	return (querie.error);
}
