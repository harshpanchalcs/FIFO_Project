
#include <sched.h>
#include <stdio.h>
int main(int argc, char **argv)
{
  printf("Setting SCHED_FIFO and priority to %d\n",argv[1]);
  struct sched_param param;
  //param.sched_priority = argv[1];
  //sched_setscheduler(0, SCHED_FIFO, &param);
  int n = 0;
  while(1) {
    n++;
    if (!(n % 10000000)) {
      printf("%s FIFO Prio %d running (n=%d)\n",argv[2], argv[1],n);
    }
  }
}
