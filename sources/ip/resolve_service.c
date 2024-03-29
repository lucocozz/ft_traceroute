/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_service.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:32:30 by lucocozz          #+#    #+#             */
/*   Updated: 2022/12/24 12:32:37 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

struct addrinfo	*resolve_service(t_cli cli)
{
	struct addrinfo	hints = {0};
	struct addrinfo	*result = {0};
	char			msg[256] = {0};

	hints.ai_family = cli.family;
	hints.ai_socktype = cli.socktype;
	hints.ai_protocol = cli.protocol;
	if (getaddrinfo(cli.host, NULL, &hints, &result) < 0) {
		sprintf(msg, "%s: Name or service not known", cli.host);
		fatal(EXIT_FAILURE, msg);
	}
	return (result);
}
