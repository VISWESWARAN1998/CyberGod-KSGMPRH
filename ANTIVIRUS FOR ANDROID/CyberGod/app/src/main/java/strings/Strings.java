// SWAMI KARUPPASWAMI THUNNAI
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package strings;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author Visweswaran This class is used to find whether the given stringsToFind
 present in a file
 */
public class Strings {

    String fileLocation = "";
    ArrayList<String> stringsToFind;
    HashSet<String> stringsInFile;
    boolean getStringsInFile = false;
    
    /**
     * This constructor assists in getting the strings present in the file
     * @param location Pass the location of the file
     */
    public Strings(String location)
    {
        this.fileLocation = location;
        this.stringsInFile = new HashSet<String>();
        this.getStringsInFile = true;
    }
    /**
     * This constructor is used to find whether the strings are present in the file
     * @param location Pass the fileLocation of the file
     * @param strings Pass the strings to be found
     */
    public Strings(String location, ArrayList<String> strings) {
        this.fileLocation = location;
        this.stringsToFind = strings;
    }

    /**
     * Checking For Strings:
     * This method is used to read the file line by line, and will pass the line
 to "isStringsPresent" method which will return true if the specified
 stringsToFind is present in line or not. If it returns true the method will
     * confirm that the String is present in the file, else will pass the
     * remaining lines
     * @return will return true if UPX stringsToFind are present in the file
     */
    public boolean Scanfile() {
        try {
            FileInputStream stream = new FileInputStream(this.fileLocation);
            BufferedReader br = new BufferedReader(new InputStreamReader(stream));
            String line;
            while ((line = br.readLine()) != null) {
                if (isStringsPresent(line)) {
                        br.close();
                        return true; // If the String is present in the line
                        // the method will return true
                    }
            }
            br.close();
        } catch (IOException e) {
            // do something....
        } catch (Exception e) {
            // do something....
        } finally {
        }
        return false;
    }

    /**
     * This method is used to find whether a sub-string is present in the string or not.
     * @param line The String in which the sub string is to be found
     * @return will return true if it is found.
     */
    private boolean isStringsPresent(String line) {
        for (String string : stringsToFind) {
            if (line.contains(string)) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * This method will return the list of Strings present in the file
     * @return will return the strings present in the file
     */
    public HashSet<String> getStrings()
    {
        try {
            FileInputStream stream = new FileInputStream(this.fileLocation);
            BufferedReader br = new BufferedReader(new InputStreamReader(stream));
            String line;
            while ((line = br.readLine()) != null) 
            {
                // a pattern which matched a-z, 0-9 this will be the more common strings
                Matcher asciiMatcher = Pattern.compile("[a-zA-Z0-9]*").matcher(line);
                while(asciiMatcher.find())
                {
                    String asciiString = asciiMatcher.group();
                    if(!this.stringsInFile.contains(asciiString))
                    {
                        this.stringsInFile.add(asciiString);
                    }
                }
            }
            br.close();
        } catch (IOException e) {
            // do something...
        } catch (Exception e) {
            // do something....
        } finally {
            
        }
        return this.stringsInFile;
    }
}
