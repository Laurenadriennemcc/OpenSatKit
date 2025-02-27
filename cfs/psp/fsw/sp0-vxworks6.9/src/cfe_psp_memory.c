/******************************************************************************
 ** File:  cfe_psp_memory.c
 **
 **      AiTech SP0-100 vxWorks 6.9 Version
 **
 **      Copyright (c) 2004-2011, United States Government as represented by 
 **      Administrator for The National Aeronautics and Space Administration. 
 **      All Rights Reserved.
 **
 **      This is governed by the NASA Open Source Agreement and may be used,
 **      distributed and modified only pursuant to the terms of that agreement.
 **
 **
 ** Purpose:
 **   cFE PSP Memory related functions. This is the implementation of the cFE
 **   memory areas that have to be preserved, and the API that is designed to allow
 **   acccess to them. It also contains memory related routines to return the
 **   address of the kernel code used in the cFE checksum.
 **
 ** History:
 **   2006/09/29  A. Cudmore      | vxWorks 6.2 MCP750 version
 **   2015/08/08  S. Duran        | Modified for SP0-100 board
 **
 ******************************************************************************/

/*
 **  Include Files
 */
#include <stdio.h>
#include <string.h>
#include <vxWorks.h>
#include <sysLib.h>
#include <moduleLib.h>

/*
 ** cFE includes
 */
#include "common_types.h"
#include "osapi.h"
#include "cfe_es.h"            /* For reset types */
#include "cfe_platform_cfg.h"  /* for processor ID */

/*
 ** Types and prototypes for this module
 */
#include "cfe_psp.h"
#include "cfe_psp_memory.h"

/*
 ** Define the cFE Core loadable module name
 */
#define CFE_MODULE_NAME "cfe-core.o"

/*
 **  External Declarations
 */
extern unsigned int GetWrsKernelTextStart(void);
extern unsigned int GetWrsKernelTextEnd(void);

/*
 ** Global variables
 */

/*
 ** Pointer to the vxWorks USER_RESERVED_MEMORY area
 ** The sizes of each memory area is defined in os_processor.h for this architecture.
 */
CFE_PSP_ReservedMemory_t *CFE_PSP_ReservedMemoryPtr;

/*
 *********************************************************************************
 ** CDS related functions
 *********************************************************************************
 */

/******************************************************************************
 **  Function: CFE_PSP_GetCDSSize
 **
 **  Purpose:
 **    This function fetches the size of the OS Critical Data Store area.
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    (none)
 */

int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS)
{
    int32 return_code;

    if (SizeOfCDS == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        *SizeOfCDS = CFE_PSP_CDS_SIZE;
        return_code = CFE_PSP_SUCCESS;
    }
    return (return_code);
}

/******************************************************************************
 **  Function: CFE_PSP_WriteToCDS
 **
 **  Purpose:
 **    This function writes to the CDS Block.
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    (none)
 */
int32 CFE_PSP_WriteToCDS(void *PtrToDataToWrite, uint32 CDSOffset,
        uint32 NumBytes)
{
    uint8 *CopyPtr = NULL;
    int32 return_code = CFE_PSP_SUCCESS;

    if (PtrToDataToWrite == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        if ((CDSOffset < CFE_PSP_CDS_SIZE)
                && ((CDSOffset + NumBytes) <= CFE_PSP_CDS_SIZE))
        {
            CopyPtr = &(CFE_PSP_ReservedMemoryPtr->CDSMemory[CDSOffset]);
            memcpy(CopyPtr, (char *) PtrToDataToWrite, NumBytes);

            return_code = CFE_PSP_SUCCESS;
        }
        else
        {
            return_code = CFE_PSP_ERROR;
        }

    } /* end if PtrToDataToWrite == NULL */

    return (return_code);
}

/******************************************************************************
 **  Function: CFE_PSP_ReadFromCDS
 **
 **  Purpose:
 **   This function reads from the CDS Block
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    (none)
 */

int32 CFE_PSP_ReadFromCDS(void *PtrToDataToRead, uint32 CDSOffset,
        uint32 NumBytes)
{
    uint8 *CopyPtr = NULL;
    int32 return_code = CFE_PSP_SUCCESS;

    if (PtrToDataToRead == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        if ((CDSOffset < CFE_PSP_CDS_SIZE)
                && ((CDSOffset + NumBytes) <= CFE_PSP_CDS_SIZE))
        {
            CopyPtr = &(CFE_PSP_ReservedMemoryPtr->CDSMemory[CDSOffset]);
            memcpy((char *) PtrToDataToRead, CopyPtr, NumBytes);

            return_code = CFE_PSP_SUCCESS;
        }
        else
        {
            return_code = CFE_PSP_ERROR;
        }

    } /* end if PtrToDataToWrite == NULL */

    return (return_code);

}

/*
 *********************************************************************************
 ** ES Reset Area related functions
 *********************************************************************************
 */

/******************************************************************************
 **  Function: CFE_PSP_GetResetArea
 **
 **  Purpose:
 **     This function returns the location and size of the ES Reset information area.
 **     This area is preserved during a processor reset and is used to store the
 **     ER Log, System Log and reset related variables
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    CFE_PSP_SUCCESS
 **    CFE_PSP_ERROR
 */
int32 CFE_PSP_GetResetArea(cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea)
{
    int32 return_code = CFE_PSP_SUCCESS;

    if ((PtrToResetArea == NULL) || (SizeOfResetArea == NULL))
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        *PtrToResetArea = (cpuaddr)&(CFE_PSP_ReservedMemoryPtr->ResetMemory[0]);
        *SizeOfResetArea = CFE_PSP_RESET_AREA_SIZE;
        return_code = CFE_PSP_SUCCESS;
    }

    return (return_code);
}

