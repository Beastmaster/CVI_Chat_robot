/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2013. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_STRING                     2
#define  PANEL_TEXTBOX                    3
#define  PANEL_CMD1                       4       /* callback function: SEND_callback */
#define  PANEL_CMD2                       5       /* callback function: QUIT_callback */
#define  PANEL_LED                        6
#define  PANEL_CMD3                       7       /* callback function: MENORY_callback */
#define  PANEL_CONNET                     8       /* callback function: connect_callback */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK connect_callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MENORY_callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QUIT_callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SEND_callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
