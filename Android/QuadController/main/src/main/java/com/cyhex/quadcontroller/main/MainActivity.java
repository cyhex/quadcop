package com.cyhex.quadcontroller.main;

import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.cyhex.quadcontroller.main.views.JoystickView;
import com.cyhex.quadcontroller.main.views.VerticalSeekBar;

public class MainActivity extends OrientationActivity{

    private VerticalSeekBar powerBar;
    private TextView powerDisplay;
    private SeekBar yawBar;
    private TextView yawDisplay;
    private Button gyroSetAxButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
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
                if(!b){
                    jc1.updateData(0,0);
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
            return true;
        }
        return super.onOptionsItemSelected(item);
    }


}
