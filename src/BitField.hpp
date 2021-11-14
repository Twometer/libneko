//
// Created by Twometer on 14 Nov 2021.
//

#ifndef LIBNEKO_BITFIELD_HPP
#define LIBNEKO_BITFIELD_HPP

#define SET_BIT(value, bit) (value = (value | (1 << bit)))
#define CLEAR_BIT(value, bit) (value = (value & ~(1 << bit)))
#define IS_BIT_SET(value, bit) ((value & (1 << bit)) != 0)

#endif //LIBNEKO_BITFIELD_HPP
