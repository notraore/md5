/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:36:38 by notraore          #+#    #+#             */
/*   Updated: 2019/05/15 16:35:16 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# define CH(e, f, g) (((e) & (f)) ^ (~(e) & (g)))
# define MA(a, b, c) (((a) & (b)) ^ ((a) & (c)) ^ ((b) & (c)))
# define ABS(x) ((x < 0) ? (-x) : (x))
# define ROTL(x, c)	(((x) << (c)) | ((x) >> (32 - (c))))
# define ROTR(x, n)	(((x) >> (n)) | ((x) << (32 - (n))))
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include "libft/libft.h"

typedef struct s_sha256	t_sha256;
typedef struct s_md5	t_md5;
typedef struct s_mode	t_mode;

struct		s_mode
{
	bool				p;
	bool				q;
	bool				r;
	bool				s;
	bool				md5;
	bool				sha;
	bool				pipe;
	bool				file;
};

struct		s_sha256
{
	uint32_t			shastate[8];
	unsigned			count[2];
	unsigned char		buff[256];
};

struct		s_md5
{
	uint32_t			mdstate[4];
	unsigned			count[2];
	unsigned char		buff[64];
};

void		check_mode_md5(t_md5 *md5, char **line, char argc, t_mode *mode);
void		check_mode_sha(t_sha256 *sha, char **l, char argc, t_mode *mode);
void		normal_sha(t_sha256 *sha, t_mode *mode, char *argv);
void		normal_md5(t_md5 *md5, t_mode *mode, char *argv);
void		display_md5(t_md5 *md5, t_mode *mode, int argc, char **argv);
void		display_sha(t_sha256 *sha, t_mode *mode, int argc, char **argv);

#endif
