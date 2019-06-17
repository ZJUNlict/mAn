TEMPLATE = app

CONFIG += c++11

QT += qml quick

RC_ICONS = mAn.ico

RESOURCES += \
    mAn.qrc

TARGET = mAn
DESTDIR = $$PWD/bin
MOC_DIR = ./temp
OBJECTS_DIR = ./temp

# Third party library dir
win32 {
    THIRD_PARTY_DIR = $$PWD/3rdParty
}
unix:!macx{
    THIRD_PARTY_DIR = /usr/local
    PROTOBUF2_DIR = $${THIRD_PARTY_DIR}# /usr/local/cellar/protobuf2
}
macx {
    THIRD_PARTY_DIR = /usr/local/Cellar
}

INCLUDEPATH += \
    src \
    src/utils \
    src/vision \
    share \
    share/proto/cpp \

HEADERS += \
    src/field.h \
    src/rec_player.h \
    src/rec_recorder.h \
    src/rec_slider.h \
    src/vision/visionmodule.h \
    src/utils/globaldata.h \
    src/interaction.h \
    src/vision/messageformat.h \
    src/vision/dealball.h \
    src/vision/dealrobot.h \
    src/vision/maintain.h \
    src/vision/collisiondetect.h \
    src/vision/kalmanfilter.h \
    src/utils/matrix2d.h \
    graph/graph.h \
    graph/gridnode.h \
    graph/linenode.h \
    src/test.h \
    src/paraminterface.h \
    src/communicator.h \
    src/simmodule.h \
    src/actionmodule.h \
    src/interaction4field.h \
    src/utils/globalsettings.h \
    src/simulator.h \
    src/refereebox.h \
    src/debugger.h \
    src/documenthandler.h \
    src/vision/kalmanfilterdir.h \
    src/utils/treeitem.h \
    src/viewerinterface.h \
    src/messageinfo.h \
    src/vision/chipsolver.h \
    src/vision/ballrecords.h \
    src/vision/log/file_format.h \
    src/vision/log/file_format_legacy.h \
    src/vision/log/file_format_timestamp_type_size_raw_message.h \
    src/vision/log/log_file.h \
    src/vision/log/log_slider.h \
    src/vision/log/message_type.h \
    src/vision/log/player.h \
    src/vision/log/qtiocompressor.h \
    src/vision/log/timer.h \
    share/singleton.hpp \
    share/dataqueue.hpp \
    share/geometry.h \
    share/staticparams.h \
    share/parammanager.h \
    share/proto/cpp/grSim_Commands.pb.h \
    share/proto/cpp/grSimMessage.pb.h \
    share/proto/cpp/grSim_Packet.pb.h \
    share/proto/cpp/grSim_Replacement.pb.h \
    share/proto/cpp/messages_robocup_ssl_detection.pb.h \
    share/proto/cpp/messages_robocup_ssl_geometry_legacy.pb.h \
    share/proto/cpp/messages_robocup_ssl_geometry.pb.h \
    share/proto/cpp/messages_robocup_ssl_refbox_log.pb.h \
    share/proto/cpp/messages_robocup_ssl_wrapper_legacy.pb.h \
    share/proto/cpp/messages_robocup_ssl_wrapper.pb.h \
    share/proto/cpp/ssl_game_controller_auto_ref.pb.h \
    share/proto/cpp/ssl_game_controller_common.pb.h \
    share/proto/cpp/ssl_game_controller_team.pb.h \
    share/proto/cpp/ssl_game_event_2019.pb.h \
    share/proto/cpp/ssl_game_event.pb.h \
    share/proto/cpp/ssl_referee.pb.h \
    share/proto/cpp/vision_detection.pb.h \
    share/proto/cpp/zss_cmd.pb.h \
    share/proto/cpp/zss_debug.pb.h \
    share/proto/cpp/zss_rec.pb.h \
    share/proto/cpp/zss_train.pb.h \
    src/vision/ballstate.h \
    src/display.h \
    src/refereethread.h

