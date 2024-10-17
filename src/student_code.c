
#include "student_code.h"

void finalize_stats(SCHEDULER_STATS* stats) {
    stats->num_processes_started > 0 ?
      stats->average_response_time = stats->sum_of_response_time / stats->num_processes_started : 0;
    stats->num_processes_completed > 0 ?
      stats->average_turnaround_time = stats->sum_of_turnaround_times / stats->num_processes_completed : 0;
}


void mark_process_start(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice) {
  stats->num_processes_started+=1;
  stats->sum_of_response_time += curr_time - p->entry_time;
}

void mark_process_run(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice) {
  p->time_remaining -= time_slice;
}

void mark_process_end(SCHEDULER_STATS* stats, PROCESS* p, float end_time, float time_slice_remaining) {
  stats->num_processes_completed+=1;
  stats->sum_of_turnaround_times += end_time - p->entry_time;
}

int compare_priority(PROCESS p1, PROCESS p2) {
    return (int)p1.priority - (int)p2.priority;
}

int compare_first(PROCESS p1, PROCESS p2) {
    return (int)p1.entry_time - (int)p2.entry_time;
}

int compare_last(PROCESS p1, PROCESS p2) {
    return (int)p2.entry_time - (int)p1.entry_time;
}

int compare_length(PROCESS p1, PROCESS p2) {
    return (int)p1.length - (int)p2.length;
}

int compare_remaining_time(PROCESS p1, PROCESS p2) {
    return (int)p1.time_remaining - (int)p2.time_remaining;
}

PROCESS* priority_process_selector(PROCESS_LIST* pl) {
    PROCESS *p;
    p = get_minimum(pl, compare_priority);
    return p;
}

PROCESS* fifo_process_selector(PROCESS_LIST* pl) {
    PROCESS *p;
    p = get_minimum(pl, compare_first);
    return p;
}

PROCESS* rr_process_selector(PROCESS_LIST* pl) {
    PROCESS* p;
    p = get_next(pl);
    return p;
}

PROCESS* sjf_process_selector(PROCESS_LIST* pl) {
    PROCESS* p;
    p = get_minimum(pl, compare_length);
    return p;
}

PROCESS* lifo_process_selector(PROCESS_LIST* pl) {
    PROCESS* p;
    p = get_minimum(pl, compare_last);
    return p;
}

PROCESS* stcf_process_selector(PROCESS_LIST* pl) {
    PROCESS *p;
    p = get_minimum(pl, compare_remaining_time);
    return p;
}

