#include "pic16f145x_wiznet.h"


unsigned int wiz_reg_read(unsigned int  addr_hi,unsigned int  addr_lo)
{
    WIZ_CS = 0;
    // Address
    spi(addr_hi);
    spi(addr_lo);
    
    // OPCODE
    spi(0x00); // Read
    spi(0x01); // Data length = 1

    unsigned int miso = spi(0x00);
    WIZ_CS = 1;

    return (miso);
}

void wiz_reg_write(unsigned int  addr_hi,unsigned int  addr_lo, unsigned int mosi)
{
    WIZ_CS = 0;
    // Address
    spi(addr_hi);
    spi(addr_lo);

    // OPCODE
    spi(0x80); // Write
    spi(0x01); // Data length = 1

    spi(mosi);
    WIZ_CS = 1;
}

void wiz_send(unsigned int  addr_hi,unsigned int  addr_lo, unsigned int * miso, unsigned int length)
{

}

void wiz_write(unsigned int  addr_hi,unsigned int  addr_lo, unsigned int * mosi, unsigned int length)
{
    WIZ_CS = 0;

    // Address
    spi(addr_hi);
    spi(addr_lo);

    // OPCODE
    spi(0x80); // Write
    spi(length); // Data length = 1

    for(int i=0;i<length;i++)
        spi(mosi[i]);

    WIZ_CS = 1;
}

void wiz_init(wiz_conf_t conf){
    // Software reset
    wiz_reg_write(REG_MSB, REG_MODE, 0x80);
    __delay_us(100);
    while (wiz_reg_read(REG_MSB, REG_MODE) & 0x80)
        __delay_us(100);

    // Disable sockets from expressing IRQ on pin
    wiz_reg_write(REG_MSB, REG_INTERRUPT_MASK, 0x00);

    // Configure Mode Register - Ping enabled
    wiz_reg_write(REG_MSB, REG_MODE, 0x00);

    // Configure Subnet
    wiz_write(REG_MSB, REG_SUBNET_MASK_IP, conf.subnet, REG_SUBNET_MASK_IP_LENGTH);

    // Configure Gateway
    wiz_write(REG_MSB, REG_GATEWAY_IP, conf.gateway, REG_GATEWAY_IP_LENGTH);

    // Configure IP
    wiz_write(REG_MSB, REG_SOURCE_ADDR_IP, conf.ip, REG_SOURCE_ADDR_IP_LENGTH);

    // Configure MAC
    wiz_write(REG_MSB, REG_SOURCE_ADDR_MAC, conf.mac, REG_SOURCE_ADDR_MAC_LENGTH);


    // Trusting default values for RTR and RCR (0x07D0, 0x08)

    wiz_reg_write(REG_MSB, REG_PHY_STAT, 0x00);
    wiz_reg_write(REG_MSB, REG_SOCK_INTR_MASK, 0x00);  // Don't trigger IRQ for any system-wide errors e.g. IP conflict

    int i;
    unsigned int sock;
    // Close all sockets
    for (i=0; i < MAX_SOCK_NUM; i++) {
        sock = SOCK_BASE_MSB+i;
        wiz_reg_write(sock,SOCK_REG_COMMAND, SOCK_CLOSE);
        wiz_reg_write(sock,SOCK_REG_MODE, 0x00);
    }

    // Open all sockets as UDP
    for (i=0; i < MAX_SOCK_NUM; i++) {
        sock = SOCK_BASE_MSB+i;
        wiz_reg_write(sock,SOCK_REG_MODE, 0x02);
        wiz_reg_write(sock,SOCK_REG_SOURCE_PORT0, 0x13);
        wiz_reg_write(sock,SOCK_REG_SOURCE_PORT1, (0x81+i));

        wiz_write(sock, SOCK_REG_DEST_ADDR_IP, conf.source_ip, SOCK_REG_DEST_ADDR_IP_LENGTH);

        wiz_write(sock,SOCK_REG_DEST_PORT, conf.source_port, PORT_LENGTH);
        //Sn_PORT0 = source_port;
        wiz_reg_write(sock,SOCK_REG_COMMAND, SOCK_OPEN);
    }

    /* wait until Sn_SR is changed to SOCK_UDP */
    __delay_us(100);

}