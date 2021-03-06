/********************************************************************************************************************
 * \file MULTICAN_GW_TX_FIFO.h
 * \copyright Copyright (C) Infineon Technologies AG 2019
 *
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are solely in the form of
 * machine-executable object code generated by a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *********************************************************************************************************************/

#ifndef MULTICAN_GW_TX_FIFO_H_
#define MULTICAN_GW_TX_FIFO_H_
/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxMultican_Can.h"
#include "IfxMultican.h"
#include "IfxPort.h"                                             /* For GPIO Port Pin Control                        */

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
                                                                /*            USER CONFIGURABLE VALUE                */
                                                                /* ------------------------------------------------- */
#define NUMBER_OF_CAN_MESSAGES      7                           /* Define the number of CAN messages to be sent      */
                                                                /* ------------------------------------------------- */
#define GTW_SRC_MESSAGE_OBJECT_ID   (IfxMultican_MsgObjId)0     /* Gateway source message object ID                  */
#define GTW_DST_MESSAGE_OBJECT_ID   (IfxMultican_MsgObjId)1     /* Gateway destination message object ID             */
#define SLAVE_MESSAGE_OBJECT_ID     (IfxMultican_MsgObjId)2     /* FIFO slave message object ID                      */
#define SRC_MESSAGE_OBJECT_ID       (IfxMultican_MsgObjId)10    /* Source standard message object ID                 */
#define DST_MESSAGE_OBJECT_ID       (IfxMultican_MsgObjId)20    /* Destination standard message object ID            */
#define GTW_SRC_MESSAGE_ID          0x444                       /* Message ID that is used in arbitration phase      */
#define SRC_MESSAGE_ID              GTW_SRC_MESSAGE_ID          /* Should be same value as gateway source ID         */
#define GTW_DST_MESSAGE_ID          0x777                       /* Message ID that is used in arbitration phase      */
#define DST_MESSAGE_ID              GTW_DST_MESSAGE_ID          /* Should be same value as gateway destination ID    */
#define TX_FIFO_SIZE                2                           /* Number of slave message objects in FIFO structure */
#define RX_INTERRUPT_SRC_ID         IfxMultican_SrcId_1         /* Receive interrupt service request ID              */
#define PORT13_PIN0                 0                           /* LED1 used in TX ISR is connected to this pin      */
#define INVALID_DATA_VALUE          (uint32)0xDEADBEEF          /* Used to invalidate RX messages data content       */
#define INVALID_ID_VALUE            (uint32)0xFFFFFFFF          /* Used to invalidate RX messages ID value           */
#define INVALID_LENGTH_VALUE        (IfxMultican_DataLengthCode)0   /* Used to invalidate RX messages length value   */
#define ISR_PRIORITY_CAN_RX         1                           /* Define the CAN RX interrupt priority              */
#define NUMBER_OF_CAN_NODES         4                           /* Define the number of CAN nodes used in example    */
#define EXPECTED_CUR_POINTER_VALUE  ( SLAVE_MESSAGE_OBJECT_ID + \
                                        (NUMBER_OF_CAN_MESSAGES % TX_FIFO_SIZE) )   /* Define expected CUR pointer   */

/*********************************************************************************************************************/
/*--------------------------------------------------Data Structures--------------------------------------------------*/
/*********************************************************************************************************************/
typedef struct
{
    IfxMultican_Can                 can;             /* CAN module handle to HW module SFR set                       */
    IfxMultican_Can_Config          canConfig;       /* CAN module configuration structure                           */
    IfxMultican_Can_Node            canNode[NUMBER_OF_CAN_NODES];        /* CAN node array structure                 */
    IfxMultican_Can_NodeConfig      canNodeConfig;   /* CAN node configuration structure                             */
    IfxMultican_Can_MsgObj          canGtwSrcMsgObj; /* CAN gateway source message object handle data structure      */
    IfxMultican_Can_MsgObj          canGtwDstMsgObj; /* CAN gateway destination message object handle data structure */
    IfxMultican_Can_MsgObj          canSrcMsgObj;    /* CAN source standard message object handle data structure     */
    IfxMultican_Can_MsgObj          canDstMsgObj;    /* CAN destination standard message object handle data structure*/
    IfxMultican_Can_MsgObjConfig    canMsgObjConfig; /* CAN message object configuration structure                   */
    IfxMultican_Message             txMsg;           /* Transmitted CAN message structure                            */
    IfxMultican_Message             rxMsg[NUMBER_OF_CAN_MESSAGES];       /* Received CAN messages array              */
} multicanType;

typedef enum
{
    CanCommunicationStatus_Success = 0,
    CanCommunicationStatus_Error_noNewDataReceived,
    CanCommunicationStatus_Error_newDataButOneLost,
    CanCommunicationStatus_Error_notExpectedFifoCurPointer,
    CanCommunicationStatus_Error_notExpectedMessageId,
    CanCommunicationStatus_Error_notExpectedLengthCode,
    CanCommunicationStatus_Error_notExpectedData
} canCommunicationStatusType;

/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/
void canIsrRxHandler(void);
void initMultican(void);
void initLed(void);
void transmitCanMessages(void);
void verifyCanMessages(void);

#endif MULTICAN_GW_TX_FIFO_H_ */
