/*
** Purpose: Define configurations for the Demo application. This 
**          app exercises the OpenSatKit application framework and 
**          serves as a good starting point for trying new ideas.
**
** Notes:
**   1. These macros can only be built with the application and can't
**      have a platform scope because the same file name is used for
**      all applications following the object-based application design.
**
** License:
**   Written by David McComas, licensed under the copyleft GNU General
**   Public License (GPL).
**
** References:
**   1. OpenSatKit Object-based Application Developers Guide.
**   2. cFS Application Developer's Guide.
**
*/

#ifndef _app_cfg_
#define _app_cfg_

/*
** Includes
*/

#include "cfe.h"
#include "osk_demo_platform_cfg.h"
#include "osk_app_fw.h"

/******************************************************************************
** OSK Demo Application Macros
*/

#define  OSK_DEMO_MAJOR_VERSION      1
#define  OSK_DEMO_MINOR_VERSION      0
#define  OSK_DEMO_REVISION           0
#define  OSK_DEMO_MISSION_REV        0

/******************************************************************************
** Command Macros
*/

#define OSK_DEMO_DEMOBJ_TBL_LOAD_CMD_FC   (CMDMGR_APP_START_FC + 0)
#define OSK_DEMO_DEMOBJ_TBL_DUMP_CMD_FC   (CMDMGR_APP_START_FC + 1)
#define OSK_DEMO_ENA_DATA_LOAD_CMD_FC     (CMDMGR_APP_START_FC + 2)
#define OSK_DEMO_SET_TBL_INDEX_CMD_FC     (CMDMGR_APP_START_FC + 3)


/******************************************************************************
** Event Macros
** 
** Define the base event message IDs used by each object/component used by the
** application. There are no automated checks to ensure an ID range is not
** exceeded so it is the developer's responsibility to verify the ranges. 
*/

#define OSK_DEMO_BASE_EID   (APP_FW_APP_BASE_EID +  0)
#define DEMOBJ_BASE_EID     (APP_FW_APP_BASE_EID + 10)
#define XMLTBL_BASE_EID     (APP_FW_APP_BASE_EID + 20)
#define SCANFTBL_BASE_EID   (APP_FW_APP_BASE_EID + 30)
#define JSONTBL_BASE_EID    (APP_FW_APP_BASE_EID + 40)

/*
** One event ID is used for all initialization debug messages. Uncomment one of
** the OSK_DEMO_INIT_EVS_TYPE definitions. Set it to INFORMATION if you want to
** see the events during initialization. This is opposite to what you'd expect 
** because INFORMATION messages are enabled by default when an app is loaded.
*/

#define OSK_DEMO_INIT_DEBUG_EID 999
#define OSK_DEMO_INIT_EVS_TYPE CFE_EVS_DEBUG
//#define OSK_DEMO_INIT_EVS_TYPE CFE_EVS_INFORMATION


/******************************************************************************
** Example Table Configurations
**
** - They must be identical
*/

#define OSK_DEMO_TBL_MAX_ENTRY_ID 32
#define XMLTBL_MAX_ENTRY_ID      OSK_DEMO_TBL_MAX_ENTRY_ID
#define SCANFTBL_MAX_ENTRY_ID    OSK_DEMO_TBL_MAX_ENTRY_ID
#define JSONTBL_MAX_ENTRY_ID     OSK_DEMO_TBL_MAX_ENTRY_ID

#endif /* _app_cfg_ */
