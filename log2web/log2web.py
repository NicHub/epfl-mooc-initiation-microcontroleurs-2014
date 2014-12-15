#!/usr/bin/python
# -*- coding: utf-8 -*-

#------------------------------------------------------------------------------
#
# ENVOIE SUR INTERNET LES DERNIÈRES LIGNES DU FICHIER DE LOG PAR REQUÊTE POST
#
# EMPLOI
# 1. S’assurer que le fichier est exécutable (chmod a+x log2web.py)
# 2. Mettre le path correct vers le fichier log (variable “cmd” dans le main)
# 3. Modifier le nombre de lignes envoyées (variable “cmd” dans le main)
# 4. Exécuter le script dans un cron (crontab -e)
# */1 * * * * /Users/nico/Documents/programmation/epfl-mooc-initiation-microcontroleurs-2014/log2web/log2web.py >> /tmp/log2web.log
#
# Le log est visible à
# http://notepadxx.com/mooc-microcontroleurs/mooc-log.csv
#
# 5. Si le log est envoyé sur un autre serveur, modifier la variable “postURL” dans le main.
#
#------------------------------------------------------------------------------



import urllib2, urllib, subprocess, sys, socket
from urllib2 import urlopen
import os.path
from os import system







def sendPost( postURL, logFileContent ):

	postData = [ ( 'moocLogData', logFileContent ) ]
	postData = urllib.urlencode( postData )
	req = urllib2.Request( postURL, postData )
	req.add_header( "Content-type", "application/x-www-form-urlencoded" )
	page = urllib2.urlopen( req ).read()




def main():

	cmd = "tail -n10     /Users/nico/Documents/programmation/epfl-mooc-initiation-microcontroleurs-2014/log2web/log-file-2014-12-02.csv"
	postURL = 'http://notepadxx.com/mooc-microcontroleurs/logger.php'

	logFileContent = "".join( os.popen( cmd ).readlines() )
	print logFileContent

	sendPost( postURL, logFileContent )





if __name__ == '__main__':

	main()

