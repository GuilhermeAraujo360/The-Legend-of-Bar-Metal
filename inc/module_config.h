#ifndef _MODULE_CONFIG_H_
#define _MODULE_CONFIG_H_
//  ====== OFFSETS =================================================
#define GPIO_OE (0x134)
#define GPIO_DATAOUT (0x13C)
#define GPIO_CLEARDATAOUT (0x190)
#define GPIO_SETDATAOUT (0x194) 
 

#define CONF_GPMC_A5    (0x854)   /* GPIO1_21  USR LED 0 */
#define CONF_GPMC_A6    (0x858)   /* GPIO1_22  USR LED 1 */
#define CONF_GPMC_A7    (0x85C)   /* GPIO1_23  USR LED 2 */
#define CONF_GPMC_A8    (0x860)   /* GPIO1_24  USR LED 3 */


#define CONF_GPMC_AD12  (0x830)   /*GPIO1_12*/
#define CONF_GPMC_CSN0  (0x87C)   /*GPIO1_29*/

#define CONF_MCASP0_FSR (0x9A4) /*GPIO3_19*/
#define CONF_MCASP0_AHCLKX (0x9AC) /*GPIO3_21*/
#define CONF_DATAIN (0x138) 

#define CONF_GPMC_AD13 (0x8D4) /*gpio1_13*/
#define CONF_GPMC_AD14 (0x8D8) /*gpio1_14*/
#define CONF_GPMC_AD15 (0x8DC) /*gpio1_15*/
#define conf_gpmc_ben1 (0x378) /*GPIO1_28*/
#define conf_gpmc_a0   (0x840) /*GPIO1_16*/

#define conf_gpmc_clk (0x88) /*gpio2_1*/

#define conf_gpmc_a1 (0x844) /*GPIO1_17*/

#define conf_lcd_data10 (0x8C8) /*GPIO2_16*/

#define conf_gpmc_ad4 (0x810) /*GPIO1_4*/

// =============================================================== 

#endif 
 
