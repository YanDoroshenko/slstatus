/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>

#include "../util.h"

#include <limits.h>
#include <stdint.h>
#include <unistd.h>

static const char * pick(const char *bat, const char *f1, const char *f2, char *path,
        size_t length) {
    if (esnprintf(path, length, f1, bat) > 0 &&
            access(path, R_OK) == 0) {
        return f1;
    }

    if (esnprintf(path, length, f2, bat) > 0 &&
            access(path, R_OK) == 0) {
        return f2;
    }

    return NULL;
}


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

const char * battery_remaining(const char *bat) {
    uintmax_t charge_now, current_now, m, h;
    double timeleft;
    char path[PATH_MAX], state[12];

    if (esnprintf(path, sizeof(path),
                "/sys/class/power_supply/%s/status", bat) < 0) {
        return NULL;
    }
    if (pscanf(path, "%12s", state) != 1) {
        return NULL;
    }

    if (!pick(bat, "/sys/class/power_supply/%s/charge_now",
                "/sys/class/power_supply/%s/energy_now", path,
                sizeof(path)) ||
            pscanf(path, "%ju", &charge_now) < 0) {
        return NULL;
    }

    if (!strcmp(state, "Discharging")) {
        if (!pick(bat, "/sys/class/power_supply/%s/current_now",
                    "/sys/class/power_supply/%s/power_now", path,
                    sizeof(path)) ||
                pscanf(path, "%ju", &current_now) < 0) {
            return NULL;
        }

        if (current_now == 0) {
            return NULL;
        }

        timeleft = (double)charge_now / (double)current_now;
        h = timeleft;
        m = (timeleft - (double)h) * 60;

        return bprintf("%juh %2jum", h, m);
    }

    return "";
}
