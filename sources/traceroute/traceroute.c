/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:03:23 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/07 20:39:33 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	traceroute(t_cli cli, struct addrinfo *address, int socket)
{
	char		*ip;
	t_querie	querie;
	t_datagram	datagram;

	//TODO: can use TCP and UDP protocol
	datagram = create_icmp_datagram(cli.packetlen, ICMP_ECHO, 0);
	if (datagram.raw == NULL)
		return (ERR_UNDEFINED);
	datagram.header->checksum = checksum(datagram.raw, datagram.total);
	ip = get_ip_address(address);
	if (ip == NULL)
		return (ERR_UNDEFINED);
	print_header(cli, ip, datagram);
	for (short hop = 1; ft_strcmp(querie.address, ip) != 0 && hop <= cli.max_ttl; ++hop)
	{
		printf("%d:", hop);
		set_ttl(socket, GET_LEVEL(cli.family), hop);
		for (short i = 0; i < cli.queries; ++i) {
			querie = traceroute_queries(socket, datagram, address);
			//TODO: SIGINT don't quit clearly
			if (querie.error == ERR_UNDEFINED || querie.error == INTERRUPTED) {
				delete_icmp_datagram(&datagram);
				free(ip);
				return (querie.error);
			}
			//TODO: don't display address as new hop if is equal to previous
			print_querie(querie);
		}
		printf("\n");
	}
	free(ip);
	delete_icmp_datagram(&datagram);
	return (0);
}
