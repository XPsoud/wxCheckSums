#include <wx/wx.h>
#include <wx/image.h>
#include <wx/mstream.h>

unsigned char wxWidgets_png[] = {
0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
0x00,0x00,0x00,0x54,0x00,0x00,0x00,0x4c,0x08,0x06,0x00,0x00,0x00,0xf3,0xee,0x90,
0x37,0x00,0x00,0x00,0x09,0x70,0x48,0x59,0x73,0x00,0x00,0x0d,0xd5,0x00,0x00,0x0d,
0xd5,0x01,0x3d,0xd6,0x58,0xf1,0x00,0x00,0x10,0xb2,0x49,0x44,0x41,0x54,0x78,0x01,
0xec,0x9c,0x7d,0x6c,0x5b,0xd5,0x7b,0xc7,0xbf,0xe7,0xfa,0xd6,0x71,0xec,0xb8,0x4d,
0x52,0x0a,0x6d,0x49,0x47,0x5f,0xda,0xb4,0x65,0xdd,0x68,0x9a,0x96,0x74,0x03,0xd4,
0x0d,0x6d,0x68,0x9a,0xb4,0x0d,0x31,0x51,0x54,0x09,0xfe,0xd8,0x86,0x04,0xff,0xa0,
0x4d,0x02,0x34,0x09,0x89,0x6d,0x7f,0x30,0x7e,0x2a,0x95,0x2a,0x0d,0x69,0x62,0x4c,
0xdb,0x90,0x7e,0x6c,0x42,0xeb,0xc4,0xc6,0x1f,0xd3,0x10,0x03,0x01,0x9d,0xca,0x4a,
0xa7,0xf4,0xa5,0x29,0x05,0x5a,0xa0,0xea,0x4b,0xd7,0x97,0xbc,0x24,0x8e,0xaf,0x7d,
0x6d,0xdf,0x97,0xfb,0xec,0x1c,0x5f,0x3f,0xd2,0xed,0x91,0xaf,0x1b,0xc7,0x6e,0x32,
0x2c,0x8e,0xf4,0xd5,0x79,0xce,0xa9,0x63,0xfb,0x7e,0xf2,0x3c,0xe7,0x39,0x2f,0xa7,
0x11,0x44,0x84,0x9f,0x4a,0xfb,0x8a,0x89,0x45,0x28,0x6f,0xbc,0x71,0x2e,0x6b,0x18,
0xa5,0x47,0x83,0x80,0x86,0x89,0xb0,0x44,0xf5,0x05,0xc1,0xad,0x52,0x85,0x48,0xd9,
0xf1,0xe2,0x9f,0xab,0xf9,0xc4,0x84,0xeb,0xd2,0xe1,0xb7,0xde,0x1a,0x3e,0x41,0x8b,
0xe8,0x25,0x0b,0xea,0xa1,0x07,0x0e,0x9c,0xdc,0x93,0xcb,0x95,0xfe,0xd6,0xb6,0xdd,
0x8d,0x00,0x19,0x0c,0x43,0xa9,0x5d,0x36,0x60,0x94,0x32,0x99,0xd4,0xbf,0xdb,0xb6,
0xfd,0x87,0x87,0x0e,0xfd,0x5a,0xa1,0x63,0x81,0xbe,0xfe,0xfa,0xe8,0x5b,0x93,0x93,
0xc5,0x67,0x89,0xc8,0x54,0x00,0x92,0x49,0x13,0xfd,0xfd,0x3d,0x30,0x0c,0x43,0xf7,
0xc4,0xa6,0xda,0x6c,0xdb,0xb6,0x83,0xd9,0xd9,0xa2,0xb4,0xa9,0xda,0x4e,0x24,0xcc,
0x9b,0xcb,0x96,0xf5,0x3e,0xf3,0xce,0x3b,0xdb,0x3e,0xee,0x38,0xa0,0xfb,0xf7,0x9f,
0x78,0xe5,0xc6,0x8d,0xfc,0x5f,0xaa,0x07,0x1d,0x18,0xe8,0xc3,0xc3,0x0f,0x6f,0xc2,
0xb2,0x65,0x69,0xa8,0xb6,0xef,0x87,0x6a,0x87,0xed,0xba,0x01,0xae,0x5e,0x9d,0xc0,
0xd8,0xd8,0xf7,0xa8,0x54,0x5c,0x09,0xd5,0x98,0x4d,0xa5,0xba,0xb7,0x1c,0x3a,0xb4,
0xeb,0x46,0xc7,0x00,0x3d,0x78,0xf0,0xf4,0xe0,0x95,0x2b,0xb3,0xa7,0x7c,0x3f,0xe8,
0x1e,0x1a,0xfa,0x05,0x8c,0x8c,0xac,0x07,0x7b,0x97,0xe7,0xa1,0xed,0x50,0x95,0x4a,
0x25,0x07,0x47,0x8e,0x9c,0x80,0x6d,0x97,0xd1,0xdd,0xdd,0xfd,0xd9,0x07,0x1f,0x8c,
0x3c,0x8a,0x05,0x2a,0x06,0xee,0x70,0x99,0x9d,0xad,0xbc,0xe6,0x79,0x41,0x77,0x6f,
0x6f,0x0f,0x86,0x87,0xd7,0x29,0x88,0xf2,0x21,0x21,0x3d,0x14,0x48,0xa7,0x43,0x10,
0xae,0x1b,0xca,0x71,0xda,0x63,0x0b,0x91,0xc4,0x96,0x2d,0x9b,0x11,0x04,0x02,0x96,
0x55,0xfa,0xf5,0x27,0x9e,0x38,0xfb,0x40,0xc7,0x64,0x79,0xcb,0x72,0x7f,0x49,0x79,
0xcd,0xe6,0xcd,0xab,0x24,0x4c,0xa1,0x20,0x56,0x55,0x2e,0x87,0xde,0x24,0x84,0x82,
0xc1,0x1e,0xc6,0x35,0xab,0x71,0x7f,0x23,0x3b,0x9b,0xed,0x43,0x77,0x77,0x06,0x96,
0x55,0x90,0x6d,0xe7,0x37,0x00,0x9c,0xfe,0xd1,0x03,0xdd,0xbb,0xf7,0x5f,0x12,0xcb,
0x97,0xdf,0xbd,0x56,0x3d,0x64,0x5f,0x5f,0xb6,0xea,0x3d,0x99,0x0c,0x87,0x7b,0x54,
0x0c,0xa4,0x31,0xc8,0x26,0xfb,0x25,0xd0,0x2c,0x72,0xb9,0x02,0x4a,0x25,0x7f,0xa4,
0x23,0x3c,0x74,0xfb,0xf6,0xad,0x77,0x5d,0xbc,0x38,0x99,0x22,0x52,0x5e,0x99,0xae,
0x02,0x35,0x0c,0xce,0xd0,0x9c,0x48,0x14,0x50,0x55,0xb7,0x0f,0x24,0xb7,0x4d,0xb3,
0xab,0xf6,0xcb,0xf3,0x57,0x77,0x04,0xd0,0x25,0x4b,0x0c,0xc1,0xf0,0x14,0x30,0xa2,
0xe8,0x83,0x33,0x48,0x96,0x06,0xa6,0x65,0x3b,0xea,0xf9,0x42,0x74,0x04,0x50,0xdb,
0x0e,0x1f,0x88,0x28,0x04,0xc6,0x70,0xa3,0x0f,0xab,0x6a,0xc7,0xe1,0x76,0x7b,0xa1,
0x7a,0x1e,0xf7,0x75,0xcc,0xd2,0xb3,0x3e,0x50,0xdf,0xd7,0xc3,0x5d,0xa9,0x9d,0xde,
0xc9,0x40,0xd9,0xee,0x20,0xa0,0x0c,0x51,0x79,0xa1,0x69,0xea,0x50,0x17,0x22,0xe4,
0x55,0xdd,0x21,0x40,0x8b,0x45,0xf6,0x50,0xf6,0x16,0xdd,0x83,0xf4,0x90,0x6f,0x2e,
0xe9,0x94,0x4a,0xa1,0x78,0x0e,0xaa,0x8a,0x10,0xa1,0x0c,0x83,0xdf,0x53,0xd9,0x1d,
0x1a,0xf2,0x86,0x11,0x9f,0x94,0x94,0x3d,0x57,0x90,0x85,0x82,0x5a,0x30,0x84,0x30,
0x55,0x5b,0x5f,0xe7,0xf3,0xeb,0xd4,0x6b,0x14,0xec,0x44,0xa2,0x03,0x43,0x3e,0x02,
0x54,0xf7,0xd0,0xc6,0x63,0xa8,0xd6,0x9e,0x9a,0x02,0xf2,0xf9,0xc6,0x20,0x59,0x95,
0x8a,0x82,0xae,0xfa,0x8d,0xee,0x0e,0x0b,0x79,0xf6,0x14,0x06,0xd3,0xdc,0x18,0xca,
0xf0,0xc7,0xc7,0x15,0xa0,0x28,0xbc,0x78,0x7b,0xd9,0xb2,0x82,0x5c,0x7e,0x5e,0x42,
0x32,0x79,0x03,0x3d,0x3d,0x89,0x7b,0x4e,0x9d,0xfa,0xf4,0x65,0x20,0x00,0x40,0x50,
0x75,0xf3,0x36,0xb9,0x86,0x81,0xd1,0x52,0xc9,0x3a,0x3a,0x32,0xf2,0xf7,0xfe,0xe2,
0x87,0x7c,0x04,0x58,0xfc,0x18,0x5a,0x1f,0xaa,0x5a,0xa6,0x4e,0x4c,0xf0,0x7b,0xc4,
0x83,0x14,0x22,0xc0,0xe3,0x8f,0xff,0xa7,0x04,0xf9,0x25,0xba,0xba,0x66,0x15,0x04,
0x06,0xb2,0x3a,0x97,0xa3,0x37,0x22,0xed,0x68,0xdd,0x94,0x2d,0x04,0x9c,0xa3,0x47,
0x9f,0xfe,0x3a,0x95,0x4a,0x3d,0x37,0x34,0xf4,0x77,0xff,0xb3,0x80,0x40,0x15,0x88,
0x84,0xa1,0x60,0x98,0x26,0x87,0xbc,0x9e,0x94,0xa2,0x50,0xeb,0x7b,0xa7,0x6d,0x03,
0x93,0x93,0xea,0x35,0x8d,0x3d,0x72,0xcd,0x9a,0x71,0x3c,0xf5,0xd4,0xcf,0x91,0xcd,
0xfe,0x2f,0x03,0x90,0x50,0x33,0x72,0x71,0x91,0x8c,0xf1,0x3a,0x1d,0x2c,0x8b,0xea,
0xd6,0x44,0x81,0x8c,0x8e,0x3c,0x82,0xc0,0x4b,0x56,0x2a,0xee,0x76,0xc7,0x29,0x1c,
0x39,0x7e,0xfc,0x99,0x37,0x87,0x87,0xdf,0x7d,0x69,0xc1,0x80,0x5a,0x96,0x10,0x2a,
0x31,0xa4,0x52,0x0c,0xb4,0xb9,0x95,0x92,0x4a,0x3e,0xd3,0xd3,0xca,0x6e,0x1c,0xe6,
0xa6,0xe9,0xe0,0xe9,0xa7,0xdf,0x96,0x9f,0x33,0x85,0x44,0x22,0x81,0x75,0xeb,0x76,
0xe3,0x9e,0x7b,0x36,0x46,0x60,0xfa,0x4a,0xcd,0xda,0x5a,0x5b,0x41,0x75,0x91,0xcf,
0x4f,0xe1,0x87,0x1f,0xce,0xc8,0x7a,0x7a,0x89,0x65,0x4d,0xbf,0x78,0xe2,0xc4,0xbe,
0x89,0x1d,0x3b,0xde,0xdb,0xbf,0x60,0xdb,0x77,0x41,0x10,0x8e,0xa5,0x57,0xae,0x44,
0xb3,0x32,0x87,0xb8,0xbe,0xf5,0xc6,0x0a,0x93,0x8f,0x0a,0x73,0x7d,0x03,0x25,0xba,
0xee,0xe7,0xfe,0x7d,0xfb,0xfe,0x4d,0xc2,0x9c,0xac,0x02,0xdc,0xb9,0xf3,0x49,0x0c,
0x0c,0xdc,0x2f,0x6d,0xe5,0x2b,0x9e,0x94,0x23,0xe5,0x2a,0x35,0x69,0xeb,0x72,0x20,
0x84,0x27,0xc7,0xe6,0x2c,0x86,0x86,0x1e,0xc4,0xbd,0xf7,0x0e,0x54,0x41,0x17,0x0a,
0xb9,0x3f,0x1b,0x1b,0xdb,0xb7,0x7e,0x41,0xb3,0x3c,0x51,0xe8,0x6d,0xe5,0x72,0x98,
0x79,0x01,0x3d,0xcb,0x33,0xa4,0xf0,0xdf,0x73,0x39,0xce,0xce,0x91,0xf5,0xbf,0xe6,
0x9d,0xdc,0xdf,0xdf,0x3f,0x8b,0x4d,0x9b,0xbe,0xa8,0x7a,0xd0,0xe0,0xe0,0x43,0xd5,
0x2d,0x3b,0x40,0x48,0xf5,0xd4,0xbc,0x2b,0x2f,0x55,0xd1,0xbd,0xae,0x25,0x5b,0x08,
0x1f,0x1b,0x36,0x6c,0x40,0x2e,0x77,0x53,0x3a,0x8b,0x95,0xae,0x54,0x8a,0xca,0x43,
0x9f,0xbc,0x2d,0xd0,0xa3,0xaf,0xbe,0xda,0xdb,0x95,0xc9,0xec,0x81,0x10,0x43,0x42,
0x88,0xae,0xba,0x87,0x39,0x0d,0xfa,0xfe,0x60,0x65,0x5f,0xf6,0x95,0xef,0x76,0xdf,
0x92,0x94,0x6c,0x5b,0x41,0x54,0xc0,0x42,0xc0,0x8e,0x13,0xda,0xc5,0x22,0xd7,0x8d,
0x41,0xea,0xfd,0x9b,0x37,0x5f,0x80,0x6c,0x55,0xb7,0xea,0x56,0xac,0xb8,0xaf,0xe6,
0x4d,0x77,0xd5,0xbc,0xd3,0xae,0xc1,0xf5,0x55,0x7f,0x5b,0xa1,0x1a,0x86,0x2f,0x23,
0x61,0x35,0xce,0x9d,0xfb,0x06,0xae,0x5b,0x7e,0xa0,0xa1,0x87,0x9e,0x3e,0x78,0xf0,
0x57,0x8a,0xd3,0xd3,0xef,0x38,0x85,0xc2,0xa6,0x4a,0xa1,0x60,0xcc,0xf7,0x28,0xd2,
0xf7,0x2d,0x59,0x85,0x40,0x3d,0x8f,0xc7,0xd0,0xd0,0xe6,0xf1,0xf1,0xfa,0x75,0x25,
0x05,0x56,0x07,0x36,0x37,0x7b,0xed,0xda,0x8b,0x90,0x96,0xda,0x50,0xae,0x41,0xeb,
0x92,0x32,0x22,0x0f,0xef,0xd5,0x60,0x38,0x1a,0x98,0xd8,0xb1,0x72,0xce,0xe0,0xb3,
0xd9,0x6e,0x65,0x4b,0xa0,0xde,0x7d,0xc7,0x8e,0xfd,0x66,0x62,0x64,0xe4,0x63,0x5f,
0x07,0x8a,0xe3,0x3f,0xfb,0xd9,0x81,0xc2,0xc4,0xc4,0x1f,0x13,0xd1,0x92,0x2a,0x71,
0xd3,0x44,0xcf,0xf2,0xe5,0x30,0x84,0x68,0xfa,0x38,0xd2,0x74,0xba,0x23,0xde,0xc5,
0x30,0xa2,0x6d,0x9e,0xf4,0x73,0x16,0x6f,0x1e,0x6a,0x6f,0xef,0x24,0xa4,0x25,0x3d,
0xb4,0xa7,0x06,0x34,0xad,0xda,0x1a,0x50,0x57,0x49,0x87,0xd2,0x32,0xe0,0x54,0x2a,
0x51,0xad,0x89,0x28,0x99,0xc9,0x74,0xa9,0xf0,0xb8,0x70,0x0b,0xd0,0x13,0xfb,0xf7,
0x3f,0x6f,0x8d,0x8f,0xbf,0x04,0x22,0xf4,0xae,0x5c,0x89,0x8d,0x8f,0x3c,0x82,0x9e,
0xfe,0xfe,0x79,0xef,0x50,0x4c,0x5a,0x09,0x04,0x9f,0x80,0x3d,0x14,0x42,0xd4,0x9f,
0x8b,0x72,0x72,0x22,0x6a,0x1e,0x2a,0x3f,0x9c,0x10,0x3e,0x7b,0x61,0x2c,0xd0,0xd6,
0xb3,0xbd,0xde,0xef,0x44,0xa6,0x5b,0x9e,0xe0,0x90,0x67,0x98,0xf7,0x16,0xc6,0xc7,
0xf7,0xab,0x6f,0xba,0xfa,0xfe,0xfb,0x31,0xb8,0x67,0x0f,0x3f,0xa9,0x7e,0x44,0x39,
0x77,0xa8,0x8e,0xaf,0xcc,0xe8,0x5a,0x5e,0x77,0x6a,0xed,0x08,0xa4,0x59,0xa8,0xaa,
0x0e,0x34,0x70,0x5e,0xf4,0x21,0x23,0xfd,0x8e,0x0e,0xac,0x0d,0x80,0xbd,0x9a,0x4d,
0xa1,0x1d,0x05,0x1a,0x54,0x2a,0xaf,0x06,0x8e,0xb3,0x34,0xd5,0xd3,0x83,0x0d,0x23,
0x23,0xe0,0x03,0x20,0x98,0x66,0x98,0x3d,0x2c,0x4b,0x0d,0x74,0x4d,0x9d,0x9c,0xf5,
0x99,0x3e,0x12,0xa2,0x5f,0x71,0x95,0x6f,0x61,0xcb,0xa9,0xcc,0xd2,0xea,0xb8,0x99,
0x4e,0x47,0x7f,0x8c,0x57,0x4a,0x51,0xd0,0x3a,0xbc,0xf8,0x7e,0x22,0x86,0xa7,0x01,
0x65,0xc8,0x2c,0x2d,0xe4,0xdb,0x63,0xbb,0x11,0xa0,0xfe,0xad,0xf3,0x50,0xb7,0x58,
0x7c,0x40,0x7d,0xd3,0x55,0x83,0x83,0x48,0x84,0x83,0x67,0x08,0x94,0x07,0x3c,0x40,
0x9f,0x89,0x2b,0x12,0xa1,0xb8,0xad,0x29,0xe1,0xbb,0x58,0x99,0x15,0xb5,0x9b,0x1d,
0x85,0xea,0xdb,0x8c,0x8e,0xd6,0x9f,0x8b,0x2a,0x9b,0xc5,0x6d,0xdf,0xbf,0x7d,0x3f,
0x11,0x3f,0x60,0x1c,0xb4,0xc6,0x73,0xcb,0x16,0x6d,0xed,0xb3,0x00,0x33,0x02,0x74,
0xa3,0x7a,0xca,0xa5,0x7d,0x7d,0xe1,0x37,0xef,0xef,0x67,0x77,0x88,0x3e,0x4d,0xd3,
0x3b,0xc1,0x1b,0x97,0x7b,0xb8,0x30,0x91,0x40,0x2e,0x77,0x03,0xa9,0xd4,0x2a,0x9c,
0x3d,0x1b,0x1e,0x25,0xab,0x8f,0xa9,0x54,0xd4,0xb2,0x92,0x47,0x95,0xe6,0xe5,0xfb,
0xba,0x87,0x3a,0x9a,0x87,0xfa,0xba,0x87,0x36,0x95,0x8c,0x88,0x3c,0x78,0x9e,0x8d,
0x20,0xa8,0x48,0x39,0xb5,0xe9,0x12,0xa4,0x8c,0x6a,0x0d,0x50,0x7c,0xc8,0xfb,0xe5,
0x72,0xaf,0x10,0x42,0xae,0x7f,0xbb,0x78,0x6b,0x88,0x61,0xb6,0x74,0xf8,0xf3,0xe2,
0x83,0x97,0xf0,0xd9,0xf9,0x0d,0xd5,0x75,0xf0,0xd4,0xd4,0x25,0x64,0xb3,0x6b,0x71,
0xf8,0x30,0x6f,0x00,0x73,0xa8,0xcf,0x5f,0x44,0x11,0x20,0x4d,0x8f,0xa1,0xf1,0x4b,
0xcc,0x4a,0x25,0x27,0x95,0x8f,0x44,0x00,0x69,0xbf,0x04,0x42,0x10,0x10,0x7c,0xbf,
0x8c,0x84,0x62,0xa5,0x7b,0x28,0x82,0x40,0x40,0x88,0xa8,0x17,0xc6,0x2f,0x69,0x9a,
0xc8,0xf6,0x9b,0x7a,0xa6,0xf1,0xec,0xf6,0x3e,0xbc,0x79,0xac,0x0f,0x33,0x33,0x17,
0x61,0xdb,0x96,0x84,0xba,0x41,0x02,0x4d,0x33,0x94,0x16,0x81,0x46,0x61,0x32,0x50,
0x9f,0xd5,0xf4,0x18,0xea,0xfb,0x25,0x14,0x8b,0x13,0x08,0x02,0x37,0x16,0x24,0xf7,
0x13,0x79,0x6a,0x52,0x5f,0xf3,0xb1,0x84,0xa9,0x03,0x0d,0xeb,0x28,0x34,0xee,0xd7,
0x43,0xbe,0xc9,0x6c,0xff,0xf2,0xf6,0xb3,0xb8,0x9a,0x1b,0xc2,0xbf,0x7e,0x93,0x91,
0x40,0xa7,0x50,0x2c,0x4e,0x55,0xaf,0xcb,0x24,0x12,0x19,0x10,0x89,0xc6,0x6b,0x84,
0xd8,0x36,0xd7,0x79,0x2d,0xe4,0xa3,0xa0,0x3c,0xee,0x9f,0xd3,0xb4,0xc9,0x75,0x0b,
0xea,0xfb,0x29,0x50,0x1a,0xc8,0x38,0xdb,0xab,0x81,0x0d,0xa4,0xb4,0x69,0x13,0x7b,
0x24,0x03,0xe5,0x76,0x9d,0xad,0xa1,0x79,0xdd,0x93,0xf9,0xab,0xdd,0x47,0xf1,0x7b,
0x72,0xa9,0xf6,0xf2,0x91,0xad,0xb8,0x2a,0x19,0xf8,0xe4,0xc0,0x75,0x1d,0x05,0xa5,
0x15,0x69,0xeb,0xf4,0x39,0x64,0xf9,0x18,0xa8,0xe5,0xf2,0x8c,0x54,0x6e,0x8e,0x20,
0xd9,0xf6,0x34,0xaf,0xd5,0x81,0x0a,0xc1,0xd9,0x9b,0x3d,0x54,0xdf,0xb4,0xac,0x07,
0x74,0xce,0x80,0x1f,0xbd,0xeb,0x02,0x8e,0xff,0xee,0xf7,0x98,0x28,0x2e,0xc1,0x67,
0xd7,0x07,0xf0,0xd5,0x74,0x1f,0x3c,0x5f,0xa0,0x50,0xb4,0x31,0x93,0xb7,0xe0,0x20,
0x3d,0xf5,0x71,0xfe,0xa1,0xf7,0x80,0x5b,0xd7,0xf0,0x42,0xa8,0x9e,0x28,0x44,0xae,
0x55,0x72,0xcb,0xfd,0x3e,0xe0,0xaf,0xba,0x35,0xe4,0x49,0x9f,0xd8,0x37,0x58,0x7a,
0x7a,0x32,0x62,0x26,0xe1,0xba,0x76,0x13,0x20,0x7d,0xed,0x33,0xc0,0x75,0x7c,0xc8,
0x33,0xe0,0xe8,0xec,0x3b,0x0a,0x5b,0x87,0xd5,0x10,0xb0,0x4a,0xe7,0xb6,0x1d,0xd6,
0xae,0x8b,0x15,0x00,0xf6,0x66,0xaf,0x4a,0xa1,0x9a,0x9d,0xae,0xcd,0xcc,0xe0,0xbc,
0xdc,0xdf,0x4b,0x99,0xe6,0xb5,0x7f,0xbe,0xf8,0xfc,0x0b,0x68,0xa2,0x7c,0xf1,0xc5,
0xc5,0x5d,0xc5,0xa2,0xbd,0x8a,0xa8,0x12,0x13,0xd6,0x6e,0xec,0xd2,0x93,0xc8,0xad,
0xc2,0xf4,0xbc,0x32,0x27,0x32,0x1d,0x9e,0x26,0x0d,0xaa,0xd6,0x6e,0x1c,0xf2,0x0a,
0x86,0x10,0xad,0xdd,0x99,0x51,0x10,0x73,0x39,0x55,0x37,0x5e,0xf6,0x58,0x56,0x08,
0x7b,0x5e,0xc5,0xaf,0x4e,0x69,0x6c,0xfb,0x26,0x3c,0xef,0x6e,0x98,0xa6,0x37,0xa7,
0xa5,0xa7,0x9a,0x0a,0x15,0x0a,0x9c,0x7c,0x02,0x5d,0x73,0x02,0xac,0x87,0xfc,0xdc,
0x92,0x92,0xe7,0x35,0x1a,0x43,0xe3,0xed,0xe9,0x69,0x05,0x73,0x4e,0xeb,0x47,0xde,
0xc3,0x33,0x3c,0x2f,0x85,0x26,0x0b,0x3f,0x1c,0x91,0x23,0x01,0x5d,0x45,0x3a,0xbd,
0x06,0xc9,0x24,0x43,0xa8,0x3f,0x6d,0x72,0xdd,0x22,0x6c,0x7b,0x06,0x44,0x0c,0xa4,
0x19,0xe9,0x21,0x1f,0x3f,0x86,0x32,0x40,0x5e,0x62,0xd6,0xf7,0xd0,0xdb,0x5d,0xe6,
0xf4,0xbc,0x70,0xab,0xdd,0xb6,0xe7,0xba,0x28,0x6f,0xed,0xce,0x8c,0x36,0x1e,0xba,
0xae,0x05,0xc0,0x82,0x61,0xd8,0x52,0x65,0x08,0x11,0x66,0xf8,0x20,0xb0,0xab,0x73,
0xc6,0x4a,0xa5,0x20,0xeb,0x8a,0x0e,0xa9,0x05,0xb0,0x6c,0xeb,0x40,0xa3,0xbb,0x18,
0x7c,0x67,0xa6,0xde,0x18,0xda,0x68,0xda,0xa4,0x60,0x8f,0x8f,0xcf,0x6f,0x73,0x93,
0xd5,0x22,0x50,0x6e,0x87,0x2b,0x9c,0x19,0xf8,0xfe,0x4d,0x59,0x5f,0x07,0xd1,0x8c,
0xea,0x6f,0xb3,0x1a,0x78,0xa8,0x0a,0x39,0x19,0x2b,0x0c,0x94,0x3d,0x74,0xee,0x07,
0xe8,0xa5,0x12,0x9f,0xf5,0xea,0x90,0x1a,0x83,0xd4,0xbd,0x7d,0x9e,0x21,0xaf,0x01,
0xd5,0xfa,0x95,0xbc,0x85,0x05,0x2a,0xf2,0x79,0x01,0x5e,0x76,0x46,0x3d,0xb4,0xf1,
0xb4,0x49,0x3f,0x9e,0x6c,0x04,0x32,0x5e,0x1c,0xf2,0x42,0xb4,0x09,0x28,0xe9,0x30,
0x17,0x1e,0x68,0x6d,0x4b,0x28,0x3c,0x9e,0x5c,0xb3,0x86,0x6f,0x59,0x31,0x94,0xf8,
0x69,0x53,0x3e,0xaf,0x92,0x4f,0x6b,0xeb,0x47,0xdf,0x6f,0x33,0xd0,0x80,0xb5,0x80,
0x40,0x11,0x33,0x86,0x2a,0xa8,0x97,0x2e,0x85,0xd3,0x18,0xe5,0xb1,0x7a,0xb8,0x2b,
0xf1,0xfd,0x44,0x05,0xb2,0x58,0x54,0xed,0x45,0x03,0x2a,0x44,0x30,0x1e,0xae,0x74,
0xca,0x0a,0x9a,0x1a,0x2b,0x17,0xcc,0x43,0x1d,0x87,0x4f,0x41,0xc9,0x0f,0x02,0xba,
0x5c,0x1f,0x28,0x27,0x17,0x05,0x4a,0x41,0x55,0x35,0x9f,0xff,0xaa,0x71,0xb2,0x50,
0xe0,0x9a,0x81,0xb4,0x0b,0xe8,0x3c,0xaf,0x9d,0x8b,0x63,0x40,0xf0,0x3b,0x72,0x72,
0x5f,0x85,0xe6,0x79,0x67,0x65,0xdf,0x43,0x9a,0x77,0x96,0xef,0x08,0xd0,0x42,0x21,
0x7c,0xcf,0x64,0x92,0x6e,0xee,0xd8,0xe1,0xda,0xf5,0x81,0x7a,0x5e,0x34,0xbb,0x87,
0x40,0xd5,0xf8,0x78,0xf3,0xa6,0x3a,0x9e,0x54,0x70,0x19,0xc4,0x62,0x03,0x65,0x0f,
0xfd,0x0f,0x20,0x78,0xad,0x5c,0xae,0x20,0x9f,0x2f,0x60,0xe9,0xd2,0x24,0x1c,0xe7,
0x23,0x24,0x12,0x9b,0x6b,0x0f,0x6e,0x81,0xc8,0xba,0x23,0x40,0xc7,0xc7,0x5d,0x55,
0xcb,0x5f,0x20,0xce,0xeb,0x37,0x47,0xf4,0x43,0x1e,0x06,0xac,0x9f,0xa8,0xdd,0x39,
0xcd,0x73,0xda,0xb4,0x73,0xe7,0xc9,0x93,0xe9,0xb4,0x79,0x9c,0x28,0xc0,0x85,0x0b,
0x13,0xf0,0x7d,0x47,0xea,0xac,0x84,0xfa,0x3e,0x5c,0xf7,0x73,0x69,0x7f,0xc7,0x1b,
0xcf,0xb7,0x91,0xdf,0x54,0xff,0xb5,0x6b,0x2e,0x2c,0xcb,0x57,0xbf,0x50,0x2f,0x95,
0xf2,0xff,0x22,0x7e,0x0c,0x8d,0xae,0xe1,0xb9,0xd6,0x61,0x2e,0xb6,0x87,0x6a,0xa5,
0xbb,0x3b,0xb1,0xb7,0x5c,0xa6,0x33,0xd2,0x4b,0xd3,0xa7,0x4f,0x5f,0xc3,0xfa,0xf5,
0x4b,0xd1,0xdb,0x9b,0x04,0x91,0xa3,0x27,0x29,0x2d,0x2b,0xeb,0x36,0x2b,0xbe,0xdf,
0x75,0x09,0x97,0x2f,0x7b,0x98,0x98,0x50,0x6d,0x92,0x11,0x81,0x7f,0xdc,0xb9,0x93,
0x0e,0xeb,0x40,0x41,0x41,0x40,0x22,0x12,0xf2,0x91,0x39,0x63,0x54,0x77,0x16,0xe8,
0x3c,0xff,0xe3,0xe9,0xae,0x5d,0x5f,0x5f,0x18,0x1d,0xdd,0xfc,0x7c,0x2e,0x67,0xff,
0xb5,0xe3,0xb8,0xd9,0x6f,0xbf,0x9d,0xac,0x1d,0x89,0x99,0xb2,0x16,0x11,0x20,0x68,
0xc9,0xb6,0x6d,0x1f,0xe5,0x32,0xf1,0xd7,0x44,0x36,0x8b,0xcf,0x5d,0x17,0xcf,0xd6,
0xbd,0x7d,0x67,0x0a,0x61,0xf9,0x41,0xd0,0xab,0xb2,0x65,0x1a,0x08,0x6f,0x6b,0x2d,
0x5f,0xce,0x0f,0xad,0x1f,0x4f,0xea,0xd7,0xe0,0x5a,0x52,0xb9,0xf6,0x9e,0x02,0x98,
0x44,0xd3,0x85,0x43,0xff,0xdc,0xbb,0xa3,0xa3,0x1b,0x3e,0x29,0x97,0x9d,0xf7,0x0b,
0x05,0x67,0xc4,0xf3,0xc8,0x98,0x9d,0xf5,0x00,0x50,0x9b,0xa5,0x12,0x21,0x66,0xa5,
0x67,0xfe,0xe9,0xae,0x5d,0xf4,0x76,0xec,0xfd,0xd0,0x2e,0xc3,0xb8,0x6c,0x3b,0x4e,
0xaf,0x65,0xdb,0xe8,0x37,0xcd,0xf0,0x78,0xf2,0xb1,0xc7,0x6e,0x3d,0x9e,0xac,0x54,
0x94,0xad,0x83,0x6c,0x19,0xb0,0x55,0x03,0xba,0x44,0x88,0x31,0x70,0x99,0x17,0xd4,
0x1f,0xae,0x03,0xf8,0xd5,0x2f,0xbf,0x1c,0xe8,0x33,0x4d,0xfa,0x6d,0xdf,0x0f,0xf6,
0x10,0x51,0x7f,0xfc,0x9d,0xd0,0x68,0x21,0xbd,0xad,0xbd,0x8e,0xbc,0x44,0x02,0x63,
0x86,0x81,0x0f,0x87,0x87,0xe9,0xe4,0x6d,0x6f,0x30,0x27,0x0d,0xe3,0x8c,0x1d,0x04,
0xbf,0x7c,0x7d,0x66,0x06,0x03,0xdd,0xdd,0x48,0x9c,0x3b,0x17,0xfe,0x97,0xe1,0x15,
0x2b,0xa2,0xc7,0x93,0xb7,0xbf,0x8b,0xcd,0x9a,0x63,0x7f,0x41,0xd6,0xb9,0x9a,0x9d,
0x04,0xfe,0x0b,0x6d,0x28,0xbb,0x77,0x5f,0x9d,0x01,0xf0,0x4f,0x4a,0x8b,0xf6,0x17,
0x1d,0xbe,0xde,0xb6,0x6d,0xed,0x94,0x6d,0x7f,0xe5,0xfb,0x7e,0x66,0x55,0x26,0x83,
0xc1,0xbe,0x3e,0x88,0x68,0x82,0x72,0x5d,0x0d,0x46,0x6b,0xb6,0x92,0x27,0x75,0xca,
0xf3,0x50,0x20,0x42,0x8a,0xe8,0xfc,0x47,0x44,0x5b,0xfe,0xfc,0xc7,0xfc,0x57,0x65,
0x18,0x28,0x97,0xaf,0xb6,0x6e,0x7d,0x69,0xb2,0x58,0x3c,0x50,0x3d,0x9f,0x97,0x03,
0xc5,0xa0,0xf4,0xd0,0x1e,0xc3,0x68,0x1b,0x48,0xb6,0x49,0xda,0xd3,0x52,0xe7,0x65,
0xbb,0x22,0x65,0x00,0x95,0x7e,0x60,0xd7,0x36,0xa2,0x33,0xe0,0xd2,0x09,0x40,0x55,
0x19,0xdb,0xb8,0xf1,0x6f,0x66,0x4a,0xa5,0x3f,0xa2,0x20,0x30,0x41,0xa4,0x92,0x15,
0x32,0x12,0x6a,0x42,0x9b,0x5e,0x45,0xe6,0xa8,0x7a,0x7f,0x43,0xdb,0x91,0xb5,0x4d,
0x24,0xcd,0x80,0xc7,0x9c,0x7c,0x1f,0xf0,0xc2,0x2f,0x12,0xfd,0x5c,0xb5,0x3b,0x0d,
0x68,0x18,0xfe,0xeb,0xd7,0x3f,0x62,0x55,0x2a,0xff,0x20,0xb3,0xef,0x3a,0x22,0x4a,
0x30,0x0c,0x55,0xa2,0x90,0x54,0x89,0xed,0x8f,0xb7,0x79,0x45,0xe1,0x64,0x80,0xff,
0x4e,0x01,0x4f,0x49,0x98,0xe3,0xaa,0xaf,0x63,0x81,0x72,0x19,0x5b,0xbd,0xba,0x47,
0x7a,0xe8,0x6f,0xf9,0x44,0xbb,0x25,0x88,0xae,0xc6,0x5e,0x18,0xdf,0x17,0x85,0x2a,
0x80,0x9c,0x01,0x7c,0x6a,0xc9,0x04,0x34,0x42,0xe4,0x43,0x2f,0x9d,0x0c,0xf4,0xa7,
0xb2,0xe8,0x7f,0xc4,0xe5,0xa7,0x62,0xfe,0xbf,0x0f,0x21,0x21,0xb6,0x01,0x78,0x4e,
0x6a,0x4a,0xea,0x35,0x22,0xf2,0xea,0xbc,0x66,0x25,0x80,0x87,0xa5,0x7a,0xa5,0xbe,
0x27,0xa2,0xcf,0xb1,0x58,0x85,0x88,0xee,0xa8,0x64,0x51,0x0f,0xfb,0xa1,0xd4,0x19,
0xa9,0x3f,0xf9,0xbf,0x76,0xcc,0x27,0xc4,0xad,0x2a,0x0a,0xe3,0x2e,0xb2,0x78,0x8b,
0x2c,0xde,0xe2,0x81,0x23,0xbe,0x45,0x16,0x05,0x67,0x11,0x68,0xa0,0x59,0xb8,0xc8,
0x22,0x0b,0x17,0x03,0xce,0x22,0x8b,0x11,0x47,0x14,0x0c,0x18,0x61,0xa0,0x95,0xa4,
0x30,0xd2,0x11,0x0a,0x06,0x5c,0xd4,0x01,0xa5,0x85,0x2c,0xa6,0x50,0x21,0x82,0x03,
0x16,0x8a,0xa8,0x14,0xa9,0x50,0xa1,0x42,0x0b,0x22,0xa3,0x4c,0xc1,0x42,0x0b,0x11,
0xa6,0xa0,0xe2,0x40,0x0b,0x2d,0x24,0x90,0x40,0x84,0xfa,0x5d,0xf8,0x3d,0xf8,0x78,
0x3c,0xc7,0x22,0xd6,0x45,0xed,0x85,0x8f,0x9b,0x7b,0xfe,0x9f,0x7b,0xcf,0x3d,0xef,
0x92,0x1c,0xaf,0x2a,0x0c,0x85,0x4e,0x8e,0xbe,0x1e,0xe8,0xf0,0x3f,0x0f,0x61,0x82,
0xe6,0x5f,0xf8,0xd8,0x30,0x99,0xd7,0x1e,0x41,0x0e,0xc9,0x43,0xcb,0xfe,0x07,0x1b,
0x1a,0x0b,0xbf,0x5b,0xc2,0x15,0xe3,0x9d,0x83,0x76,0x21,0x77,0x00,0x53,0x61,0xc4,
0x0d,0xaa,0x09,0x5b,0xc2,0xc6,0x01,0x3e,0x2e,0x9a,0xfd,0xda,0xbf,0x18,0x7b,0x59,
0x18,0x08,0xbb,0x0f,0xab,0x53,0xca,0x5d,0x9d,0x06,0xd7,0xeb,0xb6,0xf0,0xa1,0x04,
0xee,0x8b,0x16,0x12,0x3a,0x21,0x7c,0xaf,0xf5,0x19,0xe4,0xea,0x9a,0xba,0xc2,0x57,
0xa2,0x9d,0xd7,0xba,0xa5,0xdf,0x2f,0x67,0x32,0xd8,0xe9,0xb2,0xfe,0x40,0xeb,0x6b,
0xfa,0xbd,0x82,0x9b,0xa6,0xf0,0xb1,0x68,0x49,0xa8,0x26,0x68,0x89,0x85,0x71,0x54,
0x88,0x84,0x4d,0x12,0x6a,0xb1,0xb1,0xcf,0x5a,0x9c,0x61,0xbd,0x26,0x1c,0xe1,0x00,
0x9e,0x87,0x35,0x13,0x6e,0x64,0x32,0xd8,0x7f,0x51,0xd8,0xa7,0x65,0x3c,0x2d,0xc4,
0x8a,0xe9,0x15,0x64,0x82,0x9f,0x36,0x76,0xe2,0x90,0x8f,0xf0,0x05,0xfe,0x4e,0xc0,
0x4b,0x84,0xeb,0x92,0x5d,0x25,0xd7,0x05,0xe8,0x87,0xf1,0xf9,0x65,0xa0,0x17,0x5e,
0x79,0x02,0x78,0x00,0x36,0xa0,0x35,0x8d,0xd6,0x80,0x36,0x64,0x3d,0x2a,0xa8,0xc0,
0x55,0x61,0x99,0xdf,0x53,0xe4,0xfb,0xc6,0xef,0x17,0x5c,0xd3,0x2b,0xd0,0x22,0xe1,
0x0e,0xf6,0x22,0xe1,0x05,0x93,0xf9,0xc4,0x2a,0x78,0x07,0xda,0x39,0xa1,0x65,0x32,
0x3b,0x56,0x59,0x97,0xa1,0x5d,0x12,0x52,0x93,0xf9,0x0e,0x99,0x43,0xc2,0x2e,0xb4,
0x93,0x96,0xfb,0x10,0xdf,0x03,0xd3,0xe9,0xb1,0xb1,0x35,0x61,0x8a,0x5e,0x85,0xfc,
0xe7,0x42,0x9a,0xed,0x61,0xfe,0x2b,0x7f,0xde,0x7e,0xbf,0xca,0xbc,0x60,0xb4,0x26,
0x73,0xca,0xbc,0x1f,0xaa,0x58,0xf3,0x4b,0x26,0xd3,0x25,0xd8,0x30,0xbe,0x16,0x7c,
0x78,0x85,0x1d,0x65,0xe9,0xf6,0x3a,0x04,0xbe,0x29,0xbb,0x33,0x12,0xc8,0xc6,0x8f,
0xcc,0x5b,0x42,0x9d,0x6a,0x3c,0x2e,0x4c,0x4c,0xe6,0x3a,0xf3,0x3a,0x87,0x11,0xc6,
0xdb,0x9e,0x83,0xc9,0x0c,0xb0,0xff,0xab,0xf0,0xbe,0x70,0x04,0xfa,0x21,0x7c,0xa7,
0xa6,0xf3,0xad,0x68,0x77,0x35,0xbf,0x2b,0x44,0xf8,0x0c,0xeb,0x19,0xf6,0xf6,0x33,
0xc1,0xa2,0xbe,0xf1,0x0b,0xa7,0xb2,0xc7,0xfa,0x3d,0x3b,0xa9,0x01,0xb4,0x7b,0xac,
0xdb,0xa6,0xb7,0x6b,0x72,0x53,0x02,0x8e,0xe0,0xb5,0xbd,0x42,0x85,0x15,0x93,0x73,
0x5f,0xa3,0xac,0x3a,0x59,0x5f,0xc8,0xf4,0xd8,0xa0,0xc5,0x82,0xaa,0xee,0x19,0xed,
0x58,0x2e,0xbe,0x31,0xeb,0x63,0x2e,0x23,0xd4,0x6d,0x7d,0x51,0x58,0x47,0x67,0x6c,
0xb7,0x70,0x0f,0xfe,0x5c,0x28,0x41,0xbb,0x62,0x7a,0x7b,0x45,0xfd,0xba,0xe8,0x1d,
0x7a,0x9f,0x79,0xc2,0xbc,0x6a,0xbc,0x32,0x3d,0x35,0xa6,0x57,0x6d,0x5b,0xef,0xf5,
0x7e,0xbc,0x2d,0xe3,0x6f,0x71,0xd2,0x45,0xa3,0x8b,0x9f,0x6d,0xb3,0xdb,0xa2,0xb2,
0x37,0x4d,0xcf,0x2b,0xf4,0x07,0xa1,0x6a,0xeb,0x9f,0x99,0x9f,0x73,0x19,0x7a,0x5c,
0xcc,0xfa,0x16,0xf3,0x61,0x93,0xb9,0x91,0xb3,0xf3,0x87,0x50,0xa6,0x92,0x9f,0x91,
0xef,0x6b,0xb2,0x11,0xf4,0x2b,0x99,0xbc,0x3d,0xd5,0xde,0xa1,0xa2,0x9f,0x82,0x7f,
0x55,0xb2,0x8b,0x7f,0xf7,0xb0,0xbf,0x9b,0xcd,0x24,0x39,0x11,0x6e,0xdb,0x26,0xbf,
0x4e,0x10,0xc7,0x83,0x23,0xc9,0xf4,0x38,0xb9,0x5b,0x76,0x18,0x2b,0x34,0x7c,0x06,
0xfa,0x24,0xc7,0x9b,0xf1,0xac,0xf0,0x9b,0x7d,0x94,0xba,0xf8,0x3e,0xcb,0x21,0x25,
0x6c,0xb0,0xb5,0x16,0x25,0xce,0x30,0xdd,0x7a,0x6e,0xb3,0x26,0x20,0x8c,0x99,0xec,
0x54,0x42,0x3c,0x7e,0xe5,0xbd,0x05,0xf0,0x61,0xed,0x0b,0x1f,0xd9,0x35,0xaf,0xb9,
0xcd,0xec,0xad,0x0b,0xfd,0x4d,0xe1,0x1b,0x78,0x65,0x61,0xe9,0xc0,0x77,0xa8,0x95,
0xf5,0x4f,0x5c,0xc1,0x65,0x2b,0xff,0x4b,0x5c,0xd3,0x1e,0xb2,0x65,0xbb,0xb6,0xf5,
0x5c,0x23,0x3f,0x69,0x36,0x9b,0x46,0x9f,0x83,0x34,0xc8,0x64,0x74,0xd0,0x37,0x9d,
0x4a,0xc1,0x87,0xa4,0x61,0xb4,0x4e,0xae,0x05,0xdc,0xb3,0xab,0x79,0x8a,0xb8,0xc8,
0x43,0x3c,0x7e,0xc3,0x5f,0xce,0x5d,0xdd,0xd3,0xe4,0x7d,0x15,0x7e,0xc7,0xf8,0x43,
0x6f,0x3f,0xc4,0x1c,0x5b,0x2e,0x75,0xdf,0xbf,0xc2,0x0d,0x35,0xe1,0xb6,0xf7,0x13,
0xfa,0xdb,0x5a,0xee,0x9d,0x36,0xb6,0x0d,0xad,0xda,0xfa,0x72,0xe0,0xfb,0xe6,0x18,
0x3e,0xcd,0xf7,0x56,0x92,0x8e,0xcd,0x76,0x49,0xb8,0x09,0x6f,0x9c,0xbd,0x5f,0xed,
0xa1,0x7f,0x13,0xec,0x98,0x7e,0x15,0x99,0x98,0xd8,0x52,0xe6,0x07,0xe0,0x94,0xd9,
0xdf,0xca,0xe8,0x96,0xdb,0x92,0xbd,0x00,0xe6,0xe6,0x27,0xa2,0xca,0xa7,0x1c,0xd0,
0x10,0xf9,0xf6,0xc1,0x0f,0x7b,0x92,0xa7,0xa2,0x16,0x8c,0x56,0xe5,0xad,0x57,0x2a,
0x90,0x4f,0xe1,0x45,0xae,0xef,0xb2,0xff,0x14,0x6c,0x6a,0x43,0x48,0x72,0xf4,0x5a,
0x16,0xa3,0x10,0xf1,0x3b,0x85,0x77,0x3a,0xdb,0x08,0xf4,0xd7,0xac,0x40,0x6a,0xf9,
0xd8,0xd1,0x5d,0x2c,0xf0,0x9d,0x08,0x75,0xcf,0x03,0x5f,0x0d,0xe8,0x91,0xcb,0xfb,
0x86,0x3e,0x56,0xb0,0xdb,0x74,0x87,0xcd,0x1a,0xf9,0x0b,0xe5,0x51,0xe3,0xb1,0xfa,
0xfb,0x8e,0x8f,0x47,0xb8,0x2d,0x6f,0x50,0xc5,0x09,0x6f,0xc4,0xcf,0x84,0x33,0x7c,
0xad,0x9f,0xfc,0x1f,0xfa,0xe4,0xff,0xd0,0xff,0xf1,0xf8,0x13,0x3b,0xb0,0x6a,0xdb,
0x6e,0xe8,0xd2,0x18,0x00,0x00,0x00,0x00,0x49,0x45,0x4e,0x44,0xae,0x42,0x60,0x82,
};


wxBitmap wxGet_wxWidgets_png_Bitmap()
{
	wxMemoryInputStream _mem_i_s(wxWidgets_png,4352);
	return wxBitmap(wxImage(_mem_i_s,wxBITMAP_TYPE_ANY,-1),-1);
}
