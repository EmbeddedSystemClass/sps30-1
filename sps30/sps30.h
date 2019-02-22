#ifndef __SPS30_H__
#define __SPS30_H__

#include "math.h"
#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "esp_log.h"

#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"

#define SPS30_POLLING_MS 100

enum SPS30_Type {
	SPS30_MASS, SPS30_NUMBER
};

class SPS30 : public Device {
	private:
		enum {
			s_detect, 
			s_read, 
			s_error, 
			s_wait
		} state;
		TickType_t tickcnt;
		
		float mc_pm10, mc_pm25, mc_pm40, mc_pm100;
		float nc_pm5, nc_pm10, nc_pm25, nc_pm40, nc_pm100;
		float typical_particle_size;
		
		bool fan = true;
		bool fan_update_flag = true;
		
		uint8_t CalcCrc(uint8_t*) ;

	public:
		// constructor
		SPS30(int bus_ch, int dev_addr);
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		
		// method
		bool isReady() ;
		double read(SPS30_Type, uint8_t) ;
		void fan(bool) ;
		
};

#endif
