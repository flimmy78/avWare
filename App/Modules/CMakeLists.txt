﻿#/App/Modules
project (AvModules)

set (project_headers_pach ${PROJECT_SOURCE_DIR}/../Includes)

include_directories(${project_headers_pach})
include_directories(AvIntelligentAnalysis)


macro(source_group_by_dir source_files)
    if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file ${${source_files}})
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach(sgbd_file)
    endif(MSVC)
endmacro(source_group_by_dir)


#AvProtocol
include_directories(AvProtocol)
#add_subdirectory(AvProtocol)


#AvGui
if (${CMAKE_WITH_UI} STREQUAL "ON")
	add_subdirectory(AvGui)
endif()

#AvBuffer
set(AvPacketSRC_LIST 
		AvPacket/AvPacket.cpp
	)
set(AvPacketHeader_LIST 
		${project_headers_pach}/AvPacket/AvPacket.h
	)
add_library(AvPacket STATIC ${AvPacketSRC_LIST} ${AvPacketHeader_LIST})
set_property(TARGET AvPacket PROPERTY FOLDER "AvModules")

#AvCapture
set(AvCaptureSRC_LIST 
		AvCapture/AvCapture.cpp
		AvCapture/AvNetCapture.cpp
		AvCapture/AvDevCapture.cpp
		AvCapture/AvManCapture.cpp
	)
set(AvCaptureHeader_LIST
		${project_headers_pach}/AvCapture/AvCapture.h
		${project_headers_pach}/AvCapture/AvNetCapture.h
		${project_headers_pach}/AvCapture/AvDevCapture.h
		${project_headers_pach}/AvCapture/AvManCapture.h
		
	)
add_library(AvCapture STATIC ${AvCaptureSRC_LIST} ${AvCaptureHeader_LIST})
set_property(TARGET AvCapture PROPERTY FOLDER "AvModules")

#AvDevice
set(AvDeviceSRC_LIST 
		AvDevice/AvDevice.cpp
	)
set(AvDeviceHeader_LIST 
		${project_headers_pach}/AvDevice/AvDevice.h
	)
add_library(AvDevice STATIC ${AvDeviceSRC_LIST} ${AvDeviceHeader_LIST})
set_property(TARGET AvDevice PROPERTY FOLDER "AvModules")

#AvGui
#set(AvGuiSRC_LIST 
#		AvGui/AvGui.cpp
#	)
#set(AvGuiHeader_LIST 
#		${project_headers_pach}/AvGui/AvGui.h
#	)
#add_library(AvGui STATIC ${AvGuiSRC_LIST} ${AvGuiHeader_LIST})


