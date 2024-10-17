#include <stdio.h>
#include <time.h>

#define NO_ACTIVE_BUFFER_RECORDS 10

static int time_noactive = 10; /*w sekundach - czas zapisu do bufora*/
static int time_send_noactive = 60; /*w sekundach - czas wysylania bufora*/
static time_t noactive_save_time = -1 ;
static time_t noactive_send_time = -1 ;
static time_t noactive_time = -12345 ;
static int noactive_send_time_first=1;
char   noactive_save_path[128];
int    noactive_buffer_counter;
int    noactive_buffer[2][NO_ACTIVE_BUFFER_RECORDS];


typedef struct {
 int    time;
 char   status;    // 1 - active, 0 - noactive, 2 - start
} NOACTIVE_RECORD;

extern void noactive_zapisz_aktywnosc(NOACTIVE_RECORD *rec);
extern void noactive_wyslij_aktywnosc(void);
extern void return_user_ip (char *);

