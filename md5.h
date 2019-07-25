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
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include "libft/libft.h"
# define ABS(x) ((x < 0) ? (-x) : (x))
#define ROTL(x, c)	(((x) << (c)) | ((x) >> (32 - (c))))
#define ROTR(x, n)	(((x) >> (n)) | ((x) << (32 - (n))))


typedef struct s_sha256	t_sha256;
typedef struct s_md5	t_md5;
typedef struct s_mode	t_mode;

struct				s_mode
{
	bool			p;
	bool			q;
	bool			r;
	bool			s;
	bool			md5;
	bool			sha;
};

struct s_sha256
{
	uint32_t		shastate[8];
	unsigned		count[2];
	unsigned char	buff[256];
};

struct s_md5
{
	uint32_t		mdstate[4];
	unsigned		count[2];
	unsigned char	buff[64];
};
/****************************** MD5 ******************************/
/*
**digest.c
*/
void				init_md5(t_md5 *md5);
void				digest(t_md5 *md5, unsigned char const *msg, size_t len);
void				digest_suite(t_md5 *md5, unsigned char *hash, size_t count);
void				printstr_md5(t_md5 *md5, unsigned const char *msg);
void				crypt_filesha(t_sha256 *sha, char const *target, t_mode *mode);
/****************************** SHA256 ******************************/
void				rev_endian32(uint32_t *src, const size_t len);
void				rev_endian64(uint64_t *src, const size_t len);
void				init_sha256(t_sha256 *sha);
void				update(t_sha256 *sha);
void				digest_sha256(t_sha256 *sha, unsigned char const *msg, size_t len);
void				digest_sha256_suite(t_sha256 *sha, unsigned char *hash);
void				print_hash(unsigned char *hash, int count);
void				printstr_sha256(t_sha256 *sha, unsigned const char *msg);
void				crypt_filemd5(t_md5 *md5, char const *target, t_mode *mode);
#endif
