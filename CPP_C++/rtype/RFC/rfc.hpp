/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** rfc
*/

#ifndef RFC_HPP_
#define RFC_HPP_

namespace Rtype
{
    /**
     * @brief Contains the R-Type's Rfc.
     */
    namespace Rfc
    {
        /**
         * @brief Contains all tcp rfc code.
         */
        enum TcpCode
        {
            SC_OK = 101,
            SC_ERROR,
            SC_ROOM,
            SC_PLAYER_UUID,
            SC_ROOM_LOCATION,
            CS_CREATE_ROOM = 201,
            CS_JOIN_ROOM,
            CS_GET_ROOM,
            CS_LEAVE_ROOM
        };

        enum UdpCode
        {
            SC_UPDATE = 101,
            SC_ERROR_SIZE,
            SC_ERROR_AUTH,
            SC_ERROR_REQUEST,
            SC_ERROR_UNKNOW,
            CS_ACTION = 201,
        };

        namespace List
        {
            const std::vector<Rtype::Rfc::TcpCode> CSTcpList{TcpCode::CS_CREATE_ROOM,
                    TcpCode::CS_JOIN_ROOM, TcpCode::CS_GET_ROOM,
                    TcpCode::CS_LEAVE_ROOM};
            const std::vector<Rtype::Rfc::UdpCode> CSUdpList{UdpCode::CS_ACTION};
        } //namespace List
    }     // namespace Rfc
    /**
     * @brief Contains all size used.
     * 
     */
    namespace Size
    {
        const short nameLength = 17;
        const short uuidLength = 37;
        const short maxReadSize = 1024;
        const short maxReadUdpSize = 4096;
    } // namespace Size
} // namespace Rtype

#endif /* !RFC_HPP_ */
