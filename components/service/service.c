#include "service.h"

//初始化代码写在这里，不建议用自动初始化机制，这里的代码执行时是关中断的
void mySystemInit(void)
{
	//int error;
	myPrintf("mySystemInit start\n");
	//errChkPrint(usartInit(USART0PORTNUM,DEFAULTBAUDRATE),"mySystemInit:usartInit 0 error\n");
	return;
//Error:
	//return;
}

//中断里正常代码不能用myPrintf,可能会写SD卡，中断里出错可以用，反正已经出错了
void myPrintf(char* fmt,...)
{
	char buffer[MYPRINTLOGLEN]={0}; //这个RT_CONSOLEBUF_SIZE是rtthread控制台缓冲区大小宏
	va_list args;
	va_start(args,fmt);
	vsnprintf(buffer,MYPRINTLOGLEN-1,fmt,args);
	va_end(args);
#ifdef PRINT
	ESP_LOGI(MYLOGTAG,"%s",buffer);
#endif
#ifdef PRINTSDCARD
	myPrintErrorStrToSDCARD(buffer);
#endif
}

void parseMultiProtocolFrame(FINDFUNC findFunc,PARSEFUNC parseFunc,unsigned char* buf,int* pLastLen,int readLen)
{
	int totalLen=*pLastLen+readLen;

	int singleFrameLen;
	//处理的数据计数
	int index=0;
	//找到的帧在缓冲区中的偏移
	int frameStartPos;
	//循环处理帧数据
	while(1)
	{
		//如果没数据可处理了就跳出
		if(totalLen<=index)
		{
				break;
		}

		//如果找不到数据帧了就跳出
		if(findFunc(buf+index,totalLen-index,&frameStartPos,&singleFrameLen))
		{
				break;
		}

		//处理单帧
		parseFunc(buf+index+frameStartPos,singleFrameLen);
		//增加本次消耗的数据量
		index+=frameStartPos+singleFrameLen;
	}

	//如果有剩余数据，且本次有数据被处理掉，数据长度有变化，才需要移动
	*pLastLen=totalLen-index;
	if(*pLastLen>0 && *pLastLen<totalLen)
	{
		memcpy(buf,buf+index,*pLastLen);
	}
	return;
}
