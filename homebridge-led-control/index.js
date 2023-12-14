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
    this.url = config.url || 'NodeMCU device IP'; // Replace with your NodeMCU URL
    this.onValue = config.onValue || 'on'; // Replace with your NodeMCU expected 'on' value
    this.offValue = config.offValue || 'off'; // Replace with your NodeMCU expected 'off' value

    this.service = new Service.Switch(this.name);

    this.service.getCharacteristic(Characteristic.On)
      .on('get', this.getOn.bind(this))
      .on('set', this.setOn.bind(this));
  }

  getOn(callback) {
    // You might want to implement a status check here if possible
    // For simplicity, returning true
    callback(null, true);
  }

  setOn(value, callback) {
    const command = value ? this.onValue : this.offValue;
    const options = {
      url: this.url,
      method: 'GET', // Change to POST if required by your NodeMCU
      qs: { command }
    };

    request(options, (error, response, body) => {
      if (!error && response.statusCode === 200) {
        this.log(`LED turned ${value ? 'on' : 'off'}`);
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
