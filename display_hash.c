/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:38:49 by notraore          #+#    #+#             */
/*   Updated: 2019/08/01 18:38:50 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void			normal_sha(t_sha256 *sha, t_mode *mode, char *argv)
{
	if (!mode->q)
		ft_putstr("SHA256 ");
	if (mode->q == false && mode->r == false)
	{
		ft_putstr("(\"");
		ft_putstr(argv);
		ft_putstr("\") = ");
	}
	printstr_sha256(sha, (unsigned const char *)argv, mode);
	if (mode->q == false && mode->r == true)
	{
		ft_putstr(" = (\"");
		ft_putstr(argv);
		ft_putendl("\")");
	}
}

void			normal_md5(t_md5 *md5, t_mode *mode, char *argv)
{
	if (!mode->q)
		ft_putstr("MD5 ");
	if (mode->q == false && mode->r == false)
	{
		ft_putstr("(\"");
		ft_putstr(argv);
		ft_putstr("\") = ");
	}
	printstr_md5(md5, (unsigned const char *)argv, mode);
	if (mode->q == false && mode->r == true)
	{
		ft_putstr(" = (\"");
		ft_putstr(argv);
		ft_putendl("\")");
	}
}

void			display_md5(t_md5 *md5, t_mode *mode, int argc, char **argv)
{
	if (mode->pipe)
	{
		crypt_filemd5(md5, NULL, mode);
		if (mode->r)
			ft_putchar('\n');
	}
	if (mode->file)
	{
		crypt_filemd5(md5, argv[argc - 1], mode);
		if (!mode->pipe)
			ft_putchar('\n');
	}
	if (mode->file && mode->s)
	{
		normal_md5(md5, mode, argv[argc - 2]);
		if (mode->r)
			ft_putchar('\n');
	}
	else if (!mode->file && mode->s)
	{
		normal_md5(md5, mode, argv[argc - 1]);
		ft_putchar('\n');
	}
	if (mode->r)
		ft_putchar('\n');
}

void			display_sha(t_sha256 *sha, t_mode *mode, int argc, char **argv)
{
	if (mode->pipe)
	{
		crypt_filesha(sha, NULL, mode);
		if (mode->r)
			ft_putchar('\n');
	}
	if (mode->file)
	{
		crypt_filesha(sha, argv[argc - 1], mode);
		if (!mode->pipe && mode->r)
			ft_putchar('\n');
	}
	if (mode->file && mode->s)
	{
		normal_sha(sha, mode, argv[argc - 2]);
		if (mode->r)
			ft_putchar('\n');
	}
	else if (!mode->file && mode->s)
	{
		normal_sha(sha, mode, argv[argc - 1]);
		ft_putchar('\n');
	}
	if (mode->r)
		ft_putchar('\n');
}
