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

// ����������������������ƿ�
PROCESS(test1_process, "test1");
PROCESS(test2_process, "test2");


// �߳���������
AUTOSTART_PROCESSES(&test1_process, &test2_process);

PROCESS_THREAD(test1_process, ev, data)
{
    PROCESS_BEGIN();                                        // protothread���������߳���PROCESS_BEGIN()��ʼ

    static struct etimer timer;
    etimer_set(&timer, CLOCK_SECOND/4);                     // ������ʱ250ms

    while(1)
    {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));   // �ȵ�ʱ���¼���ʱ
        etimer_reset(&timer);

        printf("test1_process\n");
    }

    PROCESS_END();                                          // protothread���������߳���PROCESS_END()����
}

PROCESS_THREAD(test2_process, ev, data)
{
    PROCESS_BEGIN();                                        // protothread���������߳���PROCESS_BEGIN()��ʼ

    static struct etimer timer;
    etimer_set(&timer, CLOCK_SECOND);                       // ������ʱ1000ms

    while(1)
    {
        PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);// �ȵ�ʱ���¼���ʱ���ڶ���д��
        etimer_reset(&timer);

        printf("test2_process\n");
    }

    PROCESS_END();                                          // protothread���������߳���PROCESS_END()����
}

int main(void)
{
    clock_init(getSystemTime());                            // Contikiʱ�ӳ�ʼ��
    process_init();                                         // Contiki�̳߳�ʼ��
    process_start(&etimer_process, NULL);                   // etimer�߳�����
    autostart_start(autostart_processes);                   // �û��������߳�����

    while(1)
    {
        SysTickUpdate(getSystemTime());

        do
        {
            // ִ��������needspollΪ1�Ľ��̼����������ж���*/
        }
        while(process_run() > 0);                           // �����������ѯִ���߳�
    }

    return 0;
}



