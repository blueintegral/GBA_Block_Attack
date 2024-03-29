###################################################################
#	Make file for finalProject.						  
#																  
#	NOTE: Do not change this file unless otherwise instructed.    
#																  
###################################################################

DIR = c:/gba_studio
include $(DIR)/system/master.mak



 ####################
# GBA ROM Image Name #
 ####################

PROGNAME="finalProject"



 #########################################
# Set a list of files you want to compile #
 #########################################
 
OFILES += main.o lib.o PressEnter.o view.o narybst.o narytree.o nuclear_blast.o GameOver.o win.o StartScreen.o StartScreen4.o
 #########################################################
# Compile using Krawall (sound stuff, don't mess with it) #
 #########################################################
 
USE_KRAWALL=no
KRAWALL_IS_REGISTERED=no
KRAWALL_FILES=



 ######################################
# Standard Makefile targets start here #
 ######################################
all : $(PROGNAME).$(EXT) clean



 ##############################################
# Most Makefile targets are predefined for you,#
# such as vba, clean ... in the following file #
 ##############################################

include $(DIR)/system/standard-targets.mak



 #####################################
# Custom  Makefile targets start here #
 #####################################

gfx: makefile




