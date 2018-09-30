#include "bar.h"
#include "foo.h"
#include "socket.h"
#include "record.h"

int main(int argc, char *argv[])
{
    // Bar bar;
    // Foo foo(bar);
    // foo.baz(true);
    // foo.baz(false);

    std::string hostname = "127.0.0.1";
    std::vector<uint8_t> msg = {0x01, 0x02, 0x03, 0x04};
    int port = 8080;
    tls::ClientSocket clientSocket(hostname, port);
    clientSocket.PutMessage(msg);
    clientSocket.CloseSocket();

}
