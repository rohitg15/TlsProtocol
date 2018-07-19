#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <string>

namespace tls
{
    class BaseSocket
    {
    public:
        virtual ~BaseSocket();

        void CloseSocket();

        BaseSocket(
            BaseSocket&& move
        ) noexcept;

        BaseSocket& operator=(
            BaseSocket&& move
        ) noexcept;

        BaseSocket(
            const BaseSocket&
        ) = delete;

        BaseSocket& operator=(
            const BaseSocket&
        ) = delete;
        
    protected:
        BaseSocket(
            int socketId
        );

        int GetSocketId() const;

    private:
        int m_socketId;
        static int constexpr invalidSocketId = -1;
    };

    class ClientSocket : public BaseSocket
    {
    public:
        ClientSocket(
            const std::string& hostname,
            int port
        );

        bool GetMessage(
            std::string& msg
        );

        void PutMessage(
            const std::string& msg
        );
    };

}   //  tls

#endif  //  _SOCKET_H_