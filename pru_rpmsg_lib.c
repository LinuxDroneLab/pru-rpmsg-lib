/*
 * pru_rpmsg_lib.c
 *
 *  Created on: 08 apr 2018
 *      Author: andrea
 */
#include <pru_rpmsg_lib.h>
#include <pru_intc.h>

volatile register unsigned __R31;

unsigned char pru_rpmsg_payload[RPMSG_BUF_SIZE];

uint8_t pru_rpmsg_lib_initialized = 0;
PruRpmsgLibConfig* pru_rpmsg_lib_config = 0;
unsigned short pru_rpmsg_lib_src;
unsigned short pru_rpmsg_lib_dst;
unsigned short pru_rpmsg_lib_len;

uint8_t pru_rpmsg_lib_IsConfigured()
{
    return (pru_rpmsg_lib_config != 0);
}
uint8_t pru_rpmsg_lib_IsInitialized()
{
    return pru_rpmsg_lib_initialized;
}
uint8_t pru_rpmsg_lib_Init()
{
    if(!pru_rpmsg_lib_IsInitialized()) {
        // TODO: how to init?
        pru_rpmsg_lib_initialized = 1;
    }
    return pru_rpmsg_lib_initialized;
}
uint8_t pru_rpmsg_lib_Pulse()
{
    if (pru_rpmsg_lib_IsConfigured())
    {
        if(pru_rpmsg_lib_Init()) {
            if (__R31 & pru_rpmsg_lib_config->hostInt)
            {
                if (pru_rpmsg_receive(&pru_rpmsg_lib_config->transport,
                                      &pru_rpmsg_lib_src, &pru_rpmsg_lib_dst,
                                      pru_rpmsg_payload,
                                      &pru_rpmsg_lib_len) == PRU_RPMSG_SUCCESS)
                {
                    return pru_rpmsg_lib_config->onReceived(pru_rpmsg_payload,
                                                            pru_rpmsg_lib_len);
                } else {
                    CT_INTC.SICR_bit.STS_CLR_IDX = pru_rpmsg_lib_config->fromArmHost;
                }
            } else {
                return 1;
            }
        }
    }
    return 0;
}
uint8_t pru_rpmsg_lib_Conf(PruRpmsgLibConfig* config)
{
    pru_rpmsg_lib_config = config;
    return 1;
}
uint8_t pru_rpmsg_lib_Send(unsigned char* msg, uint8_t numBytes)
{
    if(!pru_rpmsg_send(&pru_rpmsg_lib_config->transport, pru_rpmsg_lib_dst,
                   pru_rpmsg_lib_src, msg, numBytes)) {
        return 1;
    }
    return 0;
}

