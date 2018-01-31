#ifndef TYPEDEF_H
#define TYPEDEF_H

//[2014-07-28]重新定义Null指针
#ifndef NULL															
#define NULL ((void *)0)
#endif


//[2014-07-28]重新定义数据类型
typedef unsigned char     	LUCENE_U8;								
typedef char       			LUCENE_S8;
typedef unsigned short    	LUCENE_U16;
typedef signed short      	LUCENE_S16;
typedef unsigned int     	LUCENE_U32;
typedef signed int        	LUCENE_S32;
typedef unsigned long long	LUCENE_U64;
typedef long long			LUCENE_S64;
typedef LUCENE_U8            LUCENE_BYTE;
typedef LUCENE_S32			LUCENE_BOOL;

#define LUCENE_TRUE		0;
#define LUCENE_FALSE		-1;

//[2014-07-28] 模块类型
typedef enum _MOD_TYPE_E 
{
	MOD_Store =0,
	MOD_ServiceControl,
	MOD_Other
}MOD_TYPE_E;

#define MOD_COUNT_ MOD_Other-MOD_Database


#define DEBUGLEVEL 0			/*设置打印输出级别*/

#define DEBUG_OFF 0   
#define DEBUG_ERR 1   
#define DEBUG_WRN 2   
#define DEBUG_TRC 3   
#define DEBUG_INF 4   


#if DEBUGLEVEL>0
#define DEBUG(level,msg...) \
{ \
	if (level<=DEBUGLEVEL) { \
		printf(msg); \
	} \
}
#else
#define DEBUG(level,msg...) {}
#endif
#endif

