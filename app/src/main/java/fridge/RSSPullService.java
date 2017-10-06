package fridge;

import android.app.IntentService;
import android.content.Intent;
import android.os.Bundle;
import android.os.ResultReceiver;
import android.util.Log;


import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.os.Bundle;
import android.util.Log;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.ScrollView;
import android.widget.TextView;

import usbserial.driver.UsbSerialPort;
import usbserial.util.HexDump;
import usbserial.util.SerialInputOutputManager;

import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class RSSPullService extends IntentService {
    private final String TAG = RSSPullService.class.getSimpleName();
    private SerialInputOutputManager mSerialIoManager;
    private SerialInputOutputManager.Listener mListener;
    private ResultReceiver receiver;
    private UsbSerialPort sPort;

    public RSSPullService() {
        super(RSSPullService.class.getName());
        Log.d(TAG, "This is my log message at the debug level here");
    }

    //@Override
    protected void onHandleIntent(Intent workIntent) {
        receiver = workIntent.getParcelableExtra("receiver");
        UsbSerialPort sPort = MainActivity.mPort;
        Log.e(TAG,"1");
        //String dataString = workIntent.getDataString();
        final UsbManager usbManager = (UsbManager) getSystemService(Context.USB_SERVICE);
        UsbDeviceConnection connection = usbManager.openDevice(sPort.getDriver().getDevice());
        if (connection == null) {
            Log.e(TAG, "Opening device failed");
            return;
        }
        Log.e(TAG,"2");

        try {
            sPort.open(connection);
            sPort.setParameters(9600, 8, UsbSerialPort.STOPBITS_1, UsbSerialPort.PARITY_NONE);
            Log.e(TAG,"3");

            mListener = new SerialInputOutputManager.Listener() {
                @Override
                public void onRunError(Exception e) {
                    Log.e(TAG, "Runner stopped.");
                }
                @Override
                public void onNewData(final byte[] data) {
                    RSSPullService.this.updateReceivedData(data);
                }
            };
            Bundle bundle = new Bundle();
            Log.e(TAG,"4");
            Log.i(TAG, "Starting io manager ..");
            receiver.send(0, Bundle.EMPTY);
            mSerialIoManager = new SerialInputOutputManager(sPort, mListener);
            mSerialIoManager.run();
        } catch (IOException e) {
            Log.e(TAG, "Error setting up device: " + e.getMessage(), e);
            try {
                sPort.close();
            } catch (IOException e2) {
                Log.e(TAG, "Error setting up device: " + e.getMessage(), e2);
            }
        }
    }

    private void updateReceivedData(byte[] data) {
        final String message = "Read " + data.length + " bytes: \n" + HexDump.dumpHexString(data) + "\n\n";
        Bundle bundle = new Bundle();
        bundle.putString("result", message);
        receiver.send(1, bundle);
    }
}

