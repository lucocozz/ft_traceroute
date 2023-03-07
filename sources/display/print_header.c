/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:45:07 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/07 20:32:38 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	print_header(t_cli cli, char *ip, t_datagram datagram)
{
	printf("ft_traceroute to %s (%s), %d hops max, %lu byte packets\n", cli.host, ip,
		cli.max_ttl, datagram.size + sizeof(struct iphdr));
}
