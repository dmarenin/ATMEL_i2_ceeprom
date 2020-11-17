#define FALSE 0
#define TRUE 1
#define MAX_ADDRES 65536*2
#define MAX_PAGE 16*4
#define MAX_HW_BLOCKS 2
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "usart.h"

FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);

#include "i2c_eeprom.h"

#include <stdio.h>
#include "dht11.h"

typedef struct HW_BLOCK_T {

	uint32_t start_addr;
	uint32_t end_addr;
	uint32_t size;
	uint32_t hw_addr;
	int isInit;
	
} HW_BLOCK;

HW_BLOCK HW_BLOCKS[MAX_HW_BLOCKS];

void initHWBlock()
{
	HW_BLOCKS[0].hw_addr = 0b10100000;
	HW_BLOCKS[0].isInit = true;
	HW_BLOCKS[0].size = 65535;
	HW_BLOCKS[0].start_addr = 0;
	HW_BLOCKS[0].end_addr = 65535;

	HW_BLOCKS[1].hw_addr = 0b10100010;
	HW_BLOCKS[1].isInit = true;
	HW_BLOCKS[1].size = 65535;
	HW_BLOCKS[1].start_addr = 65535;
	HW_BLOCKS[1].end_addr = 131070;
}

void setup(void)
{
	USART0Init();
	
	stdin=stdout=&usart0_str;
	
	eeInit();
	
	initHWBlock();

}

void readAllWithManualOutput(void)
{
	//printf("\n");
	//int pos = 0;
	//int page = 0;
	//for (uint16_t curadr=1; curadr<MAX_ADDRES; curadr++)
	//{
	//if (pos==0)
	//{
	//printf("*%#04x ", curadr);
	//}
	//pos++;
	//uint8_t data;
	////data = eeReadByte(curadr);
	//printf(" %#04x ", data);
	//if (pos==4)
	//{
	//printf("\n");
	//pos = 0;
	//}
	//page++;
	//if (page==MAX_PAGE)
	//{
	//printf("\n");
	//page = 0;
	//char _cmd;
	//scanf("%c",&_cmd);
	//printf("\b");
	//}
	//}
}

void readAll(void)
{
	//printf("\n");
	//int pos = 0;
	//int page = 0;
	//for (uint16_t curadr=1; curadr<MAX_ADDRES; curadr++)
	//{
	//if (pos==0)
	//{
	//printf("*%#04x ", curadr);
	//}
	//pos++;
	//uint8_t data;
	////data = eeReadByte(curadr);
	//printf(" %#04x ", data);
	//if (pos==4)
	//{
	//printf("\n");
	//pos = 0;
	//}
	//page++;
	//if (page==MAX_PAGE)
	//{
	//printf("\n");
	//page = 0;
	//}
	//}
}

uint16_t getHW_BLOCK(uint32_t addr)
{
	for (int i=0; i<MAX_HW_BLOCKS+1; i++)
	{
		if (HW_BLOCKS[i].end_addr>addr)
		{
			return HW_BLOCKS[i].hw_addr;
		}
	}

	//int16_t HW_BLOCK = HW_BLOCK_0;
	//if (addres>=(uint32_t)65536)
	//{
	//HW_BLOCK = HW_BLOCK_1;
	//}
	//return  HW_BLOCK;
}

void readAllRange(void)
{
	//printf("\n*:");
	//
	//uint32_t _uaddresMin;
	//
	////scanf(&_uaddresMin);
	//scanf("%" SCNd32 , &_uaddresMin);
	//
	//printf("\n*:");
	//
	//uint32_t _uaddresMax;
	//
	//scanf("%" SCNd32 , &_uaddresMax);
	//
	//printf("\n");
	//int pos = 0;
	//int page = 0;
	//for (_uaddresMin; _uaddresMin<_uaddresMax+1; _uaddresMin++)
	//{
	//
	//uint16_t HW_BLOCK = getHW_BLOCK(_uaddresMin);
	//
	//if (pos==0)
	//{
	//printf("*%#04x ", _uaddresMin);
	//}
	//pos++;
	//uint8_t data;
	//data = eeReadByte(_uaddresMin, HW_BLOCK);
	//
	//printf(" %#04x ", data);
	//if (pos==4)
	//{
	//printf("\n");
	//pos = 0;
	//}
	//page++;
	//if (page==MAX_PAGE)
	//{
	//printf("\n");
	//page = 0;
	//}
	//}
}

void readAddres(void)
{
	printf("\n*:");
	
	uint32_t _uaddres;
	scanf("%" SCNd32, &_uaddres);
	uint16_t HW_BLOCK = getHW_BLOCK(_uaddres);

	uint8_t data;
	data = eeReadByte(_uaddres, HW_BLOCK);
	
	printf("\n%#04x ", data);
	//scanf("%u",&_uaddres);
	//
	//uint8_t data;
	////data = eeReadByte(_uaddres);
	//printf("\n*%#04x = %#04x", _uaddres, data);
}

