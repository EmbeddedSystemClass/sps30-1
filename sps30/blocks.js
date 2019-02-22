Blockly.Blocks['sps30_is_ready'] = {
	init: function() {
		this.jsonInit({
			"message0": "PM2.5 Sensor is ready?",
			"output": "Boolean",
			"colour": 135,
			"tooltip": "",
			"helpUrl": "https://store.kidbright.info/plugin/12/%E0%B9%80%E0%B8%8B%E0%B9%87%E0%B8%99%E0%B9%80%E0%B8%8B%E0%B8%AD%E0%B8%A3%E0%B9%8C%E0%B8%9D%E0%B8%B8%E0%B9%88%E0%B8%99+SPS30"
		});
	}
};

Blockly.Blocks['sps30_read_mass_concentration'] = {
	init: function() {
		this.jsonInit({
			"message0": "PM2.5 Senser - read mass concentration %1",
			"args0": [{
				"type": "field_dropdown",
				"name": "size",
				"options": [
					[ "PM1.0", "10" ],
					[ "PM2.5", "25" ],
					[ "PM4.0", "40" ],
					[ "PM10", "100" ]
				]
			}],
			"output": "Number",
			"colour": 135,
			"tooltip": "Read mass concentration of PM1.0/2.5/4.0/10 from Sensirion SPS30",
			"helpUrl": "https://store.kidbright.info/plugin/12/%E0%B9%80%E0%B8%8B%E0%B9%87%E0%B8%99%E0%B9%80%E0%B8%8B%E0%B8%AD%E0%B8%A3%E0%B9%8C%E0%B8%9D%E0%B8%B8%E0%B9%88%E0%B8%99+SPS30"
		});
	}
};

Blockly.Blocks['sps30_read_number_concentration'] = {
	init: function() {
		this.jsonInit({
			"message0": "PM2.5 Senser - read number concentration %1",
			"args0": [{
				"type": "field_dropdown",
				"name": "size",
				"options": [
					[ "PM0.5", "5" ],
					[ "PM1.0", "10" ],
					[ "PM2.5", "25" ],
					[ "PM4.0", "40" ],
					[ "PM10", "100" ]
				]
			}],
			"output": "Number",
			"colour": 135,
			"tooltip": "Read number concentration of PM1.0/2.5/4.0/10 from Sensirion SPS30",
			"helpUrl": "https://store.kidbright.info/plugin/12/%E0%B9%80%E0%B8%8B%E0%B9%87%E0%B8%99%E0%B9%80%E0%B8%8B%E0%B8%AD%E0%B8%A3%E0%B9%8C%E0%B8%9D%E0%B8%B8%E0%B9%88%E0%B8%99+SPS30"
		});
	}
};

/*
Blockly.Blocks['sps30_control_fan'] = {
	init: function() {
		this.jsonInit({
			"message0": "PM2.5 Sensor trun %1 fan",
			"args0": [{
				"type": "field_dropdown",
				"name": "control",
				"options": [
					[ "ON", "true" ],
					[ "OFF", "false" ]
				]
			}],
			"previousStatement": null,
			"nextStatement": null,
			"colour": 135,
			"tooltip": "Control fan on Sensirion SPS30",
			"helpUrl": "https://store.kidbright.info/plugin/12/%E0%B9%80%E0%B8%8B%E0%B9%87%E0%B8%99%E0%B9%80%E0%B8%8B%E0%B8%AD%E0%B8%A3%E0%B9%8C%E0%B8%9D%E0%B8%B8%E0%B9%88%E0%B8%99+SPS30"
		});
	}
};
*/
