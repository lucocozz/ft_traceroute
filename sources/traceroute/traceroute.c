/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:03:23 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/15 15:43:09 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	traceroute(t_cli cli, struct addrinfo *address, int socket)
{
	char		*ip;
	t_querie	querie = {0};
	Packet		*packet;

	packet = packet_create(cli.prototype, cli.packetlen);
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
		update_packet_header(packet, cli, hop);
		printf("%d:", hop);
		set_ttl(socket, GET_LEVEL(cli.family), hop);
		for (short i = 0; i < cli.queries; ++i) {
			querie = traceroute_queries(socket, packet, address);
			//TODO: SIGINT don't quit clearly
			if (querie.error == ERR_UNDEFINED || querie.error == INTERRUPTED) {
				packet_destroy(packet);
				free(ip);
				return (querie.error);
			}
			//TODO: don't display address as new hop if is equal to previous
			print_querie(querie);
		}
		printf("\n");
	}
	free(ip);
	packet_destroy(packet);
	return (0);
}
