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
    private final UUID sUUID;
    private InputStream btInStream;
    private OutputStream btOutStream;
    private OnDataSend dataSendListener;

    public static BluetoothAdapter getDefaultAdapter(){
        return BluetoothAdapter.getDefaultAdapter();
    }

    public ConnectThread(BluetoothDevice btDev) {

        this.btDev = btDev;
        // Standard SerialPortDev ID
        this.sUUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");

        BluetoothSocket tmp = null;
        try {
            tmp = this.btDev.createRfcommSocketToServiceRecord(sUUID);
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
        while (!interrupted()){
            String data = dataSendListener.sendValue();
            write(data.getBytes());
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {}
        }

    }

    public ConnectThread setDataSendListener(OnDataSend dataSendListener) {
        this.dataSendListener = dataSendListener;
        return this;

    }

    public static  interface OnDataSend{
        public String sendValue();
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
