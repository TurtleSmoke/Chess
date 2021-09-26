#include "test_tmp.hh"

int f1(int x) {
    if (x > 0)
        return 0;
    if (x < 0)
        return 1;

    return -1;
}
