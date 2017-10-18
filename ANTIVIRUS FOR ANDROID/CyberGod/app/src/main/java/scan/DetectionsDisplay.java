package scan;

/**
 * Created by Visweswaran on 17-10-2017.
 */

/**
 * @since 18-10-2017 This class is currently being used as an object for array adapter to display the identified threats
 */
public class DetectionsDisplay
{
    String fileName;
    String fileLoaction;
    String fileDescription;

    public DetectionsDisplay(String fileName, String fileDescription, String fileLoaction) {
        this.fileName = fileName;
        this.fileLoaction = fileLoaction;
        this.fileDescription = fileDescription;
    }

    // get the program name
    public String getFileName() {
        return fileName;
    }

    // get the location of the threat
    public String getFileLoaction() {
        return fileLoaction;
    }

    // actually find where the threat is located
    public String getFileDescription() {
        return fileDescription;
    }
}
