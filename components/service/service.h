/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SERVICE_H
#define __SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
//三个调试宏
#define PRINT
//#define PRINTSDCARD
//#define DOG

//定义控制台缓冲区长度，这里暂时为RT_CONSOLEBUF_SIZE（rtthread的控制台缓冲区大小）
#define MYPRINTLOGLEN (1024)
#define MYLOGTAG "Cyz"

#include "esp_log.h"

//错误处理宏
#ifndef errChk
#define errChk(fCall) if(unlikely(fCall)){goto Error;}
#define errChkPrint(fCall,str,...) if(unlikely(fCall)){ESP_LOGE(MYLOGTAG,str,##__VA_ARGS__);goto Error;}
#define errChkInterPrint(fCall,str,...) if(unlikely(fCall)){esp_rom_printf(str,##__VA_ARGS__);goto Error;}
#endif

//定义一个查找函数指针
typedef int (*FINDFUNC)(unsigned char* buf,int len,int* pFrameStartPos,int* pFrameLen);
//定义一个处理函数指针
typedef void (*PARSEFUNC)(unsigned char* buf,int len);

#include "commonHead.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/

/* USER CODE BEGIN EFP */
void mySystemInit(void);
void myPrintf(char* str,...);
void parseMultiProtocolFrame(FINDFUNC findFunc,PARSEFUNC parseFunc,unsigned char* buf,int* pLastLen,int readLen);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __SERVICE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
