

/*
 *
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <asm/arch/timing.h>
#include <asm/arch/ddr_define.h>

/* DDR freq range */
#define CONFIG_DDR_CLK_LOW  20
#define CONFIG_DDR_CLK_HIGH 1500
/* DON'T OVER THESE RANGE */
#if (CONFIG_DDR_CLK < CONFIG_DDR_CLK_LOW) || (CONFIG_DDR_CLK > CONFIG_DDR_CLK_HIGH)
	#error "Over DDR PLL range! Please check CONFIG_DDR_CLK in board header file! \n"
#endif

/* CPU freq range */
#define CONFIG_CPU_CLK_LOW  600
#define CONFIG_CPU_CLK_HIGH 2000
/* DON'T OVER THESE RANGE */
#if (CONFIG_CPU_CLK < CONFIG_CPU_CLK_LOW) || (CONFIG_CPU_CLK > CONFIG_CPU_CLK_HIGH)
	#error "Over CPU PLL range! Please check CONFIG_CPU_CLK in board header file! \n"
#endif

#define DDR3_DRV_40OHM		0
#define DDR3_DRV_34OHM		1
#define DDR3_ODT_0OHM		0
#define DDR3_ODT_60OHM		1
#define DDR3_ODT_120OHM		2
#define DDR3_ODT_40OHM		3
#define DDR3_ODT_20OHM		4
#define DDR3_ODT_30OHM		5

/* lpddr2 drv odt */
#define LPDDR2_DRV_34OHM	1
#define LPDDR2_DRV_40OHM	2
#define LPDDR2_DRV_48OHM	3
#define LPDDR2_DRV_60OHM	4
#define LPDDR2_DRV_80OHM	6
#define LPDDR2_DRV_120OHM	7
#define LPDDR2_ODT_0OHM		0

/* lpddr3 drv odt */
#define LPDDR3_DRV_34OHM	1
#define LPDDR3_DRV_40OHM	2
#define LPDDR3_DRV_48OHM	3
#define LPDDR3_DRV_60OHM	4
#define LPDDR3_DRV_80OHM	6
#define LPDDR3_DRV_34_40OHM	9
#define LPDDR3_DRV_40_48OHM	10
#define LPDDR3_DRV_34_48OHM	11
#define LPDDR3_ODT_0OHM		0
#define LPDDR3_ODT_60OHM	1
#define LPDDR3_ODT_120OHM	2
#define LPDDR3_ODT_240OHM	3

#define DDR4_DRV_34OHM		0
#define DDR4_DRV_48OHM		1
#define DDR4_ODT_0OHM		0
#define DDR4_ODT_60OHM		1
#define DDR4_ODT_120OHM		2
#define DDR4_ODT_40OHM		3
#define DDR4_ODT_240OHM		4
#define DDR4_ODT_48OHM		5
#define DDR4_ODT_80OHM		6
#define DDR4_ODT_34OHM		7

#if ((CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_DDR3) || (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_AUTO))
#define CFG_DDR_DRV  DDR3_DRV_40OHM
#define CFG_DDR_ODT  DDR3_ODT_120OHM
#elif (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_LPDDR2)
#define CFG_DDR_DRV  LPDDR2_DRV_48OHM
#define CFG_DDR_ODT  DDR3_ODT_120OHM
#elif (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_LPDDR3)
#define CFG_DDR_DRV  LPDDR3_DRV_48OHM
#define CFG_DDR_ODT  LPDDR3_ODT_0OHM
#elif (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_DDR4)
#define CFG_DDR_DRV  DDR4_DRV_34OHM //useless, no effect
#define CFG_DDR_ODT  DDR4_ODT_60OHM //useless, no effect
#endif

#define CFG_DDR4_DRV  DDR4_DRV_34OHM //ddr4 driver use this one
#define CFG_DDR4_ODT  DDR4_ODT_60OHM //ddr4 driver use this one
//#define CFG_DDR4_DRV  DDR4_DRV_48OHM//DDR4_DRV_48OHM //ddr4 driver use this one
//#define CFG_DDR4_ODT DDR4_ODT_48OHM// DDR4_ODT_80OHM //ddr4 driver use this one
#if ((CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_DDR4) || (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_AUTO))
#define CONFIG_SOC_VREF    1+ (50+((50*48)/(48+480/(6+1)))) // 880/12  //(50+((50*48)/(48+160)))  //0//50+50*drv/(drv+odt)  (738/12) //0 //0  is auto --70 ---range 44.07---88.04   %
#define CONFIG_DRAM_VREF  1+ (50+((50*37)/(37+48)))// 860/12 // 0// (810/12) // 0 //77 //0 //0  is auto ---70 --range -- 45---92.50    %
#elif (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_LPDDR3)
#define CONFIG_SOC_VREF  51
#define CONFIG_DRAM_VREF 51
#else
#define CONFIG_SOC_VREF  51
#define CONFIG_DRAM_VREF 51
#endif

