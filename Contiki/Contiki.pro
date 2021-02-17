TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
        OS/Contiki \
        OS/Contiki/core

SOURCES += \
        OS/Contiki/clock.c \
        OS/Contiki/core/lib/list.c \
        OS/Contiki/core/sys/autostart.c \
        OS/Contiki/core/sys/etimer.c \
        OS/Contiki/core/sys/process.c \
        OS/Contiki/core/sys/procinit.c \
        OS/Contiki/core/sys/timer.c \
        main.c

HEADERS += \
    OS/Contiki/contiki-conf.h \
    OS/Contiki/core/contiki-default-conf.h \
    OS/Contiki/core/contiki-lib.h \
    OS/Contiki/core/contiki-net.h \
    OS/Contiki/core/contiki-version.h \
    OS/Contiki/core/contiki.h \
    OS/Contiki/core/lib/list.h \
    OS/Contiki/core/sys/arg.h \
    OS/Contiki/core/sys/autostart.h \
    OS/Contiki/core/sys/cc.h \
    OS/Contiki/core/sys/clock.h \
    OS/Contiki/core/sys/compower.h \
    OS/Contiki/core/sys/ctimer.h \
    OS/Contiki/core/sys/dsc.h \
    OS/Contiki/core/sys/energest.h \
    OS/Contiki/core/sys/etimer.h \
    OS/Contiki/core/sys/lc-addrlabels.h \
    OS/Contiki/core/sys/lc-switch.h \
    OS/Contiki/core/sys/lc.h \
    OS/Contiki/core/sys/loader.h \
    OS/Contiki/core/sys/log.h \
    OS/Contiki/core/sys/mt.h \
    OS/Contiki/core/sys/node-id.h \
    OS/Contiki/core/sys/process.h \
    OS/Contiki/core/sys/procinit.h \
    OS/Contiki/core/sys/pt-sem.h \
    OS/Contiki/core/sys/pt.h \
    OS/Contiki/core/sys/rtimer.h \
    OS/Contiki/core/sys/stimer.h \
    OS/Contiki/core/sys/subprocess.h \
    OS/Contiki/core/sys/timer.h \
    OS/Contiki/rtimer-arch.h
