/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:26:59 by mquero            #+#    #+#             */
/*   Updated: 2025/04/09 13:29:54 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define MAX_MEMORY 10240000
# define MOVE_STEP 1.0f
# define ROTATE_STEP 0.17453f
# define LIGHT_VISIBLE 0
# define LIGHT_RADIUS 1
# define METAL_FUZZ 0.01f
# define METAL_BR_RATIO 0.5f
# define GLASS_REF_IDX 1.5f
# define AIR_REF_IDX 0.8667f
# define CHECK_SCALE 0.5f
# define S (float)1e-8
# define PI (float)3.14159265358979323846
# define SHININESS 30
# define MAX_DEPTH 10
# define DEFAULT_WIDTH 1920
# define DEFAULT_HEIGHT 1080
# define MIN_WIDTH 192
# define MIN_HEIGHT 108
# define MAX_WIDTH 3840
# define MAX_HEIGHT 2160
# define TILE_SIZE 16
# define THREADS_AMOUNT 8
# define DTR(degrees) (degrees * PI / 180.0)
# define RANDOM_FLOAT (float)rand() / (float)(RAND_MAX + 1.0)
# define RANDOM_FLOAT_RANGE(min, max) (float)(min + (max - min) * RANDOM_FLOAT)

#endif