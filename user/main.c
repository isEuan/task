#include "main.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/* 软件延时 */
void delay(unsigned int count)
{
    for (; count != 0; count--)
        ;
}

/* 任务1 */
void Task1_Entry(void *p_arg)
{
    static char flag1 = 1;
    for (; flag1;)
    {
        flag1 = 1;
        delay(100);
        flag1 = 0;
        delay(100);

        /* 任务切换，这里是手动切换 */
        // taskYIELD();
    }
}

/* 任务2 */
void Task2_Entry(void *p_arg)
{
    static char flag2 = 1;
    for (; flag2;)
    {
        flag2 = 1;
        delay(100);
        flag2 = 0;
        delay(100);

        /* 任务切换，这里是手动切换 */
        // taskYIELD();
    }
}

/* 任务3 */
void Task3_Entry(void *p_arg)
{
    char *a = NULL;

    a = (char *)p_arg;
    if (*a == 0)
        return;

    printf("ASCII is %d", *a);
    printf("\r\n");

    // free(a);
    return;
}

/* 任务4 */
void Task4_Entry(void *p_arg)
{
    int len = 0;
    static char *StrIntput = NULL;
    if (StrIntput == NULL)
    {
        StrIntput = (char *)malloc(10 * sizeof(char));
        *StrIntput = '\0';
    }

    if (*(char *)p_arg == 0)
        return;

    len = strlen(StrIntput);

    StrIntput[len++] = *(char *)p_arg;
    StrIntput[len] = '\0';

    printf("%s", StrIntput);
    printf("\r\n");

    if (len == 9)
    {
        free(StrIntput);
        StrIntput = NULL;
    }

    return;
}

/* 任务5  */
void Task5_Entry(void *p_arg)
{

    return;
}

/* 任务6  */
void Task6_Entry(void *p_arg)
{

    return;
}

/* 事件读取 */
void EventInput(void *p_arg)
{
    char input = 0;
    *(char *)(p_arg) = 0;

    /* 键盘输入 */
    if (kbhit())
    {
        input = getch();
        *(char *)(p_arg) = input;

        printf("input is %c", input);
        printf("\r\n");
    }

    return;
}

/* 任务列表 */
void TaskFunc(int i, void *p)
{
    Task vTask[Task_MAX] = {EventInput, Task1_Entry, Task2_Entry, Task3_Entry, Task4_Entry, Task5_Entry, Task6_Entry};
    Task fun = vTask[i];
    (*fun)(p);
}

/* 指针函数 */
TaskHandle_t Task1_Handle;
void main(void)
{
    int a = 10;
    char B = 'B';
    char String[] = "Hello Word!!";

    int mode = 0;
    char InputChar = 0;
    int InputNum = 0;

    static time_t startT = 0, finishT = 0;

    // Task1_Handle=xTaskCreateStatic( (Task)Task1_Entry,   /* 任务入口 */
    //                                 (char *)"Task1",               /* 任务名称，字符串形式 */
    //                                 (uint32_t)TASK1_STACK_SIZE ,   /* 任务栈大小，单位为字 */
    //                                 (void *) NULL,                 /* 任务形参 */
    //                                 (StackType_t *)Task1Stack,     /* 任务栈起始地址 */
    //                                 (TCB_t *)&Task1TCB);

    printf("-- choose mode --\r\n");
    do{
        TaskFunc(TaskInput, (void *)&InputChar);
        if (mode == TaskInput)
        {
            if (InputChar != 0)
            {
                mode = InputChar - '0';
                printf("-- mode --\r\n");
            }
        }
        else if (0 < mode && mode < Task_MAX)
        {
            TaskFunc(mode, (void *)&InputChar);
        }
        else
            mode = 0;

        if (mode == 0)
            time(&startT);
        else
            time(&finishT);

        if (finishT - startT > 10)
        {
            printf("-- choose mode --\r\n");
            mode = 0;
        }
    }
    /* 回车退出程序 */
    while (13 != InputChar);

    printf("-- exit --\r\n");
    return;
}