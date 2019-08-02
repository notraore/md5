/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hashmode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:46:29 by notraore          #+#    #+#             */
/*   Updated: 2019/08/01 18:46:30 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void			check_mode_md5(t_md5 *md5, char **line, char argc, t_mode *mode)
{
	int i;
	int fd;

	i = -1;
	fd = open(line[argc - 1], O_RDONLY);
	if (fd != -1)
	{
		if (argc == 3)
			crypt_filemd5(md5, line[argc - 1], mode);
		else
			mode->file = true;
	}
	while (++i < argc)
	{
		if (line[i][0] == '-' && line[i][1] == 'p' && !line[i][2])
			mode->p = true;
		else if (line[i][0] == '-' && line[i][1] == 'q' && !line[i][2])
			mode->q = true;
		else if (line[i][0] == '-' && line[i][1] == 'r' && !line[i][2])
			mode->r = true;
		else if (line[i][0] == '-' && line[i][1] == 's' && !line[i][2])
			mode->s = true;
	}
}

void			check_mode_sha(t_sha256 *sha, char **l, char argc, t_mode *mode)
{
	int i;
	int fd;

	i = -1;
	fd = open(l[argc - 1], O_RDONLY);
	if (fd != -1)
	{
		if (argc == 3)
			crypt_filesha(sha, l[argc - 1], mode);
		else
			mode->file = true;
	}
	while (++i < argc)
	{
		if (l[i][0] == '-' && l[i][1] == 'p' && !l[i][2])
			mode->p = true;
		else if (l[i][0] == '-' && l[i][1] == 'q' && !l[i][2])
			mode->q = true;
		else if (l[i][0] == '-' && l[i][1] == 'r' && !l[i][2])
			mode->r = true;
		else if (l[i][0] == '-' && l[i][1] == 's' && !l[i][2])
			mode->s = true;
	}
}
