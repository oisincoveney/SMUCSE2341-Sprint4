TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    flightdata.cpp \
    dsstring.cpp \
    city.cpp \
    main.cpp \
    flightrequests.cpp \
    request.cpp \
    tests.cpp \
    plan.cpp \
    flightplans.cpp \
    output.cpp

HEADERS += \
    flightdata.h \
    linkedlist.h \
    node.h \
    city.h \
    dsstring.h \
    flightrequests.h \
    request.h \
    output.h \
    stack.h \
    queue.h \
    catch.hpp \
    plan.h \
    flightplans.h

DISTFILES += \
    
