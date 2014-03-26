package com.cyhex.quadcontroller.main;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

import com.cyhex.quadcontroller.main.views.JoystickView;

public class MainActivity extends ActionBarActivity {

    private JoystickView joystick;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        joystick = (JoystickView) findViewById(R.id.joyView);
        joystick.setOnJoystickMoveListener( new JoystickView.OnJoystickMoveListener() {
            @Override
            public void onValueChanged(int angle, int power, int direction) {
                Log.i("angle: ", Integer.toString(angle));
                Log.i("power: ", Integer.toString(power));
                Log.i("direction: ", Integer.toString(direction));
            }

            @Override
            public void onValueChanged(int angle, int power, int direction, int x, int y) {
                Log.i("y: ", Integer.toString(y));
                Log.i("x: ", Integer.toString(x));
            }
        }, JoystickView.DEFAULT_LOOP_INTERVAL);
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
