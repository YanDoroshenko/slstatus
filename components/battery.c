/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>

#include "../util.h"

#include <limits.h>
#include <stdint.h>
#include <unistd.h>

const char * battery(const char *bat) {
    int perc;
    char capacity_path[PATH_MAX];

    if (esnprintf(capacity_path, sizeof(capacity_path),
                "/sys/class/power_supply/%s/capacity", bat) < 0) {
        return NULL;
    }
    if (pscanf(capacity_path, "%d", &perc) != 1) {
        return NULL;
    }

    char status_path[PATH_MAX], state[12];

    if (esnprintf(status_path, sizeof(status_path),
                "/sys/class/power_supply/%s/status", bat) < 0) {
        return NULL;
    }
    if (pscanf(status_path, "%12s", state) != 1) {
        return NULL;
    }

    if (strcmp("Discharging", state) == 0) {
        if (perc >= 100)
            return bprintf("");
        else if (perc >= 90)
            return bprintf("");
        else if (perc >= 80)
            return bprintf("");
        else if (perc >= 70)
            return bprintf("");
        else if (perc >= 60)
            return bprintf("");
        else if (perc >= 50)
            return bprintf("");
        else if (perc >= 40)
            return bprintf("");
        else if (perc >= 30)
            return bprintf("");
        else if (perc >= 20)
            return bprintf("");
        else if (perc >= 10)
            return bprintf("");
        else
            return bprintf("");
    }
    else if (strcmp("Charging", state) == 0) {
        if (perc >= 100)
            return bprintf("");
        else if (perc >= 90)
            return bprintf("");
        else if (perc >= 80)
            return bprintf("");
        else if (perc >= 60)
            return bprintf("");
        else if (perc >= 40)
            return bprintf("");
        else if (perc >= 30)
            return bprintf("");
        else
            return bprintf("");
    }
    else if (strcmp("Full", state) == 0) {
        return bprintf("");
    }
    else {
        return bprintf("");
    }
}
