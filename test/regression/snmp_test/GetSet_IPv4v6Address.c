/* SNMP_TESTING_GetSet_IPv4Addresses_LargeIntegers.pcap */

/* Frame 420 Set IPv4 address request 241.254.3.129 (89 bytes) */
 const unsigned char set_ipv4_address_request_pkt[47] = {
0x30, 0x2d, 0x02, 0x01, 0x00, 0x04, /* .X0-.... */
0x07, 0x70, 0x72, 0x69, 0x76, 0x61, 0x74, 0x65, /* .private */
0xa3, 0x1f, 0x02, 0x01, 0x7a, 0x02, 0x01, 0x00, /* ....z... */
0x02, 0x01, 0x00, 0x30, 0x14, 0x30, 0x12, 0x06, /* ...0.0.. */
0x0a, 0x2b, 0x06, 0x01, 0x02, 0x01, 0x03, 0x01, /* .+...... */
0x01, 0x03, 0x00, 0x40, 0x04, 0xf1, 0xfe, 0x03, /* ...@.... */
0x81                                            /* . */
};

 int  set_ipv4_address_request_size = 47;

/* Frame 430  Get Request (84 bytes) */
 const unsigned char get_ipv4_address_request_pkt[42] = {
0x30, 0x28, 0x02, 0x01, 0x00, 0x04, /* .S0(.... */
0x06, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0xa0, /* .public. */
0x1b, 0x02, 0x01, 0x7b, 0x02, 0x01, 0x00, 0x02, /* ...{.... */
0x01, 0x00, 0x30, 0x10, 0x30, 0x0e, 0x06, 0x0a, /* ..0.0... */
0x2b, 0x06, 0x01, 0x02, 0x01, 0x03, 0x01, 0x01, /* +....... */
0x03, 0x00, 0x05, 0x00                          /* .... */
};


 int  get_ipv4_address_request_size = 42;

/* SNMP Testing_GetSet_IPv6_Addresses.pcapng */

/* Frame 88 set IPv6 address 2001:0db7:0:f101:abcd:0064:0: 0207  (102 bytes) */
 const unsigned char set_ipv6_address_request_pkt[60] = {
0x30, 0x3a, 0x02, 0x01, 0x00, 0x04, /* .e0:.... */
0x07, 0x70, 0x72, 0x69, 0x76, 0x61, 0x74, 0x65, /* .private */
0xa3, 0x2c, 0x02, 0x02, 0x00, 0x80, 0x02, 0x01, /* .,...... */
0x00, 0x02, 0x01, 0x00, 0x30, 0x20, 0x30, 0x1e, /* ....0 0. */
0x06, 0x0a, 0x2b, 0x06, 0x01, 0x02, 0x01, 0x03, /* ..+..... */
0x01, 0x01, 0x03, 0x01, 0x04, 0x10, 0x20, 0x01, /* ...... . */
0x0d, 0xb7, 0x00, 0x00, 0xf1, 0x01, 0xab, 0xcd, /* ........ */
0x00, 0x64, 0x00, 0x00, 0x02, 0x07              /* .d.... */
};

int set_ipv6_address_request_size = 60;

/* Frame 183  Get IPv6 address request (85 bytes) */
 const unsigned char get_ipv6_address_request_pkt[43] = {
0x30, 0x29, 0x02, 0x01, 0x00, 0x04, /* .T0).... */
0x06, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0xa0, /* .public. */
0x1c, 0x02, 0x02, 0x00, 0x81, 0x02, 0x01, 0x00, /* ........ */
0x02, 0x01, 0x00, 0x30, 0x10, 0x30, 0x0e, 0x06, /* ...0.0.. */
0x0a, 0x2b, 0x06, 0x01, 0x02, 0x01, 0x03, 0x01, /* .+...... */
0x01, 0x03, 0x01, 0x05, 0x00                    /* ..... */
};

int get_ipv6_address_request_size = 43;

