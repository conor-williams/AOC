#include <stdio.h>
#include <string.h>

static const char graph1[] =
    "5U2D5L4R5R6L5D8L7U4U1R2R3D6D9L8R9U6U3L2L1D4D7R8U5";
static const char graph2[] =
    "5R6R7L6U2R3U1D3D7U3R4D8R9L8L7R8DCLBDDDUBU7DBLAU6DARBRCU8U4L3L2D6L5";

enum { FROM, INPUT, TO };

int main(void)
{
    char edge1[] = "5X", edge2[] = "5X", *e, input;
    while ((input = getchar()) != -1) {
        if (input == '\n') {
            printf("\033[33m%c", edge1[FROM]);
            printf("\033[31m%c", edge2[FROM]);
        } else {
            edge1[INPUT] = input;
            if ((e = strstr(graph1, edge1))) {
                edge1[FROM] = e[TO];
            }
            edge2[INPUT] = input;
            if ((e = strstr(graph2, edge2))) {
                edge2[FROM] = e[TO];
            }
        }
    }
    puts("\033[0m");
    return 0;
}
