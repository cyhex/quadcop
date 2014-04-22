package com.cyhex.quadcontroller.main;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import com.cyhex.quadcontroller.main.bluetooth.ConnectThread;
import com.cyhex.quadcontroller.main.bluetooth.Payload;
import com.cyhex.quadcontroller.main.views.JoystickView;
import com.cyhex.quadcontroller.main.views.VerticalSeekBar;

import java.util.Set;

public class MainActivity extends OrientationActivity {

    private static final int REQUEST_ENABLE_BT = 1;
    private VerticalSeekBar powerBar;
    private TextView powerDisplay;
    private SeekBar yawBar;
    private TextView yawDisplay;
    private Button gyroSetAxButton;
    private ConnectThread bt;
    private ToggleButton btButton;
    private BluetoothAdapter btAdapter;
    private SharedPreferences sharedPref;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        btAdapter = ConnectThread.getDefaultAdapter();
        if (!btAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }


        jc1 = (JoystickView) findViewById(R.id.jc1View);


        powerBar = (VerticalSeekBar) findViewById(R.id.powerBarView);
        powerDisplay = (TextView) findViewById(R.id.powerDisplay);

        powerBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                powerDisplay.setText("P:" + Integer.toString(i));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        yawBar = (SeekBar) findViewById(R.id.yawView);
        yawDisplay = (TextView) findViewById(R.id.yawDisplay);

        yawBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                yawDisplay.setText("Z:" + Integer.toString(i - 1024));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                yawBar.setProgress(1024);
            }
        });

        gyroButton = (ToggleButton) findViewById(R.id.aGyro);
        gyroButton.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                setOrientationCenter();
                if (!b) {
                    jc1.updateData(0, 0);
                }
            }
        });

        gyroSetAxButton = (Button) findViewById(R.id.aSetAx);
        gyroSetAxButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                setOrientationCenter();
            }
        });

        btButton = (ToggleButton) findViewById(R.id.aBt);
        btButton.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if (b) {
                    bt = new ConnectThread(getBtDevice());
                    bt.setDataSendListener(new ConnectThread.OnDataSend() {
                        @Override
                        public byte[] sendValue() {
                            Payload payload = new Payload(yawBar.getProgress() - 1024, jc1.getYpos(), jc1.getXpos(), powerBar.getProgress());
                            return payload.toBytes();
                        }
                    }, Integer.parseInt(sharedPref.getString("tr_rate", "100"))).start();
                } else {
                    bt.cancel();
                    try {
                        bt.join();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        sharedPref = PreferenceManager.getDefaultSharedPreferences(this);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }


    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            Intent i = new Intent(this, SettingsActivity.class);
            startActivity(i);
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == REQUEST_ENABLE_BT && resultCode == RESULT_OK) {
            Toast.makeText(getApplicationContext(), "BlueTooth is now Enabled", Toast.LENGTH_LONG).show();
        }
    }


    public BluetoothDevice getBtDevice() {
        Set<BluetoothDevice> pairedDevs = btAdapter.getBondedDevices();
        if (pairedDevs.size() > 0) {
            for (BluetoothDevice device : pairedDevs) {
                if (device.getName().equals(sharedPref.getString("bt_dev", "JY-MCU"))) {
                    return device;
                }
            }
        }
        return null;
    }

}
