#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "robot.h"
#include <ansi_c.h>
#include <tcpsupp.h>
#include <formatio.h>
#include <string.h>

int Handle=0;

static int panelHandle;

static int fileHandle;



int CVICALLBACK ClientCallback(unsigned int handle,int event,
			int error, void* callbackData)
{
	 char ss[800];
	 int rdSize=800;

	 char message2[512];
	
	 char buffer2[1000]="ROBOT:";
	 
	int i,j=0,m=0;

	 
	 
	 switch(event)
	 {
		 case TCP_DATAREADY:
			 if((rdSize=ClientTCPRead(Handle,ss,rdSize,2000))<0)
			MessagePopup ("Acquire", "acquire data failed");
			 else 
			 {
			OpenFile("Chat Record",VAL_READ_WRITE , 
			   VAL_OPEN_AS_IS,VAL_ASCII );				
			WriteLine (fileHandle, ss,strlen(ss)+2);       //存储聊天记录     
			for(i=0;ss[i]!=0;i++)
			{
				if(ss[i]=='\"')
					j++;
				if(j==3)
					message2[m++]=ss[i];
				else if(j==4)
					break;  
	
			}
	
				SetCtrlVal (panelHandle,PANEL_TEXTBOX,strcat(buffer2,strcat(message2,"\n")));   //ss
			//	 MessagePopup ("connection", "connected!");
				WriteLine (fileHandle, ss,strlen(ss)+1);    //写聊天记录 
				CloseFile (fileHandle);
			 }
		 break;
		  case TCP_DISCONNECT:
		;//	MessagePopup ("connection", "Disconnected!"); //printf("connection %d disconnected!\n",panelHandle);
			  break;
			 
	 }
	 return 0;
}



int main (int argc, char *argv[])
{
	
	char ss[512];
	
	
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "robot.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	
	fileHandle=OpenFile ("Chat Record", VAL_READ_WRITE,     ///聊天记录
		VAL_TRUNCATE, VAL_ASCII);
	
	RunUserInterface ();
//	DisconnectFromTCPServer (Handle);
	DiscardPanel(panelHandle);
	return 0;
}

int CVICALLBACK QUIT_callback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		
			MessagePopup ("ROBOT", "YOU ARE LEAVING...");
			QuitUserInterface (0);
			break;
	}
	return 0;
}




int CVICALLBACK SEND_callback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{   
	char message[512]; 
	char text[512]="GET /request.p?key=6dfcda1f-b822-4545-94ee-65ace781e3e0&lc=ch&ft=1.0&text=";
	char text1[]=" HTTP/1.0\r\n\r\n";
	
	char robot[]="ROBOT:";
	
	char buffer1[512]="Me:" ;
	

	switch (event)
	{
		case EVENT_COMMIT:

		GetCtrlVal (panelHandle, PANEL_STRING, message);//获得发送信息
		
		OpenFile("Chat Record",VAL_READ_WRITE , 
			   VAL_OPEN_AS_IS,VAL_ASCII );
		
		WriteLine (fileHandle, message, strlen(message)+2);
		
		strcat(text,message);
		strcat(text,text1);
		
    	if(ConnectToTCPServer(&Handle, 80,"54.248.231.39",
		   ClientCallback,0,20000)<0)
		return 0;
		
		SetCtrlVal (panelHandle,PANEL_TEXTBOX, strcat(buffer1,strcat(message,"\n")));		
		
		ClientTCPWrite (Handle,text,strlen(text)+1,2000);
		
		SetCtrlVal(panelHandle,PANEL_STRING,"");
		CloseFile (fileHandle);
			break;
	}
	return 0;
}




int CVICALLBACK MENORY_callback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char buffer[512];
	
	switch (event)
	{
		case EVENT_COMMIT:
		
/*		FileSelectPopup  ("",  "*.*" , "*.*",
		"chat record",  VAL_SELECT_BUTTON  , 0,0, 					  //打开文件选择的弹窗   
		1, 1, buffer);   */
		
		
		DirSelectPopup ("","*.*", 1,
			1,buffer);



			
			break;
	}
	return 0;
}

int CVICALLBACK connect_callback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
	if(ConnectToTCPServer(&Handle, 80,"54.248.231.39",
		ClientCallback,0,2000)<0)
	MessagePopup ("connection", "connect to server success");
	else
		MessagePopup ("connection", "connect to server success");//	printf("connect to server success\n");
		SetCtrlVal (panelHandle, PANEL_LED, 1);
			break;
	}
	return 0;
}


