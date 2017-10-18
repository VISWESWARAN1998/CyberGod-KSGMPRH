package com.shiva.cybergod;

import android.content.Intent;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;

public class SplashScreenActivity extends AppCompatActivity {

    private ImageView splashScreenImage;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splash_screen);
        // Rotate the logo for a few milliseconds
        Animation animation = AnimationUtils.loadAnimation(getApplicationContext(), R.anim.rotate_clockwise);
        splashScreenImage = (ImageView) findViewById(R.id.splashScreenLogo);
        splashScreenImage.startAnimation(animation);
        // Shift over to MainActivity
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                Intent intent = new Intent(SplashScreenActivity.this, MainActivity.class);
                startActivity(intent);
                finish();
            }
        }, 3000);
    }
}
