package com.opentouchgaming.razetouch.util;

import android.content.Context;
import android.content.res.AssetManager;

import com.opentouchgaming.androidcore.AppInfo;
import com.opentouchgaming.androidcore.DebugLog;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

/**
 * Utility that copies the bundled Duke64 assets from the APK assets folder into the
 * writable application directory (AppInfo.getAppDirectory()/DUKE) on the first run.
 * It performs a simple existence check to avoid overwriting user‑modified files.
 */
public class AssetExtractor {
    private static final DebugLog log = new DebugLog(DebugLog.Module.APP, "AssetExtractor");

    /**
     * Copies all files under the assets sub‑folder "DUKE" to the internal "DUKE" directory.
     * If a file already exists it is left untouched.
     */
    public static void extractAssets(Context ctx) {
        AssetManager am = ctx.getAssets();
        try {
            String[] assets = am.list("DUKE");
            if (assets == null) return;
            String targetDirPath = AppInfo.getAppDirectory() + "/DUKE";
            File targetDir = new File(targetDirPath);
            if (!targetDir.exists()) {
                //noinspection ResultOfMethodCallIgnored
                targetDir.mkdirs();
            }
            for (String assetName : assets) {
                File outFile = new File(targetDir, assetName);
                if (outFile.exists()) {
                    log.log(DebugLog.Level.D, "Asset already exists, skipping: " + outFile.getAbsolutePath());
                    continue;
                }
                try (InputStream in = am.open("DUKE/" + assetName);
                     FileOutputStream out = new FileOutputStream(outFile)) {
                    byte[] buffer = new byte[8192];
                    int len;
                    while ((len = in.read(buffer)) != -1) {
                        out.write(buffer, 0, len);
                    }
                    log.log(DebugLog.Level.D, "Extracted asset: " + outFile.getAbsolutePath());
                } catch (IOException e) {
                    log.log(DebugLog.Level.E, "Failed to extract asset " + assetName + ": " + e.getMessage());
                }
            }
        } catch (IOException e) {
            log.log(DebugLog.Level.E, "Error listing DUKE assets: " + e.getMessage());
        }
    }
}

