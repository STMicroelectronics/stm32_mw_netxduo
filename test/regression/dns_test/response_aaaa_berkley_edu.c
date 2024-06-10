/*
No.     Time        Source                Destination           Protocol Length Info
    132 168.635407  192.2.2.1             192.2.2.240           DNS      100    Standard query response 0x0003  AAAA 2607:f140:0:81::f

Frame 132: 100 bytes on wire (800 bits), 100 bytes captured (800 bits)
Ethernet II, Src: TyanComp_45:7a:c6 (00:e0:81:45:7a:c6), Dst: Dell_8e:ec:b5 (d4:be:d9:8e:ec:b5)
Internet Protocol Version 4, Src: 192.2.2.1 (192.2.2.1), Dst: 192.2.2.240 (192.2.2.240)
User Datagram Protocol, Src Port: domain (53), Dst Port: 55272 (55272)
Domain Name System (response)
    [Request In: 131]
    [Time: 0.000208000 seconds]
    Transaction ID: 0x0003
    Flags: 0x8180 Standard query response, No error
    Questions: 1
    Answer RRs: 1
    Authority RRs: 0
    Additional RRs: 0
    Queries
    Answers
        berkeley.edu: type AAAA, class IN, addr 2607:f140:0:81::f
            Name: berkeley.edu
            Type: AAAA (IPv6 address)
            Class: IN (0x0001)
            Time to live: 59 minutes, 53 seconds
            Data length: 16
            Addr: 2607:f140:0:81::f
*/

/* Frame (100 bytes) */
char response_aaaa_berkley_edu_pkt[100] = {
0xd4, 0xbe, 0xd9, 0x8e, 0xec, 0xb5, 0x00, 0xe0, /* ........ */
0x81, 0x45, 0x7a, 0xc6, 0x08, 0x00, 0x45, 0x00, /* .Ez...E. */
0x00, 0x56, 0x4d, 0xc3, 0x00, 0x00, 0x80, 0x11, /* .VM..... */
0x67, 0xde, 0xc0, 0x02, 0x02, 0x01, 0xc0, 0x02, /* g....... */
0x02, 0xf0, 0x00, 0x35, 0xd7, 0xe8, 0x00, 0x42, /* ...5...B */
0xa1, 0x91, 0x00, 0x03, 0x81, 0x80, 0x00, 0x01, /* ........ */
0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x62, /* .......b */
0x65, 0x72, 0x6b, 0x65, 0x6c, 0x65, 0x79, 0x03, /* erkeley. */
0x65, 0x64, 0x75, 0x00, 0x00, 0x1c, 0x00, 0x01, /* edu..... */
0xc0, 0x0c, 0x00, 0x1c, 0x00, 0x01, 0x00, 0x00, /* ........ */
0x0e, 0x09, 0x00, 0x10, 0x26, 0x07, 0xf1, 0x40, /* ....&..@ */
0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x0f                          /* .... */
};

int response_aaaa_berkley_edu_pkt_size = 100;
