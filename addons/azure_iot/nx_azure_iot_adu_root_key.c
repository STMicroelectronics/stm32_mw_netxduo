/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/

#include "nx_azure_iot_adu_agent.h"

/* Update manifest is meant for ADU devices to know what files are needed to be downloaded and installed.
   The update manifest is signed by ADU so devices can trust that the content wasnot altered during the 
   transmission.

   ADU will leverage two types of keys - Root Key(s) and Signing Key(s). Signing keys will be used to 
   digest sign the update manifest and root keys will be used to sign the signing keys.
   
   *Root key - used to sign signing public key; root public key is hardcoded in ADU devices.
   *Signing key - used to sign update manifest; signing public key signed with the master key is included in digest signature header.
*/

/* Root keys.  */

/* ADU.200702.R: root production key from 7/2/2020  */
const UCHAR adu_root_key_200702_r_kid[] = "ADU.200702.R";
const UCHAR adu_root_key_200702_r_n[] = {0x00, 0xd5, 0x42, 0x2e, 0xaf, 0x11, 0x54, 0xa3, 0x50, 0x65, 0x87, 0xa2, 0x4d, 0x5b, 0xba,
                                         0x1a, 0xfb, 0xa9, 0x32, 0xdf, 0xe9, 0x99, 0x5f, 0x05, 0x45, 0xc8, 0xaf, 0xbd, 0x35, 0x1d,
                                         0x89, 0xe8, 0x27, 0x27, 0x58, 0xa3, 0xa8, 0xee, 0xc5, 0xc5, 0x1e, 0x4f, 0xf7, 0x92, 0xa6,
                                         0x12, 0x06, 0x7d, 0x3d, 0x7d, 0xb0, 0x07, 0xf6, 0x2c, 0x7f, 0xde, 0x6d, 0x2a, 0xf5, 0xbc,
                                         0x49, 0xbc, 0x15, 0xef, 0xf0, 0x81, 0xcb, 0x3f, 0x88, 0x4f, 0x27, 0x1d, 0x88, 0x71, 0x28,
                                         0x60, 0x08, 0xb6, 0x19, 0xd2, 0xd2, 0x39, 0xd0, 0x05, 0x1f, 0x3c, 0x76, 0x86, 0x71, 0xbb,
                                         0x59, 0x58, 0xbc, 0xb1, 0x88, 0x7b, 0xab, 0x56, 0x28, 0xbf, 0x31, 0x73, 0x44, 0x32, 0x10,
                                         0xfd, 0x3d, 0xd3, 0x96, 0x5c, 0xff, 0x4e, 0x5c, 0xb3, 0x6b, 0xff, 0x8b, 0x84, 0x9b, 0x8b,
                                         0x80, 0xb8, 0x49, 0xd0, 0x7d, 0xfa, 0xd6, 0x40, 0x58, 0x76, 0x4d, 0xc0, 0x72, 0x27, 0x75,
                                         0xcb, 0x9a, 0x2f, 0x9b, 0xb4, 0x9f, 0x0f, 0x25, 0xf1, 0x1c, 0xc5, 0x1b, 0x0b, 0x5a, 0x30,
                                         0x7d, 0x2f, 0xb8, 0xef, 0xa7, 0x26, 0x58, 0x53, 0xaf, 0xd5, 0x1d, 0x55, 0x01, 0x51, 0x0d,
                                         0xe9, 0x1b, 0xa2, 0x0f, 0x3f, 0xd7, 0xe9, 0x1d, 0x20, 0x41, 0xa6, 0xe6, 0x14, 0x0a, 0xae,
                                         0xfe, 0xf2, 0x1c, 0x2a, 0xd6, 0xe4, 0x04, 0x7b, 0xf6, 0x14, 0x7e, 0xec, 0x0f, 0x97, 0x83,
                                         0xfa, 0x58, 0xfa, 0x81, 0x36, 0x21, 0xb9, 0xa3, 0x2b, 0xfa, 0xd9, 0x61, 0x0b, 0x1a, 0x94,
                                         0xf7, 0xc1, 0xbe, 0x7f, 0x40, 0x14, 0x4a, 0xc9, 0xfa, 0x35, 0x7f, 0xef, 0x66, 0x70, 0x00,
                                         0xb1, 0xfd, 0xdb, 0xd7, 0x61, 0x0d, 0x3b, 0x58, 0x74, 0x67, 0x94, 0x89, 0x75, 0x76, 0x96,
                                         0x7c, 0x91, 0x87, 0xd2, 0x8e, 0x11, 0x97, 0xee, 0x7b, 0x87, 0x6c, 0x9a, 0x2f, 0x45, 0xd8,
                                         0x65, 0x3f, 0x52, 0x70, 0x98, 0x2a, 0xcb, 0xc8, 0x04, 0x63, 0xf5, 0xc9, 0x47, 0xcf, 0x70,
                                         0xf4, 0xed, 0x64, 0xa7, 0x74, 0xa5, 0x23, 0x8f, 0xb6, 0xed, 0xf7, 0x1c, 0xd3, 0xb0, 0x1c,
                                         0x64, 0x57, 0x12, 0x5a, 0xa9, 0x81, 0x84, 0x1f, 0xa0, 0xe7, 0x50, 0x19, 0x96, 0xb4, 0x82,
                                         0xb1, 0xac, 0x48, 0xe3, 0xe1, 0x32, 0x82, 0xcb, 0x40, 0x1f, 0xac, 0xc4, 0x59, 0xbc, 0x10,
                                         0x34, 0x51, 0x82, 0xf9, 0x28, 0x8d, 0xa8, 0x1e, 0x9b, 0xf5, 0x79, 0x45, 0x75, 0xb2, 0xdc,
                                         0x9a, 0x11, 0x43, 0x08, 0xbe, 0x61, 0xcc, 0x9a, 0xc4, 0xcb, 0x77, 0x36, 0xff, 0x83, 0xdd,
                                         0xa8, 0x71, 0x4f, 0x51, 0x8e, 0x0e, 0x7b, 0x4d, 0xfa, 0x79, 0x98, 0x8d, 0xbe, 0xfc, 0x82,
                                         0x7e, 0x40, 0x48, 0xa9, 0x12, 0x01, 0xa8, 0xd9, 0x7e, 0xf3, 0xa5, 0x1b, 0xf1, 0xfb, 0x90,
                                         0x77, 0x3e, 0x40, 0x87, 0x18, 0xc9, 0xab, 0xd9, 0xf7, 0x79};
