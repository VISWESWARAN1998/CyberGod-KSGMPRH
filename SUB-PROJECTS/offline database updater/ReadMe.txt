This Python Script is used to add the MD5 hashes from the file present in your local directory to CyberGod KSGMPRH's database. Please run the file in the location where ksgmprh.db[DATABASE FILE] is present.

The updation process can be done in two methods:

[METHOD 1]:
If you confirm that the hashes present in the databases doesn't comprises of false positives then run the Python script with option "n". The hashes present in your text file will be added into the database.

[Method 2]:

If you are not sure that the hashes are not false positives, you need to run the file with the option "y". You need a virustotal API key to access it.

Get your api key by creating an account here https://www.virustotal.com/

you can also create a pull request for the hashes you have personally analysed. I will update it into the primary database making it available to all!

And also you need to place this file near the binary if it is not present :

https://github.com/VISWESWARAN1998/CyberGod-KSGMPRH/blob/master/DOS-ENGINE/process_hunter.py


Regards,
Visweswaran Nagasivam