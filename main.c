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

void		 print_help(void)
{
	ft_putendl("./ft_ssl [hash mode] [-pqrs] [file or String]");

	ft_putendl("[hash mode] = \"md5\", \"sha256\" or \"sha512\"");

	ft_putendl("-p -> echo STDIN to STDOUT and append the checksum to OUTPUT.");
	ft_putendl("-q -> quiet mode.");
	ft_putendl("-r -> reverse the format of the output.");
	ft_kill("-s -> print the sum of the output.");
}

void			check_mode(char *line, t_mode *mode)
{
	if (line[0] == '-' && line[1] == 'p' && !line[2])
		mode->p = true;
	if (line[0] == '-' && line[1] == 'q' && !line[2])
		mode->q = true;
	if (line[0] == '-' && line[1] == 'r' && !line[2])
		mode->r = true;
	if (line[0] == '-' && line[1] == 's' && !line[2])
	{
		printf("fegnjer\n");
		mode->s = true;
	}
}

void			check_hashmethod(char *args, t_mode *mode)
{
	if (ft_strcmp(args, "md5") == 0)
		mode->md5 = true;
	else if (ft_strcmp(args, "sha256") == 0)
		mode->sha = true;
}

void			check_argc(int argc)
{
	if (argc < 2)
		print_help();
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
	init_md5(md5);
	while ((bits = read(fd, buffer, 1)) > 0)
	{
		digest(md5, buffer, bits);
		if (fd == 0 && (mode->q == false && mode->r == false))
			write(1, buffer, bits);
	}
	if (fd)
		close(fd);
	digest_suite(md5, hash, 16);
	print_hash(hash, 16);
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
	init_sha256(sha);
	while ((bits = read(fd, buffer, 1)) > 0)
	{
		digest_sha256(sha, buffer, bits);
		if (fd == 0 && (mode->q == false && mode->r == false))
			write(1, buffer, bits);
	}
	if (fd)
		close(fd);
	digest_sha256_suite(sha, hash);
	print_hash(hash, 32);
}

void			reverse_print(t_sha256 *sha, t_mode *mode, char *argv)
{
	if (mode->s == true)
	{
		printstr_sha256(sha, (unsigned const char *)argv);
		if (mode->q == false)
		{
			ft_putstr("SHA256 (\"");
			ft_putstr(argv);
			ft_putendl("\")");
		}
	}
}

void			normal_print(t_sha256 *sha, t_mode *mode, char *argv)
{
	if (mode->s == true)
	{
		if (mode->q == false)
		{
			ft_putstr("SHA256 (\"");
			ft_putstr(argv);
			ft_putendl("\")");
		}
		printstr_sha256(sha, (unsigned const char *)argv);
	}
}

int				main(int argc, char **argv)
{
	t_sha256	sha;
	t_md5		md5;
	t_mode		mode;
	int			i;


	i = 0;
	ft_bzero(&sha, sizeof(t_sha256));
	ft_bzero(&mode, sizeof(t_mode));
	ft_bzero(&md5, sizeof(t_md5));

	check_argc(argc);
	while (i < argc)
	{
		check_hashmethod(argv[i], &mode);
		check_mode(argv[i], &mode);
		i++;
	}
	if ((mode.md5 && mode.s) && argc == 3)
		printstr_md5(&md5, (unsigned const char *)argv[argc - 1]);
	else if (mode.md5 && argc == 2)
		crypt_filemd5(&md5, NULL, &mode);
	/* sha to finish now */
	// printstr_sha256(&sha, (unsigned const char *)argv[1]);
	// crypt_filesha(&sha, NULL, &mode);
	return (0);
}
