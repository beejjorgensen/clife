#ifndef LIFE_H
#define LIFE_H

#define LIFE_ROWS 24
#define LIFE_COLS 80

extern void life_init(void);
extern void life_update(void);
extern void life_shutdown(void);
extern char **life_get_cells(void);

#endif
