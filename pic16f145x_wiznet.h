/* 
 * File:   pic16f145x_wiznet.h
 * Author: mathewleising
 *
 * Created on January 14, 2015, 11:01 AM
 */

#ifndef PIC16F145X_WIZNET_H
#define	PIC16F145X_WIZNET_H

#include <xc.h>
#include "pic16f145x_spi.h"
#include "conf.h"

//#ifdef	__cplusplus
//extern "C" {
//#endif

#define MAX_SOCK_NUM 8

#define IDM_OR  0x8000
#define IDM_AR0 0x8001
#define IDM_AR1 0x8002
#define IDM_DR  0x8003

//socket states
#define SOCK_OPEN                        0x01
#define SOCK_LISTEN                      0x02
#define SOCK_CONNECT                     0x04
#define SOCK_DISCON                      0x08
#define SOCK_CLOSE                       0x10
#define SOCK_SEND                        0x20
#define SOCK_SEND_MAC                    0x21
#define SOCK_SEND_KEEP                   0x22
#define SOCK_RECV                        0x40

//socket statuses
#define SOCK_CLOSED                 0x00
#define SOCK_INIT                   0x13
#define SOCK_LISTENING              0x14
#define SOCK_ESTABLISHED            0x17
#define SOCK_CLOSE_WAIT             0x1C
#define SOCK_UDP                    0x22
#define SOCK_IPRAW                  0x32
#define SOCK_MACRAW                 0x42
#define SOCK_PPPOE                  0x5F
#define SOCK_SYNSENT                0x15
#define SOCK_SYNRECV                0x16
#define SOCK_FIN_WAIT               0x18
#define SOCK_CLOSING                0x1A
#define SOCK_TIME_WAIT              0x1B
#define SOCK_LAST_ACK               0x1D
#define SOCK_ARP1                   0x11
#define SOCK_ARP2                   0x21
#define SOCK_ARP3                   0x31

//#define CHIP_BASE_ADDRESS           0x0000
//#define RX_MEMORY_BASE_ADDRESS      0x6000
//#define TX_MEMORY_BASE_ADDRESS      0x4000

#define MAX_RX_SIZE                 128
#define ETHERNET_BUFF_SIZE          64

/*The register addresses*/
//Common registers
#define REG_MSB                     0x00
#define REG_MODE                    0x00

#define REG_GATEWAY_IP              0x01
#define REG_GATEWAY_IP_LENGTH       0x04

#define REG_SUBNET_MASK_IP          0x05
#define REG_SUBNET_MASK_IP_LENGTH   0x04

#define REG_SOURCE_ADDR_MAC         0x09
#define REG_SOURCE_ADDR_MAC_LENGTH  0x06

#define REG_SOURCE_ADDR_IP          0x0F
#define REG_SOURCE_ADDR_IP_LENGTH   0x04

#define REG_INTERRUPT_SOURCE        0x15
#define REG_INTERRUPT_MASK          0x16
#define REG_RETRY_TIME_VALUE0       0x17
#define REG_RETRY_TIME_VALUE1       0x18
#define REG_RETRY_COUNT             0x19
//#define REG_RX_MEM_SIZE             0x1A
//#define REG_TX_MEM_SIZE             0x1B
#define REG_PPPOE_AUTH_TYPE0        0x1C
#define REG_PPPOE_AUTH_TYPE1        0x1D
#define REG_PPPOE_ALGO              0x1E
#define REG_CHIP_VERSION            0x1E
#define REG_PPP_TIMER               0x28
#define REG_PPP_MAGIC               0x29
//#define REG_DEST_UNREACHABLE_IP0    0x2A
//#define REG_DEST_UNREACHABLE_IP1    0x2B
//#define REG_DEST_UNREACHABLE_IP2    0x2C
//#define REG_DEST_UNREACHABLE_IP3    0x2D
//#define REG_UNREACHABLE_PORT0       0x2E
//#define REG_UNREACHABLE_PORT1       0x2F
#define REG_SOCK_INTR               0x34
#define REG_PHY_STAT                0x35
#define REG_SOCK_INTR_MASK          0x36

#define PORT_LENGTH                 0x02
////Base register addresses for sockets
//#define SOCK0_REGS_BASE_ADDR        0x0400
//#define SOCK1_REGS_BASE_ADDR        0x0500
//#define SOCK2_REGS_BASE_ADDR        0x0600
//#define SOCK3_REGS_BASE_ADDR        0x0700

//
#define SOCK_BASE_MSB               0x40
//W5200 has 8 Sockets
#define SOCK0                       0
#define SOCK1                       1
#define SOCK2                       2
#define SOCK3                       3
#define SOCK4                       4
#define SOCK5                       5
#define SOCK6                       6
#define SOCK7                       7

//Register offsets for socket registers
#define SOCK_REG_MODE                 0x00
#define SOCK_REG_COMMAND              0x01
#define SOCK_REG_INTERRUPT            0x02
#define SOCK_REG_STATUS               0x03
#define SOCK_REG_SOURCE_PORT0         0x04
#define SOCK_REG_SOURCE_PORT1         0x05

#define SOCK_REG_DEST_ADDR_MAC        0x06
#define SOCK_REG_DEST_ADDR_MAC_LENGTH 0x06

#define SOCK_REG_DEST_ADDR_IP         0x0C
#define SOCK_REG_DEST_ADDR_IP_LENGTH  0x04

#define SOCK_REG_DEST_PORT            0x10

#define SOCK_REG_MAX_SEG_SIZE0        0x12
#define SOCK_REG_MAX_SEG_SIZE1        0x13
#define SOCK_REG_IP_PROTOCOL          0x14
#define SOCK_REG_IP_TOS               0x15
#define SOCK_REG_IP_TTL               0x16
#define SOCK_REG_TX_FREE_SIZE0        0x20
#define SOCK_REG_TX_FREE_SIZE1        0x21
#define SOCK_REG_TX_READ_POINTER0     0x22
#define SOCK_REG_TX_READ_POINTER1     0x23
#define SOCK_REG_TX_WRITE_POINTER0    0x24
#define SOCK_REG_TX_WRITE_POINTER1    0x25
#define SOCK_REG_RX_RECEIVED_SIZE0    0x26
#define SOCK_REG_RX_RECEIVED_SIZE1    0x27
#define SOCK_REG_RX_READ_POINTER0     0x28
#define SOCK_REG_RX_READ_POINTER1     0x29

extern unsigned int gateway[REG_GATEWAY_IP_LENGTH];
extern unsigned int mac[REG_SOURCE_ADDR_MAC_LENGTH];
extern unsigned int ip[REG_SOURCE_ADDR_IP_LENGTH];
extern unsigned int subnet[REG_SUBNET_MASK_IP_LENGTH];
extern unsigned int source_ip[REG_SOURCE_ADDR_IP_LENGTH];
extern unsigned int source_port[PORT_LENGTH];

void wiz_init();
unsigned int wiz_reg_read(unsigned int  addr_hi,unsigned int  addr_lo);
void wiz_reg_write(unsigned int  addr_hi,unsigned int  addr_lo, unsigned int data);
void wiz_send(unsigned int  addr_hi,unsigned int  addr_lo, unsigned int * data, unsigned int length);
void wiz_write(unsigned int  addr_hi,unsigned int  addr_lo, unsigned int *  data, unsigned int length);

//#ifdef	__cplusplus
//}
//#endif

#endif	/* PIC16F145X_WIZNET_H */

