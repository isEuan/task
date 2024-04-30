#ifndef __MAIN_H_
#define __MAIN_H_

/* 任务顺序 */
typedef enum
{
    TaskInput = 0,
    Task1,
    Task2,
    Task3,
    Task4,
    Task5,
    Task6,

    Task_MAX
} TaskNum;

/* 函数指针 */
typedef void (*Task)(void *);

/* 指针函数 */
typedef void *TaskHandle_t;
// TaskHandle_t xTaskCreateStatic(	Task pxTaskCode,
// 					            const char * const pcName,
// 					            const uint32_t ulStackDepth,
// 					            void * const pvParameters,
// 					            StackType_t * const puxStackBuffer,
// 					            TCB_t * const pxTaskBuffer );

// /* 结构体 */
// typedef struct tskTaskControlBlock
// {
// 	volatile StackType_t    *pxTopOfStack;    /* 栈顶 */

// 	ListItem_t			    xStateListItem;   /* 任务节点 */

//     StackType_t             *pxStack;         /* 任务栈起始地址 */
// 	                                          /* 任务名称，字符串形式 */
// 	char                    pcTaskName[ configMAX_TASK_NAME_LEN ];
// } tskTCB;
// typedef tskTCB TCB_t;

#endif
