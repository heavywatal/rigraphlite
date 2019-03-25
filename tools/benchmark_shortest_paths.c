/*
 clang -DNDEBUG -Wall -pedantic -O2 -I${HOME}/local/include -L${HOME}/local/lib -ligraph ./benchmark_shortest_paths.c && ./a.out
*/
#include <stdio.h>
#include <time.h>

#include <igraph/igraph_interface.h>
#include <igraph/igraph_constructors.h>
#include <igraph/igraph_structural.h>
#include <igraph/igraph_paths.h>

int main() {
  struct timespec ts;
  const int vcount = 1023;
  const int sink_size = vcount / 2 + 1;
  const int sink_first = sink_size - 1;
  igraph_vs_t from = igraph_vss_seq(sink_first, vcount - 1);
  igraph_vs_t to = igraph_vss_seq(sink_first, vcount - 1);
  igraph_t graph;
  igraph_tree(&graph, vcount, 2, IGRAPH_TREE_OUT);

  printf("vcount: %d, sink_size: %d, sink_first: %d\n",
    vcount, sink_size, sink_first
  );

  clock_gettime(CLOCK_REALTIME, &ts);
  printf("%ld.%ld\n", ts.tv_sec, ts.tv_nsec);

  printf("igraph_shortest_paths [%d x %d]\n", sink_size, sink_size);
  igraph_matrix_t res;
  igraph_matrix_init(&res, sink_size, sink_size);
  igraph_shortest_paths(&graph, &res, from, to, IGRAPH_ALL);
  clock_gettime(CLOCK_REALTIME, &ts);
  printf("%ld.%ld\n", ts.tv_sec, ts.tv_nsec);

  printf("igraph_shortest_paths [%d x 1] x %d\n", sink_size, sink_size);
  igraph_matrix_t res1col;
  igraph_matrix_init(&res1col, sink_size, 1);
  for (int i = sink_first; i < vcount; ++i) {
    igraph_shortest_paths(&graph, &res1col, from, igraph_vss_1(i), IGRAPH_ALL);
  }
  clock_gettime(CLOCK_REALTIME, &ts);
  printf("%ld.%ld\n", ts.tv_sec, ts.tv_nsec);

  printf("igraph_shortest_paths [1 x %d] x %d\n", sink_size, sink_size);
  igraph_matrix_t res1row;
  igraph_matrix_init(&res1row, 1, sink_size);
  for (int i = sink_first; i < vcount; ++i) {
    igraph_shortest_paths(&graph, &res1row, igraph_vss_1(i), to, IGRAPH_ALL);
  }
  clock_gettime(CLOCK_REALTIME, &ts);
  printf("%ld.%ld\n", ts.tv_sec, ts.tv_nsec);

  igraph_matrix_destroy(&res);
  igraph_matrix_destroy(&res1col);
  igraph_destroy(&graph);
  return 0;
}
