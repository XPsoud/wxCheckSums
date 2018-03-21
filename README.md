# About #

## wxCheckSums ##

wxCheckSums is a simple application for calculating checksums on files or simple text

## Features ##
#### Options : ####
 - Main window placement (known position or la registered position)
 - Multiple instances allowed or not
 - I18N or not (english)
 - Can be "portable" if a file named "settings.xml" (empty or not) is created/placed in the application's folder
 - Checksums can be displayed uppercase or lowercase
 - Checksums type can be disabled (application wide, saved with the settings)
#### Hash types : ####
 - MD5
 - SHA1
 - SHA224
 - SHA256
 - SHA384
 - SHA512

#### Mode : ####
##### 1 / 2 files #####
 - This page contains 2 identical panels on witch a file can be dropped from the file manager.
 - If 2 files have been checked, a message indicates if their checksums are identical or not
 - Each panel contains buttons for :
   - selecting a file using a dialog box (brows button
   - copy the displayed checksum to the clipboard
   - copy all calculated checksums to the clipboard
 - A "*filter panel*" is present on this tab to temporary override the enabled methods for the current session only (values not saved with the settings)

##### Multiple files #####
Not yet implemented

##### Simple text #####
Not yet implemented


## To-Do ##

#### Mode : ####
 - Multiple files : ability to calculate the checksums for more than 2 files at a time. Checksums should be able to be copied into the clipboard or saved into a text file
 - Simple text : just a multi-line text box with checksums calculation "on the fly". Options should be added for ends of lines mode.
#### Command line : ####
 - Files to check can be given using the command line. If 1 or 2 files, the first tab should be activated. If more than 2 files, the second tab will be the one visible.
#### Options : ####
 - Add an option to specify witch tab should be displayed at application startup
 - Add an option to automatically start (or not) checksums calculations when something is added to the _Multiple files_ tab
