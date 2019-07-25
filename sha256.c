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

#define CH(e, f, g) (((e) & (f)) ^ (~(e) & (g)))
#define MA(a, b, c) (((a) & (b)) ^ ((a) & (c)) ^ ((b) & (c)))
#define SIGMA0(a) (ROTR(a, 2) ^ ROTR(a, 13) ^ ROTR(a, 22))
#define SIGMA1(e) (ROTR(e, 6) ^ ROTR(e, 11) ^ ROTR(e, 25))
#define SIG0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3))
#define SIG1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10))

static uint32_t const k[64] = {
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
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

void				rev_endian32(uint32_t *src, const size_t len)
{
	unsigned char		*data;
	uint32_t			n;
	size_t				i;

	i = 0;
	while (i < len)
	{
		n = src[i];
		data = (unsigned char *)&src[i++];
		data[0] = ((n >> 24) & 0xff);
		data[1] = ((n >> 16) & 0xff);
		data[2] = ((n >> 8) & 0xff);
		data[3] = (n & 0xff);
	}
}

void				rev_endian64(uint64_t *src, const size_t len)
{
	unsigned char		*data;
	uint64_t			n;
	size_t				i;

	i = 0;
	while (i < len)
	{
		n = src[i];
		data = (unsigned char *)&src[i++];
		data[0] = ((n >> 56) & 0xff);
		data[1] = ((n >> 48) & 0xff);
		data[2] = ((n >> 40) & 0xff);
		data[3] = ((n >> 32) & 0xff);
		data[4] = ((n >> 24) & 0xff);
		data[5] = ((n >> 16) & 0xff);
		data[6] = ((n >> 8) & 0xff);
		data[7] = (n & 0xff);
	}
}

void				init_sha256(t_sha256 *sha)
{
	sha->shastate[0] = 0x6a09e667;
	sha->shastate[1] = 0xbb67ae85;
	sha->shastate[2] = 0x3c6ef372;
	sha->shastate[3] = 0xa54ff53a;
	sha->shastate[4] = 0x510e527f;
	sha->shastate[5] = 0x9b05688c;
	sha->shastate[6] = 0x1f83d9ab;
	sha->shastate[7] = 0x5be0cd19;

	sha->count[0] = 0;
	sha->count[1] = 0;
}

static uint32_t			*padding(t_sha256 *sha)
{
	static uint32_t state[8];
	uint32_t		tmp1;
	uint32_t		tmp2;
	int				i;

	i = 0;
	ft_memcpy(state, sha->shastate, sizeof(state));
	while (i < 64)
	{
		tmp1 = state[7] + SIGMA1(state[4]) + CH(state[4], state[5], state[6])
			+ k[i] + ((uint32_t *)sha->buff)[i];
		tmp2 = SIGMA0(state[0]) + MA(state[0], state[1], state[2]);
		state[7] = state[6];
		state[6] = state[5];
		state[5] = state[4];
		state[4] = state[3] + tmp1;
		state[3] = state[2];
		state[2] = state[1];
		state[1] = state[0];
		state[0] = tmp1 + tmp2;
		i++;
	}
	return (state);
}

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

void			digest_sha256(t_sha256 *sha, unsigned char const *msg, size_t len)
{
	uint32_t		bits;

	while (len)
	{
		bits = sha->count[0] >> 3;
		if (bits + len < 64)
		{
			ft_memcpy(sha->buff + bits, msg, len);
			sha->count[0] += len << 3;
			return ;
		}
		ft_memcpy(sha->buff + bits, msg, 64 - bits);
		sha->count[0] = 0;
		++sha->count[1];
		update(sha);
		msg += 64 - bits;
		len -= 64 - bits;
	}
}

void			digest_sha256_suite(t_sha256 *sha, unsigned char *hash)
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

void			print_hash(unsigned char *hash, int count)
{
	int						g;
	size_t					i;
	const unsigned char		*pc;

	pc = hash;
	i = 0;
	while (i < count)
	{
		g = (*(pc + i) >> 4) & 0xf;
		g += g >= 10 ? 'a' - 10 : '0';
		ft_putchar(g);
		g = *(pc + i) & 0xf;
		g += g >= 10 ? 'a' - 10 : '0';
		ft_putchar(g);
		i++;
	}
	ft_putchar('\n');
}

void			printstr_sha256(t_sha256 *sha, unsigned const char *msg)
{
	unsigned char hash[32];

	init_sha256(sha);
	digest_sha256(sha, msg, ft_strlen((char *)msg));
	digest_sha256_suite(sha, hash);
	print_hash(hash, 32);
}

void			printstr_md5(t_md5 *md5, unsigned const char *msg)
{
	unsigned char hash[32];

	init_md5(md5);
	digest(md5, msg, ft_strlen((char *)msg));
	digest_suite(md5, hash, 16);
	print_hash(hash, 16);
}
