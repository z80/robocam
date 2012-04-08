
#ifndef __IO_CTRL_H_
#define __IO_CTRL_H_

void queueInit();
void queueProcess();

char inQueuePush( unsigned char val );
char inQueuePop( unsigned char * val );
char outQueuePush( unsigned char val );
char outQueuePop( unsigned char * val );



#endif


