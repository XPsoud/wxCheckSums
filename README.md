# About #

## wxCheckSums ##

wxCheckSums is a simple application for calculating checksums on files or simple text

## Features ##
#### Options : ####
 - Main window placement (known position or la registered position)
 - Multiple instances allowed or not
 - I18N or not (english)
 - Can be "portable" if a file named "settings.xml" (empty or not) is created/placed in the application's folder
#### Hash types : ####
 - MD5
#### Mode : ####
 - 1 or 2 files : files can be dropped from the system's files manager
 - if 2 files have been checked, a message indicates if their checksums are identical or not


## To-Do ##
#### Hash types : ####
 - SHA1
 - SHA224
 - SHA256
 - SHA384
 - SHA512
#### Mode : ####
 - Multiple files : ability to calculate the checksums for more than 2 files at a time. Checksums should be able to be copied into the clipboard or saved into a text file
 - Simple text : just a multi-line text box with checksums calculation "on the fly". Options should be added for ends of lines mode.
#### Command line : ####
 - Files to check will can be given using the command line. If 1 or 2 files, the first tab should be activated. If more than 2 files, the second tab will be the one visible.
#### Options : ####
 - Add an option to disable calculation for a type of hash
 - Add an option to specify if hashes must be displayed uppercase or lowercase
 - Add an options to specify witch tab should be displayed at application startup
