/** @file
 *
 * @brief EtherCAT Sample application
 *
 * This module contains functions to create the objects (device model) of
 * the EtherCAT slave
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
#include <goal_ecat.h>
#include "goal_appl_ecat_objects.h"


/****************************************************************************/
/* Global variables */
/****************************************************************************/


/****************************************************************************/
/* Local variables */
/****************************************************************************/


/****************************************************************************/
/** Application initialization
 *
 * This function is used to initialize application specific resources.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ecatCreateObjects(
    GOAL_ECAT_T *pHdlEcat                       /**< GOAL EtherCAT handle */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    uint32_t uint32ValueDef = 0;                /* value of type uint32_t */
    uint32_t uint32ValueMin = 0;                /* value of type uint32_t */
    uint32_t uint32ValueMax = 0;                /* value of type uint32_t */

    uint8_t uint8ValueDef = 0;                  /* value of type uint8_t */
    uint8_t uint8ValueMin = 0;                  /* value of type uint8_t */
    uint8_t uint8ValueMax = 0;                  /* value of type uint8_t */

    uint16_t uint16ValueDef = 0;                /* value of type uint16_t */
    uint16_t uint16ValueMin = 0;                /* value of type uint16_t */
    uint16_t uint16ValueMax = 0;                /* value of type uint16_t */

    /* create object dictionary */

    /************************************************/
    /* 0x1000 - Device Type                         */
    /************************************************/
    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjAdd(pHdlEcat, 0x1000, GOAL_ECAT_OBJCODE_VAR, GOAL_ECAT_DATATYPE_UNSIGNED32);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjNameAdd(pHdlEcat, 0x1000, "Device Type");
    }

    if (GOAL_RES_OK(res)) {

        uint32ValueMin = 0x00000000;
        uint32ValueDef = 0x00000191;
        uint32ValueMax = 0xFFFFFFFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1000,
            0x00,
            GOAL_ECAT_DATATYPE_UNSIGNED32,
            EC_OBJATTR_RD | EC_OBJATTR_MAN | EC_OBJATTR_NUMERIC | EC_OBJATTR_NO_LIMITS,
            (uint8_t *) &uint32ValueDef,
            (uint8_t *) &uint32ValueMin,
            (uint8_t *) &uint32ValueMax,
            4,
            NULL);
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create object 0x1000");
    }

    /************************************************/
    /* 0x1001 - Error Register                      */
    /************************************************/
    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjAdd(pHdlEcat, 0x1001, GOAL_ECAT_OBJCODE_VAR, GOAL_ECAT_DATATYPE_UNSIGNED8);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjNameAdd(pHdlEcat, 0x1001, "Error Register");
    }

    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x00;
        uint8ValueMax = 0xFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1001,
            0x00,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_OPT | EC_OBJATTR_NUMERIC | EC_OBJATTR_NO_DFLT | EC_OBJATTR_NO_LIMITS,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create object 0x1001");
    }

    /************************************************/
    /* 0x1018 - Identity Object                     */
    /************************************************/
    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjAdd(pHdlEcat, 0x1018, GOAL_ECAT_OBJCODE_RECORD, 0x23);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjNameAdd(pHdlEcat, 0x1018, "Identity Object");
    }

    /************************************************/
    /* 0x1018:0x00 number of entries               */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x01;
        uint8ValueDef = 0x04;
        uint8ValueMax = 0x04;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1018,
            0x00,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_MAN | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1018, 0x00, "number of entries");
    }

    /************************************************/
    /* 0x1018:0x01 Vendor Id                       */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint32ValueMin = 0x00000000;
        uint32ValueDef = 0x0000E778;
        uint32ValueMax = 0xFFFFFFFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1018,
            0x01,
            GOAL_ECAT_DATATYPE_UNSIGNED32,
            EC_OBJATTR_RD | EC_OBJATTR_MAN | EC_OBJATTR_NUMERIC | EC_OBJATTR_NO_LIMITS,
            (uint8_t *) &uint32ValueDef,
            (uint8_t *) &uint32ValueMin,
            (uint8_t *) &uint32ValueMax,
            4,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1018, 0x01, "Vendor Id");
    }

    /************************************************/
    /* 0x1018:0x02 Product Code                    */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint32ValueMin = 0x00000000;
        uint32ValueDef = 0x00000067;
        uint32ValueMax = 0xFFFFFFFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1018,
            0x02,
            GOAL_ECAT_DATATYPE_UNSIGNED32,
            EC_OBJATTR_RD | EC_OBJATTR_MAN | EC_OBJATTR_NUMERIC | EC_OBJATTR_NO_LIMITS,
            (uint8_t *) &uint32ValueDef,
            (uint8_t *) &uint32ValueMin,
            (uint8_t *) &uint32ValueMax,
            4,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1018, 0x02, "Product Code");
    }

    /************************************************/
    /* 0x1018:0x03 Revision number                 */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint32ValueMin = 0x00000000;
        uint32ValueDef = 0x00000068;
        uint32ValueMax = 0xFFFFFFFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1018,
            0x03,
            GOAL_ECAT_DATATYPE_UNSIGNED32,
            EC_OBJATTR_RD | EC_OBJATTR_MAN | EC_OBJATTR_NUMERIC | EC_OBJATTR_NO_DFLT | EC_OBJATTR_NO_LIMITS,
            (uint8_t *) &uint32ValueDef,
            (uint8_t *) &uint32ValueMin,
            (uint8_t *) &uint32ValueMax,
            4,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1018, 0x03, "Revision number");
    }

    /************************************************/
    /* 0x1018:0x04 Serial number                   */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint32ValueMin = 0x00000000;
        uint32ValueDef = 0x00000069;
        uint32ValueMax = 0xFFFFFFFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1018,
            0x04,
            GOAL_ECAT_DATATYPE_UNSIGNED32,
            EC_OBJATTR_RD | EC_OBJATTR_MAN | EC_OBJATTR_NUMERIC | EC_OBJATTR_NO_DFLT | EC_OBJATTR_NO_LIMITS,
            (uint8_t *) &uint32ValueDef,
            (uint8_t *) &uint32ValueMin,
            (uint8_t *) &uint32ValueMax,
            4,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1018, 0x04, "Serial number");
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create object 0x1018");
    }

    /************************************************/
    /* 0x1600 - Receive PDO Mapping Parameter 1     */
    /************************************************/
    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjAdd(pHdlEcat, 0x1600, GOAL_ECAT_OBJCODE_RECORD, 0x21);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjNameAdd(pHdlEcat, 0x1600, "Receive PDO Mapping Parameter 1");
    }

    /************************************************/
    /* 0x1600:0x00 Number of Entries               */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x01;
        uint8ValueMax = 0xFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1600,
            0x00,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD_PREOP | EC_OBJATTR_WR_PREOP | EC_OBJATTR_RD_SAFEOP | EC_OBJATTR_RD_OP | EC_OBJATTR_MAN | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1600, 0x00, "Number of Entries");
    }

    /************************************************/
    /* 0x1600:0x01 Mapping Entry 1                 */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint32ValueMin = 0x00000000;
        uint32ValueDef = 0x70000108;
        uint32ValueMax = 0xFFFFFFFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1600,
            0x01,
            GOAL_ECAT_DATATYPE_UNSIGNED32,
            EC_OBJATTR_RD_PREOP | EC_OBJATTR_WR_PREOP | EC_OBJATTR_RD_SAFEOP | EC_OBJATTR_RD_OP | EC_OBJATTR_NUMERIC | EC_OBJATTR_NO_LIMITS,
            (uint8_t *) &uint32ValueDef,
            (uint8_t *) &uint32ValueMin,
            (uint8_t *) &uint32ValueMax,
            4,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1600, 0x01, "Mapping Entry 1");
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create object 0x1600");
    }

    /************************************************/
    /* 0x1A00 - Transmit PDO Mapping Parameter 1    */
    /************************************************/
    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjAdd(pHdlEcat, 0x1A00, GOAL_ECAT_OBJCODE_RECORD, 0x21);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjNameAdd(pHdlEcat, 0x1A00, "Transmit PDO Mapping Parameter 1");
    }

    /************************************************/
    /* 0x1A00:0x00 Number of Entries               */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x01;
        uint8ValueMax = 0xFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1A00,
            0x00,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_MAN | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1A00, 0x00, "Number of Entries");
    }

    /************************************************/
    /* 0x1A00:0x01 Mapping Entry 1                 */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint32ValueMin = 0x00000000;
        uint32ValueDef = 0x60000108;
        uint32ValueMax = 0xFFFFFFFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1A00,
            0x01,
            GOAL_ECAT_DATATYPE_UNSIGNED32,
            EC_OBJATTR_RD | EC_OBJATTR_NUMERIC | EC_OBJATTR_NO_LIMITS,
            (uint8_t *) &uint32ValueDef,
            (uint8_t *) &uint32ValueMin,
            (uint8_t *) &uint32ValueMax,
            4,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1A00, 0x01, "Mapping Entry 1");
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create object 0x1A00");
    }

    /************************************************/
    /* 0x1C00 - Sync Manager Communication Type     */
    /************************************************/
    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjAdd(pHdlEcat, 0x1C00, GOAL_ECAT_OBJCODE_ARRAY, GOAL_ECAT_DATATYPE_UNSIGNED8);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjNameAdd(pHdlEcat, 0x1C00, "Sync Manager Communication Type");
    }

    /************************************************/
    /* 0x1C00:0x00 Number of used Sync Managers    */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x04;
        uint8ValueDef = 0x05;
        uint8ValueMax = 0x05;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1C00,
            0x00,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_MAN | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1C00, 0x00, "Number of used Sync Managers");
    }

    /************************************************/
    /* 0x1C00:0x01 Sync Manager  Communication Type */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x01;
        uint8ValueMax = 0x04;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1C00,
            0x01,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1C00, 0x01, "Sync Manager  Communication Type");
    }

    /************************************************/
    /* 0x1C00:0x02 Sync Manager  Communication Type */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x02;
        uint8ValueMax = 0x04;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1C00,
            0x02,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1C00, 0x02, "Sync Manager  Communication Type");
    }

    /************************************************/
    /* 0x1C00:0x03 Sync Manager  Communication Type */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x03;
        uint8ValueMax = 0x04;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1C00,
            0x03,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1C00, 0x03, "Sync Manager  Communication Type");
    }

    /************************************************/
    /* 0x1C00:0x04 Sync Manager  Communication Type */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x04;
        uint8ValueMax = 0x04;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1C00,
            0x04,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1C00, 0x04, "Sync Manager  Communication Type");
    }

    /************************************************/
    /* 0x1C00:0x05 Sync Manager  Communication Type */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x00;
        uint8ValueMax = 0x04;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1C00,
            0x05,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1C00, 0x05, "Sync Manager  Communication Type");
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create object 0x1C00");
    }

    /************************************************/
    /* 0x1C12 - Sync Manager 2 PDO Assignment       */
    /************************************************/
    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjAdd(pHdlEcat, 0x1C12, GOAL_ECAT_OBJCODE_ARRAY, GOAL_ECAT_DATATYPE_UNSIGNED16);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjNameAdd(pHdlEcat, 0x1C12, "Sync Manager 2 PDO Assignment");
    }

    /************************************************/
    /* 0x1C12:0x00 Number of assigned PDOs         */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x01;
        uint8ValueMax = 0xFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1C12,
            0x00,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1C12, 0x00, "Number of assigned PDOs");
    }

    /************************************************/
    /* 0x1C12:0x01 PDO Mapping index of assigned PDOs */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint16ValueMin = 0x1600;
        uint16ValueDef = 0x1600;
        uint16ValueMax = 0x1BFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1C12,
            0x01,
            GOAL_ECAT_DATATYPE_UNSIGNED16,
            EC_OBJATTR_RD | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint16ValueDef,
            (uint8_t *) &uint16ValueMin,
            (uint8_t *) &uint16ValueMax,
            2,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1C12, 0x01, "PDO Mapping index of assigned PDOs");
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create object 0x1C12");
    }

    /************************************************/
    /* 0x1C13 - Sync Manager 3 PDO Assignment       */
    /************************************************/
    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjAdd(pHdlEcat, 0x1C13, GOAL_ECAT_OBJCODE_ARRAY, GOAL_ECAT_DATATYPE_UNSIGNED16);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjNameAdd(pHdlEcat, 0x1C13, "Sync Manager 3 PDO Assignment");
    }

    /************************************************/
    /* 0x1C13:0x00 Number of assigned PDOs         */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x01;
        uint8ValueMax = 0xFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1C13,
            0x00,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1C13, 0x00, "Number of assigned PDOs");
    }

    /************************************************/
    /* 0x1C13:0x01 PDO Mapping index of assigned PDOs */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint16ValueMin = 0x1600;
        uint16ValueDef = 0x1A00;
        uint16ValueMax = 0x1BFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x1C13,
            0x01,
            GOAL_ECAT_DATATYPE_UNSIGNED16,
            EC_OBJATTR_RD | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint16ValueDef,
            (uint8_t *) &uint16ValueMin,
            (uint8_t *) &uint16ValueMax,
            2,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x1C13, 0x01, "PDO Mapping index of assigned PDOs");
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create object 0x1C13");
    }

    /************************************************/
    /* 0x6000 - Input                               */
    /************************************************/
    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjAdd(pHdlEcat, 0x6000, GOAL_ECAT_OBJCODE_ARRAY, GOAL_ECAT_DATATYPE_UNSIGNED8);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjNameAdd(pHdlEcat, 0x6000, "Input");
    }

    /************************************************/
    /* 0x6000:0x00 Highest sub-index supported     */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x02;
        uint8ValueMax = 0xFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x6000,
            0x00,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_MAN | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x6000, 0x00, "Highest sub-index supported");
    }

    /************************************************/
    /* 0x6000:0x01 Input 1                         */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x00;
        uint8ValueMax = 0xFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x6000,
            0x01,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_TXPDOMAPPING | EC_OBJATTR_OPT | EC_OBJATTR_NUMERIC | EC_OBJATTR_NO_LIMITS,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x6000, 0x01, "Input 1");
    }

    /************************************************/
    /* 0x6000:0x02 Input 2                         */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x00;
        uint8ValueMax = 0xFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x6000,
            0x02,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_TXPDOMAPPING | EC_OBJATTR_OPT | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x6000, 0x02, "Input 2");
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create object 0x6000");
    }

    /************************************************/
    /* 0x7000 - Output                              */
    /************************************************/
    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjAdd(pHdlEcat, 0x7000, GOAL_ECAT_OBJCODE_ARRAY, GOAL_ECAT_DATATYPE_UNSIGNED8);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdObjNameAdd(pHdlEcat, 0x7000, "Output");
    }

    /************************************************/
    /* 0x7000:0x00 Highest sub-index supported     */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x02;
        uint8ValueMax = 0xFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x7000,
            0x00,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_MAN | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x7000, 0x00, "Highest sub-index supported");
    }

    /************************************************/
    /* 0x7000:0x01 Output 1                        */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x00;
        uint8ValueMax = 0xFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x7000,
            0x01,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_WR | EC_OBJATTR_RXPDOMAPPING | EC_OBJATTR_OPT | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x7000, 0x01, "Output 1");
    }

    /************************************************/
    /* 0x7000:0x02 Output 2                        */
    /************************************************/
    if (GOAL_RES_OK(res)) {

        uint8ValueMin = 0x00;
        uint8ValueDef = 0x00;
        uint8ValueMax = 0xFF;

        res = goal_ecatdynOdSubIndexAdd(
            pHdlEcat,
            0x7000,
            0x02,
            GOAL_ECAT_DATATYPE_UNSIGNED8,
            EC_OBJATTR_RD | EC_OBJATTR_WR | EC_OBJATTR_RXPDOMAPPING | EC_OBJATTR_OPT | EC_OBJATTR_NUMERIC,
            (uint8_t *) &uint8ValueDef,
            (uint8_t *) &uint8ValueMin,
            (uint8_t *) &uint8ValueMax,
            1,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdSubIndexNameAdd(pHdlEcat, 0x7000, 0x02, "Output 2");
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create object 0x7000");
    }

    /* finish object dictionary creation */
    if (GOAL_RES_OK(res)) {
        res = goal_ecatdynOdFinish(pHdlEcat);
    }

    return res;
}
