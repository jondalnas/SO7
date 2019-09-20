package com.chribuhbrojen.SO7;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;

public class MainActivity extends AppCompatActivity {
    private BluetoothConnector bc; //BluetoothConnector is a class used to connect to the HC-05 bluetooth module
    private byte data; //Data is a byte that represents the data that the Arduino will read after a bluetooth connection is established
    private byte lastData;

    //data = yasddddx
    //y = unusable bit
    //a = auto on/off bit
    //s = spin for victory on/off bit
    //d = directional bits
    //x = shoot bit, will turn off after on shot is fired

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        bc = new BluetoothConnector(this);

        ((ListView) findViewById(R.id.devices)).setOnItemClickListener(bc.getOnItemClickListener());
        ((ListView) findViewById(R.id.devices)).setAdapter(new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, bc.getNamesList()));

        //If any button is clicked, then cahnge the bit representing that action in the data byte, by XOR'ing it
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

        ((Button) findViewById(R.id.Up)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                data ^= 1 << 4;
            }
        });

        ((Button) findViewById(R.id.Down)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                data ^= 1 << 3;
            }
        });

        ((Button) findViewById(R.id.Left)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                data ^= 1 << 2;
            }
        });

        ((Button) findViewById(R.id.Right)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                data ^= 1 << 1;
            }
        });

        ((Button) findViewById(R.id.Shoot)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                data ^= 1 << 0;
            }
        });

        //Creates a new thread that runs in background, to send data, so all data is send at once
        Thread thread = new Thread(run);
        thread.start();
    }

    private void sendData() {
        //Only send data if the data byte changes, so we don't get redudant data
        if (data == lastData) return;

        bc.sendMessage((char) data + "");

        //Set the first byte to zero, so the shooting command only happens once
        data &= 0b01111110;

        lastData = data;
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
