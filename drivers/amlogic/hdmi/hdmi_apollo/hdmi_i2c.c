/*
 * Amlogic Apollo
 * frame buffer driver
 *	-------hdmi output
 * Copyright (C) 2009 Amlogic, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the named License,
 * or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Author:  zhou zhi<zhi.zhou@amlogic.com>
 * Firset add at:2009-7-28
 */  
    
#include <linux/version.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <linux/platform_device.h>
#include <linux/fb.h>
#include <linux/delay.h>
#include <linux/major.h>
    
#include <asm/uaccess.h>
    
#include "hdmi_module.h"
#include "hdmi_debug.h"
//#include "hdmi_reg_def.h"



{
	
//FIXME:Maybe the id is not equalt 0?
#define I2C_ID 0
	    
	
	



#define i2c_write_delay() msleep(1)

{
	

{
	
	


{
	
	reg};
	
	
				   b0,.len = 1} };
	
/*---------------------------------------------------------------*/ 
	    
	
		
		
			  ret);
		
		
	



#if 0
static int hdmi_i2c_read_buf(unsigned char device_addr, unsigned reg,
			     unsigned char *buf, int len) 
{
	
	
				   buf,.len = len} };
	
/*---------------------------------------------------------------*/ 
	    buf[0] = reg;
	
	
		
			  ret);
	



#endif	/* 
static int hdmi_i2c_write_reg(unsigned char device_addr, unsigned reg,
			      int data) 
{
	
	reg, data};
	
		    2 };
	
	
/*---------------------------------------------------------------*/ 
	    ret = i2c_transfer(hdmi_i2c_adapter, &msg, 1);
	
		
			  "(reg == 0x%02x, val == 0x%02x, ret == %i)\n",
			  
	
	



#if 0
static int hdmi_i2c_write_reg_word(unsigned char device_addr, unsigned reg,
				   int data) 
{
	
	reg, data & 0xff, (data >> 8) & 0xff};
	
	
		    3 };
	
/*---------------------------------------------------------------*/ 
	    
	
		
			  "(reg == 0x%02x, val == 0x%02x, ret == %i)\n",
			  
	
	


				 unsigned char *buf, int len) 
{
	
	
	
				   tempbuf,.len = len} };
	
/*---------------------------------------------------------------*/ 
	    tempbuf[0] = reg;
	
		
		
		    ("[I2C] Too long data to write to hdmi device,len=%d\n",
		     len);
		
		
	
	
	
		
	
	



#endif	/* 

{
	



//---------------------------------------------------------------------
unsigned short ReadWordHDMITX_CAT(unsigned addr) 
{
	
	
	
	    //  hdmi_i2c_read_buf(hdmi_slave_addr, addr, temp2, 2 );
	    
	
	
	



//---------------------------------------------------------------------
void ReadBlockHDMITX_CAT(unsigned char addr, unsigned short len,
			 unsigned char *bufer) 
{
	
	    // hdmi_i2c_read_buf(hdmi_slave_addr, addr, bufer, len );
	int i;
	
		



//--------------------------------------------------------------------- 
void WriteByteHDMITX_CAT(unsigned addr, unsigned char data) 
{
	
	



//---------------------------------------------------------------------
void WriteWordHDMITX_CAT(unsigned addr, unsigned short data) 
{
	
	


//---------------------------------------------------------------------
void WriteBlockHDMITX_CAT(unsigned char addr, unsigned short len,
			  unsigned char *bufer) 
{
	
	
		
	
	    //hdmi_i2c_write_buf(hdmi_slave_addr, addr, bufer, len );
}

