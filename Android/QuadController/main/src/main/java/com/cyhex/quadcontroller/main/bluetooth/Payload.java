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

    public Payload(int yaw, int pitch, int roll, int power) {
        this.yaw = (short) yaw;
        this.pitch = (short) pitch;
        this.roll = (short) roll;
        this.power = (short) power;
    }

    public Payload() {
    }

    public byte[] toBytes() {
        ByteBuffer buffer = ByteBuffer.allocate((2*5));

        // send starter
        buffer.putShort(Integer.valueOf(32767).shortValue());

        buffer.putShort(Integer.valueOf(yaw).shortValue());
        buffer.putShort(Integer.valueOf(pitch).shortValue());
        buffer.putShort(Integer.valueOf(roll).shortValue());
        buffer.putShort(Integer.valueOf(power).shortValue());



        byte[] bytes = buffer.array();
        return bytes;
    }

}
