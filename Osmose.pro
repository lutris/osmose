
QT += core gui opengl
TARGET = osmose
TEMPLATE = app

DEPENDPATH += . cpu emulator
INCLUDEPATH += . cpu emulator

LIBS += -lz -lasound

system-minizip {
    LIBS += -lminizip
    DEFINES += SYSTEM_MINIZIP
} else {
    DEPENDPATH += unzip
    INCLUDEPATH += unzip
    HEADERS += unzip/crypt.h \
               unzip/ioapi.h \
               unzip/unzip.h
    SOURCES += unzip/ioapi.c \
               unzip/unzip.c
}

FLAGS = -Wall -Wextra -Wunused -Wcast-qual
QMAKE_CXXFLAGS += -std=c++11 $$FLAGS
QMAKE_CFLAGS += -Wmissing-prototypes -Wshadow  $$FLAGS

# Input
HEADERS += EmulationThread.h \
           Joystick.h \
           KeyMapper.h \
           OsmoseConfigurationFile.h \
           OsmoseEmulationThread.h \
           OsmoseGUI.h \
           Pthreadcpp.h \
           QGLImage.h \
           QLogWindow.h \
           QOsmoseConfiguration.h \
           TGAWriter.h \
           WhiteNoiseEmulationThread.h \
           cpu/BasicTypes.h \
           cpu/Z80.h \
           emulator/AnsiColorTerminal.h \
           emulator/Bits.h \
           emulator/DebugEventListener.h \
           emulator/DebugEventThrower.h \
           emulator/Definitions.h \
           emulator/FIFOSoundBuffer.h \
           emulator/IOMapper.h \
           emulator/IOMapper_GG.h \
           emulator/MemoryMapper.h \
           emulator/Options.h \
           emulator/OsmoseCore.h \
           emulator/RomSpecificOption.h \
           emulator/SaveState.h \
           emulator/SmsDebugger.h \
           emulator/SmsEnvironment.h \
           emulator/SN76489.h \
           emulator/SoundThread.h \
           emulator/VDP.h \
           emulator/VDP_GG.h \
           emulator/Version.h \
           emulator/WaveWriter.h

SOURCES += EmulationThread.cpp \
           Joystick.cpp \
           KeyMapper.cpp \
           main.cpp \
           OsmoseConfigurationFile.cpp \
           OsmoseEmulationThread.cpp \
           OsmoseGUI.cpp \
           Pthreadcpp.cpp \
           QGLImage.cpp \
           QLogWindow.cpp \
           QOsmoseConfiguration.cpp \
           TGAWriter.cpp \
           WhiteNoiseEmulationThread.cpp \
           cpu/Opc_cbxx.cpp \
           cpu/Opc_dd.cpp \
           cpu/Opc_ddcb.cpp \
           cpu/Opc_ed.cpp \
           cpu/Opc_fd.cpp \
           cpu/Opc_fdcb.cpp \
           cpu/Opc_std.cpp \
           cpu/Z80.cpp \
           emulator/DebugEventThrower.cpp \
           emulator/FIFOSoundBuffer.cpp \
           emulator/IOMapper.cpp \
           emulator/IOMapper_GG.cpp \
           emulator/MemoryMapper.cpp \
           emulator/Options.cpp \
           emulator/OsmoseCore.cpp \
           emulator/RomSpecificOption.cpp \
           emulator/SmsEnvironment.cpp \
           emulator/SN76489.cpp \
           emulator/SoundThread.cpp \
           emulator/VDP.cpp \
           emulator/VDP_GG.cpp \
           emulator/WaveWriter.cpp

FORMS += Configuration.ui LogWindow.ui

# Installation
isEmpty(PREFIX) {
    PREFIX = /usr/local
}

target.path = $$PREFIX/games

icon.path = $$PREFIX/share/icons/hicolor/128x128/apps/
icon.files = osmose.png

desktop.path = $$PREFIX/share/applications/
desktop.files = osmose.desktop

INSTALLS += target icon desktop
