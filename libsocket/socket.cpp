#include "socket.h"
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


namespace tls
{
    BaseSocket::BaseSocket(
        int socketId
    ) : m_socketId(socketId)
    {
        if (m_socketId == BaseSocket::invalidSocketId)
        {
            std::string err = "BaseSocket error: ";
            err += strerror(errno);
            throw std::runtime_error(err);
        }
    }

    BaseSocket::~BaseSocket()
    {
        if (m_socketId == BaseSocket::invalidSocketId)
        {
            return;
        }
        CloseSocket();
    }

    void BaseSocket::CloseSocket()
    {
        if (m_socketId == BaseSocket::invalidSocketId)
        {
            std::string err = "BaseSocket error in CloseSocket, socket already removed";
            throw std::runtime_error(err);
        }
        close(m_socketId);
        m_socketId = BaseSocket::invalidSocketId;
    }

    int BaseSocket::GetSocketId() const
    {
        return m_socketId;
    }

}   // tls