package com.chribuhbrojen.SO7;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Toast;

import com.harrysoft.androidbluetoothserial.BluetoothManager;
import com.harrysoft.androidbluetoothserial.BluetoothSerialDevice;
import com.harrysoft.androidbluetoothserial.SimpleBluetoothDeviceInterface;

import java.util.ArrayList;
import java.util.List;

import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.schedulers.Schedulers;

public class BluetoothConnector {
    private List<String[]> devices = new ArrayList<String[]>();
    private String connectedMac = "";
    private BluetoothDevice device;

    private BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
    private SimpleBluetoothDeviceInterface deviceInterface;
    private final BluetoothManager bm;

    private Activity activity;

    public BluetoothConnector(Activity a) {
        activity = a;

        //Create Bluetooth Manager
        bm = BluetoothManager.getInstance();
        //Check if phone has bluetooth and display message if it does not
        if (bm == null) {
            Toast.makeText(a, "Bluetooth not available.", Toast.LENGTH_LONG).show();
            a.finish();
        }

        //Find paired devices and put their addresses and names in a list
        List<BluetoothDevice> pairedDevice = bm.getPairedDevicesList();
        for (BluetoothDevice device : pairedDevice) {
            String deviceName = device.getName();
            String deviceHardwareAddress = device.getAddress();
            devices.add(new String[] {deviceName, deviceHardwareAddress});
        }


    }

    //Retreaves a list of all names on the paired list
    public List<String> getNamesList() {
        List<String> result = new ArrayList<String>();

        for (String[] strs : devices) {
            result.add(strs[0]);
        }

        return result;
    }

    //Connect to the bluetooth device that is pressed
    public AdapterView.OnItemClickListener getOnItemClickListener() {
        return new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView <?> parent, View view, int position, long id) {
                connectedMac = devices.get(position)[1];
                device = bluetoothAdapter.getRemoteDevice(connectedMac);

                connectDevice(connectedMac, bm);
            }
        };
    }

    public void sendMessage(String message) {
        if (deviceInterface == null) return;

        deviceInterface.sendMessage(message);
    }

    private void connectDevice(String mac, BluetoothManager bm) {
        bm.openSerialDevice(mac).subscribeOn(Schedulers.io()).observeOn(AndroidSchedulers.mainThread()).subscribe(this::onConnected, this::onError);
    }

    private void onConnected(BluetoothSerialDevice connectedDevice) {
        deviceInterface = connectedDevice.toSimpleDeviceInterface();

        deviceInterface.setListeners(this::onMessageReceived, this::onMessageSent, this::onError);
    }

    private void onMessageSent(String message) {
        //Toast.makeText(activity, "Sent a message! Message was: " + message, Toast.LENGTH_LONG).show();
    }

    private void onMessageReceived(String message) {
        Toast.makeText(activity, "Received a message! Message was: " + message, Toast.LENGTH_LONG).show();
    }

    private void onError(Throwable error) {
    }
}
