/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:36:21 by notraore          #+#    #+#             */
/*   Updated: 2019/05/15 15:36:22 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void			print_help(void)
{
	ft_putendl("./ft_ssl [hash mode] [-pqrs] [file or String]");
	ft_putendl("[hash mode] = \"md5\", \"sha256\" or \"sha512\"");
	ft_putendl("-p >echo STDIN to STDOUT and append the checksum to OUTPUT.");
	ft_putendl("-q -> quiet mode.");
	ft_putendl("-r -> reverse the format of the output.");
	ft_kill("-s -> print the sum of the output.");
}

void			check_hashmethod(char *args, t_mode *mode)
{
	if (ft_strcmp(args, "md5") == 0)
		mode->md5 = true;
	else if (ft_strcmp(args, "sha256") == 0)
		mode->sha = true;
	else if (ft_strcmp(args, "all") == 0)
	{
		mode->md5 = true;
		mode->sha = true;
	}
	else
	{
		ft_putendl("[Unknown hash type]");
		print_help();
	}
}

void			check_argc(int argc, t_mode *mode)
{
	if (mode->pipe == true)
	{
		if (argc < 2)
			print_help();
	}
	else
	{
		if (argc < 3)
			print_help();
	}
}
