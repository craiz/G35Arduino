#ifndef _COLOR_NODE_UTILS_H_
#define _COLOR_NODE_UTILS_H_

unsigned long now();

void sleep(unsigned long milliseconds);

#ifndef ARRAYSIZE
#define ARRAYSIZE(a)(sizeof(a) / sizeof(*(a)))
#endif

#endif //_COLOR_NODE_UTILS_H_