file(GLOB_RECURSE AvNetServiceSRC_LIST AvNetService/*.h AvNetService/*.hpp)
file(GLOB_RECURSE AvNetServiceHeader_LIST AvNetService/*.c AvNetService/*.cpp)
file(GLOB_RECURSE AvNetServiceInterface_LIST ${project_headers_pach}/AvNetService/*.h)
set (AvNetServiceALL_LIST 
		${AvNetServiceSRC_LIST} 
		${AvNetServiceHeader_LIST}
		${AvNetServiceInterface_LIST}
		)
source_group_by_dir(AvNetServiceALL_LIST)
add_library(AvNetService STATIC ${AvNetServiceALL_LIST})
set_property(TARGET AvNetService PROPERTY FOLDER "AvNetService")

file(GLOB_RECURSE FaceDetectSource_LIST AvIntelligentAnalysis/AvFaceDetect/*.h AvIntelligentAnalysis/AvFaceDetect/*.hpp)
file(GLOB_RECURSE FaceDetectHeader_LIST AvIntelligentAnalysis/AvFaceDetect/*.c AvIntelligentAnalysis/AvFaceDetect/*.cpp)
set (AvIntelligentAnalysisALL_LIST ${FaceDetectSource_LIST} ${FaceDetectHeader_LIST})

set (AvIntelligentAnalysisALL_LIST
		${AvIntelligentAnalysisALL_LIST}
		AvIntelligentAnalysis/AvIntelligentAnalysis.cpp
		${project_headers_pach}/AvIntelligentAnalysis/AvIntelligentAnalysis.h
	)
source_group_by_dir(AvIntelligentAnalysisALL_LIST)
add_library(AvIntelligentAnalysis STATIC ${AvIntelligentAnalysisALL_LIST})
set_property(TARGET AvIntelligentAnalysis PROPERTY FOLDER "AvIntelligentAnalysis")


#AvThread
set(AvThreadSRC_LIST 
#		AvThread/AvThread.cpp
#		AvThread/AvQueue.cpp
#		AvThread/AvThreadPool.cpp
#		AvThread/AvTimer.cpp
#		AvThread/AvTask.cpp
#		AvThread/AvQmsg.cpp
	)
set(AvThreadHeader_LIST 
		${project_headers_pach}/AvThread/AvThread.h
		${project_headers_pach}/AvThread/AvQueue.h
		${project_headers_pach}/AvThread/AvThreadPool.h
		${project_headers_pach}/AvThread/AvTimer.h
		${project_headers_pach}/AvThread/AvTask.h
		${project_headers_pach}/AvThread/AvQmsg.h
	)
#add_library(AvThread STATIC ${AvThreadSRC_LIST} ${AvThreadHeader_LIST})
#set_property(TARGET AvThread PROPERTY FOLDER "AvModules")

#AvAudio
#set(AvAudioSRC_LIST 
#		AvAudio/AvAudioCapture.cpp
#		AvAudio/AvAudioPlay.cpp
#	)
#set(AvAudioHeader_LIST 
#		${project_headers_pach}/AvAudio/AvAudio.h
#	)
#add_library(AvAudio STATIC ${AvAudioSRC_LIST} ${AvAudioHeader_LIST})

#AvAlarm
set(AvAlarmSRC_LIST 
		AvAlarm/AvAlarmLocal.cpp
		AvAlarm/AvAlarm.cpp
	)
set(AvAlarmHeader_LIST 
		${project_headers_pach}/AvAlarm/AvAlarm.h
		${project_headers_pach}/AvAlarm/AvAlarmLocal.h
	)
add_library(AvAlarm STATIC ${AvAlarmSRC_LIST} ${AvAlarmHeader_LIST})
set_property(TARGET AvAlarm PROPERTY FOLDER "AvModules")

#UART
set(AvUartSRC_LIST 
		AvUart/AvUart.cpp
	)
set(AvUartHeader_LIST 
		${project_headers_pach}/AvUart/AvUart.h
	)
add_library(AvUart STATIC ${AvUartSRC_LIST} ${AvUartHeader_LIST})
set_property(TARGET AvUart PROPERTY FOLDER "AvModules")

#AvLog
set(AvLogSRC_LIST 
		AvLog/AvLog.cpp
	)
set(AvLogHeader_LIST 
		${project_headers_pach}/AvLog/AvLog.h
	)
add_library(AvLog STATIC ${AvLogSRC_LIST} ${AvLogHeader_LIST})
set_property(TARGET AvLog PROPERTY FOLDER "AvModules")

#AvLog
set(AvFileSRC_LIST 
		AvFile/AvFile.cpp
	)
set(AvFileHeader_LIST 
		${project_headers_pach}/AvFile/AvFile.h
	)
add_library(AvFile STATIC ${AvFileSRC_LIST} ${AvFileHeader_LIST})
set_property(TARGET AvFile PROPERTY FOLDER "AvModules")




#AvMemoryPool
set(AvMemoryPoolSRC_LIST 
		AvMemoryPool/AvMemoryPool.cpp
	)
set(AvMemoryPoolHeader_LIST 
		${project_headers_pach}/AvMemoryPool/AvMemoryPool.h
	)
add_library(AvMemoryPool STATIC ${AvMemoryPoolSRC_LIST} ${AvMemoryPoolHeader_LIST})
set_property(TARGET AvMemoryPool PROPERTY FOLDER "AvModules")

#AvUser
set(AvUserSRC_LIST 
		AvUser/AvUser.cpp
	)
set(AvUserHeader_LIST 
		${project_headers_pach}/AvUser/AvUser.h
	)
add_library(AvUser STATIC ${AvUserSRC_LIST} ${AvUserHeader_LIST})
set_property(TARGET AvUser PROPERTY FOLDER "AvModules")

#AvPreview
set(AvPreviewSRC_LIST 
		AvPreview/AvPreview.cpp
	)
set(AvPreviewHeader_LIST 
		${project_headers_pach}/AvPreview/AvPreview.h
	)
add_library(AvPreview STATIC ${AvPreviewSRC_LIST} ${AvPreviewHeader_LIST})
set_property(TARGET AvPreview PROPERTY FOLDER "AvModules")

#AvRecord
set(AvRecordSRC_LIST 
		AvRecord/AvRecord.cpp
		AvRecord/AvRecordDB.cpp
	)
set(AvRecordHeader_LIST 
		${project_headers_pach}/AvRecord/AvRecord.h
		${project_headers_pach}/AvRecord/AvRecordDB.h
	)
add_library(AvRecord STATIC ${AvRecordSRC_LIST} ${AvRecordHeader_LIST})
set_property(TARGET AvRecord PROPERTY FOLDER "AvModules")

#AvF
set(AvFSRC_LIST 
		AvF/AvF.cpp
	)
set(AvFHeader_LIST 
		${project_headers_pach}/AvF/AvF.h
	)
add_library(AvF STATIC ${AvFSRC_LIST} ${AvFHeader_LIST})
set_property(TARGET AvF PROPERTY FOLDER "AvModules")

#AvProc
set(AvProcSRC_LIST 
		AvProc/AvProc.cpp
	)
set(AvProcHeader_LIST 
		${project_headers_pach}/AvProc/AvProc.h
		${project_headers_pach}/AvProc/logAvWareExport.h
	)
add_library(AvProc STATIC ${AvProcSRC_LIST} ${AvProcHeader_LIST})
set_property(TARGET AvProc PROPERTY FOLDER "AvModules")

#AvConfigs
set(AvConfigExSRC_LIST
		AvConfigs/AvConfigTable.cpp
		AvConfigs/AvConfigManagerBase.cpp
		AvConfigs/AvConfigManagerGeneral.cpp
		AvConfigs/AvConfigNetService.cpp
		AvConfigs/AvConfigCapture.cpp
		AvConfigs/AvConfigManagerUser.cpp
		AvConfigs/AvConfigManagerNetCapture.cpp
		AvConfigs/AvConfigManagerNetWork.cpp
		AvConfigs/AvConfigDevice.cpp
		AvConfigs/AvConfigAlarm.cpp
		AvConfigs/AvConfigRecord.cpp
)
set(AvConfigExHeader_LIST 
		${project_headers_pach}/AvConfigs/AvConfigTable.h
		${project_headers_pach}/AvConfigs/AvConfigManagerBase.h
		${project_headers_pach}/AvConfigs/AvConfigManagerGeneral.h
		${project_headers_pach}/AvConfigs/AvConfigIndex.h
		${project_headers_pach}/AvConfigs/AvConfigNetService.h
		${project_headers_pach}/AvConfigs/AvConfigCapture.h
		${project_headers_pach}/AvConfigs/AvConfigManagerUser.h
		${project_headers_pach}/AvConfigs/AvConfigManagerNetCapture.h
		${project_headers_pach}/AvConfigs/AvConfigManagerNetWork.h
		${project_headers_pach}/AvConfigs/AvConfigDevice.h
		${project_headers_pach}/AvConfigs/AvConfigAlarm.h
		${project_headers_pach}/AvConfigs/AvConfigRecord.h
)
add_library(AvConfigs STATIC ${AvConfigExSRC_LIST} ${AvConfigExHeader_LIST})
set_property(TARGET AvConfigs PROPERTY FOLDER "AvModules")



















set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../)



