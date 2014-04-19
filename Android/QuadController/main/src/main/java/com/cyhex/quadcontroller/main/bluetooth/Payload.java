package com.cyhex.quadcontroller.main.bluetooth;

import android.util.Log;

import java.nio.ByteBuffer;

public class Payload {

    private short yaw;
    private short pitch;
    private short roll;
    private short power;

    public Payload(short yaw, short pitch, short roll, short power) {
        this.yaw = yaw;
        this.pitch = pitch;
        this.roll = roll;
        this.power = power;
    }

    public Payload() {
    }

    public byte[] toBytes() {
        ByteBuffer buffer = ByteBuffer.allocate(2);
        buffer.putShort(Integer.valueOf(-1024).shortValue());

        byte[] bytes = buffer.array();
        for ( byte b : bytes){
            Log.i("bytes", String.valueOf(b));
        }

        return bytes;
    }

}
