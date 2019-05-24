#include "shiny.h"
#include <stdint.h>

#define L_16(x) (x & 0x0000FFFFU)	
#define H_16(x)	(x >> 16)	

#define DEF_SDEF(x)	((x & 0b0111110000000000U) >> 10)
#define ATK_SATK(x)	((x & 0b0000001111100000U) >> 5)				
#define   HP_SPE(x) (x & 0b0000000000011111U)				


/* CALC FUNCTIONS */

uint32_t lcrng(uint32_t seed){
	return (uint32_t)(0x41C64E6DULL*((uint64_t)seed) + 0x00006073ULL);
}

// returns the pid based on the given seed and updates seed
static uint32_t pid(uint32_t *seed){
	uint32_t pid = 0;
	
	//lower 16 bits are determined by the 16 upper bits of the first rng-call
	*seed = lcrng(*seed);
	pid = H_16(*seed);
	
	//upper 16 bits are determined by the 16 upper bits of the second rng-call
	*seed = lcrng(*seed);
	pid |= (*seed & 0xFFFF0000U);
	
	return pid;
}

pkmn_t pkmn(uint32_t seed){
	uint16_t seed_h_16;
	
	//zero-init
	pkmn_t pkmn = {0};
	
	//game makes an lcrng-call first
	seed = lcrng(seed);
	
	//calculate and set pid
	pkmn.pid = pid(&seed);
	
	//third call of rng for the ivs def, atk and hp
	seed = lcrng(seed);
	seed_h_16 = H_16(seed);
	
	pkmn.ivs.def |= (uint8_t) DEF_SDEF(seed_h_16); 
	pkmn.ivs.atk |= (uint8_t) ATK_SATK(seed_h_16);
	pkmn.ivs.hp  |= (uint8_t)   HP_SPE(seed_h_16);
	
	//fourth call of rng for the ivs sdef, satk, spe 
	seed = lcrng(seed);
	seed_h_16 = H_16(seed);
	
	pkmn.ivs.sdef |= (uint8_t) DEF_SDEF(seed_h_16); 
	pkmn.ivs.satk |= (uint8_t) ATK_SATK(seed_h_16);
	pkmn.ivs.spe  |= (uint8_t)   HP_SPE(seed_h_16);
	
	return pkmn;
}

uint16_t sid(const config_t *conf, uint16_t tid){
	uint32_t seed = tid;
	
	for(uint16_t frame=0; frame<(conf->a + SID_R_ADD); frame++){
		seed = lcrng(seed);
	}
	
	return (uint16_t)H_16(seed);
}

uint8_t is_shiny(uint32_t pid, uint16_t tid, uint16_t sid){
	//a Pokemon is shiny if (tid xor pid xor (lower half of pid) xor (upper half of pid)) < 8
	
	return (tid ^ sid ^ ((uint16_t) L_16(pid)) ^ ((uint16_t) H_16(pid))) < 8;
}