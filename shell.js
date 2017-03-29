/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

downloadCount=0;


function download()
{
    downloadCount++;
    document.getElementById("noOfDownloads").innerHTML= downloadCount;
    window.open("https://github.com/VISWESWARAN1998/CyberGod-KSGMPRH/releases/tag/1.0","_self");
}