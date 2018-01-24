#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>  
#include <netdb.h>  
#include <netinet/in.h>  
#include <sys/wait.h>  
#include <sys/time.h>  
#include <unistd.h>  
#include <asm/ioctls.h>  
#include <signal.h>   
#include <fcntl.h>  
#include <sys/socket.h>
#include <arpa/inet.h>

/*
const char * destIp = "192.168.1.103";
const int port = 9000;
const int timeoutMs = 100;
*/

int _asyncConnect(const char *destIp, const int port, const int timeoutMs, int sockfd)
{
  int retval;
  int error=-1;
  int len;
  struct sockaddr_in servInfo;
  struct timeval tm;
  fd_set rset,wset, excset;  
  int ret = 0;

  memset(&servInfo, 0, sizeof(servInfo));
  servInfo.sin_family = AF_INET;
  servInfo.sin_port = htons(port);
  servInfo.sin_addr.s_addr = inet_addr(destIp);
  if(fcntl(sockfd,F_SETFL,fcntl(sockfd,F_GETFL) | O_NONBLOCK)<0){  
    printf("msg=fcntl`errno=%d`strerror=%s\n", errno, strerror(errno));
    return -3;  
  }  
  if(connect(sockfd,(struct sockaddr *)&servInfo,sizeof(struct sockaddr))<0){
    if(errno != EINPROGRESS){
      printf("msg=connect`errno=%d`strerror=%s\n", errno, strerror(errno));
      return -4;  
    }
    int timeoutS = timeoutMs/1000;
    int timeoutUs = (timeoutMs%1000)*1000;
    tm.tv_sec = timeoutS;  
    tm.tv_usec = timeoutUs;  
    FD_ZERO(&wset);  
    FD_ZERO(&excset);  
    FD_SET(sockfd,&wset);  
    FD_SET(sockfd,&excset);  
    //retval = select(sockfd+1,NULL,&wset, &escset,&tm);  
    retval = select(sockfd+1,NULL,&wset, NULL,&tm);  
    switch(retval)  
    {
      case -1:  
        printf("msg=select`errno=%d`strerror=%s\n", errno, strerror(errno));
        return -1;  
      case 0:  
        printf("msg=select timeout`errno=%d`strerror=%s\n", errno, strerror(errno));
        return 0;
      default:  
        if(FD_ISSET(sockfd,&wset))  {  
          if(getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&error,(socklen_t *)&len)<0)  {  
            return -5;
          }  
          errno = error;
          printf("msg=getsockopt`errno=%d`strerror=%s\n", errno, strerror(errno));
          if(error==0)  {
            ret=1;  
            printf("connected\n");  
          }  else  {  
            ret = -7;  
            errno=error;  
          }  
        } else {
          printf("noway to happend\n");
        }
        break;  
    }
  }

  fcntl(sockfd,F_SETFL,fcntl(sockfd,F_GETFL) & O_NONBLOCK); //set back to block mode  
  return ret;       
}

int asyncConnect(const char *destIp, const int port, const int timeoutMs)
{
  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if(sockfd <0) {
    printf("msg=socket`errno=%d`strerror=%s\n", errno, strerror(errno));
    return -999;
  }
  int ret = _asyncConnect(destIp, port, timeoutMs, sockfd);
  if(ret <0) {
    close(sockfd);
    printf("msg=_asyncConnect failed`ret=%d\n", ret);
    return ret;
  }
  return sockfd;
}

int main() 
{
  printf("begin\n");
  //int fd = asyncConnect(destIp, port, 5000);
  int fd = asyncConnect("192.168.1.103", 9000, 5000);
  return 0;
}
