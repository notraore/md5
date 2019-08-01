/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:30:46 by notraore          #+#    #+#             */
/*   Updated: 2019/05/15 15:30:46 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static const uint32_t	k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#define SIGMA0(a) (ROTR(a, 2) ^ ROTR(a, 13) ^ ROTR(a, 22))
#define SIGMA1(e) (ROTR(e, 6) ^ ROTR(e, 11) ^ ROTR(e, 25))
#define SIG0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3))
#define SIG1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10))

void		update(t_sha256 *sha)
{
	uint32_t		*pad_rest;
	uint32_t		*buffer;
	size_t			i;

	i = 16;
	buffer = (uint32_t *)sha->buff;
	rev_endian32(buffer, 16);
	while (i < 64)
	{
		buffer[i] = buffer[i - 16] + SIG0(buffer[i - 15]) + buffer[i - 7]
		+ SIG1(buffer[i - 2]);
		i++;
	}
	pad_rest = padding(sha);
	sha->shastate[0] += pad_rest[0];
	sha->shastate[1] += pad_rest[1];
	sha->shastate[2] += pad_rest[2];
	sha->shastate[3] += pad_rest[3];
	sha->shastate[4] += pad_rest[4];
	sha->shastate[5] += pad_rest[5];
	sha->shastate[6] += pad_rest[6];
	sha->shastate[7] += pad_rest[7];
	ft_memset(sha->buff, 0, 64);
}

void		digest_sha256(t_sha256 *s, unsigned char const *msg, size_t len)
{
	uint32_t		bits;

	while (len)
	{
		bits = s->count[0] >> 3;
		if (bits + len < 64)
		{
			ft_memcpy(s->buff + bits, msg, len);
			s->count[0] += len << 3;
			return ;
		}
		ft_memcpy(s->buff + bits, msg, 64 - bits);
		s->count[0] = 0;
		++s->count[1];
		update(s);
		msg += 64 - bits;
		len -= 64 - bits;
	}
}

void		digest_sha256_suite(t_sha256 *sha, unsigned char *hash)
{
	uint32_t		bits;
	uint64_t		size;
	size_t			i;

	i = 0;
	bits = sha->count[0] >> 3;
	sha->buff[bits] = 0x80;
	if (bits + sizeof(uint32_t) > 64)
		update(sha);
	size = ((size_t)sha->count[1] << 9) + sha->count[0];
	rev_endian64(&size, 1);
	ft_memcpy(sha->buff + (64 - sizeof(uint64_t)), &size, sizeof(uint64_t));
	update(sha);
	while (i < 32)
	{
		hash[i] = ((unsigned char *)sha->shastate)[i];
		++i;
	}
	rev_endian32((uint32_t *)hash, 8);
}
