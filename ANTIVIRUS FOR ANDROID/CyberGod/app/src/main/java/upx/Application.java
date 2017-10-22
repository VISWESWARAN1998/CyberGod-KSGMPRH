// SWAMI KARUPPASWAMI THUNNAI
package upx;

import java.io.File;
import java.io.FileNotFoundException;

public class Application
{
	String fileLocation = ""; // This variable holds the location of the file
        /**
         * @param fileLocation used to assign the location of the file
         */
	void getExeLocation(String fileLocation)
	{
		this.fileLocation = fileLocation;
	}
	
        /** 
         * @return  This method will return the size of the .EXE in MB
         * @throws FileNotFoundException 
         */
	long getSizeInMB() throws FileNotFoundException
	{
		File exe = new File(this.fileLocation);
		return exe.length() / 1000000;
	}
}
