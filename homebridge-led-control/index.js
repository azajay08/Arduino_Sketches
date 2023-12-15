const request = require('request');

let Service, Characteristic;

module.exports = (homebridge) => {
	Service = homebridge.hap.Service;
	Characteristic = homebridge.hap.Characteristic;
	homebridge.registerAccessory('homebridge-led-control', 'LEDControl', LEDControl);
};

class LEDControl {
	constructor(log, config) {
	this.log = log;
	this.name = config.name || 'LED';
	this.url = config.url || 'http://192.168.100.27/led'; // NodeMCU URL
	this.onValue = config.onValue || 'on'; // expected 'on' value
	this.offValue = config.offValue || 'off'; // expected 'off' value

	this.service = new Service.Switch(this.name);

	this.service.getCharacteristic(Characteristic.On)
		.on('get', this.getOn.bind(this))
		.on('set', this.setOn.bind(this));
	}

	getOn(callback) {
		const options = {
		url: this.url + '/status',
		method: 'GET'
	};

		request(options, (error, response, body) => {
			if (!error && response.statusCode === 200) {
				const currentState = body.trim();
				callback(null, currentState === 'on');
			} else {
				this.log('Error checking LED status:', error);
				callback(error || new Error('Failed to get LED state'));
			}
		});
	}

	setOn(value, callback) {
		const command = value ? this.onValue : this.offValue;
		const options = {
			url: this.url,
			method: 'GET',
			qs: { command }
		};

		request(options, (error, response, body) => {
			if (!error && response.statusCode === 200) {
			this.log(`LED turned ${value ? 'on' : 'off'}`);

			this.service.getCharacteristic(Characteristic.On).updateValue(value);

			callback(null);
			} else {
			this.log(`Error turning LED ${value ? 'on' : 'off'}`);
			callback(error || new Error('Failed to set LED state'));
			}
		});
	}

	getServices() {
		return [this.service];
	}
}