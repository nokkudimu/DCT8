#!/bin/bash
cd /home/nokkudimu/repos/tekken8_data_collector/vzlom/ && gcc -DCOMMAND=\""pidof -s tekken8 \"" checkProcess.c -o checkingProcess && sudo ./checkingProcess