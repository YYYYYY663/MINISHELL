/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:48:09 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/14 12:29:01 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "libft.h"
# include "lmap.h"
# include "sys.h"

int	path_dispacher(char path[], char *src, int mode, t_info *info);

int	_resolve_path_absolute(char path[], char *src, int mode, t_info *info);
int	_resolve_path_home(char path[], char *src, int mode, t_info *info);
int	_resolve_path_relative(char path[], char *src, int mode, t_info *info);

#endif