/*
 *********************************************************************************
 ** ES User Reserved Area related functions
 *********************************************************************************
 */

/******************************************************************************
 **  Function: CFE_PSP_GetUserReservedArea
 **
 **  Purpose:
 **    This function returns the location and size of the memory used for the cFE
 **     User reserved area.
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    CFE_PSP_SUCCESS
 **    CFE_PSP_ERROR
 */
int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea, uint32 *SizeOfUserArea)
{
    int32 return_code = CFE_PSP_SUCCESS;

    if ((PtrToUserArea == NULL) || (SizeOfUserArea == NULL))
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        *PtrToUserArea =
                (cpuaddr)&(CFE_PSP_ReservedMemoryPtr->UserReservedMemory[0]);
        *SizeOfUserArea = CFE_PSP_USER_RESERVED_SIZE;
        return_code = CFE_PSP_SUCCESS;
    }

    return (return_code);
}

/*
 *********************************************************************************
 ** ES Volatile disk memory related functions
 *********************************************************************************
 */

/******************************************************************************
 **  Function: CFE_PSP_GetVolatileDiskMem
 **
 **  Purpose:
 **    This function returns the location and size of the memory used for the cFE
 **     volatile disk.
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    CFE_PSP_SUCCESS
 **    CFE_PSP_ERROR
 */
int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk)
{
    int32 return_code = CFE_PSP_SUCCESS;

    if ((PtrToVolDisk == NULL) || (SizeOfVolDisk == NULL))
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        *PtrToVolDisk =
                (cpuaddr)&(CFE_PSP_ReservedMemoryPtr->VolatileDiskMemory[0]);
        *SizeOfVolDisk = CFE_PSP_VOLATILE_DISK_SIZE;
        return_code = CFE_PSP_SUCCESS;

    }

    return (return_code);

}

/*
 *********************************************************************************
 ** ES BSP Top Level Reserved memory initialization
 *********************************************************************************
 */

/******************************************************************************
 **  Function: CFE_PSP_InitProcessorReservedMemory
 **
 **  Purpose:
 **    This function performs the top level reserved memory initialization.
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    CFE_PSP_SUCCESS
 */
int32 CFE_PSP_InitProcessorReservedMemory(uint32 RestartType)
{
    int32 return_code = CFE_PSP_SUCCESS;

    if (RestartType != CFE_ES_PROCESSOR_RESET)
    {
        printf("CFE_PSP: Clearing Processor Reserved Memory.\n");
        memset((void *) CFE_PSP_ReservedMemoryPtr, 0,
                sizeof(CFE_PSP_ReservedMemory_t));
    }

    CFE_PSP_ReservedMemoryPtr->bsp_last_reset_type =
            CFE_PSP_ReservedMemoryPtr->bsp_reset_type;
    CFE_PSP_ReservedMemoryPtr->bsp_reset_type = CFE_ES_PROCESSOR_RESET;

    return (return_code);
}

/*
 *********************************************************************************
 ** ES BSP kernel memory segment functions
 *********************************************************************************
 */

/******************************************************************************
 **  Function: CFE_PSP_GetKernelTextSegmentInfo
 **
 **  Purpose:
 **    This function returns the start and end address of the kernel text segment.
 **     It may not be implemented on all architectures.
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    CFE_PSP_SUCCESS
 **    CFE_PSP_ERROR
 */
int32 CFE_PSP_GetKernelTextSegmentInfo(cpuaddr *PtrToKernelSegment,
        uint32 *SizeOfKernelSegment)
{
    int32 return_code = CFE_PSP_SUCCESS;
    cpuaddr StartAddress = 0;
    cpuaddr EndAddress = 0;

    if ((PtrToKernelSegment == NULL) || (SizeOfKernelSegment == NULL))
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        /*
         ** Get the kernel start and end
         ** addresses from the BSP, because the
         ** symbol table does not contain the symbols we need for this
         */
        StartAddress = (cpuaddr) GetWrsKernelTextStart();
        EndAddress = (cpuaddr) GetWrsKernelTextEnd();

        *PtrToKernelSegment = (cpuaddr) StartAddress;
        *SizeOfKernelSegment = (uint32) (EndAddress - StartAddress);

        return_code = CFE_PSP_SUCCESS;
    }

    return (return_code);
}

/******************************************************************************
 **  Function: CFE_PSP_GetCFETextSegmentInfo
 **
 **  Purpose:
 **    This function returns the start and end address of the CFE text segment.
 **     It may not be implemented on all architectures.
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    CFE_PSP_SUCCESS
 **    CFE_PSP_ERROR
 */
int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment,
        uint32 *SizeOfCFESegment)
{
    int32 return_code = CFE_PSP_SUCCESS;
    STATUS status;
    MODULE_ID cFEModuleId;
    MODULE_INFO cFEModuleInfo;

    if ((PtrToCFESegment == NULL) || (SizeOfCFESegment == NULL))
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        cFEModuleId = moduleFindByName(CFE_MODULE_NAME);

        if (cFEModuleId == NULL)
        {
            return_code = CFE_PSP_ERROR;
        }
        else
        {
            status = moduleInfoGet(cFEModuleId, &cFEModuleInfo);
            if (status != ERROR)
            {
                *PtrToCFESegment = (cpuaddr) (cFEModuleInfo.segInfo.textAddr);
                *SizeOfCFESegment = (uint32) (cFEModuleInfo.segInfo.textSize);
                return_code = CFE_PSP_SUCCESS;
            }
            else
            {
                return_code = CFE_PSP_ERROR;
            }
        }
    }
    return (return_code);
}

