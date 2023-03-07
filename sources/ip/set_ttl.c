/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ttl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:36:18 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/07 19:42:03 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	set_ttl(int socket, int level, short ttl)
{
	if (setsockopt(socket, level, IP_TTL, &ttl, sizeof(ttl)) < 0)
		return (ERR_UNDEFINED);
	return (NOERROR);
}
