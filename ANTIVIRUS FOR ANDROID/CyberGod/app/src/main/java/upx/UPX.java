// SWAMI KARUPPASWAMI THUNNAI

package upx;

import strings.Strings;
import java.io.FileInputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;


/**
* @author Visweswaran
* @version 1.0
* This class is used to find whether the executable is packed with UPX or not
*/
public class UPX extends EXE
{
	String fileLocation; // This will hold the name of the file
	Integer exeSizeLimit; // This will hold the size limit of the .EXE e.g: if 10, the program will scan for 
						  // .EXE which is greater than 10 MB
        final String[] upxStrings = {"UPX0", "UPX1", "UPX!"};
	ArrayList<String> upxStringList = null;
	
	 /**
	 @param fileLocation Holds the location of the file
	 @param exeSizeLimit Holds the size limit of the .EXE
        */
	public UPX(String fileLocation, Integer exeSizeLimit)
	{
		super.fileLocation = fileLocation;
		this.fileLocation = fileLocation;
		this.exeSizeLimit = exeSizeLimit;
                this.upxStringList = new ArrayList<String>(Arrays.asList(upxStrings));
	}
	
        /**
         * 
         * @return A boolean value which returns true if the executable is packed
         */
	public boolean isPacked()
	{
		getExeLocation(this.fileLocation);
		try
		{
			long sizeOfExe = getSizeInMB();
			if(sizeOfExe < this.exeSizeLimit || sizeOfExe == this.exeSizeLimit)
			{
				Strings strings = new Strings(this.fileLocation, this.upxStringList);
                                if(strings.Scanfile()) // will scan the file and returns true if Strings are present
                                {
                                            return true;
                                }
			}
		}
		catch(IOException e)
		{
			return false;
		}
                catch(Exception e)
                {
                    return false;
                }
			
		return false;
	}
}
