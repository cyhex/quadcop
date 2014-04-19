package com.cyhex.quadcontroller.main.bluetooth;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class ConnectThread extends Thread {

    private final BluetoothSocket btSocket;
    private final BluetoothDevice btDev;
    // Standard SerialPortDev ID
    private final UUID sUUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");

    private InputStream btInStream;
    private OutputStream btOutStream;
    private OnDataSend dataSendListener;
    private int dataSendListenerSleep;

    public ConnectThread(BluetoothDevice btDev) {

        this.btDev = btDev;
        BluetoothSocket tmp = null;
        try {
            tmp = this.btDev.createRfcommSocketToServiceRecord(sUUID);
        } catch (IOException e) {
            e.printStackTrace();
        }
        btSocket = tmp;
    }

    public static BluetoothAdapter getDefaultAdapter() {
        return BluetoothAdapter.getDefaultAdapter();
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
        while (!interrupted()) {
            byte[] data = dataSendListener.sendValue();
            write(data);
            try {
                Thread.sleep(dataSendListenerSleep);
            } catch (InterruptedException e) {
            }
        }

    }

    public ConnectThread setDataSendListener(OnDataSend dataSendListener, int sleep) {
        dataSendListenerSleep = sleep;
        this.dataSendListener = dataSendListener;
        return this;

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

    public static interface OnDataSend {
        public byte[] sendValue();
    }

}
