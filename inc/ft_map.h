/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:16:34 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/14 17:54:34 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_MAP_H
#define FT_MAP_H

#include "ft_system.h"

// entityを追加
t_status	map_export(char *ent, t_list *lmap);
t_status	map_export_item(char *key, char *value, t_list *lmap);
// keyを削除
t_status	map_unset(char *key, t_list *lmap);


#endif