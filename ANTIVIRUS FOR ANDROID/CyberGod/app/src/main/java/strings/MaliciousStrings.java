/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package strings;

import java.util.HashMap;

/**
 *
 * @author visweswaran
 */
public class MaliciousStrings {
    public static HashMap<String, String> maliciousStrings;
    
    static
    {
        // all strings are reversed to avoid false positive
        maliciousStrings = new HashMap<>();
        maliciousStrings.put("tiolpsatem.moc", "Metasploit Payload");
        maliciousStrings.put("raj.daolyap", "Metasploit Payload");
        maliciousStrings.put("xed.daolyap", "Metasploit Payload");
    }
}
