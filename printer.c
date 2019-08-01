/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:50:49 by notraore          #+#    #+#             */
/*   Updated: 2019/08/01 18:50:49 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void			print_hash(unsigned char *hash, int count, t_mode *mode)
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
	if (!mode->r)
		ft_putchar('\n');
}

void			printstr_sha256(t_sha256 *s, unsigned const char *m, t_mode *m)
{
	unsigned char hash[32];

	init_sha256(s);
	digest_sha256(s, m, ft_strlen((char *)m));
	digest_sha256_suite(s, hash);
	print_hash(hash, 32, m);
}

void			printstr_md5(t_md5 *md5, unsigned const char *msg, t_mode *mode)
{
	unsigned char hash[32];

	init_md5(md5);
	digest(md5, msg, ft_strlen((char *)msg));
	digest_suite(md5, hash, 16);
	print_hash(hash, 16, mode);
}