#define CONFIG_ZQ_VREF   51//60 //700/12//  60//0 //(50) % //tune ddr4 ,ddr3 use 0

/*
 * these parameters are corresponding to the pcb layout,
 * please don't enable this function unless these signals
 * has been measured by oscilloscope.
 */
#ifdef CONFIG_DDR_CMD_BDL_TUNE
#define DDR_AC_LCDLR   0
#define	DDR_CK0_BDL	18
#define	DDR_RAS_BDL	18
#define	DDR_CAS_BDL	24
#define	DDR_WE_BDL	21
#define	DDR_BA0_BDL	16
#define	DDR_BA1_BDL	2
#define	DDR_BA2_BDL	13
#define	DDR_ACPDD_BDL	27
#define	DDR_CS0_BDL	27
#define	DDR_CS1_BDL	27
#define	DDR_ODT0_BDL	27
#define	DDR_ODT1_BDL	27
#define	DDR_CKE0_BDL	27
#define	DDR_CKE1_BDL	27
#define	DDR_A0_BDL	14
#define	DDR_A1_BDL	9
#define	DDR_A2_BDL	5
#define	DDR_A3_BDL	18
#define	DDR_A4_BDL	4
#define	DDR_A5_BDL	16
#define	DDR_A6_BDL	1
#define	DDR_A7_BDL	10
#define	DDR_A8_BDL	4
#define	DDR_A9_BDL	7
#define	DDR_A10_BDL	10
#define	DDR_A11_BDL	9
#define	DDR_A12_BDL	6
#define	DDR_A13_BDL	16
#define	DDR_A14_BDL	8
#define	DDR_A15_BDL	27
#endif

/* CAUTION!! */
/*
 * For DDR3:
 *     7-7-7:    CONFIG_DDR_CLK range  375~ 533
 *     9-9-9:    CONFIG_DDR_CLK range  533~ 667
 *     11-11-11: CONFIG_DDR_CLK range  667~ 800
 *     12-12-12: CONFIG_DDR_CLK range  800~ 933
 *     13-13-13: CONFIG_DDR_CLK range  933~1066
 *     14-14-14: CONFIG_DDR_CLK range 1066~1200
 */
