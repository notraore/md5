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
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include "libft/libft.h"

# define MD5_H
# define CH(e, f, g) (((e) & (f)) ^ (~(e) & (g)))
# define MA(a, b, c) (((a) & (b)) ^ ((a) & (c)) ^ ((b) & (c)))
# define ABS(x) ((x < 0) ? (-x) : (x))
# define ROTL(x, c)	(((x) << (c)) | ((x) >> (32 - (c))))
# define ROTR(x, n)	(((x) >> (n)) | ((x) << (32 - (n))))
# define SIGMA0(a) (ROTR(a, 2) ^ ROTR(a, 13) ^ ROTR(a, 22))
# define SIGMA1(e) (ROTR(e, 6) ^ ROTR(e, 11) ^ ROTR(e, 25))
# define SIG0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3))
# define SIG1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10))

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
void		print_hash(unsigned char *hash, int count, t_mode *mode);
void		printstr_sha256(t_sha256 *s, unsigned const char *ms, t_mode *m);
void		printstr_md5(t_md5 *md5, unsigned const char *msg, t_mode *mode);
void		update(t_sha256 *sha);
void		digest_sha256(t_sha256 *s, unsigned char const *m, size_t len);
void		digest_sha256_suite(t_sha256 *sha, unsigned char *hash);
void		digest(t_md5 *md5, unsigned char const *msg, size_t len);
void		rev_endian32(uint32_t *src, const size_t len);
void		rev_endian64(uint64_t *src, const size_t len);
void		init_sha256(t_sha256 *sha);
void		print_help(void);
void		init_md5(t_md5 *md5);
void		check_hashmethod(char *args, t_mode *mode);
void		check_argc(int argc, t_mode *mode);
void		print_cript(t_md5 *md5, char const *target, t_mode *mode);
void		crypt_filemd5(t_md5 *md5, char const *target, t_mode *mode);
void		sha_print_cript(t_sha256 *sha, char const *target, t_mode *mode);
void		crypt_filesha(t_sha256 *sha, char const *target, t_mode *mode);
void		digest_suite(t_md5 *md5, unsigned char *hash, size_t count);
void		update_md5(t_md5 *md5);

#endif
