
QT += core gui opengl
TARGET = osmose
TEMPLATE = app

DEPENDPATH += . cpu core unzip
INCLUDEPATH += . cpu core unzip

LIBS += -lz -lasound

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
           core/AnsiColorTerminal.h \
           core/Bits.h \
           core/DebugEventListener.h \
           core/DebugEventThrower.h \
           core/Definitions.h \
           core/FIFOSoundBuffer.h \
           core/IOMapper.h \
           core/IOMapper_GG.h \
           core/MemoryMapper.h \
           core/Options.h \
           core/OsmoseCore.h \
           core/RomSpecificOption.h \
           core/SaveState.h \
           core/SmsDebugger.h \
           core/SmsEnvironment.h \
           core/SN76489.h \
           core/SoundThread.h \
           core/VDP.h \
           core/VDP_GG.h \
           core/Version.h \
           core/WaveWriter.h \
           unzip/crypt.h \
           unzip/ioapi.h \
           unzip/unzip.h

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
           core/DebugEventThrower.cpp \
           core/FIFOSoundBuffer.cpp \
           core/IOMapper.cpp \
           core/IOMapper_GG.cpp \
           core/MemoryMapper.cpp \
           core/Options.cpp \
           core/OsmoseCore.cpp \
           core/RomSpecificOption.cpp \
           core/SmsEnvironment.cpp \
           core/SN76489.cpp \
           core/SoundThread.cpp \
           core/VDP.cpp \
           core/VDP_GG.cpp \
           core/WaveWriter.cpp \
           unzip/ioapi.c \
           unzip/unzip.c

FORMS += Configuration.ui LogWindow.ui
