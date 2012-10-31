#include "jobs.h"

/**
 * Jobs that will be started after the set time
 */
list_t Jobs;

void jobs_init(void) {
    // Initiate the job lists
    list_init(&Jobs);
}

void jobs_update(void) {
    uint32_t currentTime = timer_currentTime();
    list_el_t * jobLink = Jobs.head; // Start at the top of the future jobs list
    job_t * job; // The job to run
    Bool jobComplete; // This will hold the value returned by the job.  False if the job needs to be re-executed

    while(jobLink != Null) {
        job = (job_t*)jobLink->element; // Get the details for the job from the list

        if (job->activationTime <= currentTime) { // If it is time to call the job
            jobComplete = job->jobFunction(); // Run the job
            
            if (jobComplete == True)
                jobs_remove(job); // Remove the job from the future jobs list
            else
                job->activationTime = currentTime; // Make sure the job runs on the next cycle.  TODO: I can reduce the running frequency of threads this way
        }

        jobLink = jobLink->next; // Point to the next job in the list
    }
}

Bool jobs_add(job_t * newJob) {
    job_t * jobToAdd;

    jobToAdd = malloc(sizeof(job_t));
    if (jobToAdd == Null)
        return False; // Failed to add job

    // Store the job details
    memcpy(jobToAdd, newJob, sizeof(job_t));

    return list_add(&Jobs, jobToAdd); // Add the job to the list, returning true on success
}

Bool jobs_remove(job_t * job) {
    list_remove(&Jobs, job); // Remove the job from the list, returning true on success
}
