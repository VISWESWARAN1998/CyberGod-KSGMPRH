# SWAMI KARUPPASWAMI THUNNAI

import sqlite3
import re
import json
from process_hunter import VirusTotal

class Update:
    """
    This class is used to for offline updating of md5 hashes which is to be supplied
    as a text file.
    This class doesn't have the facility to create your own tables. I only updates to the existing
    database provided by CyberGod KSGMPRH
    """
    __contents = ""
    def __init__(self,file):
        database_contents = open(file,"r")
        self.__contents = database_contents.readlines()
        database_contents.close()

    # This method is used to update the md5 hashes from the local text file
    # please use this method only if you are sure that the provided hashes are not
    # false positives and are real malware
    def add_no_false_positive(self):
        connect = sqlite3.connect("ksgmprh.db")
        print("connected to the database...")
        print("creating the cursor please wait...")
        cur = connect.cursor()
        print("created the cursor ")
        count = 0
        total = len(self.__contents)
        for i in self.__contents:
            md5 = re.sub("\n","",i)
            v = md5 # we will assume v as value for querying in database
            if len(v) == 32:
                value = ""
                if v[0] == '0':
                    value = "zero"
                elif v[0] == '1':
                    value = "one"
                elif v[0] == '2':
                    value = "two"
                elif v[0] == '3':
                    value = "three"
                elif v[0] == '4':
                    value = "four"
                elif v[0] == '5':
                    value = "five"
                elif v[0] == '6':
                    value = "six"
                elif v[0] == '7':
                    value = "seven"
                elif v[0] == '8':
                    value = "eight"
                elif v[0] == '9':
                    value = "nine"
                else:
                    value = v[0]
                try:
                    cur.execute('''INSERT INTO ''' + value + '''(hash,variant) VALUES(?,?)''', (v, "Identified threat"))
                    print("committing...")
                    connect.commit()
                except Exception as e:
                    print(e)
                    file = open("except", "a")
                    file.write(v + "\n")
                    file.close()
                count += 1
                sub = count / total
                percentile = sub * 100
                print("Completed : " + str(percentile) + "%")
    # Note that this method will add only 1 entry for 20 seconds
    # since we are using Virus Total's Public API
    def add_check_false_positive(self):
        connect = sqlite3.connect("ksgmprh.db")
        print("connected to the database...")
        print("creating the cursor please wait...")
        cur = connect.cursor()
        print("created the cursor ")
        count = 0
        total = len(self.__contents)
        for i in self.__contents:
            md5 = re.sub("\n", "", i)
            v = md5  # we will assume v as value for querying in database
            if len(v) == 32:
                process = False
                check = VirusTotal(v)
                if self.can_add(v+".json") is True:
                    print("The hash can be added")
                    process = True
                else:
                    print("It may be a false positive are you sure to add? [y/n]")
                    get = input()
                    if get.lower()=="y":
                        process = True
                if process is True:
                    value = ""
                    if v[0] == '0':
                        value = "zero"
                    elif v[0] == '1':
                        value = "one"
                    elif v[0] == '2':
                        value = "two"
                    elif v[0] == '3':
                        value = "three"
                    elif v[0] == '4':
                        value = "four"
                    elif v[0] == '5':
                        value = "five"
                    elif v[0] == '6':
                        value = "six"
                    elif v[0] == '7':
                        value = "seven"
                    elif v[0] == '8':
                        value = "eight"
                    elif v[0] == '9':
                        value = "nine"
                    else:
                        value = v[0]
                    try:
                        cur.execute('''INSERT INTO ''' + value + '''(hash,variant) VALUES(?,?)''',
                                    (v, "Identified threat"))
                        print("committing...")
                        connect.commit()
                    except Exception as e:
                        print(e)
                        file = open("except", "a")
                        file.write(v + "\n")
                        file.close()
                    count += 1
                    sub = count / total
                    percentile = sub * 100
                    print("Completed : " + str(percentile) + "%")

    def can_add(self,file_location):
        count = 0
        try:
            with open(file_location,"r") as file:
                data = json.load(file)
                value = data["scans"]
                print(type(value))
                for i in value.values():
                    if i["detected"] == True:
                        count+=1
            file.close() # close the opened file
        except KeyError:
            print("The hash is not present in VirusTotal Database! see the json file for more information about this error")
            var = input("[STOPPED]")
            return False
        if count>30:
            return True
        else:
            return False





if __name__=="__main__":
    location = input("LOCATION OF THE INPUT FILE: ")
    update = Update(location)
    check = input("Are you sure that the hashes present in the files are not false positives?\nDo you want a secondary check? [y/n] ")
    if check.lower() == "y":
        update.add_check_false_positive()
    else:
        update.add_no_false_positive()
