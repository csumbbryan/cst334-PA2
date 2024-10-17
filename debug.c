#include "src/student_code.h"
#include "src/tests.h"
#include <criterion/criterion.h>

#include "unistd.h"
#include <sys/syscall.h>
#include <stdio.h>

int main() {

    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = sjf_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect(stats->completion_time==          30.0f);
    cr_expect(stats->sum_of_turnaround_times==  65.0f);
    cr_expect(stats->sum_of_response_time==     29.0f);
    cr_expect(stats->average_turnaround_time == 13.0f);
    cr_expect(stats->average_response_time==    5.80f);
    printf("-----------------------------------\n");

  /*
  const char msg[] = "Hello World!\n";
  write(STDOUT_FILENO, msg, sizeof(msg)-1);
  syscall(SYS_write, STDOUT_FILENO, msg, sizeof(msg)-1);

  char buff[1024];
  syscall(SYS_read, STDIN_FILENO, buff, 5);
  printf("%s\n", buff);
  */

  return 0;
}
