#include "Networking/SocketInterfaces.hpp"
#include "Utility/Logger.hpp"
#include "Router.hpp"

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>


int main()
{
    Utility::Logger logger{std::cout};

    Router router{logger};
    TestDataSocket& sock1 = router.addSocket("e1", "other", 15000, 30000);
    TestDataSocket& sock2 = router.addSocket("other", "e1", 30000, 15000);
    logger.info("Main");
    std::cout << router.getSize() << "\n";
    std::cout << sock1.getEndpoint();
    // std::cout << router.sockets_[0].getPort() << "\n"; 
    // router.sockets_[0].sendData({0xAB, 0x12, 0x69});
    sock1.sendData({0xAB, 0x12, 0x69});
    // logger.info("Bla4");
    // sock1.sendData({0xAB, 0x12, 0x69});
    // auto result = sock2.receiveData(3);
    // std::cout << result;
}
