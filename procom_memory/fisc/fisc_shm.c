#include "fisc_shm.h"
#include "fisc_log.h"
void* shm_addr = 0;

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:
 --------------------------------------------------------------------------*/
int detachSHM(void) {
	if (shmdt(shm_addr) == -1) {
		fprintf(stderr, "  shmdt fail");
		fprintf(stderr, "  errno = [%d]\n", errno);
		return -1;
	}
	return 1;
}

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:
 --------------------------------------------------------------------------*/
int createSHM(int shm_mode, int shm_key) {
	int rc;
	int shm_id = 0;

	if (shm_key == 0)
		shm_key = 0x1000;

	if (shm_mode == 0)
		shm_id = shmget((key_t) shm_key, sizeof(shmRec), 0644 | IPC_CREAT);
	else
		shm_id = shmget((key_t) shm_key, sizeof(shmRec), 0444);

	if (shm_id == -1) {
		fprintf(stderr, "  shmget fail,key=[%04x]", shm_key);
		fprintf(stderr, "  errno = [%d]\n", errno);
		printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
		return -1;
	}

	shm_addr = (void *) 0;
	shm_addr = shmat(shm_id, (void *) 0, 0);
	if (shm_addr == (void*) -1) {
		fprintf(stderr, "  shmat fail");
		fprintf(stderr, "  errno = [%d]\n", errno);
		return -1;
	}

	shm = (shmRec *) shm_addr;
	return 1;
}
