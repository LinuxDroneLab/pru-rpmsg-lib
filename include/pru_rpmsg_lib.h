/*
 * pru_rpmsg_lib.h
 *
 *  Created on: 08 apr 2018
 *      Author: andrea
 */

#ifndef PRU_RPMSG_LIB_H_
#define PRU_RPMSG_LIB_H_
#include <stdint.h>
#include <pru_rpmsg.h>
#include <rsc_types.h>
#include "pru_virtio_ids.h"

typedef struct {
    uint32_t hostInt;
    uint32_t fromArmHost; /* Event number from ARM */
    struct pru_rpmsg_transport transport;
    uint8_t (*onReceived)(unsigned char* data, uint8_t dataBytes);
} PruRpmsgLibConfig;

uint8_t pru_rpmsg_lib_IsConfigured();
uint8_t pru_rpmsg_lib_IsInitialized();
uint8_t pru_rpmsg_lib_Init();
uint8_t pru_rpmsg_lib_Pulse();
uint8_t pru_rpmsg_lib_Conf(PruRpmsgLibConfig* config);
uint8_t pru_rpmsg_lib_Send(unsigned char* msg, uint8_t numBytes);


#endif /* PRU_RPMSG_LIB_H_ */
