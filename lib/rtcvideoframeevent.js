function RTCVideoFrameEvent(type, eventInitDict) {
    'use strict';
    Object.defineProperties(this, {
        'type': {
            value: type,
            enumerable: true
        },
        'label': {
            value: eventInitDict.label,
            enumerable: true
        },
        'width': {
            value: eventInitDict.width,
            enumerable: false
        },
        'height': {
            value: eventInitDict.height,
            enumerable: false
        },
        'encodedFrame': {
            value: eventInitDict.yPlane,
            enumerable: true
        },
        'yPlane': {
            value: eventInitDict.yPlane,
            enumerable: true
        },
        'uPlane': {
            value: eventInitDict.uPlane,
            enumerable: true
        },
        'vPlane': {
            value: eventInitDict.vPlane,
            enumerable: true
        }
    });
}

module.exports = RTCVideoFrameEvent;
