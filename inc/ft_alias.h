/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:30:56 by ymizukam          #+#    #+#             */
/*   Updated: 2025/02/12 18:31:00 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ALIAS_H
# define FT_ALIAS_H

# include "ft_system.h"
# include <fcntl.h>
# define RCFILE "~/.minishellrc"

t_status	alias_update(const char *file, t_info *info);
t_list		*parse_alias_file(int fd);

#endif