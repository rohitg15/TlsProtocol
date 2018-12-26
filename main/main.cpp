#include "socket.h"
#include <iostream>
#include <memory>
#include "record.h"
#include "marshal.h"

int main(int argc, char *argv[])
{

    // std::string hostname = "127.0.0.1";
    // std::vector<uint8_t> msg = {0x41, 0x42, 0x43, 0x44};
    // int port = 8080;
    // tls::ClientSocket clientSocket(hostname, port);
    // clientSocket.PutMessage(msg);
    // clientSocket.CloseSocket();

    // uint16_t fragmentLength = 3;
    // auto pBuf = std::make_unique<uint8_t[]>(sizeof(tls::TlsMessage) + fragmentLength);
    // tls::TlsMessage *pTlsRecord = reinterpret_cast<tls::TlsMessage*>(pBuf.get());
    
    
    
    // pTlsRecord->type = tls::ContentType::Handshake;
    // pTlsRecord->version.major = 0x01;
    // pTlsRecord->version.minor = 0x02;
    // pTlsRecord->length = fragmentLength;

    // pTlsRecord->fragment[50] = 0x02;
    // std::cout << pTlsRecord->fragment[50] << " , " << pTlsRecord->fragment[1000] << std::endl;
    // std::cout << sizeof(static_cast<tls::TlsMessage>(*pTlsRecord));

    ClientHello ch;
    CipherSuites cs;
    cs.length = 125;
    Marshal::Encode<CipherSuites>(cs);

    return 0;   


}
