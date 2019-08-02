/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypt_file_and_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:47:15 by notraore          #+#    #+#             */
/*   Updated: 2019/08/01 18:47:16 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void			print_cript(t_md5 *md5, char const *target, t_mode *mode)
{
	if (target && !mode->r && !mode->q)
	{
		ft_putstr("(");
		ft_putstr(target);
		ft_putstr(") = ");
	}
	else if (target && !mode->q)
	{
		ft_putstr(" = (");
		ft_putstr(target);
		ft_putstr(")");
		if (mode->r)
			ft_putchar('\n');
	}
}

void			crypt_filemd5(t_md5 *md5, char const *target, t_mode *mode)
{
	unsigned char		buffer[4096];
	unsigned char		hash[32];
	int					bits;
	int					fd;

	if (target == NULL)
		fd = 0;
	else if ((fd = open(target, O_RDONLY)) == -1)
		ft_kill("Coulnd't open file.");
	if (!mode->q && !mode->r && !mode->pipe)
		ft_putstr("MD5 ");
	if (!mode->r)
		print_cript(md5, target, mode);
	while ((bits = read(fd, buffer, 1)) > 0)
	{
		digest(md5, buffer, bits);
		if (fd == 0 && (mode->p == true))
			write(1, buffer, bits);
	}
	if (fd)
		close(fd);
	digest_suite(md5, hash, 16);
	print_hash(hash, 16, mode);
	if (mode->r)
		print_cript(md5, target, mode);
}

void			sha_print_cript(t_sha256 *sha, char const *target, t_mode *mode)
{
	if (target && !mode->r && !mode->q)
	{
		ft_putstr("(");
		ft_putstr(target);
		ft_putstr(") = ");
	}
	else if (target && !mode->q)
	{
		ft_putstr(" = (");
		ft_putstr(target);
		ft_putendl(")");
	}
}

void			crypt_filesha(t_sha256 *sha, char const *target, t_mode *mode)
{
	unsigned char		buffer[4096];
	unsigned char		hash[32];
	int					bits;
	int					fd;

	if (target == NULL)
		fd = 0;
	else if ((fd = open(target, O_RDONLY)) == -1)
		ft_kill("Coulnd't open file.");
	if (!mode->q && !mode->r && !mode->pipe)
		ft_putstr("SHA256 ");
	if (!mode->r)
		sha_print_cript(sha, target, mode);
	while ((bits = read(fd, buffer, 1)) > 0)
	{
		digest_sha256(sha, buffer, bits);
		if (fd == 0 && (mode->p == true))
			write(1, buffer, bits);
	}
	if (fd)
		close(fd);
	digest_sha256_suite(sha, hash);
	print_hash(hash, 32, mode);
	if (mode->r)
		sha_print_cript(sha, target, mode);
}
