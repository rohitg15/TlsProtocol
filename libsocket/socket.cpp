#include "socket.h"
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <stdexcept>
#include <string.h>
#include <vector>


namespace tls
{
    /*
     * Definitions for BaseSocket methods
     */
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

    /*
     * Definitions for ClientSocket methods
     */
    ClientSocket::ClientSocket(
        const std::string& hostname,
        int port
    ) : BaseSocket(::socket(PF_INET, SOCK_STREAM, 0))
    {
        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = inet_addr(hostname.c_str());

        if (::connect(GetSocketId(), (struct sockaddr*)&serverAddr, sizeof(serverAddr)) != 0)
        {
            CloseSocket();
            std::string err = "ClientSocket error in connect - ";
            err += strerror(errno);
            throw std::runtime_error(err);
        }
    }

    void ClientSocket::PutMessage(
        const std::vector<uint8_t>& msg
    )
    {
        size_t bytesWritten = 0;

        while (bytesWritten < msg.size())
        {
            ssize_t ret = ::write(GetSocketId(), msg.data() + bytesWritten, msg.size() - bytesWritten);
            if (ret == -1)
            {
                std::string err = "PutMessage error in ClientSocket - ";
                err += strerror(errno);
                throw std::runtime_error(err);
            }
            bytesWritten += static_cast<size_t>(ret);
        }
    }

    void ClientSocket::GetMessage(
        std::vector<uint8_t>& msg
    )
    {
        size_t bytesRead = 0;
        // std::vector<uint8_t> buf;
        for (;;)
        {
            ssize_t ret = ::read(GetSocketId(), msg.data() + bytesRead, ClientSocket::MAX_READ_SIZE);
            if (ret == -1)
            {
                std::string err = "GetMessage error in ClientSocket - ";
                err += strerror(errno);
                throw std::runtime_error(err);
            }
            else if (ret == 0)
            {
                break;
            }
            bytesRead += static_cast<size_t>(ret);
        }

        // do we need to copy here?
        // msg.assign(buf.begin(), buf.end());
    }

}   // tls