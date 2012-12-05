
#include <linux/version.h> 
#include <linux/kernel.h>
#include <linux/string.h>
    
#include "hdmi_debug.h"
    
#include "hdmi_cat_defstx.h"
#include "hdmi_i2c.h"
#include "hdmi_cat_hdcp.h"
#include "hdmi_cat_mddc.h"
#include "hdmi_cat_interrupt.h"
    
#define rol(x,y) (((x) << (y)) | (((unsigned long)x) >> (32-y)))










{
	
	
	
	
	
	
	WriteByteHDMITX_CAT(REG_INT_CLR1, 0);
	
	    //To clear all interrupt indicated by reg0C and reg0D bits set as 1, write reg0E[0] = 1, then write reg0E[0] = 0.
	    WriteByteHDMITX_CAT(REG_SYS_STATUS, B_INTACTDONE);

{
	
	
	
	uc = ReadByteHDMITX_CAT(REG_SW_RST);
	
	
	
	    //Switch HDCP controller or PC host to command the DDC port: 0: HDCP; 1: PC
	    WriteByteHDMITX_CAT(REG_DDC_MASTER_CTRL, B_MASTERDDC | B_MASTERHOST);	//switch PC 
	
	

{
	
	
	
	mddc_info[0] = B_MASTERDDC | B_MASTERHOST;	//Switch HDCP controller or PC host to command the DDC port: 0: HDCP; 1: PC
	mddc_info[1] = DDC_HDCP_ADDRESS;
	
	mddc_info[3] = 2;
	
	
//    WriteByteHDMITX_CAT(REG_DDC_MASTER_CTRL,B_MASTERDDC|B_MASTERHOST) ;
//    WriteByteHDMITX_CAT(REG_DDC_HEADER,DDC_HDCP_ADDRESS) ;
//    WriteByteHDMITX_CAT(REG_DDC_REQOFF,0x08) ; // Ri offset
//    WriteByteHDMITX_CAT(REG_DDC_REQCOUNT,2) ;
	    WriteByteHDMITX_CAT(REG_DDC_CMD, CMD_DDC_SEQ_BURSTREAD);
	
		
		
		
		
			
			
			
			
		
			
			
			
			
		
	



//////////////////////////////////////////////////////////////////////
// Function: CAT_HDCP_GetBCaps
// Parameter: pBCaps - pointer of byte to get BCaps.
//            pBStatus - pointer of two bytes to get BStatus
// Return: 0 if successfully got BCaps and BStatus.
// Remark: get B status and capability from HDCP reciever via DDC bus.
//////////////////////////////////////////////////////////////////////
static int CAT_HDCP_GetBCaps(unsigned char *pBCaps, unsigned short *pBStatus) 
{
	
	
	
	
	mddc_info[1] = DDC_HDCP_ADDRESS;
	
	mddc_info[3] = 3;
	
	
//    WriteByteHDMITX_CAT(REG_DDC_MASTER_CTRL, B_MASTERDDC|B_MASTERHOST) ;     
//    WriteByteHDMITX_CAT(REG_DDC_HEADER, DDC_HDCP_ADDRESS) ;
//    WriteByteHDMITX_CAT(REG_DDC_REQOFF, DDC_BCAPS_ADDR) ; 
//    WriteByteHDMITX_CAT(REG_DDC_REQCOUNT,3) ;
	    
	
		
		
		
		
			
			
			
//            printf("HDCP_GetBCaps(): DDC Done.\n"); 
			    break;
			
		
			
			
			
//            printf("HDCP_GetBCaps(): DDC fail by reg16=%02X.\n",ucdata) ;
			    CAT_ClearDDCFIFO();
			
			
		
	
		
		
		
//        printf("HDCP_GetBCaps(): TimeOut\n") ;
		    return -1;
		
	
	else			//read the datas
	{
	
	
	
	*pBStatus = (unsigned short)(mddc_info[0] | (mddc_info[1] << 8));
	
	*pBCaps = mddc_info[0];
	



//////////////////////////////////////////////////////////////////////
// Function: CAT_HDCP_GetBKSV
// Parameter: pBKSV - pointer of 5 bytes buffer for getting BKSV
// Return: 0 if successfuly got BKSV from Rx.
// Remark: Get BKSV from HDCP reciever.
//////////////////////////////////////////////////////////////////////
static int CAT_HDCP_GetBKSV(Hdmi_info_para_t * info, unsigned char *pBKSV) 
{
	
	
	
	
	mddc_info[1] = DDC_HDCP_ADDRESS;
	
	mddc_info[3] = 5;
	
	
//    WriteByteHDMITX_CAT(REG_DDC_MASTER_CTRL, B_MASTERDDC|B_MASTERHOST);    
//    WriteByteHDMITX_CAT(REG_DDC_HEADER, DDC_HDCP_ADDRESS) ;
//    WriteByteHDMITX_CAT(REG_DDC_REQOFF, DDC_BKSV_ADDR) ; 
//    WriteByteHDMITX_CAT(REG_DDC_REQCOUNT,5) ;
	    WriteByteHDMITX_CAT(REG_DDC_CMD, CMD_DDC_SEQ_BURSTREAD);
	
		
		
		
		
			
			
			
//            printf("HDCP_GetBKSV(): DDC Done.\n") ;
			    break;
			
		
			
			
			    ("CAT_HDCP_GetBKSV(): DDC No ack or arbilose, maybe cable did not connected. Fail.\n");
			
//            printf("CAT_HDCP_GetBKSV(): DDC No ack or arbilose, maybe cable did not connected. Fail.\n") ;
			    return -1;
			
		
	
		
		
		
	
	
		
		
			
			
			
			
		
	
	
		
		
		
			
				
			
		
		
	
		
	
	else
		



//////////////////////////////////////////////////////////////////////
// Function: CAT_HDCP_Auth_Fire()
// Parameter: N/A
// Return: N/A
// Remark: write anything to reg21 to enable HDCP authentication by HW
//////////////////////////////////////////////////////////////////////
static void CAT_HDCP_Auth_Fire(void) 
{
	
	    //the DDC master switch to HDCP Tx core and all DDC communication will be automatically done   
	    WriteByteHDMITX_CAT(REG_DDC_MASTER_CTRL, B_MASTERDDC | B_MASTERHDCP);	// MASTERHDCP,no need command but fire.
	
} 

//////////////////////////////////////////////////////////////////////
// Function: CAT_HDCP_GenerateAn
// Parameter: N/A
// Return: N/A
// Remark: start An ciper random run at first,then stop it. Software can get
//         an in reg30~reg38,the write to reg28~2F
// Side-Effect:
// To generate an available An, set Reg1F[0] as ��0�� to stop cipher running, 
// and an new useful An will be generated in Reg30~Reg37.
//////////////////////////////////////////////////////////////////////
static void CAT_HDCP_GenerateAn(void) 
{
	
	
	
	AVTimeDly(1);
	
	
	WriteBlockHDMITX_CAT(REG_AN, 8, Data);	//write the new An into register 0x28~0x2f
} 
{
	
	
	CAT_AbortDDC();
	
	CAT_HDCP_ClearAuthInterrupt();

				     unsigned char cDownStream) 
{
	
	
	
		
		
		
	
	mddc_info[1] = DDC_HDCP_ADDRESS;
	
	
	
	
//    WriteByteHDMITX_CAT(REG_DDC_MASTER_CTRL, B_MASTERHOST) ;
//    WriteByteHDMITX_CAT(REG_DDC_HEADER, DDC_HDCP_ADDRESS) ;
//    WriteByteHDMITX_CAT(REG_DDC_REQOFF, REG_BCAP) ;
//    WriteByteHDMITX_CAT(REG_DDC_REQCOUNT, cDownStream * 5) ;
	    WriteByteHDMITX_CAT(REG_DDC_CMD, CMD_DDC_SEQ_BURSTREAD);
	
		
		
		
			
			
			
//            printf("HDCP_GetKSVList(): DDC Done.\n") ;
			    break;
			
		
			
			
			    ("HDCP_GetKSVList(): DDC Fail by REG_DDC_STATUS \n");
			
//            printf("HDCP_GetKSVList(): DDC Fail by REG_DDC_STATUS \n") ;
			    CAT_ClearDDCFIFO();
			
			
		
		
	
		
		
		
	
	
//    printf("HDCP_GetKSVList(): KSV ") ;
	    for (TimeOut = 0; TimeOut < cDownStream * 5; TimeOut++)
		
		
//        printf(" %02X",pKSVList[TimeOut]) ;
		}
	
//  printf("\n"); 
	    return 0;


{
	
	
	
		
		
		
	
	
	mddc_info[1] = DDC_HDCP_ADDRESS;
	
	
	
	
//    WriteByteHDMITX_CAT(REG_DDC_MASTER_CTRL, B_MASTERHOST) ;   
//    WriteByteHDMITX_CAT(REG_DDC_HEADER, DDC_HDCP_ADDRESS) ;
//    WriteByteHDMITX_CAT(REG_DDC_REQOFF, REG_HDCP_DESIRE) ;  //// 20 bytes RO
//    WriteByteHDMITX_CAT(REG_DDC_REQCOUNT, 20) ;
	    WriteByteHDMITX_CAT(REG_DDC_CMD, CMD_DDC_SEQ_BURSTREAD);
	
		
		
		
			
			
			
//            printf("HDCP_GetVr(): DDC Done.\n") ;
			    break;
			
		
			
			
			    ("HDCP_GetVr(): DDC fail by REG_DDC_STATUS \n");
			
//            printf("HDCP_GetVr(): DDC fail by REG_DDC_STATUS \n") ;
			    CAT_ClearDDCFIFO();
			
			
		
		
	
		
		
		
//        printf("HDCP_GetVr(): DDC fail by timeout.\n") ;
		    CAT_ClearDDCFIFO();
		
		
	
		
		
		
		    (unsigned long)ReadByteHDMITX_CAT(REG_SHA_RD_BYTE1);
		
		    (unsigned long)ReadByteHDMITX_CAT(REG_SHA_RD_BYTE2);
		
		    (unsigned long)ReadByteHDMITX_CAT(REG_SHA_RD_BYTE3);
		
		    (unsigned long)ReadByteHDMITX_CAT(REG_SHA_RD_BYTE4);
		
//                  printf("V' = %02X %02X %02X %02X\n",pVr[TimeOut*4],pVr[TimeOut*4+1],pVr[TimeOut*4+2],pVr[TimeOut*4+3]) ;         
		} 


{
	
		
		
		
	
	ReadBlockHDMITX_CAT(REG_SHA_RD_BYTE1, 4, pM0);
	
	pM0[4] = ReadByteHDMITX_CAT(REG_AKSV_RD_BYTE5);
	
	pM0[5] = ReadByteHDMITX_CAT(REG_AKSV_RD_BYTE5);
	
	pM0[6] = ReadByteHDMITX_CAT(REG_AKSV_RD_BYTE5);
	
	pM0[7] = ReadByteHDMITX_CAT(REG_AKSV_RD_BYTE5);
	
//    printf("M[] =") ;
//        for(int i = 0 ; i < 8 ; i++){
//                printf("0x%02x,",pM0[i]) ;
//        }
//      printf("\n") ;
	    return 0;


{
	
	
		
		
		    w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16];
		
		
	
	
	
	
	
		
		    rol(h[0],
			5) + ((h[1] & h[2]) | (h[3] & ~h[1])) + h[4] + w[t] +
		    0x5a827999;
		
		
		
		
		
	
		
		    rol(h[0],
			5) + (h[1] ^ h[2] ^ h[3]) + h[4] + w[t] + 0x6ed9eba1;
		
		
		
		
		
	
		
		    rol(h[0],
			5) + ((h[1] & h[2]) | (h[1] & h[3]) | (h[2] & h[3])) +
		    h[4] + w[t] + 0x8f1bbcdc;
		
		
		
		
		
	
		
		    rol(h[0],
			5) + (h[1] ^ h[2] ^ h[3]) + h[4] + w[t] + 0xca62c1d6;
		
		
		
		
		
	
	
	
	
	


/* ----------------------------------------------------------------------
 * Outer SHA algorithm: take an arbitrary length byte string,
 * convert it into 16-word blocks with the prescribed padding at
 * the end,and pass those blocks to the core SHA algorithm.
 */ 
static void SHA_Simple(void *p, unsigned long len, unsigned char *output) 
{
	
	
	
	
		
		
		
			
			
			
		
		
		
		
	
	
		
		
		
	
	
	t++;
	
		
		
		
	
	
	
		
		
		
		
		

				      unsigned short BStatus,
				      unsigned char pKSVList[], int cDownStream,
				      unsigned char Vr[]) 
{
	
	
		
		
		
	
	
	
		
		
		
	
	
		
		
		
	
	
		
		
			
			
			
		
	


{
	
	
} 
{
	
	
	
	
	
	
	
	
		
		
		
			
			
			
			
		
		
			
			
			    ("CAT_HDCP_Authenticate_Repeater(): B_INT_AUTH_FAIL.\n");
			
			
		
			
			
			
			
			    //To clear all interrupt indicated by reg0C and reg0D bits set as 1, write reg0E[0] =1, then write reg0E[0] = 0.
			    WriteByteHDMITX_CAT(REG_SYS_STATUS, B_INTACTDONE);
			
			
			
			
		
		
	
		
		
		    ("Time out for wait KSV List checking interrupt\n");
		
		
	
	    ///////////////////////////////////////
	    // clear KSVList check interrupt.
	    ///////////////////////////////////////
	    
		
		
			
			
			
			
		
			
			
			
			
		
		
	
		
		
		
		
	
	
	
	
	     || BStatus & (B_MAX_CASCADE_EXCEEDED | B_DOWNSTREAM_OVER))
		
		
		
		
	
		
		
		
	
//    if(info->hw_sha_calculator_flag == 1)
//    {   
//       for(i = 0 ; i < cDownStream ; i++)
//       {
//                   revoked = 0 ;
//         HDCP_VerifyRevocationList(SRM1,&KSVList[i*5],&revoked) ;
//         if(revoked)
//          {
//                            goto CAT_HDCP_Repeater_Fail ;
//          }
//        }
//      }
	    
		
		
		
	
		
		
		
	
	    // do check SHA
	    if (CAT_HDCP_CheckSHA(M0, BStatus, KSVList, cDownStream, Vr) == -1)
		
		
		
	
	
	
      
	


{
	
	
	    //   unsigned char  revoked = 0 ;
	unsigned char BKSV[5] = { 0, 0, 0, 0, 0 };
	
	
	
	
//    printf("CAT_HDCP_Authenticate():\n") ;
	    CAT_HDCP_Reset();	//del by xintan 
//        CAT_ClearDDCFIFO();
	for (TimeOut = 250; TimeOut > 0; TimeOut--)
		
		
			
			
			
//        printf("HDCP_GetBCaps fail.\n") ;
			    info->auth_state = HDCP_REAUTHENTATION_REQ;
			
			
		
			
			
				
				
				
			
			else
				
				
				    ("Sink HDCP in DVI mode over HDMI,do not authenticate and encryption. \n");
				
			
		
		else
			
			
				
				
				
			
			else
				
				
				    ("Sink HDCP in HDMI mode over DVI, do not authenticate and encryption. \n");
				
			
		
		
	
//     printf("BCaps = %02X BStatus = %04X\n",BCaps, BStatus) ;
	    if (TimeOut == 0)
		
		
			
			
			{
				
				    ("Not a HDMI mode,do not authenticate and encryption. \n");
				
//                           printf("Not a HDMI mode,do not authenticate and encryption. \n") ;
				    info->auth_state = HDCP_REAUTHENTATION_REQ;
				
			
			
		
		else
			
			
				
				
				    ("Not a HDMI mode,do not authenticate and encryption\n");
				
				
			
		
	
	
//    printf("BKSV %02X %02X %02X %02X %02X\n",BKSV[0],BKSV[1],BKSV[2],BKSV[3],BKSV[4]) ;
	    
		
		
		
		
	
//     if(info->hw_sha_calculator_flag == 1)
//       {
//       HDCP_VerifyRevocationList(SRM1, BKSV, &revoked) ;
//       if(revoked)
//       {
//         hdmi_dbg_print("BKSV is revoked\n") ; 
//         return -1 ;
//        }
//      }
	    
	
	
	
	
//    if(BCaps & B_CAP_HDCP_1p1)  //support HDCP Enhanced encryption status signaling (EESS),Advance Cipher, and Enhanced Link Verification options.
//    {
//        printf("RX support HDCP 1.1\n"); 
	    WriteByteHDMITX_CAT(REG_HDCP_DESIRE, B_ENABLE_HDPC11 | B_CPDESIRE);	// bit0 = 1: ENable HDCPto desire copy protection; bit1 = : support HDCP 1.1 feature,
//    }
//    else
//    {
//        printf("RX not support HDCP 1.1\n");
	WriteByteHDMITX_CAT(REG_HDCP_DESIRE, B_CPDESIRE);	// bit0 = 1: ENable HDCP to desire copy protection.
//    }
	
//    CAT_HDCP_ClearAuthInterrupt() ;   //del by xintan
	    
//    printf("int2 = %02X DDC_Status = %02X\n",ReadByteHDMITX_CAT(REG_INT_STAT2), ReadByteHDMITX_CAT(REG_DDC_STATUS)) ;
	    
	
	
	{
		
		
		for (TimeOut = 250; TimeOut > 0; TimeOut--)
			
			
			
			
//            printf("reg46 = %02x reg16 = %02x\n",ucdata, ReadByteHDMITX_CAT(0x16)) ;
			    
				
				
				
				
			
			
				
				
				    ("CAT_HDCP_Authenticate(): Authenticate fail\n");
				
//                printf("CAT_HDCP_Authenticate(): Authenticate fail\n") ;
				    info->auth_state = HDCP_REAUTHENTATION_REQ;
				
				
			
		
			
			
			    ("CAT_HDCP_Authenticate(): Time out. return fail\n");
			
//             printf("CAT_HDCP_Authenticate(): Time out. return fail\n") ;
			    info->auth_state = HDCP_REAUTHENTATION_REQ;
			
			
		
	
	
	else
		



//////////////////////////////////////////////////////////////////////
// Function: HDCP_EnableEncryption
// Parameter: N/A
// Remark: Set regC1 as zero to enable continue authentication.
// Side-Effect: register bank will reset to zero.
//////////////////////////////////////////////////////////////////////
static void CAT_HDCP_EnableEncryption(void) 
{
	
	WriteByteHDMITX_CAT(REG_ENCRYPTION, B_ENABLE_ENCRYPTION);


//////////////////////////////////////////////////////////////////////
// Function: HDCP_ResumeAuthentication
// Parameter: N/A
// Return: N/A
// Remark: called by interrupt handler to restart Authentication and Encryption.
// Side-Effect: as Authentication and Encryption.
////////////////////////////////////////////////////////////////////// 
void CAT_HDCP_ResumeAuthentication(Hdmi_info_para_t * info) 
{
	
//    CAT_HDCP_Reset();                    //add by xintan   
	if (CAT_HDCP_Authenticate(info) == 0)
		
		
		
		
	
	else			//HDCP Authentication fail, set AVmute
	{
		
//                      hdmi_cat6611_SetAVmute(info) ;    //added by xintan
	}
	
}

{
	
		
		
			
			
			
		
	
	else
		
		
//        WriteByteHDMITX_CAT(REG_SW_RST, (ReadByteHDMITX_CAT(REG_SW_RST)) |B_HDCP_RST) ; //enable HDCP reset
//        WriteByteHDMITX_CAT(REG_HDCP_DESIRE, 0) ;   //bit0 = 0: disable HDCP
		    CAT_HDCP_Reset();
		
		
	


