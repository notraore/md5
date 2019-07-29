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
		ft_putendl("unknown hash type");
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
		if (argc < 3)
			print_help();
}

void			print_cript(t_md5 *md5, char const *target, t_mode *mode)
{
	if (target && !mode->r && !mode->q)
	{
		ft_putstr("MD5 (");
		ft_putstr(target);
		ft_putstr(") = ");
	}
	else if (target && !mode->q)
	{
		ft_putstr(" = (");
		ft_putstr(target);
		ft_putendl(") MD5");
	}
}

void			sha_print_cript(t_sha256 *sha, char const *target, t_mode *mode)
{
	if (target && !mode->r && !mode->q)
	{
		ft_putstr("SHA256 (");
		ft_putstr(target);
		ft_putstr(") = ");
	}
	else if (target && !mode->q)
	{
		ft_putstr(" = (");
		ft_putstr(target);
		ft_putendl(") SHA256");
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
	init_md5(md5);
	if (!mode->r)
		print_cript(md5, target, mode);
	while ((bits = read(fd, buffer, 1)) > 0)
	{
		digest(md5, buffer, bits);
		if (fd == 0 && (mode->q == false && mode->p == true))
			write(1, buffer, bits);
	}
	if (fd)
		close(fd);
	digest_suite(md5, hash, 16);
	print_hash(hash, 16);
	if (mode->r)
		print_cript(md5, target, mode);
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
	if (!mode->r)
		sha_print_cript(sha, target, mode);
	while ((bits = read(fd, buffer, 1)) > 0)
	{
		digest_sha256(sha, buffer, bits);
		if (fd == 0 && (mode->q == false && mode->p == true))
			write(1, buffer, bits);
	}
	if (fd)
		close(fd);
	digest_sha256_suite(sha, hash);
	print_hash(hash, 32);
	if (mode->r)
		sha_print_cript(sha, target, mode);
}

void			check_mode_md5(t_md5 *md5, char **line, char argc, t_mode *mode)
{
	int i;
	int fd;

	i = 0;
	fd = open(line[argc - 1], O_RDONLY);
	if (fd != -1)
	{
		if (argc == 3)
			crypt_filemd5(md5, line[argc - 1], mode);
		else
			mode->file = true;
	}
	while (i < argc)
	{
		if (line[i][0] == '-' && line[i][1] == 'p' && !line[i][2])
			mode->p = true;
		else if (line[i][0] == '-' && line[i][1] == 'q' && !line[i][2])
			mode->q = true;
		else if (line[i][0] == '-' && line[i][1] == 'r' && !line[i][2])
			mode->r = true;
		else if (line[i][0] == '-' && line[i][1] == 's' && !line[i][2])
			mode->s = true;
		i++;
	}
}

void			check_mode_sha(t_sha256 *sha, char **line, char argc, t_mode *mode)
{
	int i;
	int fd;

	i = 0;
	fd = open(line[argc - 1], O_RDONLY);
	if (fd != -1)
	{
		if (argc == 3)
			crypt_filesha(sha, line[argc - 1], mode);
		else
			mode->file = true;
	}
	while (i < argc)
	{
		if (line[i][0] == '-' && line[i][1] == 'p' && !line[i][2])
			mode->p = true;
		else if (line[i][0] == '-' && line[i][1] == 'q' && !line[i][2])
			mode->q = true;
		else if (line[i][0] == '-' && line[i][1] == 'r' && !line[i][2])
			mode->r = true;
		else if (line[i][0] == '-' && line[i][1] == 's' && !line[i][2])
			mode->s = true;
		i++;
	}
}

void			normal_sha(t_sha256 *sha, t_mode *mode, char *argv)
{
	if (mode->q == false && mode->r == false)
	{
		ft_putstr("SHA256 (\"");
		ft_putstr(argv);
		ft_putstr("\") = ");
	}
	printstr_sha256(sha, (unsigned const char *)argv);
	if (mode->q == false && mode->r == true)
	{
		ft_putstr(" = (\"");
		ft_putstr(argv);
		ft_putendl("\") SHA256");
	}
}

void			normal_md5(t_md5 *md5, t_mode *mode, char *argv)
{
	if (mode->q == false && mode->r == false)
	{
		ft_putstr("MD5 (\"");
		ft_putstr(argv);
		ft_putstr("\") = ");
	}
	printstr_md5(md5, (unsigned const char *)argv);
	if (mode->q == false && mode->r == true)
	{
		ft_putstr(" = (\"");
		ft_putstr(argv);
		ft_putendl("\") MD5");
	}
}

void			display_md5(t_md5 *md5, t_mode *mode, int argc, char **argv)
{
	if (mode->pipe)
		crypt_filemd5(md5, NULL, mode);
	// if (mode->file)
	// 	crypt_filemd5(md5, argv[argc - 1], mode);
	// if (mode->file && mode->s)
	// 	normal_md5(md5, mode, argv[argc - 2]);
	// else if (!mode->file && mode->s)
	// 	normal_md5(md5, mode, argv[argc - 1]);
}

void			display_sha(t_sha256 *sha, t_mode *mode, int argc, char **argv)
{
	if (mode->pipe)
		crypt_filesha(sha, NULL, mode);
	// if (mode->file)
	// 	crypt_filesha(sha, argv[argc - 1], mode);
	// if (mode->file && mode->s)
	// 	normal_sha(sha, mode, argv[argc - 2]);
	// else if (!mode->file && mode->s)
	// 	normal_sha(sha, mode, argv[argc - 1]);
}


int				main(int argc, char **argv)
{
	t_sha256	sha;
	t_md5		md5;
	t_mode		mode;

	ft_bzero(&sha, sizeof(t_sha256));
	ft_bzero(&mode, sizeof(t_mode));
	ft_bzero(&md5, sizeof(t_md5));

	if (!isatty(fileno(stdin)))
		mode.pipe = true;
	check_argc(argc, &mode);
	check_hashmethod(argv[1], &mode);
	check_mode_md5(&md5, argv, argc, &mode);
	check_mode_sha(&sha, argv, argc, &mode);
	// if (mode.md5 == true)
		// display_md5(&md5, &mode, argc, argv);
	// if (mode.sha == true)
		display_sha(&sha, &mode, argc, argv);
	return (0);
}
