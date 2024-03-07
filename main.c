#include "sysdetect.h"
#include <time.h>
#include "life.h"
#include "display.h"

#ifdef HAS_THREADS
#include <threads.h>
#elif defined(UNIXLIKE)
#include <unistd.h>
#endif

/*
 * Sleep for a floating point number of seconds, POSIX version.
 */
void delay(float seconds)
{
    struct timespec ts = {
        seconds,
        (seconds - (int)seconds) * 1000000000
    };

#ifdef HAS_THREADS
    thrd_sleep(&ts, NULL);
#elif defined(UNIXLIKE)
    nanosleep(&ts, NULL);
#else
    #error Floating-point sleep not implemented on this system
#endif
}

void init(void)
{
    life_init();
    display_init();
}

void run(void)
{
    for (;;) {
        life_update();
        char **cells = life_get_cells();
        display_update(cells);
        delay(0.15);
    }
}

void shutdown(void)
{
    life_shutdown();
}

int main(void)
{
    init();
    run();
    shutdown();
}
