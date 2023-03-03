/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:40:56 by user42            #+#    #+#             */
/*   Updated: 2023/02/26 20:13:39 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	fatal(short status, const char *msg)
{
	if (msg != NULL)
		dprintf(STDERR_FILENO, "%s\n", msg);
	exit(status);
}

void	warn(const char *msg)
{
	if (msg != NULL)
		dprintf(STDERR_FILENO, "WARNING: %s\n", msg);
}
