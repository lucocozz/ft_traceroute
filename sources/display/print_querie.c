/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_queries.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:47:07 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/07 09:42:24 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	print_querie(t_querie querie, t_cli cli)
{
	static ushort	probe = 1;
	static char		last_addr[MAX_ADDR_LEN] = {0};

	if (querie.status == ERR_TIMEOUT)
		printf(" *");
	else if (querie.status == ERR_SEND)
		printf(" %s", strerror(errno));
	else if (ft_strcmp(last_addr, querie.address) == 0 && probe > 1)
		printf(" %.3fms", querie.time);
	else {
		printf(" %s (%s) %.3fms", querie.ptr_record, querie.address, querie.time);
		ft_strcpy(last_addr, querie.address);
	}
	probe = (probe == cli.queries ? 1 : probe + 1);
}
