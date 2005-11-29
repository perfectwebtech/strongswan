/**
 * @file prf_plus_test.h
 * 
 * @brief Tests for the prf_plus_t class.
 * 
 */

/*
 * Copyright (C) 2005 Jan Hutter, Martin Willi
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include <string.h>
 
#include "prf_plus_test.h"

#include <transforms/prf_plus.h>
#include <utils/allocator.h>


/* 
 * described in Header-File
 */
void test_prf_plus(tester_t *tester)
{
	prf_plus_t *prf_plus;
	prf_t *prf;
	chunk_t key, seed;
	u_int8_t buffer[10000];
	int i;
	
	u_int8_t key_bytes[] = {
		0x01,0x02,0x03,0x04
	};
	u_int8_t seed_bytes[] = {
		0x01,0x02,0x03,0x04
	};
	

	
	key.ptr = key_bytes;
	key.len = sizeof(key_bytes);
	seed.ptr = seed_bytes;
	seed.len = sizeof(seed_bytes);
	
	prf = prf_create(PRF_HMAC_SHA1);
	prf->set_key(prf, key);
	
	prf_plus = prf_plus_create(prf, seed);
	
	
	for (i=0; i<100; i++)
	{
		prf_plus->get_bytes(prf_plus, i*i, buffer);
		
	}
	
	//tester->assert_true(tester, digest[3].len == 20, "chunk len append mode");
	//tester->assert_false(tester, memcmp(digest[3].ptr, reference[3].ptr, 20), "prf_plus value append mode");
	
	prf_plus->destroy(prf_plus);
	prf->destroy(prf);
}

void test_prf_plus_md5(tester_t *tester)
{
	/* md5 test data 
	u_int8_t nonce[] = {
		0x58,0xCC,0x4C,0xA3,0x81,0x81,0xDA,0x7D,
		0x19,0xA6,0x9F,0xB1,0xE8,0xD3,0xE7,0x96,
		0xC2,0x2A,0x6E,0xCB,0x09,0x43,0xDC,0x6E,
		0x75,0x22,0x34,0xAE,0xF8,0x53,0x7F,0xEC,
		0x00,0xC9,0xF6,0x1C,0x4A,0x39,0xB4,0x29,
		0x23,0xD8,0x24,0x22,0x95,0x52,0x77,0x29
	};

	u_int8_t shared_key[] = {
		0xC0,0xDB,0x75,0x0A,0x40,0xBE,0xE2,0x8C,0x68,0x3C,0xB4,0xAA,0xE7,0xA7,0x6E,0xCC,
		0x2A,0x4B,0x9C,0x8E,0xC6,0x71,0xAD,0xF4,0xB7,0xC4,0xD6,0x53,0x41,0xB3,0x4A,0xE4,
		0x0D,0xC2,0x0C,0x60,0x9F,0x93,0x9E,0x87,0x30,0xCC,0xDC,0x51,0x9F,0x94,0x91,0x5D,
		0x31,0xE0,0x6E,0x22,0x3A,0x66,0x53,0xA6,0xD4,0x54,0x5E,0x71,0x61,0xA6,0x64,0x3B,
		0x19,0x40,0x6E,0x6F,0x3B,0xE3,0x64,0x3F,0x3B,0x68,0xEB,0x8E,0x4B,0x2A,0x53,0xEC,
		0xB0,0xB6,0x8E,0x5C,0x42,0xA1,0xC2,0x7F,0x4F,0x0B,0x7D,0xFC,0xF6,0x7E,0xF5,0xC0,
		0xBA,0xA8,0xFB,0x13,0xEF,0xA8,0xBD,0x90,0x95,0x08,0x2C,0x81,0xA9,0xDA,0x7D,0x45,
		0xDC,0x35,0x33,0x75,0xA8,0x4D,0xE2,0x34,0xA9,0x66,0x7F,0xAD,0x04,0x3A,0xE5,0x21
	};

	u_int8_t skeyseed[] = {
		0xCD,0xC6,0xC0,0x68,
		0x60,0xDF,0x0C,0xC2,
		0x10,0xDB,0x0E,0xF7,
		0x20,0x6E,0x6C,0xB1
	};
	u_int8_t sk_d[] = {
		0xE1,0x74,0xA8,0x50,
		0x14,0xDB,0x79,0x64,
		0x92,0x3E,0x82,0x28,
		0x48,0x75,0x64,0xE7
	};
	u_int8_t sk_ai[] = {
		0xCA,0x19,0x73,0x69,
		0x38,0x35,0x40,0xA6,
		0xB1,0x98,0x4F,0x63,
		0xE6,0xF9,0x66,0xFF
	};
	u_int8_t sk_ar[] = {
		0x14,0x1D,0x0A,0xC2,
		0x7B,0x1C,0x87,0xD2,
		0x65,0xA5,0xEF,0x0C,
		0x47,0xF4,0xCE,0xE2
	};
	u_int8_t sk_ei[] = {
		0x52,0x50,0x7E,0xDA,
		0x02,0x1D,0x8E,0xCF,
		0x20,0xA3,0x67,0xA6,
		0x4D,0xA0,0xAB,0x61
	};
	u_int8_t sk_er[] = {
		0xB9,0x65,0x0A,0x3C,
		0x30,0xA8,0x26,0x78,
		0x60,0x5A,0x74,0xBB,
		0x5C,0xC4,0xF8,0x71
	};
	u_int8_t sk_pi[] = {
		0xDD,0x61,0xAB,0x53,
		0xC8,0xDD,0x3A,0x44,
		0xDA,0x47,0x09,0x9B,
		0x3B,0xD2,0xBB,0xB6
	};
	u_int8_t sk_pr[] = {
		0x18,0x75,0xE4,0xC6,
		0x57,0xC4,0xDE,0x65,
		0x10,0xEB,0xA7,0xB6,
		0x24,0x0D,0xEC,0xB4
	};*/
}
