#include <Arduino.h>
#include <pgmspace.h>
#include "Config.h"

#ifndef NULL
#define NULL 0
#endif


#if NoEmbeddedFile == true

const uint8_t* getEmbeddedFile(const char* filename,bool &gzip, unsigned int &size){
	return NULL;
}

#else

typedef struct _EmbeddedFileMapEntry{
	const char *filename;
	const uint8_t *content;
    unsigned int size;
	bool  gzipped;
} EmbeddedFileMapEntry;

#include "data/bwf_js.h"
const char file_bwf_js [] PROGMEM="/bwf.js";

#include "data/testcmd_htm.h"
const char file_testcmd_htm [] PROGMEM="/testcmd.htm";

#include "data/dygraph_js.h"

#if FrontEnd == TomsFrontEnd

#if WebPageLanguage == spanish
#include "data/spanish_index_htm.h"
#include "data/spanish_control_htm.h"
#include "data/spanish_setup_htm.h"
#include "data/spanish_log_htm.h"
#include "data/spanish_gdc_htm.h"
#include "data/spanish_config_htm.h"
#else
#include "data/english_index_htm.h"
#include "data/english_control_htm.h"
#include "data/english_setup_htm.h"
#include "data/english_log_htm.h"
#include "data/english_gdc_htm.h"
#include "data/english_config_htm.h"
#endif

const char file_index_htm [] PROGMEM="/index.htm";
const char file_dygraph_js [] PROGMEM="/dygraph-combined.js";
const char file_control_htm [] PROGMEM="/control.htm";
const char file_setup_htm [] PROGMEM="/setup.htm";
const char file_logconfig [] PROGMEM="/logging.htm";
const char file_gravitydevice [] PROGMEM="/gravity.htm";
const char file_config [] PROGMEM="/config.htm";

EmbeddedFileMapEntry fileMaps[]={
{file_bwf_js,data_bwf_min_js_gz,sizeof(data_bwf_min_js_gz),true},
{file_index_htm,data_index_htm_gz,sizeof(data_index_htm_gz),true},
{file_dygraph_js,dygraph_combined_js_gz,sizeof(dygraph_combined_js_gz),true},
{file_control_htm,control_htm_gz,sizeof(control_htm_gz),true},
{file_setup_htm,setup_htm_gz,sizeof(setup_htm_gz),true},
{file_logconfig,logging_htm_gz,sizeof(logging_htm_gz),true},
{file_gravitydevice,gravity_htm_gz,sizeof(gravity_htm_gz),true},
{file_config,config_htm_gz,sizeof(config_htm_gz),true},
{file_testcmd_htm,(const uint8_t *)data_testcmd_htm,0,false}
};

#else

#if WebPageLanguage == spanish
#include "data/spanish_c_index_htm.h"
#include "data/spanish_c_setup_htm.h"
#include "data/spanish_c_log_htm.h"
#include "data/spanish_c_gdc_htm.h"
#include "data/spanish_c_config_htm.h"
#else
#include "data/english_c_index_htm.h"
#include "data/english_c_setup_htm.h"
#include "data/english_c_log_htm.h"
#include "data/english_c_gdc_htm.h"
#include "data/english_c_config_htm.h"
#endif

const char file_index_htm [] PROGMEM="/index.htm";
const char file_setup_htm [] PROGMEM="/setup.htm";
const char file_logconfig [] PROGMEM="/log.htm";
const char file_gravitydevice [] PROGMEM="/gdc.htm";
const char file_config [] PROGMEM="/config.htm";


EmbeddedFileMapEntry fileMaps[]={
{file_bwf_js,data_bwf_min_js_gz,sizeof(data_bwf_min_js_gz),true},
{file_index_htm,data_c_index_htm_gz,sizeof(data_c_index_htm_gz),true},
{file_setup_htm,data_c_setup_htm_gz,sizeof(data_c_setup_htm_gz),true},
{file_logconfig,data_c_log_htm_gz,sizeof(data_c_log_htm_gz),true},
{file_gravitydevice,data_c_gdc_htm_gz,sizeof(data_c_gdc_htm_gz),true},
{file_config,data_c_config_htm_gz,sizeof(data_c_config_htm_gz),true},
{file_testcmd_htm,(const uint8_t *)data_testcmd_htm,0,false}
};

#endif

const uint8_t* getEmbeddedFile(const char* filename,bool &gzip, unsigned int &size)
{
	for(int i=0;i<(int)(sizeof(fileMaps)/sizeof(EmbeddedFileMapEntry));i++)
	{
		if(strcmp_P(filename,fileMaps[i].filename) ==0){
		    gzip = fileMaps[i].gzipped;
		    size = fileMaps[i].size;
			return fileMaps[i].content;
		}
	}
	return NULL;
}
#endif