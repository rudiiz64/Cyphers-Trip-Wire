/* FILE: xbee.c
 * PURPOSE: This source file will contain the main functions required to decompose and generate a frame from an xBee transceiver in order to acquire or store essential data contained within.
 * AUTHOR: Rodolfo Zaragoza
 * REV, DATE: 0.5, 12/12/22
 */

#include <stdio.h>
#include <stm32h7xx_hal.h>
#include <string.h>
#include "xbee.h"
#include "UartRingbuffer.h"

xbeeFrame frame;

void xbee_init(UART_HandleTypeDef *huart){
	Ringbuf_init(huart);
	frame.delimit = DELIMIT_XBEE;
	frame.length = 0xE;
	frame.api = TRANSMIT_XBEE;
	frame.srcAddr64 = RESUME;
	frame.srcAddr16 = RESUME;
	frame.rcvOpt = END;
	frame.data = ACKNOWLEDGE;
	frame.chksum = 0x6E;
}

void frameRead (void){
	uint8_t frame_read_state = FRAME_START_DELIM;

	switch (frame_read_state){
	case FRAME_START_DELIM:
		if (Uart_read() == DELIMIT_XBEE){
			frame_read_state = FRAME_LENGTH;
		}
		else {
			break;
		}

	case FRAME_LENGTH:
		if (IsDataAvailable() >= 2){
			frame.length = Uart_read();
			frame.length = (frame.length << 1) | Uart_read();
			frame_read_state = FRAME_API;
		}
		else {
			break;
		}
	case FRAME_API:
		if (IsDataAvailable()){
			frame.api = Uart_read();
			frame_read_state = FRAME_ADDR;
		}
		else {
			break;
		}
	case FRAME_ADDR:
		if (IsDataAvailable() >= frame.length){
			int index64 = ADDR_64_INDX;
			int index16 = ADDR_16_INDX;
			// For loop to store 64-bit address
			for (int i = 0; i < index64; i++){
				uint8_t serialRead = Uart_read();
				frame.srcAddr64 = (frame.srcAddr64 << index64) | serialRead;
				index64--;
			}

			// For loop to store 16-bit address
			for (int i = 0; i < index16; i++){
				uint8_t serialRead = Uart_read();
				frame.srcAddr16 = (frame.srcAddr16 << index16) | serialRead;
				index16--;
			}
			frame_read_state = FRAME_OPT;
		}
		else {
			break;
		}
	case FRAME_OPT:
		if (IsDataAvailable()){
			frame.rcvOpt = Uart_read();
			frame_read_state = FRAME_DATA;
		}
		else {
			break;
		}
	case FRAME_DATA:
		frame.length = frame.length - 12;
		if (frame.length > 8){
			frame.data = (uint8_t) Uart_read();
		}
		else {
			break;
		}
		frame_read_state = FRAME_CHKSM;
	case FRAME_CHKSM:
		frame.chksum = Uart_read();
		frame_read_state = FRAME_START_DELIM;
	}
}

void frameGenerate(UART_HandleTypeDef *huart){
	Uart_write(frame.data, huart);
}

void frameClear(){
	frame.delimit = 0;
	frame.length = 0;
	frame.api = 0;
	frame.srcAddr64 = 0;
	frame.srcAddr16 = 0;
	frame.rcvOpt = 0;
	frame.data = 0;
	frame.chksum = 0;
}