ddr_timing_t __ddr_timming[] = {
	//ddr3_7_7_7
	{
		.identifier				= CONFIG_DDR_TIMMING_DDR3_7,
		.cfg_ddr_rtp			= (6),
		.cfg_ddr_wtr			= (7),
		.cfg_ddr_rp				= (7),
		.cfg_ddr_rcd			= (7),
		.cfg_ddr_ras			= (20),
		.cfg_ddr_rrd			= (6),
		.cfg_ddr_rc				= (27),
		.cfg_ddr_mrd			= (4),
		.cfg_ddr_mod			= (12),
		.cfg_ddr_faw			= (27),
		.cfg_ddr_rfc			= (160),
		.cfg_ddr_wlmrd			= (40),
		.cfg_ddr_wlo			= (6),
		.cfg_ddr_xs				= (512),
		.cfg_ddr_xp				= (7),
		.cfg_ddr_cke			= (4),
		.cfg_ddr_dllk			= (512),
		.cfg_ddr_rtodt			= (0),
		.cfg_ddr_rtw			= (4),
		.cfg_ddr_refi			= (78-2),
		.cfg_ddr_refi_mddr3		= (4),
		.cfg_ddr_cl				= (7),
		.cfg_ddr_wr				= (12),
		.cfg_ddr_cwl			= (5),
		.cfg_ddr_al				= (0),
		.cfg_ddr_exsr			= (512),
		.cfg_ddr_dqs			= (4),
		.cfg_ddr_cksre			= (15),
		.cfg_ddr_cksrx			= (15),
		.cfg_ddr_zqcs			= (64),
		.cfg_ddr_zqcl			= (512),
		.cfg_ddr_xpdll			= (20),
		.cfg_ddr_zqcsi			= (1000),
	},
	//ddr3_9_9_9
	{
		.identifier				= CONFIG_DDR_TIMMING_DDR3_9,
		.cfg_ddr_rtp			= (6),
		.cfg_ddr_wtr			= (7),
		.cfg_ddr_rp				= (9),
		.cfg_ddr_rcd			= (9),
		.cfg_ddr_ras			= (27),
		.cfg_ddr_rrd			= (6),
		.cfg_ddr_rc				= (33),
		.cfg_ddr_mrd			= (4),
		.cfg_ddr_mod			= (12),
		.cfg_ddr_faw			= (30),
		.cfg_ddr_rfc			= (196),
		.cfg_ddr_wlmrd			= (40),
		.cfg_ddr_wlo			= (6),
		.cfg_ddr_xs				= (512),
		.cfg_ddr_xp				= (7),
		.cfg_ddr_cke			= (4),
		.cfg_ddr_dllk			= (512),
		.cfg_ddr_rtodt			= (0),
		.cfg_ddr_rtw			= (6),
		.cfg_ddr_refi			= (78-2),
		.cfg_ddr_refi_mddr3		= (4),
		.cfg_ddr_cl				= (9),
		.cfg_ddr_wr				= (12),
		.cfg_ddr_cwl			= (7),
		.cfg_ddr_al				= (0),
		.cfg_ddr_exsr			= (512),
		.cfg_ddr_dqs			= (23),
		.cfg_ddr_cksre			= (15),
		.cfg_ddr_cksrx			= (15),
		.cfg_ddr_zqcs			= (64),
		.cfg_ddr_zqcl			= (136),
		.cfg_ddr_xpdll			= (20),
		.cfg_ddr_zqcsi			= (1000),
	},
	//ddr3_11_11_11
	{
		.identifier				= CONFIG_DDR_TIMMING_DDR3_11,
		.cfg_ddr_rtp			= (7),
		.cfg_ddr_wtr			= (7),
		.cfg_ddr_rp				= (11),
		.cfg_ddr_rcd			= (11),
		.cfg_ddr_ras			= (35),
		.cfg_ddr_rrd			= (7),
		.cfg_ddr_rc				= (45),
		.cfg_ddr_mrd			= (6),
		.cfg_ddr_mod			= (12),
		.cfg_ddr_faw			= (33),
		.cfg_ddr_rfc			= (280),
		.cfg_ddr_wlmrd			= (40),
		.cfg_ddr_wlo			= (7),
		.cfg_ddr_xs				= (512),
		.cfg_ddr_xp				= (5),
		.cfg_ddr_cke			= (4),
		.cfg_ddr_dllk			= (512),
		.cfg_ddr_rtodt			= (0),
		.cfg_ddr_rtw			= (7),
		.cfg_ddr_refi			= (78-2),
		.cfg_ddr_refi_mddr3		= (4),
		.cfg_ddr_cl				= (11),
		.cfg_ddr_wr				= (12),
		.cfg_ddr_cwl			= (8),
		.cfg_ddr_al				= (0),
		.cfg_ddr_exsr			= (512),
		.cfg_ddr_dqs			= (23),
		.cfg_ddr_cksre			= (15),
		.cfg_ddr_cksrx			= (15),
		.cfg_ddr_zqcs			= (64),
		.cfg_ddr_zqcl			= (136),
		.cfg_ddr_xpdll			= (23),
		.cfg_ddr_zqcsi			= (1000),
	},
	//ddr3_13_13_13
	{
		.identifier				= CONFIG_DDR_TIMMING_DDR3_13,
		.cfg_ddr_rtp			= (7),
		.cfg_ddr_wtr			= (7),
		.cfg_ddr_rp				= (13),
		.cfg_ddr_rcd			= (13),
		.cfg_ddr_ras			= (37),
		.cfg_ddr_rrd			= (7),
		.cfg_ddr_rc				= (52),
		.cfg_ddr_mrd			= (6),
		.cfg_ddr_mod			= (12),
		.cfg_ddr_faw			= (33),
		.cfg_ddr_rfc			= (280),
		.cfg_ddr_wlmrd			= (40),
		.cfg_ddr_wlo			= (7),
		.cfg_ddr_xs				= (512),
		.cfg_ddr_xp				= (7),
		.cfg_ddr_cke			= (5),
		.cfg_ddr_dllk			= (512),
		.cfg_ddr_rtodt			= (0),
		.cfg_ddr_rtw			= (7),
		.cfg_ddr_refi			= (78-2),
		.cfg_ddr_refi_mddr3		= (4),
		.cfg_ddr_cl				= (13),
		.cfg_ddr_wr				= (16),
		.cfg_ddr_cwl			= (9),
		.cfg_ddr_al				= (0),
		.cfg_ddr_exsr			= (512),
		.cfg_ddr_dqs			= (23),
		.cfg_ddr_cksre			= (15),
		.cfg_ddr_cksrx			= (15),
		.cfg_ddr_zqcs			= (64),
		.cfg_ddr_zqcl			= (136),
		.cfg_ddr_xpdll			= (23),
		.cfg_ddr_zqcsi			= (1000),
	},
	/* ddr4 1600 timing */
	{
		.identifier				= CONFIG_DDR_TIMMING_DDR4_1600,
		.cfg_ddr_rtp			= (4),
		.cfg_ddr_wtr			= (6),
		.cfg_ddr_rp				= (11),
		.cfg_ddr_rcd			= (11),
		.cfg_ddr_ras			= (35),
		.cfg_ddr_rrd			= (4),
		.cfg_ddr_rc				= (46),//RAS+RP
		.cfg_ddr_mrd			= (8),
		.cfg_ddr_mod			= (24),
		.cfg_ddr_faw			= (28),
		.cfg_ddr_rfc			= (280),
		.cfg_ddr_wlmrd			= (40),
		.cfg_ddr_wlo			= (8),
		.cfg_ddr_xs				= (512),
		.cfg_ddr_xp				= (7),
		.cfg_ddr_cke			= (5),
		.cfg_ddr_dllk			= (1024),  //597 768 1024
		.cfg_ddr_rtodt			= (0),
		.cfg_ddr_rtw			= (7),
		.cfg_ddr_refi			= (78-2),
		.cfg_ddr_refi_mddr3		= (4),
		.cfg_ddr_cl				= (11),
		.cfg_ddr_wr				= (13),  //15NS+1CLK
		.cfg_ddr_cwl			= (11),
		.cfg_ddr_al				= (0),
		.cfg_ddr_exsr			= (1024),  //597 768 1024
		.cfg_ddr_dqs			= (23),
		.cfg_ddr_cksre			= (15),
		.cfg_ddr_cksrx			= (15),
		.cfg_ddr_zqcs			= 128,
		.cfg_ddr_zqcl			= (256),
		.cfg_ddr_xpdll			= (23),
		.cfg_ddr_zqcsi			= (1000),
		.cfg_ddr_tccdl			= (5),
	},
	/* ddr4 2400 timing */
	{
		.identifier				= CONFIG_DDR_TIMMING_DDR4_2400,
		.cfg_ddr_rtp			= 9,//(4),
		.cfg_ddr_wtr			= 9,//(6),
		.cfg_ddr_rp				= 15*1.2,//(11),
		.cfg_ddr_rcd			= 15*1.2,//(11),
		.cfg_ddr_ras			= 35*1.2,//(35),
		.cfg_ddr_rrd			= (8),
		.cfg_ddr_rc				=50*1.2,// (46),//RAS+RP
		.cfg_ddr_mrd			= (8),
		.cfg_ddr_mod			= (24),
		.cfg_ddr_faw			= 35*1.2,//(28),
		.cfg_ddr_rfc			= 350*1.2,//(280),
		.cfg_ddr_wlmrd			= (40),
		.cfg_ddr_wlo			= 9.5*1.2,//(8),
		.cfg_ddr_xs				= (512),
		.cfg_ddr_xp				= (7),
		.cfg_ddr_cke			= (5),
		.cfg_ddr_dllk			= (1024),  //597 768 1024
		.cfg_ddr_rtodt			= (0),
		.cfg_ddr_rtw			= (9),
		.cfg_ddr_refi			= (78-2),
		.cfg_ddr_refi_mddr3		= (4),
		.cfg_ddr_cl				= 15*1.2,// (11),
		.cfg_ddr_wr				= 15*1.2,// (13),  //15NS+1CLK
		.cfg_ddr_cwl			= 12,// (11),
		.cfg_ddr_al				= (0),
		.cfg_ddr_exsr			= (1024),  //597 768 1024
		.cfg_ddr_dqs			= 9,//12,//(23),  //6 7  8 9 10 11 ok ,bit0-3 max is 15 ,why use 15 is bad 2016_11_10 jiaxing ,test should change with ddr frequency ?
		.cfg_ddr_cksre			= (15),
		.cfg_ddr_cksrx			= (15),
		.cfg_ddr_zqcs			= 128,
		.cfg_ddr_zqcl			= (256),
		.cfg_ddr_xpdll			= (23),
		.cfg_ddr_zqcsi			= (1000),
		.cfg_ddr_tccdl			= (6),
	},
	/* lpddr3 timing */
	{
		.identifier				= CONFIG_DDR_TIMMING_LPDDR3,
		.cfg_ddr_rtp			= 6,// (6),0
		.cfg_ddr_wtr			= (6+2),
		.cfg_ddr_rp				= (17),
		.cfg_ddr_rcd			= (15),
		.cfg_ddr_ras			= (34),
		.cfg_ddr_rrd			= (8),
		.cfg_ddr_rc				= (51),
		.cfg_ddr_mrd			= (11),
		.cfg_ddr_mod			= (12),//12-17
		.cfg_ddr_faw			= (40),
		.cfg_ddr_rfc			= (168),
		.cfg_ddr_wlmrd			= (32),
		.cfg_ddr_wlo			= (8),
		.cfg_ddr_xs				= (512),
		.cfg_ddr_xp				= (6),
		.cfg_ddr_cke			= 7,//(6),//need <=7
		.cfg_ddr_dllk			= (512),
		.cfg_ddr_rtodt			= (0),
		.cfg_ddr_rtw			= (7),
		.cfg_ddr_refi			= (39-2),
		.cfg_ddr_refi_mddr3		= (0),
		.cfg_ddr_cl				= (12),
		.cfg_ddr_wr				= (12),
		.cfg_ddr_cwl			= (6),
		.cfg_ddr_al				= (0),
		.cfg_ddr_exsr			= (112),
		.cfg_ddr_dqs			= 9,//9,// (4),//rank0 rank1 turn aroud time jiaxing modify should big for 2rank lpddr3
		.cfg_ddr_cksre			= 12,// (12),//pctl need 2?
		.cfg_ddr_cksrx			= 12,// (12),//pctl need 2?
		.cfg_ddr_zqcs			= (100),
		.cfg_ddr_zqcl			= (288),
		.cfg_ddr_xpdll			= (12),
		.cfg_ddr_zqcsi			= (1000),
	//	.cfg_ddr_rpab			= (17),
	//	.cfg_ddr_rppb			= (15),
	//	.cfg_ddr_tdqsck			= (3),//2500-5500ps if no gate training should (int+1)
	//	.cfg_ddr_tdqsckmax		= (5),
	//	.cfg_ddr_tckesr			= (12),
	//	.cfg_ddr_tdpd			= (500),
	//	.cfg_ddr_taond_aofd		= 2,
	}
};

