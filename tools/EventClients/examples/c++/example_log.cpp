#include "../../lib/c++/xbmcclient.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#ifdef _WIN32
#include <Windows.h> // for sleep
#else
#include <unistd.h>
#endif

int main(int argc, char **argv)
{
  /* connect to localhost, port 9777 using a UDP socket
     this only needs to be done once.
     by default this is where XBMC will be listening for incoming
     connections. */

  CAddress my_addr; // Address => localhost on 9777
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
  {
    printf("Error creating socket\n");
    return -1;
  }

  my_addr.Bind(sockfd);
  //Normally this is already done by the client
  CPacketHELO HeloPackage("LOG Test", ICON_NONE);
  HeloPackage.Send(sockfd, my_addr);

  sleep(5);
  //This works as XBMC internal CLog::LOG(LOGTYPE, STRING);
  CPacketLOG packet(LOGERROR, "The Log Message");
  packet.Send(sockfd, my_addr);

  // BYE is not required since XBMC would have shut down
  CPacketBYE bye; // CPacketPing if you want to ping
  bye.Send(sockfd, my_addr);
}