const UCHAR adu_root_key_200702_r_e[] = {0x01, 0x00, 0x01};


/* ADU.200703.R */
const UCHAR adu_root_key_200703_r_kid[] = "ADU.200703.R";
const UCHAR adu_root_key_200703_r_n[] = {0x00, 0xb2, 0xa3, 0xb2, 0x74, 0x16, 0xfa, 0xbb, 0x20, 0xf9, 0x52, 0x76, 0xe6, 0x27, 0x3e,
                                         0x80, 0x41, 0xc6, 0xfe, 0xcf, 0x30, 0xf9, 0xc8, 0x96, 0xf5, 0x59, 0x0a, 0xaa, 0x81, 0xe7,
                                         0x51, 0x83, 0x8a, 0xc4, 0xf5, 0x17, 0x3a, 0x2f, 0x2a, 0xe6, 0x57, 0xd4, 0x71, 0xce, 0x8a,
                                         0x3d, 0xef, 0x9a, 0x55, 0x76, 0x3e, 0x99, 0xe2, 0xc2, 0xae, 0x4c, 0xee, 0x2d, 0xb8, 0x78,
                                         0xf5, 0xa2, 0x4e, 0x28, 0xf2, 0x9c, 0x4e, 0x39, 0x65, 0xbc, 0xec, 0xe4, 0x0d, 0xe5, 0xe3,
                                         0x38, 0xa8, 0x59, 0xab, 0x08, 0xa4, 0x1b, 0xb4, 0xf4, 0xa0, 0x52, 0xa3, 0x38, 0xb3, 0x46,
                                         0x21, 0x13, 0xcc, 0x3c, 0x68, 0x06, 0xde, 0xfe, 0x00, 0xa6, 0x92, 0x6e, 0xde, 0x4c, 0x47,
                                         0x10, 0xd6, 0x1c, 0x9c, 0x24, 0xf5, 0xcd, 0x70, 0xe1, 0xf5, 0x6a, 0x7c, 0x68, 0x13, 0x1d,
                                         0xe1, 0xc5, 0xf6, 0xa8, 0x4f, 0x21, 0x9f, 0x86, 0x7c, 0x44, 0xc5, 0x8a, 0x99, 0x1c, 0xc5,
                                         0xd3, 0x06, 0x9b, 0x5a, 0x71, 0x9d, 0x09, 0x1c, 0xc3, 0x64, 0x31, 0x6a, 0xc5, 0x17, 0x95,
                                         0x1d, 0x5d, 0x2a, 0xf1, 0x55, 0xc7, 0x66, 0xd4, 0xe8, 0xf5, 0xd9, 0xa9, 0x5b, 0x8c, 0xa2,
                                         0x6c, 0x62, 0x60, 0x05, 0x37, 0xd7, 0x32, 0xb0, 0x73, 0xcb, 0xf7, 0x4b, 0x36, 0x27, 0x24,
                                         0x21, 0x8c, 0x38, 0x0a, 0xb8, 0x18, 0xfe, 0xf5, 0x15, 0x60, 0x35, 0x8b, 0x35, 0xef, 0x1e,
                                         0x0f, 0x88, 0xa6, 0x13, 0x8d, 0x7b, 0x7d, 0xef, 0xb3, 0xe7, 0xb0, 0xc9, 0xa6, 0x1c, 0x70,
                                         0x7b, 0xcc, 0xf2, 0x29, 0x8b, 0x87, 0xf7, 0xbd, 0x9d, 0xb6, 0x88, 0x6f, 0xac, 0x73, 0xff,
                                         0x72, 0xf2, 0xef, 0x48, 0x27, 0x96, 0x72, 0x86, 0x06, 0xa2, 0x5c, 0xe3, 0x7d, 0xce, 0xb0,
                                         0x9e, 0xe5, 0xc2, 0xd9, 0x4e, 0xc4, 0xf3, 0x7f, 0x78, 0x07, 0x4b, 0x65, 0x88, 0x45, 0x0c,
                                         0x11, 0xe5, 0x96, 0x56, 0x34, 0x88, 0x2d, 0x16, 0x0e, 0x59, 0x42, 0xd2, 0xf7, 0xd9, 0xed,
                                         0x1d, 0xed, 0xc9, 0x37, 0x77, 0x44, 0x7e, 0xe3, 0x84, 0x36, 0x9f, 0x58, 0x13, 0xef, 0x6f,
                                         0xe4, 0xc3, 0x44, 0xd4, 0x77, 0x06, 0x8a, 0xcf, 0x5b, 0xc8, 0x80, 0x1c, 0xa2, 0x98, 0x65,
                                         0x0b, 0x35, 0xdc, 0x73, 0xc8, 0x69, 0xd0, 0x5e, 0xe8, 0x25, 0x43, 0x9e, 0xf6, 0xd8, 0xab,
                                         0x05, 0xaf, 0x51, 0x29, 0x23, 0x55, 0x40, 0x58, 0x10, 0xea, 0xb8, 0xe2, 0xcd, 0x5d, 0x79,
                                         0xcc, 0xec, 0xdf, 0xb4, 0x5b, 0x98, 0xc7, 0xfa, 0xe3, 0xd2, 0x6c, 0x26, 0xce, 0x2e, 0x2c,
                                         0x56, 0xe0, 0xcf, 0x8d, 0xee, 0xfd, 0x93, 0x12, 0x2f, 0x00, 0x49, 0x8d, 0x1c, 0x82, 0x38,
                                         0x56, 0xa6, 0x5d, 0x79, 0x44, 0x4a, 0x1a, 0xf3, 0xdc, 0x16, 0x10, 0xb3, 0xc1, 0x2d, 0x27,
                                         0x11, 0xfe, 0x1b, 0x98, 0x05, 0xe4, 0xa3, 0x60, 0x31, 0x99};
