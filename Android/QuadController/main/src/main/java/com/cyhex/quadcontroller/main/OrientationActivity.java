package com.cyhex.quadcontroller.main;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.View;

import com.cyhex.quadcontroller.main.views.JoystickView;

public class OrientationActivity extends ActionBarActivity implements SensorEventListener {

    protected JoystickView jc1;
    private SensorManager msManager;
    private float[] mGravity;
    private float[] mMag;
    private float[] orientation = new float[3];
    private float[] orientationCenter = new float[3];

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        msManager = (SensorManager) getSystemService(SENSOR_SERVICE);

    }

    @Override
    public void onSensorChanged(SensorEvent sensorEvent) {

        if (sensorEvent.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
            mGravity = sensorEvent.values;
        }

        if (sensorEvent.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD) {
            mMag = sensorEvent.values;
        }
        if (mGravity != null && mMag != null) {
            getOrientation();
            updateGui();
        }

    }

    public void setOrientationCenter(View v){
        orientationCenter = orientation.clone();
    }

    private void updateGui() {
        int x = (int) Math.toDegrees(orientation[1] - orientationCenter[1]);
        int y = (int) Math.toDegrees(orientation[2] - orientationCenter[2]);
        jc1.updateData(x, y);

    }

    private void getOrientation() {
        float R[] = new float[9];
        float I[] = new float[9];
        float rawOrient[] = new float[3];

        SensorManager.getRotationMatrix(R, I, mGravity, mMag);
        SensorManager.getOrientation(R, rawOrient);

        // cheap LPS :)
        orientation[0] = (float) (orientation[0] * 0.9 + rawOrient[0] * 0.1);
        orientation[1] = (float) (orientation[1] * 0.9 + rawOrient[1] * 0.1);
        orientation[2] = (float) (orientation[2] * 0.9 + rawOrient[2] * 0.1);

    }


    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {

    }

    @Override
    protected void onResume() {
        super.onResume();
        msManager.registerListener(this, msManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_GAME);
        msManager.registerListener(this, msManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD), SensorManager.SENSOR_DELAY_GAME);
    }

    @Override
    protected void onPause() {
        super.onPause();
        msManager.unregisterListener(this);
    }
}
