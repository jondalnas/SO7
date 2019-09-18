package com.chribuhbrojen.SO7;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;

public class MainActivity extends AppCompatActivity {
    private BluetoothConnector bc;
    private byte data;
    private byte lastData;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

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

        Thread thread = new Thread(run);
        thread.start();
    }

    private void sendData() {
        if (data == lastData) return;

        bc.sendMessage((char) data + "");

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
