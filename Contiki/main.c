#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <sys/types.h>

#include <sys/process.h>
#include <sys/procinit.h>
#include <sys/etimer.h>
#include <sys/autostart.h>
#include <sys/clock.h>


uint64_t getSystemTime(void)
{
    struct timeb t;

    ftime(&t);

    return (clock_time_t)(1000*t.time + t.millitm);
}

// 声明任务函数，定义任务控制块
PROCESS(test1_process, "test1");
PROCESS(test2_process, "test2");


// 线程自启动绑定
AUTOSTART_PROCESSES(&test1_process, &test2_process);

PROCESS_THREAD(test1_process, ev, data)
{
    PROCESS_BEGIN();                                        // protothread机制所有线程以PROCESS_BEGIN()开始

    static struct etimer timer;
    etimer_set(&timer, CLOCK_SECOND/4);                     // 设置延时250ms

    while(1)
    {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));   // 等到时钟事件超时
        etimer_reset(&timer);

        printf("test1_process\n");
    }

    PROCESS_END();                                          // protothread机制所有线程以PROCESS_END()结束
}

PROCESS_THREAD(test2_process, ev, data)
{
    PROCESS_BEGIN();                                        // protothread机制所有线程以PROCESS_BEGIN()开始

    static struct etimer timer;
    etimer_set(&timer, CLOCK_SECOND);                       // 设置延时1000ms

    while(1)
    {
        PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);// 等到时钟事件超时，第二种写法
        etimer_reset(&timer);

        printf("test2_process\n");
    }

    PROCESS_END();                                          // protothread机制所有线程以PROCESS_END()结束
}

int main(void)
{
    clock_init(getSystemTime());                            // Contiki时钟初始化
    process_init();                                         // Contiki线程初始化
    process_start(&etimer_process, NULL);                   // etimer线程启动
    autostart_start(autostart_processes);                   // 用户自启动线程启动

    while(1)
    {
        SysTickUpdate(getSystemTime());

        do
        {
            // 执行完所有needspoll为1的进程及处理完所有队列*/
        }
        while(process_run() > 0);                           // 任务调度器轮询执行线程
    }

    return 0;
}