const UCHAR adu_root_key_200703_r_e[] = {0x01, 0x00, 0x01};

/* RSA Root key for verifying manifest.  */
const NX_AZURE_IOT_ADU_AGENT_RSA_ROOT_KEY _nx_azure_iot_adu_agent_rsa_root_key_list[] =
{
    {
        /* kid */
        adu_root_key_200702_r_kid,
        sizeof(adu_root_key_200702_r_kid) - 1,

        /* n */
        adu_root_key_200702_r_n,
        sizeof(adu_root_key_200702_r_n),

        /* e */
        adu_root_key_200702_r_e,
        sizeof(adu_root_key_200702_r_e),
    },
    {
        /* kid */
        adu_root_key_200703_r_kid,
        sizeof(adu_root_key_200703_r_kid) - 1,

        /* n */
        adu_root_key_200703_r_n,
        sizeof(adu_root_key_200703_r_n),

        /* e */
        adu_root_key_200703_r_e,
        sizeof(adu_root_key_200703_r_e),
    }
};

const UINT _nx_azure_iot_adu_agent_rsa_root_key_list_size = (sizeof(_nx_azure_iot_adu_agent_rsa_root_key_list) / sizeof(NX_AZURE_IOT_ADU_AGENT_RSA_ROOT_KEY));
