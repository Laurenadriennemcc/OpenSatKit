###############################################################################
# OSK Global
#
# Notes:
#   1. System is the primary entry point into the OpenSatKit framework. It
#      serves as a central access point for all OSK configurations and
#      definitions. Whenever possible it uses existing COSMOS definitions
#      to prevent multiple definitions
#   2. System is designed as a Singleton 
#   TODO - Resolve interface switch management: remap vs reconnect 
#
# License:
#   Written by David McComas, licensed under the copyleft GNU General Public
#   License (GPL).
#
###############################################################################

require 'cosmos'

module Osk

   PASSWORD = "osk"

   ###########################
   ## JSON Naming standards ##
   ###########################

   JSON_APP_TYPE_CFS = "cfs"
   JSON_APP_TYPE_OSK = "osk"
   
   ######################
   ## Network Settings ##
   ######################

   NULL_IP_ADDR  = "0.0.0.0"

   # The following definitions must match cmd_tlm_Server.txt definitions
   COSMOS_IP_ADDR = "127.0.0.1"
   COSMOS_CFS_INT = "LOCAL_CFS_INT"

   PISAT_IP_ADDR = "192.168.0.1"
   PISAT_CFS_INT = "PISAT_CFS_INT"
   PISAT_CONTROL = "PISAT_CONTROL"
   HOST_IP_ADDR  = "192.168.0.6"

   CFS_CMD_PORT  = "1234"
   CFS_TLM_PORT  = "1235"

   ###################
   ## Text Messages ##
   ###################

   BUTTON_CONT   = "OK"
   BUTTON_CANCEL = "Cancel"  # Equal to hard coded message_box() string
   UNDEFSTR = "Undefined"

   MSG_TBD_FEATURE = "Coming Soon"

   ################
   ## File Names ##
   ################

   DOCS_TOUR_FILE = "OSK_Tour.pdf"
   DOCS_UG_FILE   = "OSK_UsersGuide.pdf"

   TUTORIAL_DEF_FILE  = "osk_tutorials.json"
   TUTORIAL_SCR_FILE  = "tutorial_screen.txt"

   # Tutorial file format types
   TUTORIAL_HTML   = "HTML"
   TUTORIAL_PDF    = "PDF"
   TUTORIAL_SCRIPT = "SCRIPT"

   CFE_UG_FILE   = "index.html"

   CFE_STARTUP_FILE = "cfe_es_startup.scr"
   
   CPU1_TARGET_FILE  = "targets.cmake"
   CPU1_PLT_CFG_FILE = "cpu1_platform_cfg.h"
   CPU1_MSG_ID_FILE  = "cpu1_msgids.h"
   CPU1_OS_CFG_FILE  = "cpu1_osconfig.h"
   CPU1_STARTUP_FILE = "cpu1_cfe_es_startup.scr"
   
   JSON_TBL_MGMT_SCR_FILE = "json_table_mgmt_scr.txt"
   
   TMP_BIN_FILE  = "osk_tmp_bin.dat"
   TMP_TBL_FILE  = "osk_tmp_tbl.dat"
   TMP_JSON_FILE = "osk_tmp.json"
   TMP_TXT_FILE  = "osk_tmp.txt"
   
   TMP_FLT_CMD_SCR_FILE = "osk_tmp_flt_cmd_scr.txt"
   TMP_FLT_CMD_SCR_STR  = "OSK_TMP_FLT_CMD_SCR"

   TMP_TBL_MGR_SCR_FILE = "osk_tmp_tbl_mgr_scr.txt"
   TMP_TBL_MGR_SCR_STR  = "OSK_TMP_TBL_MGR_SCR"
   
   TMP_GET_BIN_FILE_SCR_FILE = "osk_tmp_get_bin_file_scr.txt"
   TMP_GET_BIN_FILE_SCR_STR  = "OSK_TMP_GET_BIN_FILE_SCR"

   #########################################
   ## Table Manager Definition File Names ##
   #########################################

   TBL_MGR_DEF_CFE_ES_APP_INFO  = "cfe_es_app_info.txt"
   TBL_MGR_DEF_CFE_ES_CDS_REG   = "cfe_es_cds_reg.txt"
   TBL_MGR_DEF_CFE_ES_ERLOG     = "cfe_es_erlog.txt"
   TBL_MGR_DEF_CFE_ES_SYSLOG    = "cfe_es_syslog.txt"
   TBL_MGR_DEF_CFE_ES_TASK_INFO = "cfe_es_task_info.txt"
   
   TBL_MGR_DEF_CFE_EVS_LOG      = "cfe_evs_log.txt"
   TBL_MGR_DEF_CFE_EVS_APP_INFO = "cfe_evs_app_info.txt"

   TBL_MGR_DEF_CFE_SB_PIPE = "cfe_sb_pipe_info.txt"

   TBL_MGR_DEF_CFE_TBL_REG = "cfe_tbl_reg.txt"

   TBL_MGR_DEF_FM_DIR = "fm_dir_list.txt"
   TBL_MGR_DEF_MD_TBL = "md_tbl.txt"
   TBL_MGR_DEF_MM_DMP = "mm_dump.txt"
   
   #####################
   ## Directory Paths ##
   #####################

   # Directory paths relative to Cosmos::USERPATH
   REL_DIR_CFS  = "../cfs"
   REL_DIR_42   = "../42"
   REL_DIR_DOCS = "../docs"

   OSK_42_DIR   = File.expand_path(REL_DIR_42,Cosmos::USERPATH)
   OSK_CFS_DIR  = File.expand_path(REL_DIR_CFS,Cosmos::USERPATH)
   OSK_DOCS_DIR = File.expand_path(REL_DIR_DOCS,Cosmos::USERPATH)

   CFS_EXE_DIR     = "#{OSK_CFS_DIR}/build/exe/cpu1"
   CFS_EXE_CF_DIR  = "#{OSK_CFS_DIR}/build/exe/cpu1/cf"
   CFS_CMAKE_DIR   = "#{OSK_CFS_DIR}/osk_defs"
   
   REL_SRV_DIR     = "cfs_kit/file_server"
   REL_SRV_TBL_DIR = "cfs_kit/file_server/tables"
   GND_SRV_DIR     = "#{Cosmos::USERPATH}/#{REL_SRV_DIR}"
   GND_SRV_TBL_DIR = "#{Cosmos::USERPATH}/#{REL_SRV_TBL_DIR}"

   FLT_SRV_DIR = "/cf"

   LIB_DIR = "#{Cosmos::USERPATH}/config/targets/CFS_KIT/lib"
   SCR_DIR = "#{Cosmos::USERPATH}/config/targets/CFS_KIT/screens"
   
   APPS_JSON_DIR  = "#{Cosmos::USERPATH}/cfs_kit/apps"

   CFE_DOCS_DIR   = "#{Cosmos::USERPATH}/cfs_kit/docs"
   CFE_UG_DIR     = "#{CFE_DOCS_DIR}/cfe_users_guide"

   REL_TUTORIAL_DIR  = "cfs_kit/tutorials"
   TUTORIAL_DIR      = "#{Cosmos::USERPATH}/cfs_kit/tutorials"

   TOOLS_DIR      = "#{Cosmos::USERPATH}/cfs_kit/tools"
   PERF_MON_DIR   = "#{TOOLS_DIR}/perf-monitor"
   CREATE_APP_DIR = "#{TOOLS_DIR}/create-app"
   
   COSMOS_CFG_EDITOR  = "#{Cosmos::USERPATH}/tools/ConfigEditor"
   COSMOS_PKT_VIEWER  = "#{Cosmos::USERPATH}/tools/PacketViewer"
   COSMOS_SCR_RUNNER  = "#{Cosmos::USERPATH}/tools/ScriptRunner"
   COSMOS_TBL_MANAGER = "#{Cosmos::USERPATH}/tools/TableManager"
   COSMOS_TLM_GRAPHER = "#{Cosmos::USERPATH}/tools/TlmGrapher"
   COSMOS_CMD_TLM_SRV = "#{Cosmos::USERPATH}/tools/CmdTlmServer"
   
   TMP_FLT_BIN_PATH_FILE = "#{FLT_SRV_DIR}/#{TMP_BIN_FILE}"
   TMP_GND_BIN_PATH_FILE = "#{GND_SRV_DIR}/#{TMP_BIN_FILE}"
    
   TMP_FLT_TXT_PATH_FILE = "#{FLT_SRV_DIR}/#{TMP_TXT_FILE}"
   TMP_GND_TXT_PATH_FILE = "#{GND_SRV_DIR}/#{TMP_TXT_FILE}"
    
   #################################
   ## Demo Standard Text Strings  ## 
   #################################

   DEMO_STEP_NO_INFO = "\n\nNo additional information for this demo step."

   ###################################
   ## Screen Standard Text Strings  ## 
   ###################################

   WIDGET_GND_WORK_DIR = "gnd_work_dir"
   WIDGET_FLT_WORK_DIR = "flt_work_dir"
   
   ################################
   ## Standard Cmd Tlm mnemonics ## 
   ################################

   CMD_STR_NOOP      = "NOOP"
   CMD_STR_RESET     = "RESET_CTRS"
   CMD_STR_LOAD_TBL  = "LOAD_TBL"
   CMD_STR_DUMP_TBL  = "DUMP_TBL"
   CMD_DEF_FILENAME  = TMP_BIN_FILE
   CMD_DEF_DIR_NAME  = FLT_SRV_DIR
  
   TLM_STR_HK_PKT    = "HK_TLM_PKT"
   TLM_STR_CMD_VLD   = "CMD_VALID_COUNT"
   TLM_STR_CMD_ERR   = "CMD_ERROR_COUNT"
   
end # Module Osk
