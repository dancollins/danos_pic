/**
 * @author: Dan
 * @since October 30, 2012, 8:03 PM
 * @version 1.0
 *
 * This will manage the addition, removal and execution of processor jobs
 */

#ifndef JOBS_H
#define JOBS_H

#include <xc.h>
#include <stdlib.h>

#include "types.h"
#include "list.h"

struct job_s {
    uint32_t activationTime;
    Bool (*jobFunction)(void);
};

typedef struct job_s job_t;

/**
 * Prepare the scheduler to accept new jobs
 */
void jobs_init(void);

/**
 * This needs to be run often to process the jobs list.
 */
void jobs_update(void);

/**
 * Add a job to the jobs list.
 * This requires that you fill out a job structure and pass it by reference.
 * @param newJob Reference to the job structure to add
 * @return True on sucess
 */
Bool jobs_add(job_t * newJob);

/**
 * Remove a job from the job list
 * @param job The job to remove
 * @return True if the job was removed
 */
Bool jobs_remove(job_t * job);

#endif