ddr_set_t __ddr_setting = {
	/* common and function defines */
	.ddr_channel_set		= CONFIG_DDR_CHANNEL_SET,
	.ddr_type				= CONFIG_DDR_TYPE,
	.ddr_clk				= CONFIG_DDR_CLK,
	.ddr4_clk				= CONFIG_DDR4_CLK,
	.ddr_base_addr			= CFG_DDR_BASE_ADDR,
	.ddr_start_offset		= CFG_DDR_START_OFFSET,
	.ddr_timing_ind			= 0,
	.ddr_size				= CONFIG_DDR_SIZE,
	.ddr_pll_ctrl			= (0),
	.ddr_dmc_ctrl			= 0,
#if (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_LPDDR3)
#if (CONFIG_LPDDR_REMAP_SET ==  LPDDR_DIE_ROW_COL_R14_C9)
	.ddr0_addrmap			= {
								[0]=( 5 |  6 << 5 |  7 << 10 |  8 << 15 |  9 << 20 | 10 << 25) ,
								[1]=( 11| 0<< 5 | 0 << 10 | 14 << 15 | 15 << 20 | 16 << 25 ) ,
								[2]=( 17| 18 << 5 | 19 << 10 | 20 << 15 | 21<< 20 | 22 << 25 ) ,
								[3]=( 23| 24 << 5 | 25 << 10 | 26 << 15 | 27 << 20 |29 << 25 ) ,
								[4]=( 0| 12 << 5 | 13 << 10 | 28 << 15 | 0 << 20 | 0 << 25 ) ,
	},
	.ddr1_addrmap			= {
								[0]=( 5 |  6 << 5 |  7 << 10 |  8 << 15 |  9 << 20 | 10 << 25) ,
								[1]=( 11| 0<< 5 | 0 << 10 | 14 << 15 | 15 << 20 | 16 << 25 ) ,
								[2]=( 17| 18 << 5 | 19 << 10 | 20 << 15 | 21<< 20 | 22 << 25 ) ,
								[3]=( 23| 24 << 5 | 25 << 10 | 26 << 15 | 27 << 20 |29 << 25 ) ,
								[4]=( 0| 12 << 5 | 13 << 10 | 28 << 15 | 0 << 20 | 0 << 25 ) ,
	},
#elif (CONFIG_LPDDR_REMAP_SET==  LPDDR_DIE_ROW_COL_R13_C10)
	.ddr0_addrmap			= {
								[0]=( 5 |  6 << 5 |  7 << 10 |  8 << 15 |  9 << 20 | 10 << 25) ,
								[1]=( 11| 29 << 5 | 0 << 10 | 14 << 15 | 15 << 20 | 16 << 25 ) ,
								[2]=( 17| 18 << 5 | 19 << 10 | 20 << 15 | 21<< 20 | 22 << 25 ) ,
								[3]=( 23| 24 << 5 | 25 << 10 | 26 << 15 | 27 << 20 | 30 << 25 ) ,
								[4]=( 31| 12 << 5 | 13 << 10 | 28 << 15 | 0 << 20 | 0 << 25 ) ,
	},
	.ddr1_addrmap			= {
								[0]=( 5 |  6 << 5 |  7 << 10 |  8 << 15 |  9 << 20 | 10 << 25) ,
								[1]=( 11| 29 << 5 | 0 << 10 | 14 << 15 | 15 << 20 | 16 << 25 ) ,
								[2]=( 17| 18 << 5 | 19 << 10 | 20 << 15 | 21<< 20 | 22 << 25 ) ,
								[3]=( 23| 24 << 5 | 25 << 10 | 26 << 15 | 27 << 20 | 30 << 25 ) ,
								[4]=( 31| 12 << 5 | 13 << 10 | 28 << 15 | 0 << 20 | 0 << 25 ) ,
	},
#endif /*CONFIG_LPDDR_REMAP_SET*/
#else
	.ddr0_addrmap			= {0},
	.ddr1_addrmap			= {0},
#endif /*CONFIG_DDR_TYPE_LPDDR3*/
	.ddr_2t_mode			= 1,
	.ddr_full_test			= CONFIG_DDR_FULL_TEST,
#if (0 == CONFIG_DDR_SIZE)
	.ddr_size_detect		= 1,
#else
	.ddr_size_detect		= 0,
#endif
	.ddr_drv				= CFG_DDR_DRV,
	.ddr_odt				= CFG_DDR_ODT,
	.ddr4_drv				= CFG_DDR4_DRV,
	.ddr4_odt				= CFG_DDR4_ODT,

	/* pub defines */
	.t_pub_ptr				= {
							[0] = ( 6 | (320 << 6) | (80 << 21)),
							[1] = (120 | (1000 << 16)),
							[2] = 0,
							[3] = (20000 | (136 << 20)),
							[4] = (1000 | (180 << 16)),
							},  //PUB PTR0-3
	.t_pub_odtcr			= 0x00030000,
	.t_pub_mr				= {
							(0X0 | (0X1 << 2) | (0X0 << 3) | (0X0 << 4) | (0X0 << 7) | (0X0 << 8) | (0X7 << 9) | (1 << 12)),
							(0X6|(1<<6)),
							0X20,
							0,
							},
	.t_pub_dtpr				= {0},
	.t_pub_pgcr0			= 0x07d81e3f,   //PUB PGCR0
	.t_pub_pgcr1			= 0x02004620,   //PUB PGCR1
	.t_pub_pgcr2			= 0x00f05f97,   //PUB PGCR2
	//.t_pub_pgcr2			= 0x01f12480,   //PUB PGCR2
	.t_pub_pgcr3			= 0xc0aae860,   //PUB PGCR3
	.t_pub_dxccr			= 0x20c01ee4,   //PUB DXCCR
	.t_pub_aciocr			= {0},  //PUB ACIOCRx
	.t_pub_dx0gcr			= {0},  //PUB DX0GCRx
	.t_pub_dx1gcr			= {0},  //PUB DX1GCRx
	.t_pub_dx2gcr			= {0},  //PUB DX2GCRx
	.t_pub_dx3gcr			= {0},  //PUB DX3GCRx
#if (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_DDR3)
	.t_pub_dcr				= 0XB,     //PUB DCR
	.t_pub_dtcr0			= 0x80003187,    //PUB DTCR //S905 use 0x800031c7
	.t_pub_dtcr1			= 0x00010237,    //PUB DTCR
	.t_pub_dsgcr			= 0x020641b,
#elif (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_DDR4)
	.t_pub_dcr				= 0X40C,     //PUB DCR
	.t_pub_dtcr0			= 0x800031c7,    //PUB DTCR //S905 use 0x800031c7
	.t_pub_dtcr1			= 0x00010237,
	.t_pub_dsgcr			= 0x020641b,
#elif (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_LPDDR3)
	.t_pub_dcr				= 0X89,     //PUB DCR
	.t_pub_dtcr0			= 0x80003187,    //PUB DTCR //S905 use 0x800031c7
	.t_pub_dtcr1			= 0x00010237,
	.t_pub_dsgcr			= 0x02064db,
#elif (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_AUTO)
	.t_pub_dcr				= 0XB,     //PUB DCR
	.t_pub_dtcr0			= 0x80003187,    //PUB DTCR //S905 use 0x800031c7
	.t_pub_dtcr1			= 0x00010237,    //PUB DTCR
	.t_pub_dsgcr			= 0x020641b,
#endif
	.t_pub_vtcr1			= 0x0fc00172,
	.t_pub_dtar				= (0X0 | (0X0 <<12) | (0 << 28)),

#if (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_LPDDR3)
//lpddr3
	.t_pub_zq0pr			= 0x0ca1c, //0x0ca1c,   //PUB ZQ0PR  //lpddr3
	.t_pub_zq1pr			= 0x1cf3c,   //PUB ZQ1PR
	.t_pub_zq2pr			= 0x1cf3c,   //PUB ZQ2PR
	.t_pub_zq3pr			= 0x1dd1d,   //PUB ZQ3PR

/* 2layer board
	.t_pub_zq0pr			= 0x00007759,   //PUB ZQ0PR, 0x5aa59,0x59959,  0x58859,  //99drriver s912 ddr4 maybe 950m is bad
	.t_pub_zq1pr			= 0x0006fc5d,   //PUB ZQ1PR//0x8fc5d, 0x4f95d,
	.t_pub_zq2pr			= 0x0006fc5d,   //PUB ZQ2PR//0x3fc5d, 0x4f95d,
*/
#elif (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_DDR4)
/* 4layer ddr4 */
	.t_pub_zq0pr			= 0x0995d,   //PUB ZQ0PR
	.t_pub_zq1pr			= 0x3f95d,   //PUB ZQ1PR
	.t_pub_zq2pr			= 0x3f95d,   //PUB ZQ2PR
	.t_pub_zq3pr			= 0x1dd1d,   //PUB ZQ3PR
#else // ddr3 and auto
/* p212 4layer board ddr3 */
	.t_pub_zq0pr			= 0x5d95d,   //PUB ZQ0PR
	.t_pub_zq1pr			= 0x5d95d,   //PUB ZQ1PR
	.t_pub_zq2pr			= 0x5d95d,   //PUB ZQ2PR
	.t_pub_zq3pr			= 0x1dd1d,   //PUB ZQ3PR
#endif

	/* pctl0 defines */
	/* pctl1 use same define as pctl0 */
	.t_pctl0_1us_pck		= CONFIG_DDR_CLK / 2,   //PCTL TOGCNT1U
	.t_pctl0_100ns_pck		= CONFIG_DDR_CLK / 20, //PCTL TOGCNT100N
	.t_pctl0_init_us		= 2,   //PCTL TINIT
	.t_pctl0_rsth_us		= 2,   //PCTL TRSTH
	.t_pctl0_mcfg			= 0XA2F01,   //PCTL MCFG default 1T
	//.t_pctl0_mcfg1			= 0X80000000,  //PCTL MCFG1
	.t_pctl0_mcfg1			= 0, //[B10,B9,B8] tfaw_cfg_offset
								//tFAW= (4 + MCFG.tfaw_cfg)*tRRD - tfaw_cfg_offset,  //PCTL MCFG1
	.t_pctl0_scfg			= 0xF01,   //PCTL SCFG
	.t_pctl0_sctl			= 0x1,   //PCTL SCTL
	.t_pctl0_ppcfg			= 0,
	.t_pctl0_dfistcfg0		= 0x4,
	.t_pctl0_dfistcfg1		= 0x1,
	.t_pctl0_dfitctrldelay	= 2,
	.t_pctl0_dfitphywrdata	= 2,
	.t_pctl0_dfitphywrlta	= 7,
	.t_pctl0_dfitrddataen	= 8,
	.t_pctl0_dfitphyrdlat	= 22,
	.t_pctl0_dfitdramclkdis	= 1,
	.t_pctl0_dfitdramclken	= 1,
	.t_pctl0_dfitphyupdtype0 = 16,
	.t_pctl0_dfitphyupdtype1 = 16,
	.t_pctl0_dfitctrlupdmin	= 16,
	.t_pctl0_dfitctrlupdmax	= 64,
	.t_pctl0_dfiupdcfg		= 0x3,
	.t_pctl0_cmdtstaten		= 1,
	//.t_pctl0_dfiodtcfg		= 8,
	//.t_pctl0_dfiodtcfg1		= ( 0x0 | (0x6 << 16) ),
	.t_pctl0_dfiodtcfg		= (1<<3)|(1<<11),
	.t_pctl0_dfiodtcfg1		= (0x0 | (0x6 << 16)),

	.t_pctl0_dfilpcfg0		= ( 1 | (3 << 4) | (1 << 8) | (13 << 12) | (7 <<16) | (1 <<24) | ( 3 << 28)),

///*lpddr3
#if (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_LPDDR3)
	.t_pub_acbdlr0			= 0,  //CK0 delay fine tune  TAKE CARE LPDDR3 ADD/CMD DELAY
	.t_pub_aclcdlr			= 0,
	.t_pub_acbdlr3			= 0x2020,//0,  //CK0 delay fine tune b-3f  //lpddr3 tianhe 2016-10-13
#elif (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_DDR4)
//2layer board DDR4
	.t_pub_acbdlr0			= 0, //0x3f,
	.t_pub_aclcdlr			= 0, //0x28,//0x18,   ///1t  ,if 2t can add some value
	.t_pub_acbdlr3			= 0, //0x10,// 0x10,//0xa,  //cs    add 22ohm 08  0ohm 0x10
#else // ddr3 and auto
//4layer ddr3
	.t_pub_acbdlr0			= 0,
	.t_pub_aclcdlr			= 0,//0x18,   ///1t  ,if 2t can add some value
	.t_pub_acbdlr3			= 0,//0xa,  //cs
#endif
	.t_pub_soc_vref_dram_vref =((((CONFIG_SOC_VREF<45)?(0):((((CONFIG_SOC_VREF*1000-44070)/698)>0X3F)?(0X3F):(((CONFIG_SOC_VREF*1000-44070)/698))))<<8)|(
	(((CONFIG_DRAM_VREF))<45)?(0):((((CONFIG_DRAM_VREF))<61)?((((((CONFIG_DRAM_VREF*1000-45000)/650)>0X32)?(0X32):(((CONFIG_DRAM_VREF*1000-45000)/650)))|(1<<6))):
	((((CONFIG_DRAM_VREF*1000-60000)/650)>0X32)?(0X32):(((CONFIG_DRAM_VREF*1000-60000)/650)))))),
	.t_pub_mr[7]	= ((CONFIG_ZQ_VREF<45)?(0):((((CONFIG_ZQ_VREF*1000-44070)/698)>0X3F)?(0X3F):(((CONFIG_ZQ_VREF*1000-44070)/698)))) ,//jiaxing use for tune zq vref 20160608
	.ddr_func				= DDR_FUNC, /* ddr func demo 2016.01.26 */

#if (CONFIG_DDR_TYPE == CONFIG_DDR_TYPE_LPDDR3)
	//tianhe lpddr3 20161013
	.wr_adj_per 			= {
							[0] = 90, //aclcdlr
							[1] = 100,
							[2] = 120,
							[3] = 110,
							[4] = 120,
							[5] = 105,
							},
	.rd_adj_per				= {
							[0] = 100,
							[1] = 100,
							[2] = 110,
							[3] = 110,
							[4] = 110,
							[5] = 110,},
#else
	/* P212 */
	.wr_adj_per				= {
							[0]=100,
							[1]=100,
							[2]=95,
							[3]=95,
							[4]=95,
							[5]=95,
							},
	.rd_adj_per				= {
							[0]=100,
							[1]=100,
							[2]=88,
							[3]=95,
							[4]=95,
							[5]=100,
							},
#endif

};