void writeByte(void)
{
	printf("\n*:");
	
	uint32_t _uaddres;
	scanf("%" SCNd32, &_uaddres);
	
	//printf_P(PSTR("\nreading..."));
	//
	//uint8_t data;
	//
	uint16_t HW_BLOCK = getHW_BLOCK(_uaddres);
	//
	//data = eeReadByte(_uaddres, HW_BLOCK);
	//
	//printf("\n*%#04x = %#04x", _uaddres, data);
	
	printf("\ndata: ");
	//
	uint8_t _data;
	//
	scanf("%u", &_data);
	//
	//printf_P(PSTR("\nwriting..."));
	//
	
	eeWriteByte(_uaddres, _data, HW_BLOCK);
	
	//
	//printf_P(PSTR("\ntesting..."));
	//
	//data = eeReadByte(_uaddres, HW_BLOCK);
	//
	//printf("\n*%#04x = %#04x", _uaddres, data);
	//
	//if (data!=_data)
	//{
	//printf(PSTR("\ns_err"));
	//}
	//else
	//{
	//printf(PSTR("\ns_ok"));
	//}
}

int main(void)
{
	setup();

	printf("\nq - read all ");
	printf("\nw - read * ");
	printf("\ne - write byte");
	printf("\nr - read all with manual output");
	printf("\nt - read range *");
				
	initDHT();
	
	while(TRUE)
	{
		//char buffer[8];
		//uint8_t temperature = 0;
		//temperature = dht11_gettemperature();
		//sprintf(buffer, "%02d", temperature);
		//printf(buffer);
		//_delay_ms(1000);
		
	
			//uint8_t data [4];
			////
			//int8_t i;
////
////
			////
			//if(fetchData(data))
			//{
				//for(i = data[2]; i >= 0; --i)
				//{
					//SET_BIT(PORTB,LED);
					//_delay_ms(1000);
					//
					//CLEAR_BIT(PORTB,LED);
					//_delay_ms(500);
				//}
			//}
//
		//
		////}

		//continue;
//
		printf("\n>");
		char _cmd[2];
		scanf("%s",&_cmd);
		//_cmd=getchar();//принимаем символ через usart в переменную choose

		printf("\n>>");
		printf(_cmd[0]);
		printf(_cmd[1]);
		printf(_cmd[2]);
		printf("\n>>");
		switch (_cmd[0])
		{
			case 'q':
			readAll();
			break;

			case 'w':
			readAddres();
			break;
			
			case 'e':
			writeByte();
			break;

			case 'r':
			readAllWithManualOutput();
			break;

			case 't':
			readAllRange();
			break;

			//default:
			//printf_P(PSTR("???\r\n"));
		}
		
		//else if  (_cmd=='e')
		//{
		//writeByte();
		//}
		//else
		//{
		////printf("\n???");
		//}
		//switch (_cmd)
		//{
		//case 'r1':
		//printf("\nr1");
		//break;
		//
		//case 'r2':
		//printf("\nr2");
		//break;
		//
		//default:printf_P(PSTR("???\r\n"));
		//}
		//printf("\nEnter EEPROM address to write: ");
		//
		//uint16_t _uaddres;
		//scanf("%u",&_uaddres);
		//printf_P(PSTR("\nReading current val..."));
		//
		//uint8_t data;
		//data = eeReadByte(_uaddres);
		//printf("\n*%#04x = %#04x", _uaddres, data);
		//
		//printf("\nEnter data to write to EEPROM at address %u: ", _uaddres);
		//
		//uint8_t _data;
		//
		//scanf("%u",&_data);
		//
		//printf_P(PSTR("\nWriting..."));
		//
		//eeWriteByte(_uaddres, _data);
		//
		//printf_P(PSTR("\nReading..."));
		//
		//data = eeReadByte(_uaddres);
		//
		//printf("\n*%#04x = %#04x", _uaddres, data);
	}

}

//typedef struct pglist_data {
//zone_t node_zones[MAX_NR_ZONES];
//zonelist_t node_zonelists[GFP_ZONEMASK+1];
//int nr_zones;
//struct page *node_mem_map;
//unsigned long *valid_addr_bitmap;
//struct bootmem_data *bdata;
//unsigned long node_start_paddr;
//unsigned long node_start_mapnr;
//unsigned long node_size;
//int node_id;
//struct pglist_data *node_next;
//} pg_data_t;//
//typedef struct zone_struct {
//spinlock_t lock;
//unsigned long free_pages;
//unsigned long pages_min, pages_low, pages_high;
//int need_balance;
//
//free_area_t free_area[MAX_ORDER];
//
//wait_queue_head_t * wait_table;
//unsigned long wait_table_size;
//unsigned long wait_table_shift;
//
//struct pglist_data *zone_pgdat;
//struct page *zone_mem_map;
//unsigned long zone_start_paddr;
//unsigned long zone_start_mapnr;
//
//char *name;
//unsigned long size;
//} zone_t;
//
//
//pg_data_t * pgdat;
//pgdat = pgdat_list;
//do {
///* do something with pgdata_t */
//...
//} while ((pgdat = pgdat->node_next));




