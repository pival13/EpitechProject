/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** header
*/

#ifndef HEADER_HPP_
#define HEADER_HPP_

#include "../../../RFC/rfc.hpp"

typedef struct header_s {
    Rtype::Rfc::TcpCode type;
    short size;
}header_t;

typedef struct header_udp_input_s{
    char uuid[Rtype::Size::uuidLength];
    Rtype::Rfc::UdpCode type;
    short size;
}header_udp_input_t;

typedef struct header_udp_output_s{
    Rtype::Rfc::UdpCode type;
    short size;
}header_udp_output_t;

#endif /* !HEADER_HPP_ */
