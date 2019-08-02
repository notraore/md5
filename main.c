/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:30:46 by notraore          #+#    #+#             */
/*   Updated: 2019/05/15 15:30:46 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

int				main(int argc, char **argv)
{
	t_md5		md5;
	t_sha256	sha;
	t_mode		mode;

	ft_bzero(&md5, sizeof(t_md5));
	ft_bzero(&mode, sizeof(t_mode));
	ft_bzero(&sha, sizeof(t_sha256));
	if (!isatty(fileno(stdin)))
		mode.pipe = true;
	check_argc(argc, &mode);
	check_hashmethod(argv[1], &mode);
	if (mode.md5 == true)
	{
		init_md5(&md5);
		check_mode_md5(&md5, argv, argc, &mode);
		display_md5(&md5, &mode, argc, argv);
	}
	if (mode.sha == true)
	{
		init_sha256(&sha);
		check_mode_sha(&sha, argv, argc, &mode);
		display_sha(&sha, &mode, argc, argv);
	}
	return (0);
}