////uint8_t eeWriteByte(uint16_t address,uint8_t data); //Запись байта в модуль памяти EEPROM
//
////uint8_t eeReadByte(uint16_t address); //Чтение байта из модуля памяти EEPROM
//
////v2
////
//eeWriteByte(100, 0x65);
//
//
//for (uint16_t curadr=100; curadr<110;curadr++)
//{
//
//uint8_t data;
//
//printf_P(PSTR("\nRead byte From eeprom"));
//data = eeReadByte(curadr);
//
//
////if (EEReadByte(curadr, &u8ebyte) != ERROR)
////{
//printf("\n*%#04x = %#04x", curadr, data);
////}
////else printf_P(PSTR("\nStatus fail!"));
//}
////v2
//
////TWIInit();
//////assign our stream to standard I/O streams
////stdin=stdout=&usart0_str;
////
////printf_P(PSTR("\nSTART"));
////
//////while(1)
//////{
//////printf("\nEnter EEPROM address to write (MAX = %u): ", EEMAXADDR);
//////scanf("%u",&u16eaddress);
//////
//////printf_P(PSTR("\nTesting..."));
//////if (EEReadByte(u16eaddress, &u8erbyte) !=ERROR)
//////{
//////printf("\n*%#04x = %#04x", u16eaddress, u8ebyte);
//////}
//////else printf_P(PSTR("\nStatus fail!"));
//////
////////TODO:: Please write your application code
//////}
////
////
//////printf_P(PSTR("\nSTART"));
////if (EEWriteByte(0x65, 0) == ERROR)
////{
////printf_P(PSTR("\nStatus fail!"));
////}
////
////for (uint16_t curadr=50; curadr<111;curadr++)
////{
////printf_P(PSTR("\nRead byte From eeprom"));
////if (EEReadByte(curadr, &u8ebyte) != ERROR)
////{
////printf("\n*%#04x = %#04x", curadr, u8ebyte);
////}
////else printf_P(PSTR("\nStatus fail!"));
////}
//////
//////
//////printf("\nWrite byte %#04x to eeprom address %#04x", 0x58, u16eaddress);
//////if (EEWriteByte(u16eaddress, 0x58) != ERROR)
//////{
//////printf_P(PSTR("\nRead byte From eeprom"));
//////if (EEReadByte(u16eaddress, &u8ebyte) != ERROR)
//////{
//////printf("\n*%#04x = %#04x", u16eaddress, u8ebyte);
//////}
//////else printf_P(PSTR("\nStatus fail!"));
//////
//////}
//////else printf_P(PSTR("\nStatus fail!"));
//////
//////printf_P(PSTR("\nWriting 16 bytes to page 5 "));
//////if(EEWritePage(page, eewritepage) != ERROR)
//////{
//////printf_P(PSTR("\nReading 16 bytes from page 5 "));
//////if (EEReadPage(page, eereadpage) != ERROR)
//////{
////////compare send and read buffers
//////for (i=0; i<16; i++)
//////{
//////if (eereadpage[i] != eewritepage[i])
//////{
//////break;
//////}
//////else continue;
//////}
//////if (i==16)
//////printf_P(PSTR("\nPage write and read success!"));
//////else
//////printf_P(PSTR("\nPage write and read fail!"));
//////} else printf_P(PSTR("\nStatus fail!"));
//////
//////}else printf_P(PSTR("\nStatus fail!"));
//////
//////printf_P(PSTR("\nContinue testing EEPROM from terminal!"));
//////while(1)
//////{
//////printf("\nEnter EEPROM address to write (MAX = %u): ", EEMAXADDR);
//////scanf("%u",&u16eaddress);
//////printf("Enter data to write to EEPROM at address %u: ", u16eaddress);
//////scanf("%u",&u8ebyte);
//////printf_P(PSTR("\nWriting..."));
//////EEWriteByte(u16eaddress, u8ebyte);
//////printf_P(PSTR("\nTesting..."));
//////if (EEReadByte(u16eaddress, &u8erbyte) !=ERROR)
//////{
//////if (u8ebyte==u8erbyte)
//////printf_P(PSTR("\nSuccess!"));
//////else
//////printf_P(PSTR("\nFail!"));
//////}
//////else printf_P(PSTR("\nStatus fail!"));
//////
////////TODO:: Please write your application code
//////}