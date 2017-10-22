// SWAMI KARUPPASWAMI THUNNAI
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package scan;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;
import strings.MaliciousStrings;

/**
 * This class is used to scan the file itself for active threats.
 * @author Visweswaran
 */
public class ScanFile {
    private String fileLocation;
    private String threatName;


    /**
     * @param fileLocation Assigning the location of the file itself
     */
    public ScanFile(String fileLocation)
    {
        this.fileLocation = fileLocation;
    }
    
    /**
     * @return will return true if the application is threat
     */
    public boolean isThreat()
    {
        threatName = null;
        // If it is an apk and contains malicious strings
        return isApk() && isStringPresent();
    }
    /**
     * @return will return true if the specified location is .APK
     */
    private boolean isApk()
    {
        File file = new File(this.fileLocation);
        if(file.isFile()){
            String fileName = file.getName();
            if(fileName.contains(".apk")) return true;
        }
        return false;
    }
    
    // This method is used to check for malicious strings are present
    private boolean isStringPresent()
    {
        BufferedReader br;
        try 
        {
            ZipFile zipFile = new ZipFile(this.fileLocation);
            Enumeration<? extends ZipEntry> zipEntries = zipFile.entries();
            while(zipEntries.hasMoreElements())
            {
                //System.out.println("Scanning the zip file");
                ZipEntry zipEntry = zipEntries.nextElement();
                String zipFileName = zipEntry.getName();
                // Once the classes.dex file is found, read and check whether the string is present
                if("classes.dex".equals(zipFileName))
                {
                    //System.out.println("clsses.dex found!");
                    InputStream stream = zipFile.getInputStream(zipEntry);
                    br = new BufferedReader(new InputStreamReader(stream));
                    String stringsInLine;
                    while((stringsInLine = br.readLine()) != null)
                    {
                        // check for malicious strings here
                        for(String key : MaliciousStrings.maliciousStrings.keySet())
                        {
                            String maliciousString = new StringBuffer(key).reverse().toString();
                            if(stringsInLine.contains(maliciousString))
                            {
                                this.threatName = MaliciousStrings.maliciousStrings.get(key);
                                // close everything to free up the memory
                                stream.close();
                                br.close();
                                zipFile.close();
                                return true;
                            }
                        }
                    }
                    stream.close();
                    br.close();
                    zipFile.close();
                }
            }
        } catch (IOException ex) {
            // do some android specific things to log the message
            System.out.println(ex);
            return false;
        }
        catch (IllegalStateException e){
            return false;
        }
        catch(Exception e){}
        
        return false;
    }
    
    /**
     * @return Will return the name of the threat
     */
    public String getThreatName()
    {
        return this.threatName;
    }

    /**
     * @return will return the absolute location of the threat
     */
    public String getFileLocation()
    {
        return fileLocation;
    }
    
}
