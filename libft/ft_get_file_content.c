/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 21:24:12 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/10/24 04:10:31 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_get_file_content(int fd, int size)
{
	char	*content;
	int		r;
	int		step;
	int		i;

	if (!(content = ft_strnew(size)))
		ft_error("can\'t allocate for ft_get_file_content");
	step = size / 2;
	i = 0;
	while (i < MX_READ && (r = read(fd, content + i, step)) > 0)
	{
		i += r;
		if (i + step + 1 >= size)
		{
			content = ft_realloc(content, size, size * 3 / 2, sizeof(char));
			size = size * 3 / 2;
		}
		content[i + 1] = '\0';
	}
	if (i >= MX_READ || r < 0)
	{
		free(content);
		return (NULL);
	}
	return (content);
}
