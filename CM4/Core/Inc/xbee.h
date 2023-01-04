#ifndef XBEE_H_
#define XBEE_H_

#include "stm32h7xx_hal.h"


#define DELIMIT_XBEE 0x7E
#define RECEIVE_XBEE 0x90
#define TRANSMIT_XBEE 0x10
#define ADDR_64_INDX 8
#define ADDR_16_INDX 2

enum FRAME_SEND {
	END = 0,
	RESUME = 1,
	ACKNOWLEDGE = 2
};

enum FRAME_STATE {
	FRAME_START_DELIM = 0,
	FRAME_LENGTH,
	FRAME_API,
	FRAME_ADDR,
	FRAME_OPT,
	FRAME_DATA,
	FRAME_CHKSM
};

typedef struct  {
	uint8_t delimit;    /* 1 byte */
	uint8_t length;     /* 2 bytes */
	uint8_t api;        /* 1 byte */
	uint64_t srcAddr64; /* 8 bytes */
	uint16_t srcAddr16; /* 2 bytes */
	uint8_t rcvOpt;     /* 1 byte */
	uint8_t data;       /* 2 bytes */
	uint8_t chksum;		/* 1 byte */
	int flag;
} xbeeFrame;

/*
 * @Purpose: This function initializes the sensor module by sending an initial frame to begin data transfer.
 * @Param: frame is the struct defined in xbee.h. The function initializes the struct.
*/
void xbee_init(void);

/*
 * @Purpose: The purpose of this function is to read incoming frames from external xbee devices. The function takes an incoming frame string, disassembles it into components, and assigns them to their respective struct variables to assess what kind of frame is being sent
 * @Params: inFrame is the incoming data that is read from UART buffer.
 */
void frameRead(void);

/*
 * @Purpose: The purpose of this function is to generate a frame to send to the external xbee devices. The sent frame is either an acknowledgment frame (this frame acknowledges that an alarm was triggered) or a clear frame (this clears the alarm).
 * @Params: data is the data that is going to be sent in the frame; api defines the type of frame we want to send.
*/
void frameGenerate(void);

/*
 * @Purpose: The purpose of this function is to flush the buffer in order to prevent data loss and/or resetting and instance.
 * @Params: None
*/
void frameClear(void);

#endif /* XBEE_H_ */
