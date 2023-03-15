/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cli.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:30:35 by user42            #+#    #+#             */
/*   Updated: 2023/03/03 20:37:57 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

char	*__get_argument(char *flag)
{
	uint	i = 0;

	while (flag[i] != '\0' && flag[i] != '=')
		++i;
	if (flag[i] == '\0')
		return (NULL);
	return (&flag[i + 1]);
}

bool	__exec_handler(const t_options *options, t_cli *cli, char *flag, char *argument, int argc)
{
	uint	i = 0;

	for (i = 0; options[i].flag != NULL; ++i)
	{
		if (ft_start_with(options[i].flag, flag) == true)
		{
			if (options[i].has_argument == true && argument == NULL)
				missing_arg_error(options[i].flag, argc, options[i].help);
			if (options[i].handler(cli, argument) == -1)
				arg_error(options[i].flag, argument, argc);
			break ;
		}
	}
	if (options[i].flag == NULL)
		bad_option(options[i].flag, argc);
	return (options[i].has_argument);
}

static int	__double_dash_flag(t_cli *cli, char *flag, int argc)
{
	char						*argument = __get_argument(flag);
	static const t_options	options[] = {
		{.flag = "help", .handler = &handle_flag_help, .has_argument = false},
		{.flag = "icmp", .handler = &handle_flag_icmp, .has_argument = false},
		{.flag = "tcp", .handler = &handle_flag_tcp, .has_argument = false},
		{.flag = "udp", .handler = &handle_flag_udp, .has_argument = false},
		{.flag = "first", .handler = &handle_flag_first, .has_argument = true, .help = "--first=first_ttl"},
		{.flag = "max-hops", .handler = &handle_flag_max, .has_argument = true, .help = "--max-hops=max_ttl"},
		{.flag = "port", .handler = &handle_flag_port, .has_argument = true, .help = "--port=port"},
		{.flag = "queries", .handler = &handle_flag_queries, .has_argument = true, .help = "--queries=nqueries"},
		{NULL, false, NULL, NULL}
	};
	
	return (__exec_handler(options, cli, flag, argument, argc));
}

static int	__dash_flag(t_cli *cli, char *flag, char *argument, int argc)
{
	static const t_options	options[] = {
		{.flag = "4", .handler = &handle_flag_4, .has_argument = false},
		{.flag = "6", .handler = &handle_flag_6, .has_argument = false},
		{.flag = "I", .handler = &handle_flag_icmp, .has_argument = false},
		{.flag = "T", .handler = &handle_flag_tcp, .has_argument = false},
		{.flag = "U", .handler = &handle_flag_udp, .has_argument = false},
		{.flag = "f", .handler = &handle_flag_first, .has_argument = true, .help = "-f first_ttl"},
		{.flag = "m", .handler = &handle_flag_max, .has_argument = true, .help = "-m max_ttl"},
		{.flag = "p", .handler = &handle_flag_port, .has_argument = true, .help = "-p port"},
		{.flag = "q", .handler = &handle_flag_queries, .has_argument = true, .help = "-q queries"},
		{NULL, false, NULL, NULL}
	};

	return (__exec_handler(options, cli, flag, argument, argc));
}

static t_cli	__init_cli(void)
{
	t_cli	cli;

	cli.first_ttl = DFT_FIRST_TTL;
	cli.host = DFT_HOST;
	cli.interval = DFT_INTERVAL;
	cli.family = DFT_FAMILY;
	cli.max_ttl = DFT_MAX_TTL;
	cli.queries = DFT_QUERIES;
	cli.port = DFT_PORT;
	cli.socktype = DFT_SOCKTYPE;
	cli.prototype = DFT_PROTOTYPE;
	cli.packetlen = DFT_PACKETLEN;
	return (cli);
}

void	__handle_argument(t_cli *cli, char *arg, int i)
{
	int	error;

	if (cli->host != NULL && cli->packetlen != DFT_PACKETLEN)
		extra_arg_error(arg, i);
	if (cli->host == NULL)
		cli->host = arg;
	else {
		error = handle_packetlen(cli, arg);
		if (error == -1)
			dprintf(STDERR_FILENO, "Cannot handle \"packetlen\" cmdline arg `%s' on position %d (argc %d)\n", arg, i, i);
		else if (error == -2)
			dprintf(STDERR_FILENO, "Bad option `%s' (argc %d)\n", arg, i);
		if (error < 0)
			exit(EXIT_ERROR);
	}
}

int	__handle_flag(t_cli *cli, char **argv, int argc, int i)
{
	char	*flag = &argv[i][1];

	while (*flag != '\0')
	{
		if (*flag == '-')
			i += __double_dash_flag(cli, flag, i);
		if (*(flag + 1) != '\0') {
			__dash_flag(cli, flag, (flag + 1), i);
			break ;
		}
		else if (i < argc - 1)
			i += __dash_flag(cli, flag, argv[i + 1], i);
		else
			__dash_flag(cli, flag, NULL, i);
		++flag;
	}
	return (i);
}

t_cli	parse_cli(int argc, char **argv)
{
	t_cli	cli = __init_cli();

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0')
			i = __handle_flag(&cli, argv, argc, i);
		else
			__handle_argument(&cli, argv[i], i);
	}
	return (cli);
}
