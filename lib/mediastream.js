var EventTarget = require('./eventtarget');

var RTCMediaStreamMessageEvent = require('./mediastreammessageevent');

function RTCMediaStream(internalMS) {
  'use strict';
  var that = this;

  EventTarget.call(this);

  that._internalMS = internalMS;
  internalMS.onerror = function onerror() {
    that.dispatchEvent({type: 'error'});
  };

  internalMS.onmessage = function onmessage(data) {
    that.dispatchEvent(new RTCMediaStreamMessageEvent(data));
  };

  internalMS.onstatechange = function onstatechange(state) {
    state = that.RTCMediaStates[state];
    switch(state) {
      case 'open':
        that.dispatchEvent({type: 'open'});
        break;

      case 'closed':
        that.dispatchEvent({type: 'close'});
        break;
    }
  };

  Object.defineProperties(this, {
    'id': {
        get: function getID() {
            return internalMS.id;
        }
    },
    'readyState': {
        get: function getReadyState() {
            var state = internalMS.readyState;
            return this.RTCMediaStates[state];
        }
    }
  });

  this.close = function close() {
    internalMS.close();
  };
}

RTCMediaStream.prototype.RTCMediaStates = [
  'connecting',
  'open',
  'closing',
  'closed'
];

module.exports = RTCMediaStream;
