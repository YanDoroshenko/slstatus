/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>

#include "../util.h"

#include <limits.h>
#include <stdint.h>
#include <unistd.h>

const char * camera(const char *cam) {
    char camera_path[PATH_MAX];

    if (esnprintf(camera_path, sizeof(camera_path),
                "/dev/%s", cam) < 0) {
        return bprintf("");
    }
    else if (access(camera_path, R_OK) == 0) {
        return bprintf(" ");
    }
    else {
        return bprintf("");
    }
}
