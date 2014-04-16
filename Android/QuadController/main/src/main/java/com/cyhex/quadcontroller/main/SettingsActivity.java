package com.cyhex.quadcontroller.main;

import android.os.Bundle;
import android.preference.PreferenceActivity;
import java.lang.Override;

public class SettingsActivity extends PreferenceActivity {

    @Override
    protected void onPostCreate(Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);
        addPreferencesFromResource(R.xml.preferences);
    }

}