pll_set_t __pll_setting = {
	.cpu_clk				= CONFIG_CPU_CLK / 24 * 24,
	.spi_ctrl				= 0,
	.vddee					= CONFIG_VDDEE_INIT_VOLTAGE,
	.vcck					= CONFIG_VCCKA_INIT_VOLTAGE,
	.lCustomerID			= CONFIG_AML_CUSTOMER_ID,
#ifdef CONFIG_DEBUG_MODE
	.debug_mode				= CONFIG_DEBUG_MODE,
	.ddr_clk_debug			= CONFIG_DDR_CLK_DEBUG,
	.cpu_clk_debug			= CONFIG_CPU_CLK_DEBUG,
#endif
	/* pll ssc setting:

	.ddr_pll_ssc = 0x00120000, ppm1000 center SS, boot log show: Set ddr ssc: ppm1000
	.ddr_pll_ssc = 0x00124000, ppm1000 up SS,     boot log show: Set ddr ssc: ppm1000+
	.ddr_pll_ssc = 0x00128000, ppm1000 down SS,   boot log show: Set ddr ssc: ppm1000-

	.ddr_pll_ssc = 0x00140000, ppm2000 center SS, boot log show: Set ddr ssc: ppm2000
	.ddr_pll_ssc = 0x00144000, ppm2000 up SS,     boot log show: Set ddr ssc: ppm2000+
	.ddr_pll_ssc = 0x00148000, ppm2000 down SS,   boot log show: Set ddr ssc: ppm2000-

	.ddr_pll_ssc = 0x00160000, ppm3000 center SS, boot log show: Set ddr ssc: ppm3000
	.ddr_pll_ssc = 0x00164000, ppm3000 up SS,     boot log show: Set ddr ssc: ppm3000+
	.ddr_pll_ssc = 0x00168000, ppm3000 down SS,   boot log show: Set ddr ssc: ppm3000-
	*/
	.ddr_pll_ssc			= 0,
};
