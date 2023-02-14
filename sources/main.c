/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2023/02/14 19:32:43 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

t_traceroute g_traceroute = {
	.running = true,
	.stats = {.min = __FLT_MAX__, .max = 0}
};

int main(int argc, char **argv)
{
	// int				socket;
	// int				result;
	t_options		options;
	// struct addrinfo	*address;

	options = get_options(argc, argv);
	// address = resolve_service(options.destination, options.family);
	// socket = create_icmp_socket(options, address);
	// if (socket == -1) {
	// 	cleanup(-1, address);
	// 	fatal(EXIT_FAILURE, strerror(errno));
	// }
	// set_signals_handlers();
	// set_alarm(options);
	// result = traceroute(options, address, socket);
	// cleanup(socket, address);
	// if (result == ERR_UNDEFINED)
	// 	fatal(EXIT_FAILURE, strerror(errno));
	return (EXIT_SUCCESS);
}