SOURCES += \
    src/main.cpp \
    src/field.cpp \
    src/interaction.cpp \
    src/rec_player.cpp \
    src/rec_recorder.cpp \
    src/rec_slider.cpp \
    src/utils/singleparams.cpp \
    src/utils/globalsettings.cpp \
    src/utils/treeitem.cpp \
    src/utils/globaldata.cpp \
    src/utils/matrix2d.cpp \
    graph/graph.cpp \
    graph/gridnode.cpp \
    graph/linenode.cpp \
    src/test.cpp \
    src/communicator.cpp \
    src/simmodule.cpp \
    src/actionmodule.cpp \
    src/interaction4field.cpp \
    src/simulator.cpp \
    src/refereebox.cpp \
    src/paraminterface.cpp \
    src/debugger.cpp \
    src/documenthandler.cpp \
    src/viewerinterface.cpp \
    src/messageinfo.cpp \
    src/vision/dealball.cpp \
    src/vision/dealrobot.cpp \
    src/vision/maintain.cpp \
    src/vision/collisiondetect.cpp \
    src/vision/visionmodule.cpp \
    src/vision/kalmanfilter.cpp \
    src/vision/chipsolver.cpp \
    src/vision/kalmanfilterdir.cpp \
    src/vision/log/file_format_legacy.cpp \
    src/vision/log/file_format_timestamp_type_size_raw_message.cpp \
    src/vision/log/log_file.cpp \
    src/vision/log/log_slider.cpp \
    src/vision/log/player.cpp \
    src/vision/log/timer.cpp \
    src/vision/log/qtiocompressor.cpp \
    share/geometry.cpp \
    share/parammanager.cpp \
    share/proto/cpp/grSim_Commands.pb.cc \
    share/proto/cpp/grSimMessage.pb.cc \
    share/proto/cpp/grSim_Packet.pb.cc \
    share/proto/cpp/grSim_Replacement.pb.cc \
    share/proto/cpp/messages_robocup_ssl_detection.pb.cc \
    share/proto/cpp/messages_robocup_ssl_geometry_legacy.pb.cc \
    share/proto/cpp/messages_robocup_ssl_geometry.pb.cc \
    share/proto/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    share/proto/cpp/messages_robocup_ssl_wrapper_legacy.pb.cc \
    share/proto/cpp/messages_robocup_ssl_wrapper.pb.cc \
    share/proto/cpp/ssl_game_controller_auto_ref.pb.cc \
    share/proto/cpp/ssl_game_controller_common.pb.cc \
    share/proto/cpp/ssl_game_controller_team.pb.cc \
    share/proto/cpp/ssl_game_event_2019.pb.cc \
    share/proto/cpp/ssl_game_event.pb.cc \
    share/proto/cpp/ssl_referee.pb.cc \
    share/proto/cpp/vision_detection.pb.cc \
    share/proto/cpp/zss_cmd.pb.cc \
    share/proto/cpp/zss_debug.pb.cc \
    share/proto/cpp/zss_rec.pb.cc \
    share/proto/cpp/zss_train.pb.cc \
    src/vision/ballstate.cpp \
    src/display.cpp \
    src/refereethread.cpp

win32 {
    PROTOBUF_INCLUDE_DIR = $${THIRD_PARTY_DIR}/protobuf/include
    ZLIB_INCLUDE_DIR = $${THIRD_PARTY_DIR}/zlib/include
    EIGEN_INCLUDE_DIR = $${THIRD_PARTY_DIR}/Eigen

    contains(QMAKE_TARGET.arch, x86_64){
        message("64-bit")
        CONFIG(release,debug|release){
            PROTOBUF_LIB = $${THIRD_PARTY_DIR}/protobuf/lib/x64/libprotobuf.lib
            ZLIB_LIB = $${THIRD_PARTY_DIR}/zlib/lib/x64/zlib.lib
        }
        CONFIG(debug,debug|release){
            PROTOBUF_LIB = $${THIRD_PARTY_DIR}/protobuf/lib/x64/libprotobufd.lib
            ZLIB_LIB = $${THIRD_PARTY_DIR}/zlib/lib/x64/zlibD.lib
        }
    } else {
        message("32-bit")
        CONFIG(release,debug|release){
            PROTOBUF_LIB = $${THIRD_PARTY_DIR}/protobuf/lib/x86/libprotobuf.lib
            ZLIB_LIB = $${THIRD_PARTY_DIR}/zlib/lib/x86/zlib.lib
        }
        CONFIG(debug,debug|release){
            PROTOBUF_LIB = $${THIRD_PARTY_DIR}/protobuf/lib/x86/libprotobufd.lib
            ZLIB_LIB = $${THIRD_PARTY_DIR}/zlib/lib/x86/zlib.lib
        }
    }
}

unix:!macx{
    PROTOBUF_INCLUDE_DIR = $${PROTOBUF2_DIR}/include
    PROTOBUF_LIB = $${PROTOBUF2_DIR}/lib/libprotobuf.a
    ZLIB_INCLUDE_DIR = $${THIRD_PARTY_DIR}/zlib/include
    ZLIB_LIB = -lz
    EIGEN_INCLUDE_DIR = /usr/include/eigen3
}

macx {
    PROTOBUF_INCLUDE_DIR = $${THIRD_PARTY_DIR}/protobuf/2.6.1/include
    PROTOBUF_LIB = $${THIRD_PARTY_DIR}/protobuf/2.6.1/lib/libprotobuf.a
    ZLIB_INCLUDE_DIR = $${THIRD_PARTY_DIR}/zlib/include
    ZLIB_LIB = $${THIRD_PARTY_DIR}/zlib/lib/zlib.a
    EIGEN_INCLUDE_DIR = $${THIRD_PARTY_DIR}/Eigen
}

defineTest(copyToDestdir) {
    files = $$1
    for(FILE, files) {
        macx {
            DDIR = $${DESTDIR}/$${TARGET}.app/Contents/MacOS
        }else {
            DDIR = $$DESTDIR
        }
        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g
        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }
    export(QMAKE_POST_LINK)
}
LIBS += $$PROTOBUF_LIB \
        $$ZLIB_LIB

INCLUDEPATH += $$PROTOBUF_INCLUDE_DIR \
               $$ZLIB_INCLUDE_DIR \
               $$EIGEN_INCLUDE_DIR

QMAKE_LFLAGS += -Wl,-rpath,"'$$ORIGIN'"
