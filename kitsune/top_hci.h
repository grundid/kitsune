/**
 * Top board control daemon
 */
#ifndef TOP_HCI_H
#define TOP_HCI_H

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	void (*on_message)(uint8_t * message_body, uint32_t body_length);
	void (*on_ack_failed)(void);	//ack fail
	void (*on_ack_success)(void);	//ack sucess
	void (*on_decode_failed)(void);
}hci_decode_handler_t;

void hci_init(void);
uint32_t hci_decode(uint8_t * raw, uint32_t length, const hci_decode_handler_t * handler);
uint8_t * hci_encode(uint8_t * body, uint32_t body_length, uint32_t * out_encoded);
uint16_t hci_crc16_compute(uint8_t * raw, uint32_t length);
uint16_t hci_crc16_compute_cont(uint8_t * raw, uint32_t length, const uint16_t * cont);
void hci_free(uint8_t * encoded_message);

#ifdef __cplusplus
}
#endif
    
#endif
