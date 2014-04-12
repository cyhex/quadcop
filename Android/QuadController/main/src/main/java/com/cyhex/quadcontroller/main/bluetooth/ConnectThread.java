package com.cyhex.quadcontroller.main.bluetooth;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class ConnectThread extends Thread {

    private final BluetoothSocket btSocket;
    private final BluetoothDevice btDev;
    private final UUID sUUID;
    private InputStream btInStream;
    private OutputStream btOutStream;


    public ConnectThread(BluetoothDevice btDev) {

        this.btDev = btDev;
        // Standard SerialPortDev ID
        this.sUUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");

        BluetoothSocket tmp = null;
        try {
            tmp = btDev.createRfcommSocketToServiceRecord(sUUID);
        } catch (IOException e) {
            e.printStackTrace();
        }
        btSocket = tmp;

    }

    public void run() {

        try {
            btSocket.connect();
            btInStream = btSocket.getInputStream();
            btOutStream = btSocket.getOutputStream();
        } catch (IOException e) {
            try {
                btSocket.close();
            } catch (IOException e1) {
            }
            return;
        }

    }

    public void write(byte[] bytes) {
        try {
            btOutStream.write(bytes);
        } catch (IOException e) {
        }
    }

    public void cancel() {
        try {
            btSocket.close();
        } catch (IOException e) {
        }
    }

}
