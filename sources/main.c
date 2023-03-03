/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2023/03/03 20:32:04 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int main(int argc, char **argv)
{
	int				socket;
	// int				result;
	t_options		options;
	struct addrinfo	*address;

	options = get_options(argc, argv);
	address = resolve_service(options);
	socket = create_socket(address);
	if (socket == -1) {
		cleanup(-1, address);
		fatal(EXIT_FAILURE, strerror(errno));
	}
	// result = traceroute(options, address, socket);
	// cleanup(socket, address);
	// if (result == ERR_UNDEFINED)
	// 	fatal(EXIT_FAILURE, strerror(errno));
	return (EXIT_SUCCESS);
}
