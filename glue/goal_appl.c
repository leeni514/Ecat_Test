/** @file
 *
 * @brief EtherCAT demo
 *
 * This application provides a simple demo for the EtherCAT stack.
 *
 * @copyright
 * Copyright 2026 NXP
 *
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP
 * and may only be used strictly in accordance with the applicable license
 * terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you
 * have read, and that you agree to comply with and are bound by, such license
 * terms. If you do not agree to be bound by the applicable license terms, then
 * you may not retain, install, activate or otherwise use the software.
 *
 */


#include "goal_includes.h"
#include "goal_ecat.h"
#include "goal_appl_ecat.h"
#include "goal_appl_ecat_objects.h"


/****************************************************************************/
/* Local defines */
/****************************************************************************/
#define APPL_ECAT_PDO_BUF_SIZE 1               /**< PDO buffer size */


/****************************************************************************/
/* Local Prototypes */
/****************************************************************************/
static GOAL_ECAT_T *pHdlEcat;                   /**< GOAL EtherCAT handle */


/****************************************************************************/
/** Application initialization
 *
 * This function initializes the CTC and GOAL.
 *
 * @result GOAL_STATUS_T result
 */
GOAL_STATUS_T appl_init(
    void
)
{
    GOAL_STATUS_T res;                          /* result */

    res = goal_ecatInit();
    if (GOAL_RES_ERR(res)) {
       goal_logErr("Initialization of EtherCAT failed");
    }

    return res;
}


/****************************************************************************/
/** Application Setup
 *
 * Setup the application.
 */
GOAL_STATUS_T appl_setup(
    void
)
{
    GOAL_STATUS_T res;                          /* result */

    /* enable CoE emergency */
    res = goal_ecatCfgEmergencyOn(GOAL_TRUE);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to enable CoE Emergency support");
        return res;
    }

    /* set emergency queue size to 8 */
    res = goal_ecatCfgEmergencyQueueNum(8);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to set CoE Emergency Queue size to 8");
        return res;
    }

    /* set size of PDO buffer
     *
     * The buffer must be big enough to hold both the input and output data.
     * The size depends on the possible combinations of mappable objects.
     */
    res = goal_ecatCfgSizePdoStreamBufSet(APPL_ECAT_PDO_BUF_SIZE);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to set PDO buffer size to %d", APPL_ECAT_PDO_BUF_SIZE);
        return res;
    }


    /* initialize EtherCAT instance */
    res = goal_ecatNew(&pHdlEcat, GOAL_ECAT_INSTANCE_DEFAULT, appl_ecatCallback);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create a new EtherCAT instance");
        return res;
    }

    /* init EtherCAT application */
    res = appl_ecatApplInit(pHdlEcat);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to init application resources");
        return res;
    }

    /* create dynamic objects */
    res = appl_ecatCreateObjects(pHdlEcat);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to initialize object dictionary");
        return res;
    }

    return GOAL_OK;
}
