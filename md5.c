/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:30:46 by notraore          #+#    #+#             */
/*   Updated: 2019/05/15 15:30:46 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static uint32_t const	k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

#define S1			7, 12, 17, 22
#define S2			5, 9, 14, 20
#define S3			4, 11, 16, 23
#define S4			6, 10, 15, 21

static uint32_t const	g[64] = {
	S1, S1, S1, S1,
	S2, S2, S2, S2,
	S3, S3, S3, S3,
	S4, S4, S4, S4
};

static int s[64] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
	5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
	0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9 };


void			init_md5(t_md5 *md5)
{
	md5->mdstate[0] = 0x67452301;
	md5->mdstate[1] = 0xefcdab89;
	md5->mdstate[2] = 0x98badcfe;
	md5->mdstate[3] = 0x10325476;
	md5->count[0] = 0;
	md5->count[1] = 0;
}


#define F1(b, c, d)	(((b) & (c)) | (~(b) & (d)))
#define F2(b, c, d)	(((b) & (d)) | ((c) & ~(d)))
#define F3(b, c, d)	((b) ^ (c) ^ (d))
#define F4(b, c, d)	((c) ^ ((b) | ~(d)))


static uint32_t			*padding(t_md5 *md5)
{
	static uint32_t	state[4];
	uint32_t		f;
	int				i;

	i = 0;
	ft_memcpy(state, md5->mdstate, sizeof(state));
	while (i < 64)
	{
		if (i < 16)
			f = F1(state[1], state[2], state[3]);
		else if (i < 32)
			f = F2(state[1], state[2], state[3]);
		else if (i < 48)
			f = F3(state[1], state[2], state[3]);
		else
			f = F4(state[1], state[2], state[3]);
		f += state[0] + k[i] + ((uint32_t *)md5->buff)[s[i]];
		state[0] = state[3];
		state[3] = state[2];
		state[2] = state[1];
		state[1] += ROTL(f, g[i]);
		++i;
	}
	return (state);
}

static void				update_md5(t_md5 *md5)
{
	uint32_t	*chunk_res;

	chunk_res = padding(md5);
	md5->mdstate[0] += chunk_res[0];
	md5->mdstate[1] += chunk_res[1];
	md5->mdstate[2] += chunk_res[2];
	md5->mdstate[3] += chunk_res[3];
	ft_memset(md5->buff, 0, 64);
}

void					digest(t_md5 *md5, unsigned char const *msg, size_t len)
{
	uint32_t	bytes;

	while (len)
	{
		bytes = md5->count[0] >> 3;
		if (bytes + len < 64)
		{
			ft_memcpy(md5->buff + bytes, msg, len);
			md5->count[0] += len << 3;
			return ;
		}
		ft_memcpy(md5->buff + bytes, msg, 64 - bytes);
		md5->count[0] = 0;
		++md5->count[1];
		update_md5(md5);
		msg += 64 - bytes;
		len -= 64 - bytes;
	}
}

void					digest_suite(t_md5 *md5, unsigned char *hash, size_t count)
{
	uint32_t	bytes;
	uint64_t	total_size;
	int			i;

	bytes = md5->count[0] >> 3;
	md5->buff[bytes] = 0x80;
	if (bytes + sizeof(uint64_t) > 64)
		update_md5(md5);
	total_size = ((size_t)md5->count[1] << 9) + md5->count[0];
	ft_memcpy(md5->buff + (64 - sizeof(uint64_t)), &total_size,
		sizeof(uint64_t));
	update_md5(md5);
	i = 0;
	while (i < count)
	{
		hash[i] = ((unsigned char *)md5->mdstate)[i];
		++i;
	}
}

