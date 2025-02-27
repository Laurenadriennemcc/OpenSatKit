/*================================================================================*
** File:  ut_oscore_queue_test.h
** Owner: Alan Cudmore
** Date:  April 2013
**================================================================================*/

#ifndef _UT_OSCORE_QUEUE_TEST_H_
#define _UT_OSCORE_QUEUE_TEST_H_

/*--------------------------------------------------------------------------------*
** Includes
**--------------------------------------------------------------------------------*/

#include "ut_os_stubs.h"

/*--------------------------------------------------------------------------------*
** Macros
**--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*
** Data types
**--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*
** External global variables
**--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*
** Global variables
**--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*
** Function prototypes
**--------------------------------------------------------------------------------*/

void UT_os_queue_create_test(void);
void UT_os_queue_delete_test(void);
void UT_os_queue_put_test(void);
void UT_os_queue_get_test(void);
void UT_os_queue_get_id_by_name_test(void);
void UT_os_queue_get_info_test(void);

/*--------------------------------------------------------------------------------*/

#endif  /* _UT_OSCORE_QUEUE_TEST_H_ */

/*================================================================================*
** End of File: ut_oscore_queue_test.h
**================================================================================*/
