# SWAMI KARUPPASWAMI THUNNAI


import urllib.parse
import urllib.request
import time

"""
Global declarations
"""

class VirusTotal:
    __apiKey = "ADD YOUR API KEY HERE"
    __url = 'https://www.virustotal.com/vtapi/v2/file/report'
    __result = ''
    __md5 = ''
    def __init__(self,md5):
        print('initializing....')
        params = {'apikey': self.__apiKey,
                  'resource': md5}
        print('accessing virus total database.....')
        parameters = urllib.parse.urlencode(params)
        req = urllib.request.Request(self.__url, parameters.encode('utf-8'))
        response = urllib.request.urlopen(req)
        the_page = response.read()
        self.__result = the_page.decode('utf-8')
        self.__md5 = md5
        self.create_json()
        print('result stored as '+md5+".json")
        print("waiting for another process...")
        time.sleep(20) # Must sleep for 20 seconds
    def create_json(self):
        file = open(self.__md5+'.json',"w")
        file.write(self.__result)
        file.close()







