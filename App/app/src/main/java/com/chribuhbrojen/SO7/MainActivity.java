package com.chribuhbrojen.SO7;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.SystemClock;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;

import com.zerokol.views.joystickView.JoystickView;

public class MainActivity extends AppCompatActivity {
    private BluetoothConnector bc;
    private byte data;
    private byte lastData;

    private double carX, carY;
    private double lastCarX, lastCarY;
    private double cannonX, cannonY;
    private double lastCannonX, lastCannonY;

    private Thread thread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ((JoystickView) findViewById(R.id.joystickView_car)).setOnJoystickMoveListener(new JoystickView.OnJoystickMoveListener() {
            @Override
            public void onValueChanged(int angle, int power, int direction) {
                carX = (Math.sin(Math.toRadians(angle)) * (power / 100.0));
                carY = (Math.cos(Math.toRadians(angle)) * (power / 100.0));
            }
        }, JoystickView.DEFAULT_LOOP_INTERVAL);

        ((JoystickView) findViewById(R.id.joystickView_servo)).setOnJoystickMoveListener(new JoystickView.OnJoystickMoveListener() {
            @Override
            public void onValueChanged(int angle, int power, int direction) {
                cannonX = (Math.sin(Math.toRadians(angle)) * (power / 100.0));
                cannonY = (Math.cos(Math.toRadians(angle)) * (power / 100.0));
            }
        }, JoystickView.DEFAULT_LOOP_INTERVAL);

        bc = new BluetoothConnector(this);

        ((ListView) findViewById(R.id.devices)).setOnItemClickListener(bc.getOnItemClickListener());
        ((ListView) findViewById(R.id.devices)).setAdapter(new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, bc.getNamesList()));

        ((Button) findViewById(R.id.Auto)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                data ^= 1 << 6;
            }
        });

        ((Button) findViewById(R.id.Spin)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                data ^= 1 << 5;
            }
        });

        ((Button) findViewById(R.id.Shoot)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                data ^= 1 << 4;
            }
        });

        thread = new Thread(run);
        thread.start();
    }

    private void sendData() {
        if (data == lastData && carX == lastCarX && carY == lastCarY && cannonX == lastCannonX && cannonY == lastCannonY) return;

        bc.sendMessage(carX + " " + carY + " " + cannonX + " " + cannonY + " " + data + (char) 0);

        lastData = data;
        lastCarX = carX;
        lastCarY = carY;
        lastCannonX = cannonX;
        lastCannonY = cannonY;
    }

    Runnable run = new Runnable() {
        @Override
        public void run() {
            while (true) {
                sendData();
            }
        }
    };
}
