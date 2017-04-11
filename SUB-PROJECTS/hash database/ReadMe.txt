Malware hash database:
=======================

This is one of the important Malware hash database(not the only one, the antivirus utilizes some other databases too) which will be frequently updated. It currently has 320K hashes of known malware.

This is shipped as a database file (SQLite3) which is a serverless database, which can also be integrated into other applications.

Hashes are contributed by VirusShare: https://virusshare.com/


Note:
======

The database size is bigger and will be going to be much bigger! currently the size of the database is approximately 62 Mega Bytes which is larger than the recommended maximum size of github which is 50 MB. So I am planning to move the database to somewhere where it is easily made available to everyone.

The offline database updater is available now! so you can get the hashes from VirusShare and locally update the database if you want.

Regars,
Visweswaran Nagasivam