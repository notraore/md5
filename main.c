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
	ft_putendl("-s -> print the sum of the output.");
}

void			check_argv(char *line, t_mode *mode)
{
	if (line[0] == '-' && line[1] == 'p' && !line[2])
		mode->p = true;
	if (line[0] == '-' && line[1] == 'q' && !line[2])
		mode->q = true;
	if (line[0] == '-' && line[1] == 'r' && !line[2])
		mode->r = true;
	if (line[0] == '-' && line[1] == 's' && !line[2])
		mode->s = true;
}

void			check_argc(int argc)
{
	if (argc < 1)
	{
		print_help();
		return ;
	}
}

void			crypt_file(t_sha256 *sha, char const *target)
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
	while ((bits = read(fd, buffer, 4096)) > 0)
	{
		// if (fd == STDIN_FILENO && mode->p == true && mode->r == false)
		// 	write(STDOUT_FILENO, buffer, bits);
		if (fd == STDIN_FILENO)
			write(STDOUT_FILENO, buffer, bits);
		for (int i = 0; i< 7; i++)
			ft_putchar(buffer[i]);
		printf("GO LINE \"%d\" in file \"%s\"\n", __LINE__, __FILE__);
		digest_sha256(sha, buffer, bits);
	}
	if (fd)
		close(fd);
	digest_sha256_suite(sha, hash);
	print_hash(hash);
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
	// t_mdf		target;
	t_sha256	sha;
	t_mode		mode;
	// unsigned	*ret;
	// char		*msg;

	ft_bzero(&sha, sizeof(t_sha256));
	check_argc(argc);
	int i;

	i = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			check_argv(argv[i], &mode);
		i++;
	}
	// printf("mode.r = %d\n", mode.r);
	// if (argc == 1)
		crypt_file(&sha, NULL);
	// if (mode.r == true)
	// 	reverse_print(&sha, &mode, argv[argc - 1]);
	// else if (mode.r == false)
	// 	normal_print(&sha, &mode, argv[argc - 1]);

	// 	// printf("argc = %d\n", argc);
	// else
		// crypt_file(&sha, argv[argc - 1]);
	// ft_bzero(&target, sizeof(t_mdf));
	// close(fd);
	// init_mdf(&target);

	// msg = ft_strjoin(line, "\n");
	// ret = mdf(msg, strlen(msg), &target);
	// while (target.i < 4)
	// {
	// 	wbunion.w = ret[target.i];
	// 	while (target.j < 4)
	// 	{
	// 		printf("%02x", wbunion.b[target.j]);
	// 		target.j++;
	// 	}
	// 	target.i++;
	// 	target.j = 0;
	// }
	// printf("\n");

	// if (argc == 2)
		// printstr_sha256(&sha, argv[1]);
	return (0);
}
