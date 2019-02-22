#ifndef __SPS30_CPP__
#define __SPS30_CPP__

#include "sps30.h"

SPS30::SPS30(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = SPS30_POLLING_MS;
}

void SPS30::init(void) {
	esp_log_level_set("*", ESP_LOG_INFO);
	
	/*
	// Reset speed of I2C
	i2c_config_t conf;

	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = CHAIN_SDA_GPIO;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_io_num = CHAIN_SCL_GPIO;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = 100E3;

	i2c_param_config(I2C_NUM_1, &conf);
	*/
	
	// Set new timeout of i2c
	i2c_set_timeout(I2C_NUM_1, 12800);
	
	
	
	state = s_detect;
}

int SPS30::prop_count(void) {
	return 0;
}

bool SPS30::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool SPS30::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool SPS30::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool SPS30::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool SPS30::prop_write(int index, char *value) {
	// not supported
	return false;
}

void SPS30::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				uint8_t dataWrite[5] = { 0x00, 0x10, 0x03, 0, 0 };
				dataWrite[4] = CalcCrc(&dataWrite[2]);
				if (i2c->write(channel, address, dataWrite, 5) == ESP_OK) {
					// get current tickcnt
					tickcnt = get_tickcnt();
					
					state = s_read;
				} else {
					ESP_LOGI("SPS30", "Start fail !");
					state = s_error;
				}
			} else {
				state = s_error;
			}
			break;
		
		case s_read:
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				// get current tickcnt
				tickcnt = get_tickcnt();
				
				uint8_t reg[2], dataRead[60];
				
				// Check flag
				reg[0] = 0x20;
				reg[1] = 0x20;
				if (i2c->read(channel, address, reg, 2, dataRead, 3) == ESP_OK) {
					if (CalcCrc(dataRead) == dataRead[2]) { // Check CRC
						if (dataRead[1] == 0x01) { // new measurements ready to read
							// Read Measured Values
							reg[0] = 0x03;
							reg[1] = 0x00;
							if (i2c->read(channel, address, reg, 2, dataRead, 60) == ESP_OK) {
								uint32_t data32[10], upper, lower;
								uint8_t dataNext = 0;
								for (uint8_t inx=0;inx<60;inx+=6) {
									// Check CRC of Upper
									if (CalcCrc(&dataRead[inx + 0]) != dataRead[inx + 2]) {
										ESP_LOGI("SPS30", "Check Upper CRC error");
										continue;
									}
									
									// Check CRC of Lower
									if (CalcCrc(&dataRead[inx + 3]) != dataRead[inx + 5]) {
										ESP_LOGI("SPS30", "Check Lower CRC error");
										continue;
									}
									
									upper = (((uint16_t)dataRead[inx + 0])<<8)|((uint16_t)dataRead[1]);
									lower = (((uint16_t)dataRead[inx + 3])<<8)|((uint16_t)dataRead[4]);
									data32[dataNext++] = (upper<<16)|lower;
								}
								
								mc_pm10 = (float)data32[0];
								mc_pm25 = (float)data32[1];
								mc_pm40 = (float)data32[2];
								mc_pm100 = (float)data32[3];
								nc_pm5 = (float)data32[4];
								nc_pm10 = (float)data32[5];
								nc_pm25 = (float)data32[6];
								nc_pm40 = (float)data32[7];
								nc_pm100 = (float)data32[8];
								typical_particle_size = (float)data32[9];
								
								// set initialized flag
								initialized = true;
								// clear error flag
								error = false;
								
								ESP_LOGI("SPS30", "Measurement work, PM1.0: %f, PM2.5: %f, PM4.0: %f, PM10: %f", mc_pm10, mc_pm25, mc_pm40, mc_pm100);
							} else {
								ESP_LOGI("SPS30", "Read measurement error");
								state = s_error;
							}
						}
					} else {
						ESP_LOGI("SPS30", "Check CRC error 0x%X != 0x%X", dataRead[2], CalcCrc(dataRead));
						state = s_error;
					}
				} else {
					ESP_LOGI("SPS30", "Check flag error");
					state = s_error;
				}
			}
			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

		case s_wait:
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_detect;
			}
			break;
	}
}

uint8_t SPS30::CalcCrc(uint8_t *data) {
	uint8_t crc = 0xFF;
	for(int i = 0; i < 2; i++) {
		crc ^= data[i];
		for(uint8_t bit = 8; bit > 0; --bit) {
			if(crc & 0x80) {
				crc = (crc << 1) ^ 0x31u;
			} else {
				crc = (crc << 1);
			}
		}
	}
	return crc;
}

bool SPS30::isReady() {
	return initialized;
}

double SPS30::read(SPS30_Type type, uint8_t size) {
	float value = 0.0;
	
	if (type == SPS30_MASS) {
		switch(size) {
			case 10:
				value = mc_pm10;
				break;
			
			case 25:
				value = mc_pm25;
				break;
				
			case 40:
				value = mc_pm40;
				break;
				
			case 100:
				value = mc_pm100;
				break;
				
		}
	} else if (type == SPS30_NUMBER) {
		switch(size) {
			case 5:
				value = nc_pm5;
				break;
				
			case 10:
				value = nc_pm10;
				break;
			
			case 25:
				value = nc_pm25;
				break;
				
			case 40:
				value = nc_pm40;
				break;
				
			case 100:
				value = nc_pm100;
				break;
				
		}
	}
	
	return value;
}

void SPS30::fan(bool isON) {
	fan_on = isON;
	fan_update_flag = true;
}

#endif
