#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

struct  timeval tz; 

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
  struct  timeval now;
  gettimeofday(&now, 0);
  double total = ((double)now.tv_sec + (double)now.tv_usec/1000000) - ((double)tz.tv_sec + (double)tz.tv_usec/1000000);
  printf("tT=%.2f\n", total);
}

int main(int argc, char* argv[]) {
  gettimeofday(&tz, 0);
  for(int i=0; i<1000000; i++) {
    for(int j=0; j<1000000; j++) {
      if(i%100 == 0 && j%1000000 == 0) {
        showCpuInfo();
      }
      if(j % 100000 == 0) {
        struct rusage self_ru, c_ru;
        int r1 = getrusage(RUSAGE_SELF, &self_ru);
        int r2 = getrusage(RUSAGE_CHILDREN, &c_ru);
        double sysT = (double)self_ru.ru_stime.tv_sec + (double)self_ru.ru_stime.tv_usec/1000000;
        double userT = (double)self_ru.ru_utime.tv_sec+ (double)self_ru.ru_utime.tv_usec/1000000;
        double cST = (double)c_ru.ru_stime.tv_sec + (double)c_ru.ru_stime.tv_usec/1000000;
        double cUT = (double)c_ru.ru_utime.tv_sec + (double)c_ru.ru_utime.tv_usec/1000000;
        struct  timeval now;
        gettimeofday(&now, 0);
        double total = ((double)now.tv_sec + (double)now.tv_usec/1000000) - ((double)tz.tv_sec + (double)tz.tv_usec/1000000);
        double tmp =100*(sysT + userT + cST + cUT)/65 - total;
        /*
        printf("r1=%d`r2=%d`used_cpu_sys=%.2f`used_cpu_user=%.2f`used_cpu_sys_children:%.2f`used_cpu_user_children:%.2f\n", 
            r1, r2,
            (double)self_ru.ru_stime.tv_sec+(double)self_ru.ru_stime.tv_usec/1000000,
            (double)self_ru.ru_utime.tv_sec+(double)self_ru.ru_utime.tv_usec/1000000,
            (double)c_ru.ru_stime.tv_sec+(double)c_ru.ru_stime.tv_usec/1000000,
            (double)c_ru.ru_utime.tv_sec+(double)c_ru.ru_utime.tv_usec/1000000);
            */
        if(tmp > 0) {
          //printf("%.2f\n", (sysT+userT)/(double)total);
          usleep((int)(tmp*1000000));
        }
      }
    }
  }
}
