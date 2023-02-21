/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:30:35 by user42            #+#    #+#             */
/*   Updated: 2023/02/21 18:33:31 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

char	*__get_argument(const char *flag)
{
	uint	i = 0;

	while (flag[i] != '\0' && flag[i] != '=')
		++i;
	if (flag[i] == '\0')
		return (NULL);
	return (&flag[i + 1]);
}

static int	__check_double_dash_flag(t_options *data, char flag)
{
	uint						i = 0;
	char						*argument = __get_argument(flag);
	static const t_option_table	options[] = {
		{.flag = "help", .handler = &handle_flag_help, .has_argument = false},
		{.flag = "icmp", .handler = &handle_flag_icmp, .has_argument = false},
		{.flag = "tcp", .handler = &handle_flag_tcp, .has_argument = false},
		{.flag = "udp", .handler = &handle_flag_udp, .has_argument = false},
		{.flag = "first", .handler = &handle_flag_first, .has_argument = true},
		{.flag = "max-hops", .handler = &handle_flag_max, .has_argument = true},
		{.flag = "port", .handler = &handle_flag_port, .has_argument = true},
		{.flag = "queries", .handler = &handle_flag_queries, .has_argument = true},
		{NULL}
	};

	for (i = 0; options[i].flag != 0; ++i)
	{
		if (ft_start_with(options[i].flag, flag) == true)
		{
			if (options[i].has_argument == true && argument == NULL)
			{
				printf("%s'%c'\n\n", MSG_REQUIRED_ARG, flag);
				handle_flag_help(NULL, NULL);
			}
			options[i].handler(data, options[i].has_argument == true ? argument : NULL);
			break ;
		}
	}
	if (options[i].flag == NULL) {
		printf("%s'%c'\n\n", MSG_INVALID_OPT, flag);
		handle_flag_help(NULL, NULL);
	}
	return (options[i].has_argument);
}

static int	__check_dash_flag(t_options *data, char flag, char *argument)
{
	uint						i = 0;
	static const t_option_table	options[] = {
		{.flag = "4", .handler = &handle_flag_4, .has_argument = false},
		{.flag = "6", .handler = &handle_flag_6, .has_argument = false},
		{.flag = "I", .handler = &handle_flag_icmp, .has_argument = false},
		{.flag = "T", .handler = &handle_flag_tcp, .has_argument = false},
		{.flag = "U", .handler = &handle_flag_udp, .has_argument = false},
		{.flag = "f", .handler = &handle_flag_first, .has_argument = true},
		{.flag = "m", .handler = &handle_flag_max, .has_argument = true},
		{.flag = "p", .handler = &handle_flag_port, .has_argument = true},
		{.flag = "q", .handler = &handle_flag_queries, .has_argument = true},
		{NULL}
	};

	for (i = 0; options[i].flag != NULL; ++i)
	{
		if (ft_start_with(options[i].flag, flag) == true)
		{
			if (options[i].has_argument == true && argument == NULL)
			{
				printf("%s'%c'\n\n", MSG_REQUIRED_ARG, flag);
				handle_flag_help(NULL, NULL);
			}
			options[i].handler(data, options[i].has_argument == true ? argument : NULL);
			break ;
		}
	}
	if (options[i].flag == NULL) {
		printf("%s'%c'\n\n", MSG_INVALID_OPT, flag);
		handle_flag_help(NULL, NULL);
	}
	return (options[i].has_argument);
}

static t_options	__init_options(void)
{
	t_options	options;

	options.first_ttl = DFT_FIRST_TTL;
	options.host = DFT_HOST;
	options.interval = DFT_INTERVAL;
	options.family = DFT_FAMILY;
	options.max_ttl = DFT_MAX_TTL;
	options.queries = DFT_QUERIES;
	options.port = DFT_PORT;
	options.socktype = DFT_SOCKTYPE;
	options.packetlen = DFT_PACKETLEN;
	return (options);
}

t_options	parse_options(int argc, char **argv)
{
	char		*flag;
	t_options	options = __init_options();

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0')
		{
			flag = &argv[i][1];
			while (*flag != '\0')
			{
				if (*flag == '-')
					__check_double_dash_flag(&options, *flag);
				if (*(flag + 1) != '\0') {
					__check_dash_flag(&options, *flag, (flag + 1));
					break ;
				}
				else if (i < argc - 1)
					i += __check_dash_flag(&options, *flag, argv[i + 1]);
				else
					__check_dash_flag(&options, *flag, NULL);
				++flag;
			}
		}
		else
			options.host = argv[i];
	}
	return (options);
}
