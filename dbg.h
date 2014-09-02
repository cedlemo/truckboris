#include <cstdio>
#include <cerrno>

#define clean_errno() (errno == 0 ? "None" : strerror(errno))
#define SENTINEL(M, ...) printf("[SENTINEL] (%s:%s:%d: errno: %s) " M "\n",__FILE__, __FUNCTION__, __LINE__, clean_errno(), ##__VA_ARGS__)


