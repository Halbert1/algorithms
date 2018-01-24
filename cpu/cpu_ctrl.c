#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/resource.h>

struct timeval begin; 

void showCpuInfo() {
  struct rusage self_ru, c_ru;
  int r1 = getrusage(RUSAGE_SELF, &self_ru);
  int r2 = getrusage(RUSAGE_CHILDREN, &c_ru);
  printf("r1=%d`r2=%d`used_cpu_sys=%.2f`used_cpu_user=%.2f`used_cpu_sys_children:%.2f`used_cpu_user_children:%.2f\n", 
      r1, r2,
      (double)self_ru.ru_stime.tv_sec+(double)self_ru.ru_stime.tv_usec/1000000,
      (double)self_ru.ru_utime.tv_sec+(double)self_ru.ru_utime.tv_usec/1000000,
      (double)c_ru.ru_stime.tv_sec+(double)c_ru.ru_stime.tv_usec/1000000,
      (double)c_ru.ru_utime.tv_sec+(double)c_ru.ru_utime.tv_usec/1000000);
  struct timeval now;
  gettimeofday(&now, 0);
  printf("tT=%.2f\n", ((double)now.tv_sec+(double)now.tv_usec/1000000) - ((double)begin.tv_sec+(double)begin.tv_usec/1000000));
}

bool end(struct  timeval &then, int out) {
  struct timeval now;
  gettimeofday(&now, 0);
  //return ((double)now.tv_sec + (double)now.tv_usec/1000000 - ((double)then.tv_sec + (double)then.tv_usec/1000000)) <= out;
  return ((double)now.tv_sec + (double)now.tv_usec/1000000 - ((double)then.tv_sec + (double)then.tv_usec/1000000)) <= (double)out/1000000;
}

int main(int argc, char* argv[]) {
  gettimeofday(&begin, 0);
  int tmp = 100;
  int i = 0;
  while(true) {
    struct timeval tz; 
    gettimeofday(&tz, 0);
    for(;end(tz, tmp*7);){
      continue;
    }
    usleep(tmp * 3);
    if(i++ % 10000 ==0) {
      showCpuInfo();
    }
  }
}
