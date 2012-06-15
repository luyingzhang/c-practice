#include	<stdio.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/ipc.h>
#include	<sys/shm.h>
#include	<sys/sem.h>
#include	<errno.h>

#define RUN_SERVICE   2
#define WAIT_SERVICE  1
#define STOP_SERVICE  0

typedef struct shm_struct shmRec;
struct shm_struct {
	/*process id*/
	int fisc_in_con_pid;
	int fisc_out_con_pid;
	int fep_in_con_pid;
	int fep_out_con_pid;
	int fisc_gw_pid;
	int fep_gw_pid;
	/*status*/
	int fisc_in_con_status;
	int fisc_out_con_status;
	int fep_in_con_status;
	int fep_out_con_status;
	/*財金電文序號*/
	int fisc_tx_no;
	/*queue*/
	int fisc_con_queue;
	int fep_con_queue;
	int fisc_gw_queue;
	int fep_gw_queue;
	int log_queue;
};

shmRec *shm;
