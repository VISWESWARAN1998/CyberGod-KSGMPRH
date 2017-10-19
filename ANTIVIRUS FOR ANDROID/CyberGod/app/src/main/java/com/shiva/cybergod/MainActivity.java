package com.shiva.cybergod;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.AsyncTask;
import android.os.Environment;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import java.io.File;
import java.util.ArrayList;
import scan.DetectionsDisplay;
import scan.ScanFile;


public class MainActivity extends AppCompatActivity {
    private Button startScan, stopScan;
    private ImageView scanningGear;
    public TextView scanningFile, filesScanned, filesInfected;
    private int totalFilesScanned  = 0;
    private int totalFilesInfected = 0;
    private volatile boolean running;
    private Animation scanningAnimation;
    private final int READ_FILE_REQUEST_CODE = 777;
    private ListView detectionsList;
    private ArrayList<DetectionsDisplay> detections;
    private ArrayAdapter<DetectionsDisplay> detectionsDisplayArrayAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = (Toolbar) findViewById(R.id.mainToolbar);
        startScan = (Button) findViewById(R.id.startScanButton);
        stopScan = (Button) findViewById(R.id.stopScanButton);
        scanningGear = (ImageView) findViewById(R.id.scanningGearImage);
        scanningFile = (TextView) findViewById(R.id.scanningFileTextView);
        filesScanned = (TextView) findViewById(R.id.filesScannedTextView);
        filesInfected = (TextView) findViewById(R.id.infectedFilesTextView);
        detectionsList = (ListView) findViewById(R.id.detectionsListView);
        toolbar.inflateMenu(R.menu.main_menu_toolbar);

        askPermission(Manifest.permission.READ_EXTERNAL_STORAGE, READ_FILE_REQUEST_CODE);

        scanningAnimation = AnimationUtils.loadAnimation(getApplicationContext(), R.anim.rotate_clockwise);

        running = false;
        stopScan.setEnabled(false);
        scanningGear.setVisibility(View.INVISIBLE);

        detections = new ArrayList<>();
        detectionsDisplayArrayAdapter = new DisplayThreats();
        detectionsList.setAdapter(detectionsDisplayArrayAdapter);

        startScan.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                running = true;
                disableStartButton();
                new Scan().execute();
            }
        });

        stopScan.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Toast.makeText(getApplicationContext(), "Stopping...", Toast.LENGTH_SHORT).show();
                running = false;
                enableStartButton();
            }
        });

        toolbar.setOnMenuItemClickListener(new Toolbar.OnMenuItemClickListener() {
            @Override
            public boolean onMenuItemClick(MenuItem item) {
                switch (item.getItemId())
                {
                    case R.id.aboutMenuId:
                        Intent intent = new Intent(MainActivity.this, AboutActivity.class);
                        startActivity(intent);
                }
                return true;
            }
        });
    }

    void enableStartButton()
    {
        startScan.setEnabled(true);
        stopScan.setEnabled(false);
    }

    void disableStartButton()
    {
        startScan.setEnabled(false);
        stopScan.setEnabled(true);
    }

    /**
     * @return true if we have file access permission
     */
    boolean canScan()
    {
        if(ContextCompat.checkSelfPermission(MainActivity.this, Manifest.permission.READ_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED) return true;
        return false;
    }

    // This is used to ask File Access Permission from android
    void askPermission(String permission, int requestCode)
    {
        if(ContextCompat.checkSelfPermission(this, permission) != PackageManager.PERMISSION_GRANTED)
        {
            ActivityCompat.requestPermissions(this, new String[]{permission}, requestCode);
        }
    }

    // This is used to rotate a small gear[Animation] in the scanning process
    void showAnimation()
    {
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                scanningGear.setVisibility(View.VISIBLE);
                scanningGear.startAnimation(scanningAnimation);
            }
        });
    }

    void hideAnimation()
    {
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                scanningGear.setVisibility(View.VISIBLE);
            }
        });
    }

    // used to increment the no of files scanned
    private synchronized void incrementScannedFilesCount()
    {
        totalFilesScanned++;
    }

    // used to increment the infected files
    private synchronized void incremetInfectedFiles()
    {
        totalFilesInfected++;
    }

    // Updates scanning file to TextView
    synchronized void updateScanningFile(final String file)
    {
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                scanningFile.setText(file);
            }
        });
    }

    // Updates scanned files to TextView
    private synchronized void updateScannedFilesCount()
    {
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                filesScanned.setText(totalFilesScanned+"");
            }
        });
    }

    // Update InfectedFiles TextView
    private synchronized void updateInfectedFilesCount()
    {
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                filesInfected.setText(totalFilesInfected+"");
            }
        });
    }

    // Display a threat in the ListView
    synchronized void updateThreat(final String programName, final String threatName, final String location)
    {
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                detections.add(new DetectionsDisplay(programName, threatName, location));
                detectionsDisplayArrayAdapter.notifyDataSetChanged();
            }
        });
    }

    // A sub class which has a recursive scanner
    class Scan extends AsyncTask<Void, Void, Void>
    {

        @Override
        protected Void doInBackground(Void... voids) {
            showAnimation();
            scan(Environment.getExternalStorageDirectory());
            return null;
        }

        @Override
        protected void onPostExecute(Void aVoid)
        {
            enableStartButton();
            totalFilesScanned  = 0;
            totalFilesInfected = 0;
        }

        /**
         * scan the directories
         * @param parentDir The directory to be scanned
         */
        private void scan(File parentDir)
        {
            File[] files = parentDir.listFiles();
            try
            {
                for (File file : files)
                {
                    if (file.isDirectory())
                    {
                        if(running) scan(file);
                    } else
                    {
                        updateScanningFile(file.getName());
                        ScanFile scanFile = new ScanFile(file.getAbsolutePath());
                        if(scanFile.isThreat())
                        {
                            incremetInfectedFiles();
                            updateInfectedFilesCount();
                            updateThreat(file.getName(), scanFile.getThreatName(), scanFile.getFileLocation());
                        }
                        incrementScannedFilesCount();
                        updateScannedFilesCount();
                    }
                }
            }catch (NullPointerException e){
                Log.i("NullPointerException", "@new Scan().scan()");
            }
        }
    }

    /**
     * An array adapted to customize the ListView
     */
    class DisplayThreats extends ArrayAdapter<DetectionsDisplay>
    {
        DisplayThreats()
        {
            super(MainActivity.this, R.layout.detections_list, detections);
        }

        @NonNull
        @Override
        public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
            View view = convertView;
            if(view == null)
            {
                view = getLayoutInflater().inflate(R.layout.detections_list, parent, false);
            }

            DetectionsDisplay display = detections.get(position);

            TextView programName =  (TextView) view.findViewById(R.id.programNameTextView);
            TextView threatName = (TextView) view.findViewById(R.id.threatNameTextView);
            TextView threatLocation = (TextView) view.findViewById(R.id.threatLocationTextView);

            programName.setText(display.getFileName());
            threatName.setText(display.getFileDescription());
            threatLocation.setText(display.getFileLoaction());

            return view;
        }
    }

    /**
     * ========================================= Toolbar related contents here ============================
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main_menu_toolbar, menu);
        return true;
    }
}
