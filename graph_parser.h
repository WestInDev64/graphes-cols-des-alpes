#ifndef GRAPH_PARSER_H
#define GRAPH_PARSER_H

#include "graph.h"

/* Constants =========================================================== */
#define BUFF_SIZE 1024
#define DELIM ";\r\n"

/* Functions =========================================================== */
Graph* parse_graph(const char* nodes_filename, const char* arcs_filename);

#endif // GRAPH_PARSER_H