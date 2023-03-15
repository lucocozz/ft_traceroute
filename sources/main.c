/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2023/03/09 17:11:46 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int main(int argc, char **argv)
{
	int				socket;
	int				result;
	t_cli			cli;
	struct addrinfo	*address;

	cli = get_cli(argc, argv);
	address = resolve_service(cli);
	socket = create_socket(address);
	if (socket == -1) {
		freeaddrinfo(address);
		fatal(EXIT_FAILURE, strerror(errno));
	}
	set_signals_handlers();
	result = traceroute(cli, address, socket);
	cleanup(socket, address);
	if (result == ERR_UNDEFINED)
		fatal(EXIT_FAILURE, strerror(errno));
	return (EXIT_SUCCESS);
}
