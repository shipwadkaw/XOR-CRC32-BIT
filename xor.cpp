//////////////////////////////////////////////////////////////////////////////
//
#include "../stdafx.h"

#include <math.h>
#include <stdio.h>

//
//////////////////////////////////////////////////////////////////////////////
//
#define ROTL32(x,y) ((x<<y)|(x>>(32-y)))
#define ROTR32(x,y) ((x>>y)|(x<<(32-y)))
#define ROTL24(x,y) ((x<<y)|(x>>(24-y)))
#define ROTR24(x,y) ((x>>y)|(x<<(24-y)))
#define ROTL16(x,y) ((x<<y)|(x>>(16-y)))
#define ROTR16(x,y) ((x>>y)|(x<<(16-y)))
#define ROTL8(x,y) ((x<<y)|(x>>(8-y)))
#define ROTR8(x,y) ((x>>y)|(x<<(8-y)))
//
//////////////////////////////////////////////////////////////////////////////
//
static unsigned int g_nRSeed = 0;
//
//////////////////////////////////////////////////////////////////////////////
//
int getRand( int mod )
{
	g_nRSeed = (1664525 * g_nRSeed) + 1013904223;
	
	if ( mod )
	{
		return ( ((g_nRSeed >> 16) & 0xFFFF) % mod );		
	}
	else
	{
		return (g_nRSeed >> 16) & 0xFFFF;
	}
}
//
//////////////////////////////////////////////////////////////////////////////
//
void ENCODE_XOR32(char *buffer , unsigned int size , char* output , unsigned int key)
{
	g_nRSeed = key;
	
	unsigned int block;
	int a, b, c, d, magnitude, polarity;
	int index = 0;
	int oIndex = 0;

	while( (index + 3) < size )
	{
		a = buffer[index++] & 0xff ;
		b = buffer[index++] & 0xff ;
		c =	buffer[index++] & 0xff ;
		d =	buffer[index++] & 0xff ;

		polarity = getRand(2);
		magnitude = getRand(32);

		block = ( (d<<24) | (c<<16) |(b<<8) | a);
		block ^= ( (getRand(256)<<24) | (getRand(256)<<16) | (getRand(256)<<8) | getRand(256) );
		
		if (polarity) 
		{
			block = ROTL32(block,magnitude);
		}
		else 
		{
			block = ROTR32(block,magnitude);
		}

		output[oIndex++] = block;
		block = block >> 8 ;
		
		output[oIndex++] = block;
		block = block >> 8 ;
		
		output[oIndex++] = block;
		block = block >> 8 ;
		
		output[oIndex++] = block;
			
	}

	int diff = size - index;
	
	polarity = getRand(2);

	switch (diff)
	{
		case 3:
		{
			a = buffer[index++] & 0xff ;
			b = buffer[index++] & 0xff ;
			c =	buffer[index++] & 0xff ;
		
			magnitude = getRand(24);
			block = ((c<<16) |(b<<8) | a);
			block ^= ((getRand(256)<<16) | (getRand(256)<<8) | getRand(256));
			
			if (polarity)
			{
				block = ROTL24(block,magnitude);
			}
			else
			{
				block = ROTR24(block,magnitude);
			}

			output[oIndex++] = block;
			block = block >> 8 ;
		
			output[oIndex++] = block;
			block = block >> 8 ;
		
			output[oIndex++] = block;
			
		}
		break;
		
		case 2:
		{
			a = buffer[index++] & 0xff ;
			b = buffer[index++] & 0xff ;
						
			magnitude = getRand(16);
			block = ((b<<8) | a);
			block ^= ((getRand(256)<<8) | getRand(256));

			if (polarity) 
			{
				block = ROTL16(block,magnitude);
			}
			else
			{
				block = ROTR16(block,magnitude);
			}

			output[oIndex++] = block;
			block = block >> 8 ;
		
			output[oIndex++] = block;
		}
		break;
		
		case 1:
		{
			a = buffer[index++] & 0xff ;
			
			magnitude = getRand(8);
			block = (a);
			block ^= (getRand(256));
			if (polarity)
			{ 
				block = ROTL8(block,magnitude);
			}
			else
			{
				block = ROTR8(block,magnitude);
			}

			output[oIndex++] = block;
		}
		break;
		
		case 0:
		
		break;
		
		default:
		
		break;
	}	
}
//
//////////////////////////////////////////////////////////////////////////////
//
void DECODE_XOR32(char *buffer , unsigned int size , char* output  , unsigned int key)
{
  	g_nRSeed = key;
	
	unsigned int block;
	int a, b, c, d, magnitude, polarity;
	int index = 0;
	int oIndex = 0;

	while( (index + 3) < size)
	{
		a = buffer[index++] & 0xff ;
		b = buffer[index++] & 0xff ;
		c =	buffer[index++] & 0xff ;
		d =	buffer[index++] & 0xff ;

		polarity = getRand(2);
		magnitude = getRand(32);

		block = ((d<<24) | (c<<16) |(b<<8) | a);
				
		if (polarity) 
		{
			block = ROTR32(block,magnitude);
		}
		else 
		{
			block = ROTL32(block,magnitude);
		}

		block ^= ( (getRand(256)<<24) | (getRand(256)<<16) | (getRand(256)<<8) | getRand(256) );

		output[oIndex++] = block;
		block = block >> 8 ;
		
		output[oIndex++] = block;
		block = block >> 8 ;
		
		output[oIndex++] = block;
		block = block >> 8 ;
		
		output[oIndex++] = block;
			
	}

	int diff = size - index;
	
	polarity = getRand(2);

	switch (diff)
	{
		case 3:
		{
			a = buffer[index++] & 0xff ;
			b = buffer[index++] & 0xff ;
			c =	buffer[index++] & 0xff ;
		
			magnitude = getRand(24);
			block = ((c<<16) |(b<<8) | a);
						
			if (polarity)
			{
				block = ROTR24(block,magnitude);
			}
			else
			{
				block = ROTL24(block,magnitude);
			}

			block ^= ((getRand(256)<<16) | (getRand(256)<<8) | getRand(256));

			output[oIndex++] = block;
			block = block >> 8 ;
		
			output[oIndex++] = block;
			block = block >> 8 ;
		
			output[oIndex++] = block;
			
		}
		break;
		
		case 2:
		{
			a = buffer[index++] & 0xff ;
			b = buffer[index++] & 0xff ;
						
			magnitude = getRand(16);
			block = ((b<<8) | a);
			
			if (polarity) 
			{
				block = ROTR16(block,magnitude);
			}
			else
			{
				block = ROTL16(block,magnitude);
			}

			block ^= ((getRand(256)<<8) | getRand(256));

			output[oIndex++] = block;
			block = block >> 8 ;
		
			output[oIndex++] = block;
		}
		break;
		
		case 1:
		{
			a = buffer[index++] & 0xff ;
			
			magnitude = getRand(8);
			block = (a);
			
			if (polarity)
			{ 
				block = ROTR8(block,magnitude);
			}
			else
			{
				block = ROTL8(block,magnitude);
			}

			block ^= (getRand(256));

			output[oIndex++] = block;
		}
		break;
		
		case 0:
		
		break;
		
		default:
		  printf("something went wrong %d !\n" , diff);
		break;
	}	
}
//
//////////////////////////////////////////////////////////////////////////////