#include <nds.h>

#include <stdio.h>
#include <string>

#define DIGIT_RANGE 10
#define OEM_DAY_RANGE 367

//typedef enum { FALSE, TRUE } bool;

bool gen;
bool display_keys;

int oem_key_year[2];
int oem_key_5[5];
int oem_key_5_random[5];
int retail_key_1[3];
int retail_key_2[7];

int oem_key_day;
int digit;
int sum7;

int sw_clock;

void gen_oem_day() 
{
    gen = true;
    while(gen) 
    {
        oem_key_day = rand() % OEM_DAY_RANGE;

        if(oem_key_day == 0)
        {
            gen = true;
        }
        else
        {
            gen = false;
        }
    }
}

void gen_oem_year() 
{
    gen = true;
    while(gen) 
    {
        for(digit=0; digit<2; ++digit)
        oem_key_year[digit] = rand() % DIGIT_RANGE;

        if((oem_key_year[0] == 9 && oem_key_year[1] >= 5) || (oem_key_year[0] == 0 && oem_key_year[1] < 3))
        {
            gen = false;
        }
        else
        {
            gen = true;
        }
    }
}

void gen_5digits_oem()
{
    gen = TRUE;
    while(gen)
    {
        for(digit=0; digit<5; ++digit)
        oem_key_5[digit] = rand() % DIGIT_RANGE;

        sum7 = oem_key_5[0] + oem_key_5[1] + oem_key_5[2] + oem_key_5[3] + oem_key_5[4];

        if(sum7 % 7 == 0)
        {
            gen = false;
        }
        else
        {
            gen = true;
        }
    }
}

void gen_5digits_random_oem()
{
    for(digit=0; digit<5; ++digit)
    oem_key_5_random[digit] = rand() % DIGIT_RANGE;   
}



void gen_3digits_retail() 
{
    gen = true;
    while(gen) 
    {
        for(digit=0; digit<3; ++digit)
        retail_key_1[digit] = rand() % DIGIT_RANGE;

        if((retail_key_1[0] == 3 && retail_key_1[1] == 3 && retail_key_1[2] == 3) || (retail_key_1[0] == 4 && retail_key_1[1] == 4 && retail_key_1[2] == 4) || (retail_key_1[0] == 5 && retail_key_1[1] == 5 && retail_key_1[2] == 5) || (retail_key_1[0] == 6 && retail_key_1[1] == 6 && retail_key_1[2] == 6) || (retail_key_1[0] == 7 && retail_key_1[1] == 7 && retail_key_1[2] == 7) || (retail_key_1[0] == 8 && retail_key_1[1] == 8 && retail_key_1[2] == 8) || (retail_key_1[0] == 9 && retail_key_1[1] == 9 && retail_key_1[2] == 9))
        {
            gen = true;
        }
        else
        {
            gen = false;
        }
    }
}

void gen_7digits_retail()
{
    gen = true;
    while(gen)
    {
        for(digit=0; digit<7; ++digit)
        retail_key_2[digit] = rand() % DIGIT_RANGE;

        sum7 = retail_key_2[0] + retail_key_2[1] + retail_key_2[2] + retail_key_2[3] + retail_key_2[4] + retail_key_2[5] + retail_key_2[6];

        if(sum7 % 7 == 0)
        {
            gen = false;
        }
        else
        {
            gen = true;
        }
    }
}

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	srand(sw_clock);
	consoleDemoInit();
	iprintf("press a to generate a win 95 key!\n");

	while(1) {
		swiWaitForVBlank();
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;
		if(keys & KEY_A){
			gen_3digits_retail();
			gen_7digits_retail();
			gen_oem_day();
			gen_oem_year();
			gen_5digits_oem();
			gen_5digits_random_oem();
			//Retail Product Key: %d%d%d-%d%d%d%d%d%d%d\nOEM Product Key: %03d%d%d-OEM-00%d%d%d%d%d-%d%d%d%d%d\n\n
			std::string daKey = "RETAIL PRODUCT KEY: " + std::to_string(retail_key_1[0]) + std::to_string(retail_key_1[1]) + std::to_string(retail_key_1[2]) + "-" 
			+ std::to_string(retail_key_2[0]) + std::to_string(retail_key_2[1]) + std::to_string(retail_key_2[2]) + std::to_string(retail_key_2[3]) + std::to_string(retail_key_2[4]) + std::to_string(retail_key_2[5]) + std::to_string(retail_key_2[6]) + "\n" 
			
			"OEM PRODUCT KEY: 03"+ std::to_string(oem_key_day) +std::to_string(oem_key_year[0]) + std::to_string(oem_key_year[1]) + "-OEM-00"
			+ std::to_string(oem_key_5[0]) + std::to_string(oem_key_5[1]) + std::to_string(oem_key_5[2]) + std::to_string(oem_key_5[3]) + std::to_string(oem_key_5[4]) + "-"
			+ std::to_string(oem_key_5_random[0]) + std::to_string(oem_key_5_random[1]) + std::to_string(oem_key_5_random[2]) + std::to_string(oem_key_5_random[3]) + std::to_string(oem_key_5_random[4]) + "\n";
			
			iprintf(daKey.c_str());
		}
	}

	return 0;
}