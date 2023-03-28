/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2023/03/28 18:20:02 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int main(int argc, char **argv)
{
	t_sockets		sockets;
	int				result;
	t_cli			cli;
	struct addrinfo	*address;

	cli = get_cli(argc, argv);
	address = resolve_service(cli);
	if (create_socket(address, &sockets) == -1) {
		freeaddrinfo(address);
		fatal(EXIT_FAILURE, strerror(errno));
	}
	result = traceroute(cli, address, sockets);
	cleanup(sockets, address);
	if (result == ERR_UNDEFINED)
		fatal(EXIT_FAILURE, strerror(errno));
	return (EXIT_SUCCESS);
}
